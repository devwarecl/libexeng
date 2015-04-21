/*
 * Copyright (c) 2013-2014 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
#define __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__

#include <exeng/framework/Application.hpp>
#include <exeng/Timer.hpp>

namespace exeng { namespace framework {
    /**
     * @brief Basic application skeleton for graphics-based multimedia applications.
     */
    class EXENGAPI GraphicsApplication : public Application {
    public:
		GraphicsApplication() {}
        
		virtual ~GraphicsApplication() {}
        
        virtual int run(int argc, char **argv) override;

		virtual ApplicationStatus::Enum getApplicationStatus() const override {
			return this->applicationStatus;
		}

    protected:
		inline void setExitCode(int code) {
			this->exitCode = code;
		}

        inline int getExitCode() const {
			return this->exitCode;
		}

		inline void setApplicationStatus(ApplicationStatus::Enum status) {
			this->applicationStatus = status;
		}
        
	public:
		virtual void initialize(int argc, char **argv) {}
		virtual void terminate() {}
        
		virtual void pollEvents() {}
        
		virtual void update(float frameTime) {}
        
		virtual void render() {}

	private:
		int exitCode = 0;
		ApplicationStatus::Enum applicationStatus = ApplicationStatus::Terminated;
    };
}}

#endif // __EXENG_FRAMEWORK_GRAPHICSAPPLICATION_HPP__
