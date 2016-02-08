
#ifndef __EXENG_STATIC_BUFFER_HPP__
#define __EXENG_STATIC_BUFFER_HPP__

#include <xe/Buffer.hpp>

namespace xe {
    
	/**
	 * @brief Wrapper over a raw C buffer.
	 */
	class StaticBuffer : public Buffer {
	public:
        StaticBuffer() {}
        StaticBuffer(void* data_, const int dataSize_) : data(data_), dataSize(dataSize_) {}

        virtual int getSize() const override {
            return dataSize;
        }
        
        virtual void* lock(BufferUsage::Enum) override {
            return data;
        }
        
        virtual void unlock() override {}
        
        virtual const void* lock() const override {
            return data;
        }
        
        virtual void unlock() const override {}
        
        virtual int getHandle() const override {
            return 0;
        }
        
	private:
		void* data = nullptr;
		int dataSize = 0;
	};
    
	typedef std::unique_ptr<StaticBuffer> StaticBufferPtr;
}

#endif	// __EXENG_STATIC_BUFFER_HPP__
