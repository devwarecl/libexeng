

#include "SceneLoader.hpp"

#include <exeng/Vector.hpp>
#include <exeng/scenegraph/Mesh.hpp>
#include <exeng/graphics/Material.hpp>

namespace raytracer {
    using namespace exeng;
    using namespace exeng::scenegraph;
    using namespace exeng::graphics;
    
    SceneLoader::~SceneLoader() {}
    
    SceneLoader::SceneLoader(GraphicsDriver *driver_, MeshManager *meshManager_) : graphicsDriver(driver_), meshManager(meshManager_) {
    }
    
    // For now, just create a simple scene, boxed scene.
    std::unique_ptr<Scene> SceneLoader::loadScene(const std::string &filename) {
        // empty object
        auto scene = std::unique_ptr<Scene>(new Scene());

        // box material
        Material *boxMaterial = scene->createMaterial("boxMaterial");
        boxMaterial->setProperty("diffuse", Vector4f(1.0f, 0.3f, 0.2f, 1.0f));

        // box mesh
        // Mesh *boxMesh = this->meshManager->getMesh("/cube", this->graphicsDriver);
		Mesh *boxMesh = this->meshManager->generateBoxMesh("box1", this->graphicsDriver, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
        boxMesh->getMeshSubset(0)->setMaterial(boxMaterial);

        // box scenenode
        scene->getRootNode()->addChild("boxNode")->setData(boxMesh);

        return scene;
    }
}
