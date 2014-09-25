/**
 * @file VertexBuffer.hpp
 * @brief 
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */


#ifndef __EXENG_GRAPHICS_VERTEXBUFFER_HPP__
#define __EXENG_GRAPHICS_VERTEXBUFFER_HPP__

#include <stdexcept>

#include <exeng/Buffer.hpp>
#include <exeng/Vector.hpp>
#include <exeng/graphics/VertexFormat.hpp>

namespace exeng { namespace graphics {
	// /**
	//  * @brief Buffer that stores vertex data, directly in VideoRAM.
	//  */
	// class EXENGAPI VertexBuffer : public Buffer {
	// public:
	// 	virtual ~VertexBuffer();
    // 
	// 	/**
	// 	 * @brief Get the current vertex format
	// 	 */
	// 	virtual const VertexFormat& getFormat() const = 0;
	// };
}}

#endif  //__EXENG_GRAPHICS_VERTEXBUFFER_HPP__
