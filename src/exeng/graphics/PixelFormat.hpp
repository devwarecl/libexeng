
#ifndef __EXENG_GRAPHICS_PIXELFORMAT_HPP__
#define __EXENG_GRAPHICS_PIXELFORMAT_HPP__

#include "../Config.hpp"

namespace exeng {
    namespace graphics {
        
        enum class ColorFormat {
            Unknown,
            R8G8B8,
            R8G8B8A8,
            R8G8B8X8,
            R5G5B5X1,
            R5G5B5A1,
            R5G6B5,
            B8G8R8,
            B8G8R8A8,
            B8G8R8X8,
            L8,
            L8A8
        };
        
        // extern int EXENGAPI getPitch(ColorFormat::Type pf);
        
        //!
        enum class DepthFormat {
            Unknown,
            D8,
            D16,
            D24,
            D32
        };
        
        //!
        enum class StencilFormat {
            Unknown,
            S8,
            S16,
            S24,
            S32
        };
        
        
        //!
        struct PixelFormat {
        public:
			PixelFormat() {}
            
			/*
            //!
            PixelFormat(ColorFormat::Type color, DepthFormat::Type depth, StencilFormat::Type stencil);
            
            //!
            void SetColorFormat(ColorFormat::Type color);
            
            //!
            void SetDepthFormat(DepthFormat::Type depth);
            
            //!
            void SetStencilFormat(StencilFormat::Type stencil);
            
            //!
            ColorFormat::Type GetColorFormat() const;
            
            //!
            DepthFormat::Type  GetDepthFormat() const;
            
            //!
            StencilFormat::Type GetStencilFormat() const;
            
            //!
            int GetStorage() const;
			
            
            ColorFormat::Type   color;
            DepthFormat::Type   depth;
            StencilFormat::Type stencil;
            */
        };
    }
}

#endif  //__EXENG_GRAPHICS_PIXELFORMAT_HPP__
