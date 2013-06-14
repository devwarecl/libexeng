/**
 * @file 
 * @brief Definition of the Application class.
 */

/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_MAIN_HPP__
#define __EXENG_FRAMEWORK_MAIN_HPP__

#include <exeng/Config.hpp>
#include <exeng/framework/Application.hpp>

namespace exeng {
namespace framework {
template<typename AppClass>
int RunApplication(const StringVector &cmdLine) {
    return Application::run( new AppClass(), cmdLine );
}

}
}

#define EXENG_IMPLEMENT_MAIN(AppClass)          \
int main(int argc, char** argv) {               \
    using namespace exeng;                      \
    using namespace exeng::framework;           \
    StringVector cmdLine;                       \
    cmdLine.reserve(argc);                      \
    cmdLine.resize(argc);                       \
    for(int i=0; i<argc; ++i) {                 \
        cmdLine[i] = std::string(argv[i]);      \
    }                                           \
    return RunApplication<AppClass>(cmdLine);   \
}
    
#endif 
