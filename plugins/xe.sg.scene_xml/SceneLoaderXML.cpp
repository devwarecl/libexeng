
#include <list>
#include <xe/sys/Plugin.hpp>
#include <xe/sg/SceneLoader.hpp>

#include "xmlpp/Document.hpp"

namespace xml {
	struct ShaderLibrary {
		struct Shader {
			std::string name;
			std::string type;
			std::string file;
		};

		struct Module {
			std::string ref_name;
		};

		struct Progam {
			std::string name;
			std::vector<Module> modules;
		};

		std::string language;
		std::vector<Shader> shaders;
		std::vector<Progam> programs;
	};

	struct MaterialLibrary {
		struct Format {
			struct Attribute {
				std::string name;
				std::string type;
			};

			std::vector<Attribute> attributes;
		} format;

		struct Material {
			struct Program {
				std::string ref_name;
			} program;

			struct Layer {
				struct Texture {
					std::string name;
					std::string source;
					std::string file;

					struct Generator {
						std::string type;
						std::string size;
						std::string grid;
					} generator;

				} texture;
			};

			struct Attribute {
				std::string ref_name;
				std::string value;
			};

			std::vector<Layer> layers;
			std::vector<Attribute> attributes;
		};

		std::vector<Material> materials;
	};

	struct GeometryLibrary {
		struct VertexFormat {
			struct Attribute {
				std::string name;
				std::string type;
				std::string use;
			};

			std::vector<Attribute> attributes;
		};

		struct Geometry {
			struct Mesh {
				struct MeshSubset {
					struct Generator {
						std::string type;
						std::string size;
						std::string center;
					} generator;

					struct Material {
						std::string ref_name;
					} material;
				};

				std::string source;
				std::string filename;
				std::vector<MeshSubset> subsets;
			};

			std::string name;
			std::string type;
			Mesh mesh;
		};

		VertexFormat vertexFormat;
		std::vector<Geometry> geometries;
	};

	struct Scene {

		struct Background {
			struct Color {
				std::string value;
			};
		};

		struct CameraCollection {

			struct Camera {
				struct View {
					struct LookAt {
						std::string position;
						std::string look_at;
						std::string up;
					};

					LookAt lookAt;
				};

				struct Projection {
					struct Perspective {
						std::string fov;
						std::string aspect;
						std::string z_near;
						std::string z_far;
					};

					Perspective perspective;
				};

				struct Viewport {
					std::string position;
					std::string size;
				};

				std::string name;
				View view;
				Projection projection;
				Viewport viewport;
			};

			Camera cameras;
		};

		struct Node {

			struct Transformation {

			};

			struct Data {
				std::string type;
				std::string ref_name;
			};

			Transformation transformation;
			std::string name;
			Data data;
			std::vector<Node> childs;
		};

	};
}

namespace xe { namespace sg {
	class SceneLoaderXML : public SceneLoader {
	public:
		virtual ~SceneLoaderXML() {}

		virtual bool isSupported(const std::string &file) {
			return true;
		}

		virtual ScenePtr load(const std::string &file) {
			return nullptr;
		}

	private:

	};
}}
