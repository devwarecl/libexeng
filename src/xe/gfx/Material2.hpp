
#pragma once

#ifndef __xe_gfx_material__
#define __xe_gfx_material__

#include <array>
#include <cassert>
#include <xe/DataType.hpp>
#include <xe/Buffer.hpp>
#include <xe/gfx/Texture.hpp>

namespace xe { namespace gfx {

	struct TextureFilter : public Enum {
		enum Enum {
			Nearest,
			Linear
		};
	};

	struct TextureWrapMode : public Enum {
		enum Enum {
			Repeat,
			Clamp
		};
	};

	struct MaterialLayer {
		Texture *texture = nullptr;

		TextureFilter::Enum magFilter = TextureFilter::Nearest;
		TextureFilter::Enum minFilter = TextureFilter::Nearest;

		TextureWrapMode::Enum xWrap = TextureWrapMode::Clamp;
		TextureWrapMode::Enum yWrap = TextureWrapMode::Clamp;
		TextureWrapMode::Enum zWrap = TextureWrapMode::Clamp;
		TextureWrapMode::Enum wWrap = TextureWrapMode::Clamp;
	};

	struct MaterialFormat {
		
	};

    class EXENGAPI Material : public Object {
	public:
		typedef std::unique_ptr<Material> Ptr;

    public:
		virtual ~Material() {}

		virtual const MaterialFormat* getFormat() const = 0;

		virtual std::size_t getLayerCount() const = 0;
		virtual MaterialLayer* getLayer(const int index) = 0;
		virtual const MaterialLayer* getLayer(const int index) const = 0;

        virtual Buffer* getBuffer() = 0;
        virtual const Buffer* getBuffer() const = 0;

		Texture* getTexture(const int index=0);
		const Texture* getTexture(const int index=0) const;
		void setTexture(const int index, Texture* texture);
    };
}}

#endif 
