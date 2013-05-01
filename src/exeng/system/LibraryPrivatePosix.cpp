
#include "../DetectEnv.hpp"
#include "LibraryPrivate.hpp"

#if defined(EXENG_LINUX) || defined(EXENG_UNIX)

namespace exeng {
    namespace system {
        Library::Private::Private() {
        }


        void Library::Private::load(const std::string &name) {
        }


        void Library::Private::unload() {
        }


        FunctionPtr Library::Private::getFunctionPtr(const std::string &name) {
			return nullptr;
        }
    }
}

#endif
