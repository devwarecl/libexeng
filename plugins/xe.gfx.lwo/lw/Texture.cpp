
#include "Texture.hpp"

namespace lw {

	Texture::Texture() {}
	Texture::Texture(::lwTexture *value) : Collection<Texture, ::lwTexture>(value) {}

	short Texture::axis() const {
		return this->value->axis;
	}

	unsigned int Texture::chan() const {
		return this->value->chan;
	}

	short Texture::enabled() const {
		return this->value->enabled;
	}

	short Texture::negative() const {
		return this->value->negative;
	}

	EParam Texture::opacity() const {
		return EParam(&this->value->opacity);
	}

	short Texture::opac_type() const {
		return this->value->opac_type;
	}

	std::string Texture::ord() const {
		return this->value->ord;
	}

	Gradient Texture::grad() const {
		return Gradient(&this->value->param.grad);
	}

	ImageMap Texture::imap() const {
		return ImageMap(&this->value->param.imap);
	}

	Procedural Texture::proc() const {
		return Procedural(&this->value->param.proc);
	}

	TMap Texture::tmap() const {
		return TMap(&this->value->tmap);
	}

	unsigned int Texture::type() const {
		return this->value->type;
	}
}
