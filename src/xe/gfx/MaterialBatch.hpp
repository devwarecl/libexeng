
#pragma once

#ifndef __xe_gfx_materialbatch__
#define __xe_gfx_materialbatch__

#include <xe/Object.hpp>
#include <xe/gfx/Material2.hpp>

namespace xe { namespace gfx {
	
	class EXENGAPI MaterialBatch : public Object {
	public:
		typedef std::unique_ptr<MaterialBatch> Ptr;

	public:
		virtual ~MaterialBatch();
		
		virtual int getMaterialCount() const = 0;
		virtual Material* getMaterial(const int index) = 0;
		virtual const Material* getMaterial(const int index) const = 0;
		
		virtual const MaterialFormat* getFormat() const = 0;

		virtual Buffer* getBuffer() = 0;
		virtual const Buffer* getBuffer() const = 0;
	};	
}}

#endif
