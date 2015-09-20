//
//#ifndef __RAYTRACER_RAYTRACERAPP_HPP__
//#define __RAYTRACER_RAYTRACERAPP_HPP__
//
//#include <vector>
//#include <list>
//#include <memory>
//#include <map>
//
//#include <exeng/Exeng.hpp>
//#include <exeng/Vector.hpp>
//#include <exeng/util/FrameCounter.hpp>
//
//#include <exeng/framework/GraphicsApplication.hpp>
//#include <exeng/graphics/Texture.hpp>
//#include <exeng/graphics/MeshSubset.hpp>
//#include <exeng.raytracer/SceneLoader.hpp>
//#include <exeng.raytracer/samplers/Sampler.hpp>
//#include <exeng.raytracer/tracers/Tracer.hpp>
//#include <exeng.raytracer/tracers/TracerFactory.hpp>
//
//namespace raytracer {
//    typedef std::list<exeng::scenegraph::SceneNode*> SceneNodeList;
//    typedef SceneNodeList::iterator SceneNodeListIt;
//    
//	class SceneNodeAnimator {
//	public:
//		virtual ~SceneNodeAnimator() {}
//		virtual void animateNode(const float seconds, exeng::scenegraph::SceneNode *node) = 0;
//	};
//
//    class RayTracerApp : public exeng::framework::GraphicsApplication, public exeng::input::IEventHandler {
//    public:
//        RayTracerApp();
//        virtual ~RayTracerApp();
//        
//        virtual exeng::BufferPtr getAssetsXmlData() override {
//            return exeng::BufferPtr();
//        }
//
//        virtual exeng::graphics::GraphicsDriverPtr createGraphicsDriver() override {
//            return exeng::graphics::GraphicsDriverPtr();
//        }
//
//        virtual exeng::scenegraph::AssetLibraryPtr createAssetLibrary() override {
//            return exeng::scenegraph::AssetLibraryPtr();
//        }
//
//        virtual exeng::scenegraph::SceneRendererPtr createSceneRenderer(exeng::graphics::GraphicsDriver *graphicsDriver) override {
//            return exeng::scenegraph::SceneRendererPtr();
//        }
//
//        virtual bool onInitialize() override {
//            return true;
//        }
//
//    public:
//        /* exeng::framework::GraphicsApplication */
//        virtual void initialize(int argc, char **argv);
//        virtual void pollEvents();
//        virtual exeng::framework::ApplicationStatus::Enum getStatus() const;
//        virtual void update(double seconds);        
//        virtual void render();
//        virtual int getExitCode() const;
//        virtual void terminate();
//        
//    public:
//        /* exeng::input::IEventHandler*/
//        virtual void handleEvent(const exeng::input::EventData &data);
//        
//    private:
//        std::unique_ptr<exeng::graphics::Texture> createTexture (
//            exeng::graphics::GraphicsDriver *driver, 
//            const exeng::Vector3f& size, 
//            const exeng::Vector4f &color
//        );
//        
//        void clear();
//        void present();
//        void loadScene();
//        
//    private:
//        exeng::scenegraph::Camera camera;
//		raytracer::tracers::TracerFactory tracerFactory;
//
//        std::unique_ptr<exeng::graphics::GraphicsDriver> driver;
//        std::unique_ptr<raytracer::samplers::Sampler> sampler;
//        std::unique_ptr<raytracer::tracers::Tracer> tracer;
//        std::unique_ptr<exeng::scenegraph::Scene> scene;
//        
//        std::unique_ptr<exeng::graphics::Texture> screenTexture;
//        std::unique_ptr<exeng::graphics::Material> screenMaterial;
//        std::unique_ptr<exeng::graphics::MeshSubset> screenMeshSubset;
//
//		std::unique_ptr<exeng::graphics::Material> defaultMaterial;
//
//        std::unique_ptr<SceneLoader> sceneLoader;
//
//		exeng::graphics::MaterialFormat materialFormat;
//
//        mutable uint32_t lastTime;
//        exeng::util::FrameCounter frameCounter;
//        exeng::framework::ApplicationStatus::Enum applicationStatus;
//        exeng::graphics::ButtonStatus::Enum buttonStatus[exeng::graphics::ButtonCode::Count];
//        
//		std::map<exeng::scenegraph::SceneNode*, std::unique_ptr<SceneNodeAnimator>> animators;
//        
//        float rotationAngle = 0.0f;
//    };
//}
//
//#endif	//__RAYTRACER_RAYTRACERAPP_HPP__
