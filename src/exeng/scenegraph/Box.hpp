
#ifndef __EXENG_SCENEGRAPH_BOX_HPP__
#define __EXENG_SCENEGRAPH_BOX_HPP__

#include <exeng/Boundary.hpp>

namespace exeng { namespace scenegraph {
    template<typename OtherSolid>
    exeng::Boxf box(const OtherSolid &solid);
    
    exeng::Boxf box(const exeng::Boxf &solid);

	 template<typename OtherSolid>
    inline exeng::Boxf box(const OtherSolid &solid) {
        return exeng::Boxf();
    }
    
    inline exeng::Boxf box(const exeng::Boxf &solid) {
        return solid;
    }

}}

#endif  
