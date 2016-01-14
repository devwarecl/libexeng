
#include "Surface.hpp"

namespace lw {
	Surface::Surface() {}
	Surface::Surface(::lwSurface *value) : Collection<Surface, ::lwSurface>(value) {}

	EParam Surface::add_trans() const {
		return EParam(&this->value->add_trans);
	}

	float Surface::alpha() const {
		return this->value->alpha;
	}

	int Surface::alpha_mode() const {
		return this->value->alpha_mode;
	}

	TParam Surface::bump() const {
		return TParam(&this->value->bump);
	}

	CParam Surface::color() const {
		return CParam(&this->value->color);
	}

	EParam Surface::color_filter() const {
		return EParam(&this->value->color_filter);
	}

	EParam Surface::color_hilite() const {
		return EParam(&this->value->color_hilite);
	}

	TParam Surface::diffuse() const {
		return TParam(&this->value->diffuse);
	}
		
	EParam Surface::dif_sharp() const {
		return EParam(&this->value->dif_sharp);
	}

	TParam Surface::eta() const {
		return TParam(&this->value->eta);
	}

	TParam Surface::glossiness() const {
		return TParam(&this->value->glossiness);
	}

	EParam Surface::glow() const {
		return EParam(&this->value->glow);
	}

	Line Surface::line() const {
		return Line(&this->value->line);
	}

	TParam Surface::luminosity() const {
		return TParam(&this->value->luminosity);
	}

	std::string Surface::name() const {
		return this->value->name;
	}

	int Surface::nshaders() const {
		return this->value->nshaders;
	}

	RMap Surface::reflection() const {
		return RMap(&this->value->reflection);
	}

	Plugin Surface::shader() const {
		return Plugin(this->value->shader);
	}

	int Surface::sideflags() const {
		return this->value->sideflags;
	}

	float Surface::smooth() const {
		return this->value->smooth;
	}

	TParam Surface::specularity() const {
		return TParam(&this->value->specularity);
	}

	std::string Surface::srcname() const {
		return this->value->srcname;
	}

	TParam Surface::translucency() const {
		return TParam(&this->value->translucency);
	}

	RMap Surface::transparency() const {
		return RMap(&this->value->transparency);
	}
}
