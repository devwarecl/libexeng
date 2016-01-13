
#pragma once

namespace lw {
	
	class Surface : public Collection<Surface, ::lwSurface> {
	public:
		Surface() {}
		Surface(::lwSurface *value) : Collection<Surface, ::lwSurface>(value) {}

		EParam add_trans() const {
			return EParam(&this->value->add_trans);
		}

		float alpha() const {
			return this->value->alpha;
		}

		int alpha_mode() const {
			return this->value->alpha_mode;
		}

		TParam bump() const {
			return TParam(&this->value->bump);
		}

		CParam color() const {
			return CParam(&this->value->color);
		}

		EParam color_filter() const {
			return EParam(&this->value->color_filter);
		}

		EParam color_hilite() const {
			return EParam(&this->value->color_hilite);
		}

		TParam diffuse() const {
			return TParam(&this->value->diffuse);
		}
		
		EParam dif_sharp() const {
			return EParam(&this->value->dif_sharp);
		}

		TParam eta() const {
			return TParam(&this->value->eta);
		}

		TParam glossiness() const {
			return TParam(&this->value->glossiness);
		}

		EParam glow() const {
			return EParam(&this->value->glow);
		}

		Line line() const {
			return Line(&this->value->line);
		}

		TParam luminosity() const {
			return TParam(&this->value->luminosity);
		}

		std::string name() const {
			return this->value->name;
		}

		int nshaders() const {
			return this->value->nshaders;
		}

		RMap reflection() const {
			return RMap(&this->value->reflection);
		}

		Plugin shader() const {
			return Plugin(this->value->shader);
		}

		int sideflags() const {
			return this->value->sideflags;
		}

		float smooth() const {
			return this->value->smooth;
		}

		TParam specularity() const {
			return TParam(&this->value->specularity);
		}

		std::string srcname() const {
			return this->value->srcname;
		}

		TParam translucency() const {
			return TParam(&this->value->translucency);
		}

		RMap transparency() const {
			return RMap(&this->value->transparency);
		}
	};

}
