
#ifndef __RAYTRACER_SCENELOADER_HPP__
#define __RAYTRACER_SCENELOADER_HPP__

#include <exeng/scenegraph/Scene.hpp>

namespace raytracer {
    
    class SceneLoader {
    public:
        SceneLoader();
        ~SceneLoader();
        
        exeng::scenegraph::Scene* loadScene(const std::string &filename);
        
    private:
        
    };
}

#endif  //__RAYTRACER_SCENELOADER_HPP__
