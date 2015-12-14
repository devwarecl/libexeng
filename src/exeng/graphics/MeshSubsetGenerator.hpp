
#pragma once

#ifndef __exeng_graphics_meshsubsetgenerator_hpp__
#define __exeng_graphics_meshsubsetgenerator_hpp__

#include <exeng/Config.hpp>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/graphics/IndexFormat.hpp>

namespace exeng {
	class EXENGAPI Buffer;
}

namespace exeng { namespace graphics {

	class EXENGAPI VertexBuffer;
	class EXENGAPI MeshSubset;
	
	class EXENGAPI MeshSubsetGenerator {
	public:
		virtual ~MeshSubsetGenerator() {}

		virtual int getVertexBufferSize(const VertexFormat *format) const = 0;

		virtual int getIndexBufferSize(const IndexFormat::Enum format) const = 0;

		virtual void generate(MeshSubset *subset) = 0;
	};
	
	class EXENGAPI BoxGenerator : public MeshSubsetGenerator {
	public:
		virtual int getVertexBufferSize(const VertexFormat *format) const override;

		virtual int getIndexBufferSize(const IndexFormat::Enum format) const override;

		virtual void generate(MeshSubset *subset) override;

	private:
		void fillVertexBuffer(Buffer *buffer, const VertexFormat *format);

		void fillIndexBuffer(Buffer *buffer, IndexFormat::Enum indexFormat);
	};

	class EXENGAPI RectGenerator : public MeshSubsetGenerator {
	public:
		virtual int getVertexBufferSize(const VertexFormat *format) const override;

		virtual int getIndexBufferSize(const IndexFormat::Enum format) const override;

		virtual void generate(MeshSubset *subset) override;

	private:
		void fillVertices(Buffer *buffer, const VertexFormat *format);

		void fillIndices(Buffer *buffer, IndexFormat::Enum indexFormat);
	};
}}

#endif	
