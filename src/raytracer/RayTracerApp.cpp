
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <cstdint>
#include <list>

#include <SDL/SDL.h>

#include <exeng/graphics/Color.hpp>
#include <exeng/math/TVector.hpp>
#include <exeng/scenegraph/Geometry.hpp>
#include <exeng/scenegraph/Sphere.hpp>
#include <exeng/scenegraph/SceneNode.hpp>
#include <exeng/scenegraph/Scene.hpp>

#include "SphereGeometry.hpp"
#include "RayTracerApp.hpp"


namespace RayTracer {
	// Define la forma en que se generara la imagen trazada
	struct CameraView {
		std::int32_t screenWidth;	// Ancho de la pantalla
		std::int32_t screenHeight;	// Alto de la pantalla
		float pixelSize;			// El tamaño de cada pixel
		float gamma;				// El factor gamma
		float invGamma;				// El inverso del factor gamma

		// Define los atributos por defecto
		CameraView() {	
			this->screenWidth = 320;
			this->screenHeight = 200;
			this->pixelSize = 1.0f;
			this->gamma = 0.0f;
			this->invGamma = 0.0f;
		}
	};
}


typedef std::list<exeng::scenegraph::SceneNode*> SceneNodeList;

// Atributos y metodos privados de la aplicacion
struct RayTracer::RayTracerApp::Private {
	std::uint32_t defaultColor;
    SDL_Surface *backbuffer;
    SDL_Event evt;
    bool running;    
	CameraView cameraView;

	exeng::scenegraph::Scene scene;

    Private() {
		this->defaultColor = 0xFF000000;
        this->backbuffer = NULL;
        this->running = false;

		this->cameraView.screenWidth = 640;
		this->cameraView.screenHeight = 480;
    }
    
	
	// Convierte una posicion bidimensional en una unidimensional
    inline std::uint32_t pointToOffset(const exeng::math::Vector2i &point) const
    {
#ifdef EXENG_DEBUG

        if (point.x >= this->cameraView.screenWidth) {
            throw std::invalid_argument("");
		}
        
        if (point.y >= this->cameraView.screenHeight) {
            throw std::invalid_argument("");
		}
#endif	
        auto offset = point.y * this->cameraView.screenWidth + point.x;
        return static_cast<uint32_t>(offset);
    }
    

	// Establece el color de un pixel
    inline void putPixel(const exeng::math::Vector2i &point, std::uint32_t color)
    {
        auto offset = this->pointToOffset(point);
        auto data = static_cast<uint32_t*>(this->backbuffer->pixels);
		
        data += offset;
        
        *data = color;
    }
    
    
	// Devuelve el color de un pixel
    inline std::uint32_t getPixel(const exeng::math::Vector2i &point) const
    {
        auto offset = this->pointToOffset(point);
        auto data = static_cast<uint32_t*>( this->backbuffer->pixels );
        
        data += offset;
        
        return *data;
    }
    

	// Crea un rayo a partir de las coordenadas de pantalla indicadas



	// Aplana la jerarquia de un nodo de escena.
	inline void flattenHierarchy(SceneNodeList &out, exeng::scenegraph::SceneNode* node) {
		using exeng::TypeInfo;
		using exeng::scenegraph::Geometry;

		if (node != nullptr && node->getDataPtr() != nullptr) {
			if (node->getDataPtr()->getTypeInfo() == TypeInfo::get<Geometry>())  {
				out.push_back(node);
			}
		}

		for (auto child : node->getChilds()) {
			this->flattenHierarchy(out, child);
		}
	}


	/**
	 *	@brief Recursivamente, detecta colision entre un rayo y el nodo de escena indicado, 
	 *	devolviendo la informacion colision con el objeto mas cercano al rayo indicado.
	 *	@return Devuelve el estado de la interseccion
	 */
	inline exeng::scenegraph::IntersectInfo intersectRay(	const SceneNodeList &nodes, 
															const exeng::scenegraph::Ray &ray) {
		using exeng::TypeInfo;
		using exeng::scenegraph::Geometry;
		using exeng::scenegraph::IntersectInfo;

		IntersectInfo prevInfo, currentInfo, info;

		// Determinar colision con el contenido del nodo
		for (auto node : nodes) {
			auto geometry = static_cast<Geometry*>( node->getDataPtr() );

			assert(geometry != nullptr);

			if (geometry->hit(ray, &currentInfo) == true) {

				bool isFirstInfo = prevInfo.parametricCoord == 0.0f;
				bool isBetterInfo = currentInfo.parametricCoord > prevInfo.parametricCoord;

				if (isFirstInfo == true || isBetterInfo == true) {
					info = currentInfo;

					assert(info.surfaceMaterial != nullptr);
					assert(info.surfaceNormal != exeng::math::Vector3f(0.0f));
				}

				prevInfo = currentInfo;
			}
		}

		return info;
	}
};


namespace RayTracer
{
    RayTracerApp::RayTracerApp() {
		this->impl.reset(new RayTracerApp::Private());
    }


    RayTracerApp::~RayTracerApp() {
        this->terminate();
    }


    void RayTracerApp::initialize(const StringVector& cmdLine) {
        SDL_Init(SDL_INIT_VIDEO);
        
		auto screenWidth = this->impl->cameraView.screenWidth;
		auto screenHeight = this->impl->cameraView.screenHeight;

        auto flags = SDL_DOUBLEBUF | SDL_HWSURFACE;
        auto buffer = SDL_SetVideoMode(screenWidth, screenHeight, 32, flags);

        this->impl->backbuffer = buffer;
        this->impl->running = true;

		// Crear una escena de juguete, con una esfera al centro de la escena
		auto rootNode = this->impl->scene.getRootNodePtr();

		auto sphereGeometry = new SphereGeometry();
		auto sphereGeometry2 = new SphereGeometry();

		sphereGeometry->sphere.setAttributes(20.0, exeng::math::Vector3f(-10.0f, 0.0f, 0.0f));
		sphereGeometry->material.setDiffuse(exeng::math::Vector4f(0.8f, 0.3f, 0.2f, 1.0f));

		sphereGeometry2->sphere.setAttributes(30.0, exeng::math::Vector3f(20.0f, 0.0f, 0.0f));
		sphereGeometry2->material.setDiffuse(exeng::math::Vector4f(0.3f, 0.5f, 1.0f, 1.0f));

		rootNode->addChildPtr("sphereGeometry")->setDataPtr(sphereGeometry);
		rootNode->addChildPtr("sphereGeometry2")->setDataPtr(sphereGeometry2);
    }


    double RayTracerApp::getFrameTime() const {
        return 0.0;
    }


    void RayTracerApp::processInput() {
        while (SDL_PollEvent(&this->impl->evt)) {
            switch (this->impl->evt.type) {
                case SDL_QUIT:
                    this->impl->running = false;
                    break;
            }
        }
    }


    ApplicationStatus::Enum RayTracerApp::getStatus() {
        if (this->impl->running == true) {
            return ApplicationStatus::Running;
		} else {
            return ApplicationStatus::Stopped;
		}
    }


    void RayTracerApp::update(double seconds) {
    }


    void RayTracerApp::present() {
		union RawColor {
			std::uint32_t c_ui32;
			std::uint8_t c_4_ui32[4];
		};

		using exeng::scenegraph::IntersectInfo;
		using exeng::scenegraph::Ray;
		using exeng::math::Vector3f;
		using exeng::math::Vector4f;
		using exeng::math::Vector2i;

		auto& cameraView = this->impl->cameraView;

        auto backbuffer = this->impl->backbuffer;
        SDL_Rect screenRect = {0};
        
		screenRect.w = cameraView.screenWidth;
        screenRect.h = cameraView.screenHeight;
        
        SDL_FillRect(backbuffer, &screenRect, 0xFF000000);
        SDL_LockSurface(backbuffer);

		Vector4f color;
		Ray ray;
		RawColor rawColor;
		IntersectInfo info;
		SceneNodeList nodeList;

		cameraView.pixelSize = 0.1f;

		this->impl->flattenHierarchy(nodeList, this->impl->scene.getRootNodePtr());

		const auto halfWidth = cameraView.screenWidth * 0.5f;
		const auto halfHeight = cameraView.screenHeight * 0.5f;

		exeng::graphics::Color colore;

        for(int y=0; y<cameraView.screenHeight; ++y) {
            for(int x=0; x<cameraView.screenWidth; ++x) {
				color = this->impl->scene.getBackgroundColor();

                // Trazar un rayo
				ray.setPointX(cameraView.pixelSize * (x - halfWidth + 0.5f));
				ray.setPointY(cameraView.pixelSize * (y - halfHeight + 0.5f));
				ray.setPointZ(-50.0f);

                ray.setDirection( 0.0f, 0.0f, 1.0f );

                // Intersectarlo con los objetos de la escena
				info = this->impl->intersectRay(nodeList, ray);

				if (info.intersect == true)  {
					// Determinar el color
					auto factor = info.surfaceNormal.dot(ray.getDirection());

					assert( info.surfaceMaterial != nullptr );

					color = factor * info.surfaceMaterial->getDiffuse();
				} else {
					color = Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
				}

				// Convertir el color a un formato esperado por la tarjeta de video
				for (int i=0; i<3; ++i) {
					rawColor.c_4_ui32[i] = static_cast<std::uint8_t>(255.0f * color[2 - i]);
				}

				rawColor.c_4_ui32[3] = static_cast<std::uint8_t>(255.0f * color[3]);

				// Pintar el backbuffer 
				this->impl->putPixel(Vector2i(x, y), rawColor.c_ui32);
            }
        }

        SDL_UnlockSurface(backbuffer);
        SDL_Flip(backbuffer);
    }


    int RayTracerApp::getExitCode() const {
        return 0;
    }


    void RayTracerApp::terminate() {
        SDL_Quit();
    }
}


// Registrar la aplicacion de trazado de rayos
namespace {
    using namespace RayTracer;
    static const bool b = Application::set( new RayTracerApp() );
}
