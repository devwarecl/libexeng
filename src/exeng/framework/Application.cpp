/**
 * @file Application.cpp
 * @brief Implementation of the Application class.
 */

/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#include "Application.hpp"

#include <exeng/util/MessageBox.hpp>

namespace exeng { namespace framework {
	using exeng::util::MessageBox;
	using exeng::util::MessageBoxIcon;

    int Application::execute(Application &app, int argc, char** argv) {
        int exitCode = 0;
        
        try {
            exitCode = app.run(argc, argv);
        } catch (std::exception &exp) {
			MessageBox::show("Caught unhandled exception", exp.what(), MessageBoxIcon::Error);
        }
        
        return exitCode;
    }
}}
