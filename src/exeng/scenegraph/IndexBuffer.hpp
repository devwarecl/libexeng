
#ifndef __EXENG_SCENEGRAPH_INDEXBUFFER_HPP__
#define __EXENG_SCENEGRAPH_INDEXBUFFER_HPP__

#include "../Object.hpp"
#include <stdexcept>

namespace exeng {
    namespace scenegraph {
        
        /**
         *  @brief Formatos para un buffer de indices
         */
        enum class IndexFormat {
            Index16=16,
            Index32=32,
        };
        
        
        /**
         * @brief Area de memoria dedicada a almacenar informacion sobre indices a un VertexBuffer
         */
        class IndexBuffer : public Object {
        public:
            
            /**
             * @brief 
             */
            IndexBuffer();
            
            /**
             * @brief 
             */
            IndexBuffer(IndexFormat indexFormat, int indexCount);
            
            /**
             * @brief 
             */
            virtual ~IndexBuffer();
            
            /**
             * @brief 
             */
            void allocate(IndexFormat indexFormat, int indexCount);
            
            /**
             * @brief 
             */
            void release();
            
            /**
             * @brief Comprueba si el buffer ya esta bloqueado.
             */
            bool isEmpty() const;
            
            /**
             * @brief Bloquea al buffer de indices
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
            IndexFormat getFormat() const;
            
        private:
            struct Private;
            Private *impl;
        };
        
        
        /**
         * @brief Ayuda a inicializar buffers de vertices, a travez de una interfaz similar a la de un 
         * arreglo.
         */
        template<typename IndexType>
        class IndexArray {
        public:
            
            IndexArray(IndexBuffer *buffer) {
                this->bufferData = static_cast<IndexType*>(buffer->lock());
                this->buffer = buffer;
            }
            
            
            ~IndexArray() {
                this->buffer->unlock();
            }
            
            
            IndexType& operator[] (int index) {
                if (index >= this->buffer->getCount()) {
                    throw std::out_of_range();
                }
                
                return this->bufferData[index];
            }
            
            
            const IndexType& operator[] (int index) const {
                if (index >= this->buffer->getCount()) {
                    throw std::out_of_range();
                }
                
                return this->bufferData[index];
            }
            
            
            std::size_t size() const {
                return static_cast<std::size_t>(this->buffer->getCount());
            }
            
            
        private:
            IndexBuffer *buffer;
            IndexType *bufferData;
        };
    }
}


#endif
