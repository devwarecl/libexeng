//
//#ifndef __RAYTRACER_SCENELOADER_HPP__
//#define __RAYTRACER_SCENELOADER_HPP__
//
//#include <memory>
//#include <exeng/Vector.hpp>
//#include <exeng/scenegraph/Scene.hpp>
//#include <exeng/graphics/GraphicsDriver.hpp>
//#include <exeng/scenegraph/MeshManager.hpp>
//
//namespace raytracer {
//    class SceneLoader {
//    public:
//        SceneLoader(const SceneLoader &) = delete;
//        SceneLoader& operator=(const SceneLoader &) = delete;
//
//    public:
//        explicit SceneLoader(exeng::graphics::GraphicsDriver *driver, exeng::scenegraph::MeshManager *meshManager);
//        virtual ~SceneLoader();
//
//        std::unique_ptr<exeng::scenegraph::Scene> loadScene(const std::string &filename, const exeng::graphics::MaterialFormat *materialFormat);
//
//	private:
//		exeng::scenegraph::SceneNode* addBoxNode(exeng::scenegraph::Scene *scene, const std::string &boxNodeName, const std::string &materialName, const exeng::Vector4f &materialColor, const std::string &boxMeshName, const exeng::Vector3f &boxCenter, const exeng::Vector3f &sizeCenter);
//
//    private:
//        exeng::graphics::GraphicsDriver *graphicsDriver = nullptr;
//        exeng::scenegraph::MeshManager *meshManager = nullptr;
//    };
//}
//
//#endif  //__RAYTRACER_SCENELOADER_HPP__
