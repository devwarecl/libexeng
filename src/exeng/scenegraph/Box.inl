
namespace exeng { namespace scenegraph {
    template<typename OtherSolid>
    exeng::math::Boxf box(const OtherSolid &solid) {
        return exeng::math::Boxf();
    }
    
    exeng::math::Boxf box(const exeng::math::Boxf &solid) {
        return solid;
    }
}}
