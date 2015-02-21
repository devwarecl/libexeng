
#include "LwoMeshLoader.hpp"

namespace raytracer { namespace loaders {

	using namespace exeng;
	using namespace exeng::graphics;
	using namespace exeng::scenegraph;



class LwoMeshLoader : public exeng::scenegraph::IMeshLoader {
	private:
		/**
		 * @brief Texture projection
		 */
		enum lwProj {
			LW_PROJ_PLANAR = 0,
			LW_PROJ_CYLINDRICAL = 1,
			LW_PROJ_SPHERICAL = 2,
			LW_PROJ_CUBIC = 3,
			LW_PROJ_FRONT = 4,
			LW_PROJ_UV = 5
		};

		enum lwAxis {
			LW_AXIS_X = 0,
			LW_AXIS_Y = 1,
			LW_AXIS_Z = 2
		};

		typedef std::function<
			void(std::vector<exeng::graphics::Vertex> &vertices, lwLayer *layer, lwPointList *pointList , lwPolygon *polygon, lwImageMap *imageMap, lwTMap *tmap)
		> ProjVertexGeneratorFunction;


	public:
		LwoMeshLoader() 
		{
			// to make VC 2013 happy
			std::map<lwProj, ProjVertexGeneratorFunction> generators = {
				{LW_PROJ_UV, ProjVertexGeneratorFunction(generateVertices_ProjUV)}, 
				{LW_PROJ_CUBIC, ProjVertexGeneratorFunction(generateVertices_ProjCubic)}, 
				{LW_PROJ_SPHERICAL, ProjVertexGeneratorFunction(generateVertices_Proj<SphericalTexCoordGenerator>)},
				{LW_PROJ_CYLINDRICAL, ProjVertexGeneratorFunction(generateVertices_Proj<CylindricalTexCoordGenerator>)},
				{LW_PROJ_PLANAR, ProjVertexGeneratorFunction(generateVertices_Proj<PlanarTexCoordGenerator>)}
			};

			this->generators = generators;
		}

		virtual bool isSupported(const std::string &filename) override 
		{
			std::string ext = boost::filesystem::path(filename).extension().string();

			return ext == ".lwo";
        }

		virtual std::unique_ptr<Mesh> loadMesh(const std::string &filename, GraphicsDriver *graphicsDriver) override 
		{
			struct lwObjectGuard {
				lwObject *obj = nullptr;

				explicit lwObjectGuard(lwObject *obj_) : obj(obj_){}

				lwObject* operator->() { return this->obj; }
				const lwObject* operator->() const { return this->obj;}

				~lwObjectGuard() {
					if (obj) {
						lwFreeObject(obj);
					}
				}
			};

			std::vector<std::unique_ptr<MeshSubset>> meshSubsets;

			lwObjectGuard obj = lwObjectGuard(lwGetObject( (char*)filename.c_str(), nullptr, nullptr));
			for (lwSurface *surf=obj->surf; surf!=nullptr; surf=surf->next) {
				for (lwLayer *layer=obj->layer; layer!=nullptr; layer=layer->next) {
					auto meshSubset = this->createMeshSubsetFromLWOData(graphicsDriver, layer, surf);
					meshSubsets.push_back( std::move(meshSubset) );
				}
			}

            return std::unique_ptr<Mesh>( new Mesh(std::move(meshSubsets)) );
        }

	private:
		std::map<lwProj, ProjVertexGeneratorFunction> generators;

		/**
		 * @brief Automatically generate the index array from the specified polygon size
		 */
		static void appendIndices(std::vector<int> &indices, int polygonSize, int indexBase, bool invert) 
		{
			if (invert) {
				for(int j=1; j<polygonSize-1; j++) {
					indices.push_back(indexBase + 0);
					indices.push_back(indexBase + j);
					indices.push_back(indexBase + j + 1);
				}
			} else {
				for(int j=1; j<polygonSize-1; j++) {
					indices.push_back(indexBase + 0);
					indices.push_back(indexBase + j + 1);
					indices.push_back(indexBase + j);
				}
			}
		}

		/**
		 * @brief Search a clip with the specified index (id)
		 */
		static lwClip* findClipFromIndex(lwObject* Object, int index)
		{
			//Recorrer los clips hasta dar con el que tenga el índice indicado
			lwClip *outClip = nullptr;
			for (outClip=Object->clip; outClip!=nullptr; outClip=outClip->next) {
				if (outClip->index == index) {
					break;
				}
			}

			return outClip;
		}

		/**
		 * @brief Pending.
		 */
		static Vector3f setupTexturePoint(const Vector3f &point, lwTMap *tmap, lwProj proj)
		{
			Vector3f center = Vector3f(tmap->center.val); 
			Vector3f ypr = Vector3f(tmap->rotate.val); 
			Vector3f size = Vector3f(tmap->size.val); 

			Vector3f q = point - center;

			q = exeng::transform(exeng::rotate<float>(ypr.z, { 0.0f, 0.0f, -1.0f}), q);
			q = exeng::transform(exeng::rotate<float>(ypr.y, { 0.0f, 1.0f,  0.0f}), q);
			q = exeng::transform(exeng::rotate<float>(ypr.x, {-1.0f, 0.0f,  0.0f}), q);

			if (proj != LW_PROJ_SPHERICAL) {
				q = q / size;
			}

			return q;
		}

		static Vector3f computePolygonNormal(const lwPolygon *poly, const lwPointList *points, bool invertNormal)
		{
			Vector3f normal = {0.0f, 0.0f, 0.0f};

			if (poly->nverts >= 3) {
				Vector3f a = Vector3f(points->pt[ poly->v[0].index ].pos);
				Vector3f b = Vector3f(points->pt[ poly->v[1].index ].pos);
				Vector3f c = Vector3f(points->pt[ poly->v[2].index ].pos);

				normal = exeng::normalize(exeng::cross(b-a, c-a));

				if (invertNormal) {
					normal = -normal;
				}
			}

			return normal;
		}

		static float cylindricalAngle(float x, float y)
		{
			float r = std::sqrt(x*x + y*y);
			float a = 0.0f;

			if (r == 0.0f)  {
				return 0.0f;
			}

			x /= r;

			if (x < 0.0f && y >= 0.0f) {
				a = pi_2 - acosf(-x);
			} else if (x < 0.0f && y < 0.0f) {
				a = acosf(-x) + pi_2;
			} else if (x >= 0.0f && y >= 0.0f) {
				a = acosf(x) + 3.0f * pi_2;
			} else if (x >= 0.0f && y < 0.0f) {
				a = 3.0f * pi_2 - acosf(x);
			} else {
				a = 0.0f;
			}

			return a/pi/2.0f;
		}

		static lwVMap* findVMap(lwVMap* Map, const std::string &vmapname, unsigned int type)
		{
			lwVMap* VMap = nullptr;

			for(VMap=Map; VMap!=nullptr; VMap=VMap->next) {
				if ((vmapname == VMap->name) && (type == VMap->type)){
					break;
				}
			}

			if ((VMap != nullptr) && (type == ID_TXUV)) {
				lwVMap* BetterVMap = findVMap(VMap->next, vmapname, ID_TXUV);

				if (BetterVMap != nullptr) {
					VMap = BetterVMap;
				}
			}

			return VMap;
		}

		static lwVMap* getVMap(lwLayer* Layer, char* Name, bool Continuous)
		{
			lwVMap* VMap = nullptr;

			for(VMap=Layer->vmap; VMap!=nullptr; VMap=VMap->next) {
				if (std::string(Name) == std::string(VMap->name)) {
					if (Continuous==true) {
						if (VMap->pindex==nullptr) {
							return VMap;
						}
					} else {
						if (VMap->pindex!=nullptr) {
							return VMap;
						}
					}
				}
			}

			return nullptr;
		}
		
		static void generateVertices_ProjUV (std::vector<Vertex> &vertices, lwLayer *layer, lwPointList *pointList , lwPolygon *polygon, lwImageMap *imageMap, lwTMap *tmap)
		{
			lwVMap *vmap = LwoMeshLoader::getVMap(layer, imageMap->vmap_name, true);

			for (int j=0; j<polygon->nverts; ++j) {
				bool discontinuous = false;

				const int pointIndex = polygon->v[j].index;
				float *texCoordData = nullptr;

				// search for discontinous mapping
				for (int k=0; k<polygon->v[j].nvmaps; ++k) {
					lwVMapPt *vmapPt = &polygon->v[j].vm[k];

					if (vmapPt->vmap->dim==2 && vmapPt->vmap->type==ID_TXUV) {
						texCoordData = vmapPt->vmap->val[vmapPt->index];
						discontinuous = true;
						break;
					}
				}

				// check for continuous mapping
				if (discontinuous == false) {
					// search for discontinous mapping
					for (int k=0; k<pointList->pt[pointIndex].nvmaps; ++k) {
						lwVMapPt *vmapPt = &pointList->pt[pointIndex].vm[k];

						if (vmapPt->vmap->dim==2 && vmapPt->vmap->type==ID_TXUV) {
							texCoordData = vmapPt->vmap->val[vmapPt->index];
							break;
						}
					}
				}

				Vertex vertex = {
					Vector3f(pointList->pt[pointIndex].pos),
					Vector3f(polygon->norm),
					Vector2f(texCoordData[0], 1.0f - texCoordData[1])
				};

				vertices.push_back(vertex);
			}
		}

		static void generateVertices_ProjCubic(std::vector<Vertex> &vertices, lwLayer *layer, lwPointList *pointList , lwPolygon *polygon, lwImageMap *imageMap, lwTMap *tmap)
		{
			Vector3f normal = LwoMeshLoader::computePolygonNormal(polygon, pointList, false);

			lwAxis axis = LW_AXIS_X;

			if ( normal.y>normal.x &&  normal.y>normal.z)	axis = LW_AXIS_Y;
			if (-normal.y>normal.x && -normal.y>normal.z)	axis = LW_AXIS_Y;

			if ( normal.z>normal.x &&  normal.z>normal.y)	axis = LW_AXIS_Z;
			if (-normal.z>normal.x && -normal.z>normal.y)	axis = LW_AXIS_Z;

			for (int j=0; j<polygon->nverts; ++j) {
				const int pointIndex = polygon->v[j].index;

				Vector3f coord = Vector3f(pointList->pt[pointIndex].pos);
				Vector3f point = LwoMeshLoader::setupTexturePoint(coord, tmap, lwProj(imageMap->projection));
				Vector2f texCoord;

				switch (axis) {
					case LW_AXIS_X: texCoord = Vector2f(point.z, point.y); break;
					case LW_AXIS_Y: texCoord = Vector2f(point.x, point.z); break;
					case LW_AXIS_Z: texCoord = Vector2f(point.x, point.y); break;
				}

				texCoord += Vector2f(0.5f, 0.5f);
				texCoord.y = 1.0f - texCoord.y;

				Vertex vertex = {coord, normal, texCoord};

				vertices.push_back(vertex);
			}
		}

		template<typename TexCoordGeneratorFunctor>
		static void generateVertices_Proj(std::vector<Vertex> &vertices, lwLayer *layer, lwPointList *pointList , lwPolygon *polygon, lwImageMap *imageMap, lwTMap *tmap)
		{
			TexCoordGeneratorFunctor texCoordGenerator;

			for (int j=0; j<polygon->nverts; ++j) {
				const int pointIndex = polygon->v[j].index;

				Vector3f coord = Vector3f(pointList->pt[pointIndex].pos);
				Vector3f normal = Vector3f(polygon->norm);
				Vector2f texCoord = Vector2f(0.0f, 0.0f);

				Vector3f point = LwoMeshLoader::setupTexturePoint(coord, tmap, lwProj(imageMap->projection));

				float r = exeng::abs(point);

				if (r != 0.0f) {
					texCoord = texCoordGenerator(r, point, lwAxis(imageMap->axis));
				}

				texCoord *= Vector2f(imageMap->wrapw.val, imageMap->wraph.val);
				texCoord.y = 1.0f - texCoord.y;

				Vertex vertex = {coord, normal, texCoord};
				vertices.push_back(vertex);
			}
		}

		struct SphericalTexCoordGenerator {
			Vector2f operator() (float r, const Vector3f &point, lwAxis axis) 
			{
				float tx=0.0f, ty=0.0f;

				switch (axis) {
				case LW_AXIS_X: 
					tx = cylindricalAngle(-point.z, -point.y); 
					ty = (std::asin(point.x/r) + pi_2) / pi;
					break;

				case LW_AXIS_Y: 
					tx = cylindricalAngle(point.x, point.z); 
					ty = (std::asin(point.y/r) + pi_2) / pi;
					break;

				case LW_AXIS_Z: 
					tx = cylindricalAngle(point.x, -point.y); 
					ty = (std::asin(point.z/r) + pi_2) / pi;
					break;
				}

				return Vector2f(tx, ty);
			}
		};

		struct CylindricalTexCoordGenerator {
			Vector2f operator() (float r, const Vector3f &point, lwAxis axis) 
			{
				switch (axis) {
				case LW_AXIS_X: 
					return Vector2f(cylindricalAngle(-point.z, -point.y), point.x);
					
				case LW_AXIS_Y: 
					return Vector2f(cylindricalAngle(point.x, point.z), point.y);
					
				case LW_AXIS_Z: 
					return Vector2f(cylindricalAngle(point.x, -point.y), point.z);
				}

				return Vector2f(0.0f, 0.0f);
			}
		};

		struct PlanarTexCoordGenerator {
			Vector2f operator() (float r, const Vector3f &point, lwAxis axis) 
			{
				switch (axis) {
				case LW_AXIS_X: return Vector2f(point.z, point.y);
				case LW_AXIS_Y: return Vector2f(point.x, point.z);
				case LW_AXIS_Z: return Vector2f(point.x, point.y);
				}

				return Vector2f(0.0f, 0.0f);
			}
		};

		static void generateVertices_ProjDefault(std::vector<Vertex> &vertices, lwLayer *layer, lwPointList *pointList , lwPolygon *polygon, lwImageMap *imageMap, lwTMap *tmap)
		{
			for(int j=0; j<polygon->nverts; j++)
			{
				Vector3f pivot = Vector3f(layer->pivot);

				const int pointIndex = polygon->v[j].index;
				Vector3f coord = Vector3f(pointList->pt[pointIndex].pos);
				Vector3f normal = Vector3f(polygon->norm);
				Vector2f texCoord = {0.0f, 0.0f};

				vertices.push_back(Vertex{coord + pivot, normal, texCoord});
			}
		}

		static void generateVertices_Default(std::vector<Vertex> &vertices, lwLayer *layer, lwPointList *pointList , lwPolygon *polygon, lwImageMap *imageMap, lwTMap *tmap)
		{
			for(int j=0; j<polygon->nverts; j++)
			{
				const int pointIndex = polygon->v[j].index;
				Vector3f coord = Vector3f(pointList->pt[pointIndex].pos);
				Vector3f normal = Vector3f(polygon->norm);
				Vector2f texCoord = {0.0f, 0.0f};

				vertices.push_back(Vertex{coord, normal, texCoord});
			}
		}

		std::unique_ptr<MeshSubset> createMeshSubsetFromLWOData(GraphicsDriver *graphicsDriver, lwLayer *layer, lwSurface *surf)
		{
			std::vector<Vertex> vertices;
			std::vector<int> indices;

			lwPolygonList *polygonList = &layer->polygon;
			lwPointList *pointList = &layer->point;

			for (int i=0; i<polygonList->count; ++i) {
				int baseIndex = vertices.size();

				lwPolygon *polygon = &polygonList->pol[i];

				if (polygon->type != ID_FACE) {
					continue;
				}

				if (surf != polygon->surf) {
					continue;
				}

				if (surf->color.tex && surf->color.tex->type==ID_IMAP) {
					lwImageMap *imageMap = &surf->color.tex->param.imap;
					lwTMap *tmap = &surf->color.tex->tmap;

					ProjVertexGeneratorFunction generator;

					// Get the appropiate generator
					auto generatorIt = this->generators.find(lwProj(imageMap->projection));
					if (generatorIt != std::end(this->generators)) {
						generator = generatorIt->second;
					} else {
 						generator = generateVertices_ProjDefault;
					}
					
					generator(vertices, layer, pointList, polygon, imageMap, tmap);
				} else {
					ProjVertexGeneratorFunction generator = generateVertices_Default;
					generator(vertices, layer, pointList, polygon, nullptr, nullptr);
				}

				appendIndices(indices, polygon->nverts, baseIndex, false);

				// ¿The material is two-sided?
				if (surf->sideflags == 3) {
					const int begin = vertices.size()-polygon->nverts;
					const int end = baseIndex;

					for (int vertexIndex=begin; vertexIndex<end; vertexIndex++) {
						Vertex vertex = { 
							vertices[vertexIndex].coord,
							-vertices[vertexIndex].normal,
							vertices[vertexIndex].texCoord,
						};

						vertices.push_back(vertex);
					}

					appendIndices(indices, polygon->nverts, baseIndex, true);
				}
			}

			auto vertexBuffer = graphicsDriver->createVertexBuffer(vertices);
			auto indexBuffer = graphicsDriver->createIndexBuffer(indices);
			auto meshSubset = graphicsDriver->createMeshSubset(std::move(vertexBuffer), std::move(indexBuffer), VertexFormat::makeVertex());

			return meshSubset;
		}
	};

}}