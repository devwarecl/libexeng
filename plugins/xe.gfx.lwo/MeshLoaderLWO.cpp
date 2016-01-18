
#include "MeshLoaderLWO.hpp"

#include <cassert>
#include <vector>
#include <boost/filesystem/path.hpp>
#include <xe/gfx/Vertex.hpp>

#include "lwo/lwo2.h"

#include "Object.hpp"
#include "Array.hpp"
#include "List.hpp"

namespace xe { namespace gfx {
	namespace fs = boost::filesystem;

	MeshLoaderLWO::MeshLoaderLWO() {}
	
	MeshLoaderLWO::~MeshLoaderLWO() {}

	bool MeshLoaderLWO::isSupported(const std::string &filename) {
		std::string ext = fs::path(filename).extension().string();
		return ext == ".lwo";
	}

	//typedef std::vector<xe::gfx::StandardVertex> VertexArray;

	//float cylindricalAngle(const xe::Vector2f &point) {
	//	const float pi		= xe::Pi<float>::Value;
	//	const float pi_2	= xe::PiHalf<float>::Value;
	//	const float r		= xe::abs(point);
	//	const float x		= point.x / r;
	//	const float y		= point.y;

	//	if (r == 0.0f)  {
	//		return 0.0f;
	//	}

	//	float a = 0.0f;

	//	if (x < 0.0f && y >= 0.0f) {
	//		a = pi_2 - acosf(-x);

	//	} else if (x < 0.0f && y < 0.0f) {
	//		a = acosf(-x) + pi_2;

	//	} else if (x >= 0.0f && y >= 0.0f) {
	//		a = acosf(x) + 3.0f * pi_2;

	//	} else if (x >= 0.0f && y < 0.0f) {
	//		a = 3.0f * pi_2 - acosf(x);

	//	} else {
	//		a = 0.0f;
	//	}

	//	return a/pi/2.0f;
	//}

	//xe::Vector2f generateTexCoord_Spherical(float radius, const xe::Vector3f &point, lw::Axis::Enum axis) {
	//	const float pi		= xe::Pi<float>::Value;
	//	const float pi_2	= xe::PiHalf<float>::Value;

	//	xe::Vector2f texCoord = {0.0f, 0.0f};

	//	switch (axis) {
	//	case lw::Axis::X: 
	//		texCoord.x = cylindricalAngle({-point.z, -point.y}); 
	//		texCoord.y = (std::asin(point.x/radius) + pi_2) / pi;

	//		break;

	//	case lw::Axis::Y: 
	//		texCoord.x = cylindricalAngle({point.x, point.z}); 
	//		texCoord.y = (std::asin(point.y/radius) + pi_2) / pi;

	//		break;

	//	case lw::Axis::Z: 
	//		texCoord.x = cylindricalAngle({point.x, -point.y}); 
	//		texCoord.y = (std::asin(point.z/radius) + pi_2) / pi;
	//		break;
	//	}

	//	return texCoord;
	//}

	//xe::Vector2f generateTexCoord_Cylindrical(float radius, const xe::Vector3f &point, lw::Axis::Enum axis) {
	//	xe::Vector2f texCoord = {0.0f, 0.0f};

	//	switch (axis) {
	//		case lw::Axis::X: 
	//			texCoord.x = cylindricalAngle({-point.z, -point.y});
	//			texCoord.y = point.x;
	//			break;

	//		case lw::Axis::Y: 
	//			texCoord.x = cylindricalAngle({point.x,  point.z});
	//			texCoord.y = point.y;
	//			break;

	//		case lw::Axis::Z: 
	//			texCoord.x = cylindricalAngle({point.x, -point.y});
	//			texCoord.y = point.z;
	//			break;
	//	}

	//	return texCoord;
	//}

	//xe::Vector2f generateTexCoord_Planar(float radius, const xe::Vector3f &point, lw::Axis::Enum axis) {
	//	xe::Vector2f texCoord = {0.0f, 0.0f};

	//	switch (axis) {
	//		case lw::Axis::X:
	//			texCoord.x = point.z;
	//			texCoord.y = point.y;
	//			break;

	//		case lw::Axis::Y: 
	//			texCoord.x = point.x;
	//			texCoord.y = point.z;
	//			break;

	//		case lw::Axis::Z: 
	//			texCoord.x = point.x;
	//			texCoord.y = point.y;
	//			break;
	//	}

	//	return texCoord;
	//}

	//xe::Vector2f generateTexCoord_Default(float radius, const xe::Vector3f &point, lw::Axis::Enum axis) {
	//	return {0.0f, 0.0f};
	//}

	//xe::Vector2f generateTexCoord_Cubic() {
	//	xe::Vector2f texCoord;

	//	return texCoord;
	//}

	//VertexArray generateVertices_UV(const lw::Layer &layer, lw::Polygon &polygon, const lw::PointList points, const lw::ImageMap &imap) {
	//	VertexArray vertices;

	//	lw::VMap map = layer.findVMap(imap.vmap_name(), true);

	//	for (int j=0; j<polygon.nverts(); ++j) {
	//		bool discontinuous = false;

	//		const int pointIndex = polygon.v(j).index();
	//		float *texCoordData = nullptr;

	//		// search for discontinous mapping
	//		for (int k=0; k<polygon.v(j).nvmaps(); ++k) {
	//			const lw::VMapPt vmap_pt = polygon.v(j).vm(k);
	//			const lw::VMap vmap = vmap_pt.vmap();
	//			
	//			if (vmap.dim()==2 && vmap.type()==ID_TXUV) {
	//				texCoordData = vmap.val(vmap_pt.index());
	//				discontinuous = true;
	//				break;
	//			}
	//		}

	//		// check for continuous mapping
	//		if (discontinuous == false) {

	//			// search for discontinous mapping
	//			for (int k=0; k<points.pt(pointIndex).nvmaps(); ++k) {
	//				lw::VMapPt vmap_pt = points.pt(pointIndex).vm(k);

	//				if (vmap_pt.vmap().dim()==2 && vmap_pt.vmap().type()==ID_TXUV) {
	//					texCoordData = vmap_pt.vmap().val(vmap_pt.index());
	//					break;
	//				}
	//			}
	//		}

	//		if (!texCoordData) {
	//			texCoordData[1] = 1.0f - texCoordData[1];
	//		}

	//		xe::gfx::StandardVertex vertex;
	//		vertex.coord = Vector3f(points.pt(pointIndex).pos());
	//		vertex.normal = polygon.norm();
	//		vertex.texCoord = Vector2f(texCoordData[0], 1.0f - texCoordData[1]);

	//		vertices.push_back(vertex);	
	//	}

	//	return vertices;
	//}

	//VertexArray generateVerticesFromPolygon(const ::lwPolygon *polygon, const ::lwPointList *points, const ::lwTexture *texture) {
	//	VertexArray vertices;

	//	return vertices;
	//}

	//VertexArray generateVertices(const lw::Layer &layer, const lw::Surface &surface) {
	//	VertexArray vertices;

	//	const lw::PolygonList polygons = layer.polygon();
	//	const lw::PointList points = layer.points();

	//	for (const lw::Polygon polygon : polygons) {

	//	}


	//	for (int i=0; i<polygons.count(); i++) {
	//		const lw::Polygon polygon = polygons.pol(i);

	//		if (polygon.type()==ID_FACE || polygon.surf()!=surface) {
	//			continue;
	//		}

	//		const lw::Texture texture = surface.color().tex();
	//		
	//		if (texture.type()==ID_IMAP) {
	//			// subset with texture

	//			const lw::ImageMap imap = texture.imap();

	//			switch (imap.projection()) {
	//				case lw::Proj::Planar: break;
	//				case lw::Proj::Cylindrical: break;
	//				case lw::Proj::Spherical: break;
	//				case lw::Proj::Cubic: break;
	//				case lw::Proj::Front: break;
	//				case lw::Proj::Map: break;
	//				
	//				default: break;
	//			}

	//		} else {
	//			// subset without texture

	//		}
	//	}

	//	return vertices;
	//}

	

	MeshPtr MeshLoaderLWO::load(const std::string &filename) {
		char *file = const_cast<char*>(filename.c_str());
		lw::Object object(::lwGetObject(file , nullptr, nullptr));
		lw::List<::lwLayer> layers (object.getHandle()->layer);

		for (const auto& layer : layers) {
			
		}

		return MeshPtr();
	}
}}
