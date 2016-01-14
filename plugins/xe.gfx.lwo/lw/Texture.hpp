
#pragma once

#ifndef __lw_texture_hpp__
#define __lw_texture_hpp__

#include <string>
#include "Collection.hpp"
#include "EParam.hpp"
#include "Gradient.hpp"
#include "ImageMap.hpp"
#include "Procedural.hpp"
#include "TMap.hpp"

namespace lw {
	
	class Texture : public Collection<Texture, ::lwTexture> {
	public:
		Texture() {}
		Texture(::lwTexture *value) : Collection<Texture, ::lwTexture>(value) {}

		short axis() const {
			return this->value->axis;
		}

		unsigned int chan() const {
			return this->value->chan;
		}

		short enabled() const {
			return this->value->enabled;
		}

		short negative() const {
			return this->value->negative;
		}

		EParam opacity() const {
			return EParam(&this->value->opacity);
		}

		short opac_type() const {
			return this->value->opac_type;
		}

		std::string ord() const {
			return this->value->ord;
		}

		Gradient grad() const {
			return Gradient(&this->value->param.grad);
		}

		ImageMap imap() const {
			return ImageMap(&this->value->param.imap);
		}

		Procedural proc() const {
			return Procedural(&this->value->param.proc);
		}

		TMap tmap() const {
			return TMap(&this->value->tmap);
		}

		unsigned int type() const {
			return this->value->type;
		}
	};
}

#endif	
