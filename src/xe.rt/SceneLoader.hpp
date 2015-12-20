//
//#ifndef __RAYTRACER_SCENELOADER_HPP__
//#define __RAYTRACER_SCENELOADER_HPP__
//
//#include <memory>
//#include <xe/Vector.hpp>
//#include <xe/sg/Scene.hpp>
//#include <xe/gfx/GraphicsDriver.hpp>
//#include <xe/sg/MeshManager.hpp>
//
//namespace raytracer {
//    class SceneLoader {
//    public:
//        SceneLoader(const SceneLoader &) = delete;
//        SceneLoader& operator=(const SceneLoader &) = delete;
//
//    public:
//        explicit SceneLoader(xe::gfx::GraphicsDriver *driver, xe::sg::MeshManager *meshManager);
//        virtual ~SceneLoader();
//
//        std::unique_ptr<xe::sg::Scene> loadScene(const std::string &filename, const xe::gfx::MaterialFormat *materialFormat);
//
//	private:
//		xe::sg::SceneNode* addBoxNode(xe::sg::Scene *scene, const std::string &boxNodeName, const std::string &materialName, const xe::Vector4f &materialColor, const std::string &boxMeshName, const xe::Vector3f &boxCenter, const xe::Vector3f &sizeCenter);
//
//    private:
//        xe::gfx::GraphicsDriver *graphicsDriver = nullptr;
//        xe::sg::MeshManager *meshManager = nullptr;
//    };
//}
//
//#endif  //__RAYTRACER_SCENELOADER_HPP__
