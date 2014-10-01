
#ifndef __RAYTRACER_SCENELOADER_HPP__
#define __RAYTRACER_SCENELOADER_HPP__

#include <memory>
#include <exeng/scenegraph/Scene.hpp>
#include <exeng/graphics/GraphicsDriver.hpp>
#include <exeng/scenegraph/MeshManager.hpp>

namespace raytracer {
    class SceneLoader {
    public:
        SceneLoader(const SceneLoader &) = delete;
        SceneLoader& operator=(const SceneLoader &) = delete;

    public:
        explicit SceneLoader(exeng::graphics::GraphicsDriver *driver, exeng::scenegraph::MeshManager *meshManager);
        virtual ~SceneLoader();

        std::unique_ptr<exeng::scenegraph::Scene> loadScene(const std::string &filename);

    private:
        exeng::graphics::GraphicsDriver *graphicsDriver = nullptr;
        exeng::scenegraph::MeshManager *meshManager = nullptr;
    };
}

#endif  //__RAYTRACER_SCENELOADER_HPP__
