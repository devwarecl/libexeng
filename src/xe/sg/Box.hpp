
#ifndef __EXENG_SCENEGRAPH_BOX_HPP__
#define __EXENG_SCENEGRAPH_BOX_HPP__

#include <xe/Boundary.hpp>

namespace xe { namespace sg {
    template<typename OtherSolid>
    xe::Boxf box(const OtherSolid &solid);
    
    xe::Boxf box(const xe::Boxf &solid);

	template<typename OtherSolid>
    inline xe::Boxf box(const OtherSolid &solid) {
        return xe::Boxf();
    }
    
    inline xe::Boxf box(const xe::Boxf &solid) {
        return solid;
    }

}}

#endif  
