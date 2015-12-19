
#include <exeng/ISerializable.hpp>

namespace xe {
    ISerializable::~ISerializable() {}
    
    bool ISerializable::isReadable() const {
        return false;
    }
    
    
    bool ISerializable::isWritable() const {
        return false;
    }
}
