
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
		Texture();
		Texture(::lwTexture *value);

		short axis() const;

		unsigned int chan() const;

		short enabled() const;

		short negative() const;

		EParam opacity() const;

		short opac_type() const;

		std::string ord() const;

		Gradient grad() const;

		ImageMap imap() const;

		Procedural proc() const;

		TMap tmap() const;

		unsigned int type() const;
	};
}

#endif	
