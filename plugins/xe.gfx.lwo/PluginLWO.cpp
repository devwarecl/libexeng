
#include <xe/sys/Plugin.hpp>

namespace xe { namespace gfx {

	class PluginLWO : public xe::sys::Plugin {
	public:
		virtual std::string getName() const override {
			return "LWO Mesh Loader Plugin";
		}

        virtual std::string getDescription() const override {
			return "Loads static meshes stored in Lightwave Object (.lwo) binary files.";
		}

        virtual Version getVersion() const override {
			return Version(1, 0, 0, 0);
		}

        virtual void initialize(Core *core) override {
			
		}

        virtual void terminate() override {
			
		}
	};
}}


#if defined (EXENG_WINDOWS)
#  if defined (EXENG_64)
#    pragma comment (linker, "/export:ExengGetPluginObject")
#    undef EXENG_EXPORT
#  endif
#endif 

EXENG_EXPORT_PLUGIN(xe::gfx::PluginLWO);
