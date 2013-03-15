
#ifndef __EXENG_GRAPHICS_INDEXBUFFER_HPP__
#define __EXENG_GRAPHICS_INDEXBUFFER_HPP__

#include "../Object.hpp"

namespace exeng
{
	namespace graphics
	{
	    namespace IndexBufferFormat
	    {
	        enum Type
	        {
	            Index16,
                Index32
	        };
	    }
	    
	    
        class EXENGAPI IndexBuffer : public Object
	    {
        public:
            virtual ~IndexBuffer() {}
            
            virtual void* Lock() = 0;
            virtual void Unlock() = 0;
            virtual int GetCount() const = 0;
            virtual IndexBufferFormat::Type GetFormat() = 0;
	    };
	}
}

#endif
