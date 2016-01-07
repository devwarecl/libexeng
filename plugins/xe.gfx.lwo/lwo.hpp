
#pragma once

#ifndef __lw_lwo_hpp__
#define __lw_lwo_hpp__

#include <cassert>
#include <string>

#include "Collection.hpp"
#include "lwo/lwo2.h"

namespace lw {

	struct Proj {
		enum Enum {
			Planar,
			Cylindrical,
			Spherical,
			Cubic,
			Front,
			Map
		};
	};

	struct Axis {
		enum Enum {
			X, Y, Z
		};
	};

	class VMap : public Collection<VMap, ::lwVMap> {
	public:
		VMap() {}
		explicit VMap(::lwVMap *vmap) : Collection<VMap, ::lwVMap>(vmap) {}

		std::string name() const {
			return this->value->name;
		}

		int dim() const {
			return this->value->dim;
		}

		unsigned int type() const {
			return this->value->type;
		}

		VMap next() const {
			return VMap(this->value->next);
		}

		VMap prev() const {
			return VMap(this->value->prev);
		}

		int* pindex() const {
			return this->value->pindex;
		}

		VMap find(const std::string &name, unsigned int type) const {
			VMap result;

			for (const VMap &sibling : *this) {
				if (sibling.name() == name && sibling.type() == type) {
					result = sibling;
					break;
				}
			}

			if (!result && type == ID_TXUV) {
				VMap better_result = result.next().find(name, ID_TXUV);

				if (!better_result) {
					result = better_result;
				}
			}

			return result;
		}
	};

	class Clip : public Collection<Clip, ::lwClip> {
	public:
		Clip() {}
		explicit Clip(::lwClip *clip) : Collection<Clip, ::lwClip>(clip) {}

		int index() const {
			return this->value->index;
		}

		Clip find(const int index) const {
			Clip result;

			for (const Clip &clip : *this) {
				if (clip.index() == index) {
					result = clip;
					break;
				}
			}

			return result;
		}
	};

	class Layer : public Collection<Layer, ::lwLayer> {
	public:
		Layer() {}
		explicit Layer(::lwLayer *layer) : Collection<Layer, ::lwLayer>(layer) {}

		VMap vmap() const {
			return VMap(this->value->vmap);
		}

		VMap findVMap(const std::string &name, bool continuous) const {
			VMap result;

			for (VMap vmap : this->vmap()) {
				const int* pindex = vmap.pindex();
				const bool found1 = continuous && !pindex;
				const bool found2 = !continuous && pindex;
				
				if (vmap.name() == name && (found1 || found2)) {
					result = vmap;
				}
			}

			return result;
		}
	};

	class Texture : public Collection<Texture, ::lwTexture> {
	public:
		Texture() {}
		Texture(::lwTexture *value) : Collection<Texture, ::lwTexture>(value) {}
	};

	class TParam : public Wrapper<TParam, ::lwTParam> {
	public:
		TParam() {}
		TParam(::lwTParam *value) : Wrapper<TParam, ::lwTParam>(value) {}

		float val() const {
			return this->value->val;
		}

		int eindex() const {
			return this->value->eindex;
		}

		Texture tex() const {
			return Texture(this->value->tex);
		}
	};

	class VParam : public Wrapper<VParam, ::lwVParam> {
	public:
		VParam() {}
		VParam(::lwVParam *value) : Wrapper<VParam, ::lwVParam>(value) {}

		xe::Vector3f val() const {
			return xe::Vector3f(&this->value->val[0]);
		}

		int eindex() const {
			return this->value->eindex;
		}
	};

	class TMap : public Collection<TMap, ::lwTMap> {
	public:
		TMap() {}
		explicit TMap(::lwTMap *value) : Collection<TMap, ::lwTMap>(value) {}

		VParam center() const {
			return VParam(&this->value->center);
		}

		xe::Vector3f setupTexturePoint(const xe::Vector3f &point, Proj::Enum proj) {
			xe::Vector3f center(this->value->center.val); 
			xe::Vector3f ypr(this->value->rotate.val); 
			xe::Vector3f size(this->value->size.val); 

			xe::Vector3f q = point - center;

			q = xe::transform(xe::rotate<float>(ypr.z, { 0.0f, 0.0f, -1.0f}), q);
			q = xe::transform(xe::rotate<float>(ypr.y, { 0.0f, 1.0f,  0.0f}), q);
			q = xe::transform(xe::rotate<float>(ypr.x, {-1.0f, 0.0f,  0.0f}), q);

			if (proj != Proj::Spherical) {
				q = q / size;
			}

			return q;
		}

	};

	class Surface : public Collection<Surface, ::lwSurface> {
	public:
		Surface() {}
		Surface(::lwSurface *value) : Collection<Surface, ::lwSurface>(value) {}
	};

	class Object : public Wrapper<Object, ::lwObject> {
	public:
		explicit Object(lwObject *value) : Wrapper<Object, ::lwObject>(value) {}

		Surface surf() const {
			return Surface(this->value->surf);
		}

		Layer layer() const {
			return Layer(this->value->layer);
		}

		virtual ~Object() {
			if (this->value) {
				::lwFreeObject(this->value);
			}
		}
	};
}

#endif
