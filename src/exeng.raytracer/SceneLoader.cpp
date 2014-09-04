

#include <exeng/Vector.hpp>
#include <exeng/scenegraph/Box.hpp>
#include <exeng/graphics/Material.hpp>
#include <exeng/scenegraph/TSolidGeometry.hpp>

#include <exeng.raytracer/SceneLoader.hpp>

namespace raytracer {
    using namespace exeng;
    using namespace exeng::scenegraph;
    using namespace exeng::graphics;
    
    SceneLoader::SceneLoader() {}
    SceneLoader::~SceneLoader() {}
    
    Scene* SceneLoader::loadScene(const std::string &filename) {
        // For now, just create a simple scene, boxed scene.
        Scene *scene = new Scene();
        
        Material *boxMaterial = scene->createMaterial("boxMaterial");
        boxMaterial->setProperty("diffuse", Vector4f(1.0f, 0.3f, 0.2f, 1.0f));
        
        Geometry* boxGeometry = new TSolidGeometry<Boxf>(
            Boxf(-Vector3f(10.0f), Vector3f(10.0f)),
            boxMaterial
        );
        
        scene->getRootNode()->addChild("boxGeometry")->setData(boxGeometry);
        
        return scene;
    }
}
