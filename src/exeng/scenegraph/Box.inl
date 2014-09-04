
namespace exeng { namespace scenegraph {
    template<typename OtherSolid>
    inline exeng::Boxf box(const OtherSolid &solid) {
        return exeng::Boxf();
    }
    
    inline exeng::Boxf box(const exeng::Boxf &solid) {
        return solid;
    }
}}
