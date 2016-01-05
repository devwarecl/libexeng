
#include <xe/Core.hpp>
#include <xe/gfx/GraphicsManager.hpp>
#include <xe/sys/Plugin.hpp>

#include "ImageLoaderFI.hpp"

namespace xe { namespace gfx {

	class PluginFI : public xe::sys::Plugin {
	public:
		virtual std::string getName() const override {
			return "FreeImage-based image loader plugin.";
		}

        virtual std::string getDescription() const override {
			return "No description.";
		}

        virtual Version getVersion() const override {
			return Version(1, 0, 0, 0);
		}

        virtual void initialize(Core *core) override {
			this->imageLoader = std::make_unique<ImageLoaderFI>();
			core->getGraphicsManager()->setImageToolkit(this->imageLoader.get());
		}

        virtual void terminate() override {
			this->imageLoader.reset();
		}

	private:
		std::unique_ptr<ImageLoaderFI> imageLoader;
	};
}}

#if defined (EXENG_WINDOWS)
#  if defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#    undef EXENG_EXPORT
#  endif
#endif 

EXENG_EXPORT_PLUGIN(xe::gfx::PluginFI);
