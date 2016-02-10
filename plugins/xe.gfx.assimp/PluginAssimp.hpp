
#ifndef __xe_gfx_pluginassimp_hpp__
#define __xe_gfx_pluginassimp_hpp__

#include <xe/sys/Plugin.hpp>

namespace xe { namespace gfx {
    
    class PluginAssimp : public xe::sys::Plugin {
    public:
        PluginAssimp();
        
        ~PluginAssimp();

        virtual std::string getName() const;

        virtual std::string getDescription() const;

        virtual Version getVersion() const;

        virtual void initialize(Core *core);
           
        virtual void terminate();
        
    private:
        Core *core = nullptr;
    };
}}

#endif
