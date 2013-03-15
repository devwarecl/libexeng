
#ifndef __EXENG_GRAPHICS_MATERIAL_HPP__
#define __EXENG_GRAPHICS_MATERIAL_HPP__

#include "../Object.hpp"
#include "../math/TVector.hpp"

namespace exeng
{
	namespace graphics
    {
        class EXENGAPI Texture;
        
        /**
         *  @brief Capa de un material
         */
        class EXENGAPI MaterialLayer
        {
        public:
            
            /**
             *  @brief
             */
            MaterialLayer();
            
            /**
             *  @brief
             */
            ~MaterialLayer();
            
            /**
             *  @brief Devuelve la textura que esta almacenada en la capa
             */
            const Texture* getTexture() const;
            
            /**
             *  @brief Devuelve la textura que esta almacenada en la capa
             */
            Texture* getTexture();
            
            /**
             *  @brief Cambia la textura actual por otra existente
             */
            void setTexture(Texture* tex);
            
            /**
             *  @brief Comprueba si existe una textura en la capa actual
             */
            bool hasTexture() const;
            
            /**
             *  @brief Compara si la capa de textura contiene la misma textura o no
             */
            bool operator == (const MaterialLayer& other) const;

            /**
             *  @brief Compara si tienen texturas diferentes
             */
            bool operator != (const MaterialLayer& other) const;
            
            /**
             *  @brief Asigna la informacion de una capa de textura en otra
             */
            MaterialLayer& operator= (const MaterialLayer& other);

        private:
            struct Private;
            Private *impl;
        };
        
        
        /**
         *  @brief Describe la apariencia visual de un objeto tridimensional
         */
	    class EXENGAPI Material : public Object
	    {
        public:
            /**
             *  @brief 
             */
            Material();
            
            /**
             *  @brief 
             */
            Material(const Material& Other);
            
            /**
             *  @brief 
             */
            virtual ~Material();
            
            /**
             *  @brief 
             */
            void setAmbient( const exeng::math::Vector4f &color );
            
            /**
             *  @brief 
             */
            void setDiffuse( const exeng::math::Vector4f &color );
            
            /**
             *  @brief 
             */
            void setSpecular( const exeng::math::Vector4f &color);
            
            /**
             *  @brief 
             */
            void setEmissive( const exeng::math::Vector4f &color );
            
            /**
             *  @brief 
             */
            void setShininess( float Value);
            
            /**
             *  @brief 
             */
            exeng::math::Vector4f getAmbient() const;
            
            /**
             *  @brief 
             */
            exeng::math::Vector4f getDiffuse() const;
            
            /**
             *  @brief 
             */
            exeng::math::Vector4f getSpecular() const;
            
            /**
             *  @brief 
             */
            exeng::math::Vector4f getEmissive() const;
            
            /**
             *  @brief 
             */
            float getShininess() const;
            
            /**
             *  @brief Devuelve el nombre del material
             */
            std::string getName() const;
            
            /**
             *  @brief Establece el nombre del material
             */
            void setName(const std::string& name);
            
            /**
             *  @brief Devuelve la capa que se encuentra en la ubicacion indicada
             */
            MaterialLayer& getLayerRef(int index);
            
            /**
             *  @brief Devuelve la capa de textura indicada
             */
            const MaterialLayer& getLayerRef(int index) const;
            
            // Sobrecargar metodos de Object
            
            /**
             *  @brief Hace una copia exacta del material
             */
            virtual Material* clone() const;
            
            /**
             *  @brief Compara el material con otro material
             */
            virtual bool equals(const Object &other) const;
    
            /**
             *  @brief
             */
            virtual bool lesserThan(const Object& other) const;
            
            /**
             *  @brief Copia los atributos de otro material en este material
             */
            virtual void assign(const Object& other);
        
            /**
             *  @brief Devuelve el identificador de tipo del material
             */
            virtual TypeInfo getTypeInfo() const;
            
        public:
            /**
             *  @brief Devuelve la cantidad maxima de capas soportadas en el material
             */
            static const int getLayerCount();
            
        private:
            struct Private;
            Private *impl;
	    };
	}
}

#endif
