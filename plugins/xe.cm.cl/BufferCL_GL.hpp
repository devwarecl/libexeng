
#pragma once

#ifndef __xe_cm_buffercl_gl_hpp__
#define __xe_cm_buffercl_gl_hpp__

#include <xe/Buffer.hpp>
#include <CL/cl-xe.hpp>

namespace xe { namespace cm {
    class BufferCL_GL : public xe::Buffer {
    public:
        BufferCL_GL(cl::Context context, cl_GLuint bufferId);
        
        virtual ~BufferCL_GL();
        
		virtual int getHandle() const override;

		virtual int getSize() const override;

        virtual void* lock(BufferUsage::Enum mode) override;

		virtual void unlock() override;

		virtual const void* lock() const override;

		virtual void unlock() const override;
		
		virtual TypeInfo getTypeInfo() const override;
		
		cl::BufferGL& getWrapped() {
            return buffergl;
		}
		
		const cl::BufferGL& getWrapped() const {
            return buffergl;
		}
		
	private:
        cl::BufferGL buffergl;
    };
}}

#endif // __xe_cm_buffercl_gl_hpp__
