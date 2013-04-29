
#ifndef __EXENG_SCENEGRAPH_VERTEXBUFFER_HPP__
#define __EXENG_SCENEGRAPH_VERTEXBUFFER_HPP__

#include "../Object.hpp"
#include "../math/TVector.hpp"

#include <stdexcept>

namespace exeng {
    namespace scenegraph {
        
        /**
         *  @brief Estructura de un vertice de pruebas
         */
        struct Vertex {
            exeng::math::Vector3f coord;
            exeng::math::Vector3f normal;
            exeng::math::Vector2f texCoord;
        };
        
        
        /**
         * @brief Area de memoria dedicada a almacenar informacion sobre vertices, del formato estandar.
         */
        class VertexBuffer : public Object {
        public:
            
            /**
             * @brief 
             */
            VertexBuffer();
            
            /**
             * @brief 
             */
            VertexBuffer(int vertexSize, int vertexCount);
            
            /**
             * @brief 
             */
            virtual ~VertexBuffer();
            
            /**
             * @brief 
             */
            void allocate(int vertexSize, int vertexCount);
            
            /**
             * @brief 
             */
            void release();
            
            /**
             * @brief Comprueba si el buffer ya esta bloqueado.
             */
            bool isEmpty() const;
            
            /**
             * @brief Bloquea al buffe__EXENG_SCENEGRAPH_INDEXBUFFER_HPP__r.
             */
            void* lock();
            
            /**
             * @brief Comprueba si es posible bloquear al buffer.
             */
            bool isLocked() const;
            
            /**
             * @brief Desbloquea al buffer, en caso de que ya este bloqueado.
             */
            void unlock();
            
            
            /**
             * @brief Devuelve la cantidad de vertices del buffer.
             */
            int getCount() const;
            
            /**
             * @brief Devuelve el tamaño en bytes, de cada vertice almacenado.
             */
            int getSize() const;
            
        private:
            struct Private;
            Private *impl;
        };
        
        
        /**
         * @brief Ayuda a inicializar buffers de vertices, a travez de una interfaz similar a la de un 
         * arreglo.
         */
        template<typename VertexType>
        class VertexArray {
        public:
            
            VertexArray(VertexBuffer *buffer) {
                this->bufferData = static_cast<VertexType*>(buffer->lock());
                this->buffer = buffer;
            }
            
            
            ~VertexArray() {
                this->buffer->unlock();
            }
            
            
            VertexType& operator[] (int index) {          
#ifdef EXENG_DEBUG
                if (index >= this->buffer->getCount()) {
                    throw std::out_of_range("");
                }
#endif
                
                return this->bufferData[index];
            }
            
            
            const VertexType& operator[] (int index) const {
#ifdef EXENG_DEBUG
                if (index >= this->buffer->getCount()) {
                    throw std::out_of_range("");
                }
#endif                
                return this->bufferData[index];
            }
            
            
            int size() const {
                return this->buffer->getCount();
            }
            
            
        private:
            VertexBuffer *buffer;
            VertexType *bufferData;
        };
    }
}

#endif  //__EXENG_SCENEGRAPH_VERTEXBUFFER_HPP__
