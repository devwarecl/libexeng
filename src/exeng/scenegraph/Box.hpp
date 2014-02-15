
#ifndef __EXENG_SCENEGRAPH_BOX_HPP__
#define __EXENG_SCENEGRAPH_BOX_HPP__

#include <exeng/math/TBoundary.hpp>

namespace exeng { namespace scenegraph {
    template<typename OtherSolid>
    exeng::math::Boxf box(const OtherSolid &solid);
    
    exeng::math::Boxf box(const exeng::math::Boxf &solid);
}}

#include <exeng/scenegraph/Box.inl>

#endif  
