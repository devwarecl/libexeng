
namespace exeng { namespace scenegraph {
    template<typename OtherSolid>
    inline exeng::math::Boxf box(const OtherSolid &solid) {
        return exeng::math::Boxf();
    }
    
    inline exeng::math::Boxf box(const exeng::math::Boxf &solid) {
        return solid;
    }
}}
