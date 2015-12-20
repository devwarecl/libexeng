/**
 * @file Vertex.hpp
 * @brief Basic vertex structure, with coordinates, normal and texture coordinates.
 */

#pragma once

#ifndef __exeng_graphics_vertex_hpp__
#define __exeng_graphics_vertex_hpp__

#include <algorithm>
#include <vector>

#include "../Vector.hpp"
#include "VertexFormat.hpp"

namespace xe { namespace gfx {

	template<typename AttribType>
	struct Attrib {
		typedef typename AttribType attrib_type;
		typedef typename AttribType::type type;
		static const int size = AttribType::size;
		static const DataType::Enum dataType = AttribType::dataType;
	};

	template<typename AttribType>
	struct AttribCoord : public Attrib<AttribType> {

		static const VertexAttrib::Enum attrib = VertexAttrib::Position;

		AttribCoord() {}
		AttribCoord(const AttribType &value) : coord(value) {}

		AttribType coord;
	};

	template<typename AttribType>
	struct AttribNormal : public Attrib<AttribType> {
		static const VertexAttrib::Enum attrib = VertexAttrib::Normal;

		AttribNormal() {}
		AttribNormal(const AttribType &value) : coord(value) {}
	
		AttribType normal;
	};

	template<typename AttribType>
	struct AttribBinormal: public Attrib<AttribType> {
		static const VertexAttrib::Enum attrib = VertexAttrib::Binormal;

		AttribBinormal() {}
		AttribBinormal(const AttribType &value) : coord(value) {}
		
		AttribType binormal;
	};

	template<typename AttribType>
	struct AttribTangent : public Attrib<AttribType> {
		static const VertexAttrib::Enum attrib = VertexAttrib::Tangent;

		AttribTangent() {}
		AttribTangent(const AttribType &value) : coord(value) {}

		AttribType tangent;
	};

	template<typename AttribType>
	struct AttribTexCoord : public Attrib<AttribType> {
		static const VertexAttrib::Enum attrib = VertexAttrib::TexCoord;

		AttribTexCoord() {}
		AttribTexCoord(const AttribType &value) : coord(value) {}

		AttribType texCoord;
	};
	
	template<typename AttribType>
	struct AttribTexCoord2 : public Attrib<AttribType> {
		static const VertexAttrib::Enum attrib = VertexAttrib::TexCoord;

		AttribTexCoord2() {}
		AttribTexCoord2(const AttribType &value) : coord(value) {}

		AttribType texCoord2;
	};

	template<typename AttribType>
	struct AttribTexCoord3 : public Attrib<AttribType> {
		static const VertexAttrib::Enum attrib = VertexAttrib::TexCoord;

		AttribTexCoord3() {}
		AttribTexCoord3(const AttribType &value) : coord(value) {}

		AttribType texCoord3;
	};

	template<typename AttribType>
	struct AttribTexCoord4 : public Attrib<AttribType> {
		static const VertexAttrib::Enum attrib = VertexAttrib::TexCoord;

		AttribTexCoord4() {}
		AttribTexCoord4(const AttribType &value) : coord(value) {}

		AttribType texCoord4;
	};

	/*namespace detail {

		template<int index, typename ...Args>
		struct GetTypeAt {};

		template<typename Arg, typename ...Args>
		struct GetTypeAt<0, Arg, Args...> {
			using type = Arg;
		};
	}*/

	/*
	template <typename Attrib, typename ...Attribs>
	void constructFormat(std::vector<VertexField> &fields) {
		constructFormat<Attribs...>(fields);
		fields.push_back(VertexField(Attrib::attrib, Attrib::size, Attrib::dataType));
	}

	template<typename Attrib>
	void constructFormat(std::vector<VertexField> &fields) {
		fields.push_back(VertexField(Attrib::attrib, Attrib::size, Attrib::dataType));
	}
	*/
	
	
	template <int index, typename Attrib, typename ...Attribs>
	struct VertexFormatConstructor {
		static void construct(std::vector<VertexField> &fields) {
			VertexFormatConstructor<index - 1, Attribs...>::construct(fields);
			fields.push_back(VertexField(Attrib::attrib, Attrib::size, Attrib::dataType));
		}
	};

	template <typename Attrib>
	struct VertexFormatConstructor<0, Attrib> {
		static void construct(std::vector<VertexField> &fields) {
			fields.push_back(VertexField(Attrib::attrib, Attrib::size, Attrib::dataType));
		}
	};

	template <
		typename VertexAttrib, 
		typename ...VertexAttribs
	>
	struct Vertex : public VertexAttrib, public VertexAttribs... {
		Vertex() {}

		static VertexFormat getFormat() {
			std::vector<VertexField> fields;

			fields.resize(sizeof...(VertexAttribs));

			VertexFormatConstructor <
				sizeof...(VertexAttribs), 
				VertexAttrib, 
				VertexAttribs...
			>::construct(fields);

			VertexFormat format;

			for (int i=0; i<std::min(8, static_cast<int>(fields.size())); i++) {
				format.fields[i] = fields[i];
			}

			return format;
		}
	};

	typedef Vertex < 
		AttribCoord<Vector3f>,
		AttribNormal<Vector3f>,
		AttribTexCoord<Vector2f>
	> StandardVertex;

	typedef Vertex < 
		AttribCoord<Vector4f>,
		AttribTexCoord<Vector2f>
	> ScreenVertex;

	typedef Vertex < 
		AttribCoord<Vector4f>,
		AttribNormal<Vector4f>,
		AttribTexCoord<Vector4f>
	> RayTracingVertex;
}}

#endif
