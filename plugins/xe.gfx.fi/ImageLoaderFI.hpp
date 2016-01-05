
#ifndef __xe_gfx_imageloaderfi_hpp__
#define __xe_gfx_imageloaderfi_hpp__

#include <xe/ProductManagerImpl.hpp>
#include <xe/gfx/ImageLoader.hpp>

namespace xe { namespace gfx {

	class ImageLoaderFI : public ImageLoader {
	public:
		ImageLoaderFI();

		virtual ~ImageLoaderFI();

		virtual Image* getImage(const std::string &uri) override;

		virtual const Image* getImage(const std::string &uri) const override;

		ImagePtr load(const std::string &uri);

		bool isSupported(const std::string &uri);

	private:
		ProductManagerImpl<ImageLoaderFI, Image> manager;
	};
}}

#endif 
