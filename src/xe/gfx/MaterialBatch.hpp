
#pragma once

#ifndef __xe_gfx_materialbatch_hpp__
#define __xe_gfx_materialbatch_hpp__

#include <xe/Object.hpp>
#include <xe/gfx/Forward.hpp>

namespace xe { namespace gfx {
	
	class EXENGAPI MaterialBatch : public Object {
	public:
		virtual ~MaterialBatch();
		
		virtual int getMaterialCount() const = 0;
		virtual Material2* getMaterial(const int index) = 0;
		virtual const Material2* getMaterial(const int index) const = 0;
		
		virtual const MaterialFormat2* getFormat() const = 0;
	};

	typedef std::unique_ptr<MaterialBatch> MaterialBatchPtr;
}}

#endif
