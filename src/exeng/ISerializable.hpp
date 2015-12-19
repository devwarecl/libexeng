
#ifndef __EXENG_ISERIALIZABLE_HPP__
#define __EXENG_ISERIALIZABLE_HPP__

#include <exeng/Config.hpp>

namespace xe {
    class EXENGAPI ISerializable {
    public:
        virtual ~ISerializable();
        
        virtual bool isReadable() const;
        
        virtual void read(void* dst, const int size) = 0;
        
        template<typename Type> 
        void read(Type &dst) {
            this->read(&dst, sizeof(Type));
        }
        
        template<typename Type>
        void read(Type *dst, const int count) {
            this->read(dst, sizeof(Type) * count);
        }
        
        virtual bool isWritable() const;
        
        virtual void write(const void* src, const int size) = 0;
        
        template<typename Type> 
        void write(const Type &src) {
            this->write(&src, sizeof(Type));
        }
        
        template<typename Type> 
        void write(const Type *src, const int count) {
            this->write(src, sizeof(Type) * count);
        }
    };
}

#endif  // __EXENG_ISERIALIZABLE_HPP__
