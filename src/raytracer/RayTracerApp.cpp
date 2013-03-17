
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

typedef std::list<exeng::scenegraph::SceneNode*> SceneNodeList;
typedef SceneNodeList::iterator SceneNodeListIt;

using exeng::TypeInfo;
using exeng::math::Vector2f;
using exeng::math::Vector3f;
using exeng::math::Vector4f;
using exeng::math::Vector2i;
using exeng::graphics::Color;
using exeng::scenegraph::Geometry;
using exeng::scenegraph::Scene;
using exeng::scenegraph::SceneNode;
using exeng::scenegraph::IntersectInfo;
using exeng::scenegraph::Ray;

namespace RayTracer {
    
	// Define la forma en que se generara la imagen trazada
	struct CameraView {
        Vector2i size;              // Porte de la pantalla
		float pixelSize;			// El tamaño de cada pixel
		float gamma;				// El factor gamma
		float invGamma;				// El inverso del factor gamma

		// Define los atributos por defecto
		CameraView() {
            this->size = Vector2i(320, 200);
			this->pixelSize = 0.2f;
			this->gamma = 0.0f;
			this->invGamma = 0.0f;
		}
	};
}


// Atributos y metodos privados de la aplicacion
struct RayTracer::RayTracerApp::Private {
    
	std::uint32_t defaultColor;
    SDL_Surface *backbuffer;
    SDL_Event evt;
    bool running;
	CameraView cameraView;
	Scene scene;

    
    Private() {
		this->defaultColor = 0xFF000000;
        this->backbuffer = NULL;
        this->running = false;
        this->cameraView.size.set(320, 200);
    }
    
	
	// Convierte una posicion bidimensional en una unidimensional
    inline std::uint32_t pointToOffset(const Vector2i &point) const {
#ifdef EXENG_DEBUG
        if (point.x >= this->cameraView.size.x) {
            throw std::invalid_argument("");
		}
        
        if (point.y >= this->cameraView.size.y) {
            throw std::invalid_argument("");
		}
#endif	
        auto offset = point.y * this->cameraView.size.x + point.x;
        return static_cast<uint32_t>(offset);
    }
    
    
	// Establece el color de un pixel
    inline void putPixel(const Vector2i &point, std::uint32_t color) {
        auto offset = this->pointToOffset(point);
        auto data = static_cast<uint32_t*>(this->backbuffer->pixels);
		
        data += offset;
        
        *data = color;
    }
    
    
	// Devuelve el color de un pixel
    inline std::uint32_t getPixel(const Vector2i &point) const {
        auto offset = this->pointToOffset(point);
        auto data = static_cast<uint32_t*>(this->backbuffer->pixels);
        
        data += offset;
        
        return *data;
    }
    

	// Crea un rayo a partir de las coordenadas de pantalla indicadas
	
	
	// Aplana la jerarquia de un nodo de escena.
	inline void flattenHierarchy(SceneNodeList &out, SceneNode* node) {
        // Poner los nodos de escena
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
	 *	@brief Detecta si existe colision entre un rayo y algun nodo de la lista de nodos, 
	 *	devolviendo la informacion colision con el objeto mas cercano al rayo indicado.
	 *	@return Devuelve el estado de la interseccion
	 */
	inline IntersectInfo intersectRay(const SceneNodeList &nodes, const Ray &ray) {
		IntersectInfo prevInfo;
        IntersectInfo currentInfo;
        IntersectInfo info;

		// Determinar colision con el contenido del nodo
		for (auto node : nodes) {
			auto geometry = static_cast<Geometry*>( node->getDataPtr() );
			assert(geometry != nullptr);

			if (geometry->hit(ray, &currentInfo) == true) {
                
				bool isFirst = prevInfo.parametricCoord == 0.0f;
				bool isBetter = currentInfo.parametricCoord > prevInfo.parametricCoord;

				if (isFirst == true || isBetter == true) {
					info = currentInfo;
                    
					assert(info.surfaceMaterial != nullptr);
					assert(info.surfaceNormal != exeng::math::Vector3f(0.0f));
				}

				prevInfo = currentInfo;
			}
		}

		return info;
	}
	
	
	// Limpia el buffer.
	void clear() {
        SDL_Rect screenRect = {0};
        
        screenRect.w = this->cameraView.size.x;
        screenRect.h = this->cameraView.size.y;
        
        SDL_FillRect(this->backbuffer, &screenRect, 0xFF000000);
        SDL_LockSurface(this->backbuffer);
    }
	
	
	// Presenta los resultados actuales a la pantalla
	void present() {
        SDL_UnlockSurface(this->backbuffer);
        SDL_Flip(this->backbuffer);
    }
};


namespace RayTracer {
    RayTracerApp::RayTracerApp() {
		this->impl.reset(new RayTracerApp::Private());
    }


    RayTracerApp::~RayTracerApp() {
        this->terminate();
    }


    void RayTracerApp::initialize(const StringVector& cmdLine) {
        SDL_Init(SDL_INIT_VIDEO);
        
        auto screenSize = this->impl->cameraView.size;
        
        auto flags = SDL_DOUBLEBUF | SDL_HWSURFACE;
        auto buffer = SDL_SetVideoMode(screenSize.x, screenSize.y, 32, flags);

        this->impl->backbuffer = buffer;
        this->impl->running = true;

		// Crear una escena de juguete, con una esfera al centro de la escena.
        // TODO: Cargar esta escena desde un archivo XML, o similar
		auto rootNode = this->impl->scene.getRootNodePtr();
		auto sphereGeometry = new SphereGeometry();
		auto sphereGeometry2 = new SphereGeometry();
        
		sphereGeometry->sphere.setAttributes(10.0, Vector3f(-15.0f, 0.0f, 0.0f));
		sphereGeometry->material.setDiffuse(Color(1.0f, 0.5f, 0.25f, 1.0f));
        
		sphereGeometry2->sphere.setAttributes(15.0, Vector3f(15.0f, 0.0f, 0.0f));
		sphereGeometry2->material.setDiffuse(Color(0.0f, 0.0f, 1.0f, 1.0f));

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
        auto screenSize = this->impl->cameraView.size;
        auto pixelSize = this->impl->cameraView.pixelSize;
        Color color;
        Ray ray;
        IntersectInfo info;
        SceneNodeList nodeList;
        
        this->impl->clear();
        
		this->impl->flattenHierarchy(nodeList, this->impl->scene.getRootNodePtr());
        
		const auto halfWidth = screenSize.x * 0.5f;
		const auto halfHeight = screenSize.y * 0.5f;
        
        for(int y=0; y<screenSize.y; ++y) {
            for(int x=0; x<screenSize.x; ++x) {
                
				color = this->impl->scene.getBackgroundColor();

                // Trazar un rayo
				ray.setPointX(pixelSize * (x - halfWidth + 0.5f));
				ray.setPointY(pixelSize * (y - halfHeight + 0.5f));
				ray.setPointZ(-50.0f);

                ray.setDirection( 0.0f, 0.0f, 1.0f );

                // Intersectarlo con los objetos de la escena
				info = this->impl->intersectRay(nodeList, ray);

				if (info.intersect == true)  {
					// Determinar el color
					auto factor = info.surfaceNormal.dot(ray.getDirection());
					color = info.surfaceMaterial->getDiffuse() * factor;
				}
				
				std::swap(color[0], color[1]);
                
                // Pintar el backbuffer 
                this->impl->putPixel(Vector2i(x, y), static_cast<uint32_t>(color) );
            }
        }

        this->impl->present();
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
