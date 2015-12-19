
/**
 * @file VertexArray.hpp
 * @brief Defines the VertexArray template.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_GRAPHICS_VERTEXARRAY_HPP__
#define __EXENG_GRAPHICS_VERTEXARRAY_HPP__

#include <cassert>
#include <stdexcept>
#include <exeng/Config.hpp>

#include "VertexFormat.hpp"

namespace xe { namespace gfx {

	/** 
	 * @brief Aids in the manipulation of a buffer for initializing a sequence of vertices.
	 */
	class EXENGAPI VertexArray {
	public:
		VertexArray(void *data, const VertexFormat *format);

		void setAttribValue(const int index, const VertexAttrib::Enum attrib, const void *attribValue);

		void getAttribValue(const int index, const VertexAttrib::Enum attrib, void *attribValue) const;

		template<typename AttribType>
		void setValue(const int index, const VertexAttrib::Enum attrib, const AttribType &value) {
			this->setAttribValue(index, attrib, &value);
		}

	private:
		const int computeOffset(const int index, const VertexAttrib::Enum attrib) const;

		std::uint8_t* getAttribPtr(const int index, const VertexAttrib::Enum attrib);

		const std::uint8_t* getAttribPtr(const int index, const VertexAttrib::Enum attrib) const;

	private:
		std::uint8_t *data = nullptr;
		const VertexFormat *format = nullptr;
	};
}}

#endif  //__EXENG_GRAPHICS_VERTEXARRAY_HPP__
