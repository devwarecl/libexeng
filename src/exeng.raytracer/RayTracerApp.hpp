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
//    typedef std::list<xe::sg::SceneNode*> SceneNodeList;
//    typedef SceneNodeList::iterator SceneNodeListIt;
//    
//	class SceneNodeAnimator {
//	public:
//		virtual ~SceneNodeAnimator() {}
//		virtual void animateNode(const float seconds, xe::sg::SceneNode *node) = 0;
//	};
//
//    class RayTracerApp : public xe::fw::GraphicsApplication, public xe::input::IEventHandler {
//    public:
//        RayTracerApp();
//        virtual ~RayTracerApp();
//        
//        virtual xe::BufferPtr getAssetsXmlData() override {
//            return xe::BufferPtr();
//        }
//
//        virtual xe::gfx::GraphicsDriverPtr createGraphicsDriver() override {
//            return xe::gfx::GraphicsDriverPtr();
//        }
//
//        virtual xe::sg::AssetLibraryPtr createAssetLibrary() override {
//            return xe::sg::AssetLibraryPtr();
//        }
//
//        virtual xe::sg::SceneRendererPtr createSceneRenderer(xe::gfx::GraphicsDriver *graphicsDriver) override {
//            return xe::sg::SceneRendererPtr();
//        }
//
//        virtual bool onInitialize() override {
//            return true;
//        }
//
//    public:
//        /* xe::fw::GraphicsApplication */
//        virtual void initialize(int argc, char **argv);
//        virtual void pollEvents();
//        virtual xe::fw::ApplicationStatus::Enum getStatus() const;
//        virtual void update(double seconds);        
//        virtual void render();
//        virtual int getExitCode() const;
//        virtual void terminate();
//        
//    public:
//        /* xe::input::IEventHandler*/
//        virtual void handleEvent(const xe::input::EventData &data);
//        
//    private:
//        std::unique_ptr<xe::gfx::Texture> createTexture (
//            xe::gfx::GraphicsDriver *driver, 
//            const xe::Vector3f& size, 
//            const xe::Vector4f &color
//        );
//        
//        void clear();
//        void present();
//        void loadScene();
//        
//    private:
//        xe::sg::Camera camera;
//		raytracer::tracers::TracerFactory tracerFactory;
//
//        std::unique_ptr<xe::gfx::GraphicsDriver> driver;
//        std::unique_ptr<raytracer::samplers::Sampler> sampler;
//        std::unique_ptr<raytracer::tracers::Tracer> tracer;
//        std::unique_ptr<xe::sg::Scene> scene;
//        
//        std::unique_ptr<xe::gfx::Texture> screenTexture;
//        std::unique_ptr<xe::gfx::Material> screenMaterial;
//        std::unique_ptr<xe::gfx::MeshSubset> screenMeshSubset;
//
//		std::unique_ptr<xe::gfx::Material> defaultMaterial;
//
//        std::unique_ptr<SceneLoader> sceneLoader;
//
//		xe::gfx::MaterialFormat materialFormat;
//
//        mutable uint32_t lastTime;
//        xe::util::FrameCounter frameCounter;
//        xe::fw::ApplicationStatus::Enum applicationStatus;
//        xe::gfx::ButtonStatus::Enum buttonStatus[xe::gfx::ButtonCode::Count];
//        
//		std::map<xe::sg::SceneNode*, std::unique_ptr<SceneNodeAnimator>> animators;
//        
//        float rotationAngle = 0.0f;
//    };
//}
//
//#endif	//__RAYTRACER_RAYTRACERAPP_HPP__
