
#include <cassert>
#include <stdexcept>
#include "Camera.hpp"


/**
 * @brief Atributos y funciones privados de la clase Camera.
 */
struct exeng::scenegraph::Camera::Private
{
    exeng::math::Vector3f position;   
    exeng::math::Vector3f lookAt;
    exeng::math::Vector3f up;
    exeng::scenegraph::Viewport viewport;
    exeng::scenegraph::Projection proj;
    exeng::scenegraph::ProjectionType::Enum projType;
    
    Private()
    {
        this->position = exeng::math::Vector3f(0.0f, 0.0f, 1.0f);
        this->up = exeng::math::Vector3f(0.0, 1.0, 0.0);
        
        this->viewport.size = exeng::math::Size2f(1.0, 1.0);
        this->projType = exeng::scenegraph::ProjectionType::Orthographic;
    }
};


namespace exeng
{
    namespace scenegraph
    {
        std::string invalidArgument = "La posicion no puede ser igual al punto de vision de la camara";
    
    
        Camera::Camera()
        {
            this->impl = new Camera::Private();
        }
		
		
		Camera::~Camera() 
		{
			delete this->impl;
		}
		
        
        void Camera::setOrientation(const exeng::math::Vector3f &pos, const exeng::math::Vector3f &lookAt)
        {
            if (pos == lookAt)
                throw std::invalid_argument(invalidArgument);
            
            this->impl->position = pos;
            this->impl->lookAt = lookAt;
        }
        
        
        auto Camera::setPosition(const exeng::math::Vector3f &pos) -> void
        {
            assert(this->impl != NULL);
            
            if (pos == this->impl->lookAt)
                throw std::invalid_argument(invalidArgument);
            
            this->impl->position = pos;
        }
        
        
        auto Camera::getPosition() const -> exeng::math::Vector3f
        {
            assert(this->impl != NULL);
            
            return this->impl->position;
        }
        
        
        auto Camera::setLookAt(const exeng::math::Vector3f &lookAt) -> void
        {
            assert(this->impl != NULL);
            
            if (this->impl->position == lookAt)
                throw std::invalid_argument(invalidArgument);
            
            this->impl->lookAt = lookAt;
        }
        
        
        auto Camera::getLookAt() const -> exeng::math::Vector3f
        {
            assert(this->impl != NULL);
            
            return this->impl->lookAt;
        }
        
        
        auto Camera::getUp() const -> exeng::math::Vector3f
        {
            assert(this->impl != NULL);
            
            return this->impl->up;
        }
        
        
        auto Camera::setUp(const exeng::math::Vector3f &up) -> void
        {
            assert(this->impl != NULL);
            
            if (up == exeng::math::Vector3f(0.0, 0.0, 0.0))
                throw std::invalid_argument("La direccion superior de la camara no puede ser el vector cero.");
            
            this->impl->up = up;
            this->impl->up.normalize();
        }
        
        
        auto Camera::setViewport(const Viewport &viewport) -> void
        {
            assert(this->impl != NULL);
            
            if (viewport.size == exeng::math::Size2f(0.0, 0.0))
                throw std::invalid_argument("El tamanio debe tener todos sus valores positivos");
            
            this->impl->viewport = viewport;
        }
        
        
        auto Camera::getViewport() const -> Viewport
        {
            assert(this->impl != NULL);
            
            return this->impl->viewport;
        }
        
        
        auto Camera::setProjection(const Projection &proj) -> void
        {
            assert(this->impl != NULL);
            
            if (proj.back > proj.left || proj.bottom > proj.top || proj.front > proj.back)
                throw std::invalid_argument("El objeto de proyeccion tiene algunos valores invalidos");
            
            this->impl->proj = proj;
        }
        
        
        auto Camera::getProjection() -> Projection
        {
            assert(this->impl != NULL);
            
            return this->impl->proj;
        }
        
        
        auto Camera::setProjectionType(ProjectionType::Enum projType) -> void
        {
            assert(this->impl != NULL);
            
            this->impl->projType = projType;
        }
        
        
        auto Camera::getProjectionType() -> ProjectionType::Enum
        {
            assert(this->impl != NULL);
            
            return this->impl->projType;
        }
    }
}


