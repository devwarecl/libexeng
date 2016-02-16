
#pragma once

#ifndef __xe_gfx_inputmanagerglfw_hpp__
#define __xe_gfx_inputmanagerglfw_hpp__

#include <memory>
#include <xe/input2/IInputManager.hpp>
#include <xe/input2/Event.hpp>

#include "GL3.hpp"
#include <GLFW/glfw3.h>

namespace xe { namespace gfx {

	class KeyboardGLFW : public xe::input2::IKeyboard {
	public:
		KeyboardGLFW() {}

		virtual ~KeyboardGLFW() {}

		virtual xe::input2::KeyboardStatus* getStatus() override {
			return &status;
		}

		virtual const xe::input2::KeyboardStatus* getStatus() const override {
			return &status;
		}

		virtual xe::input2::IEvent<xe::input2::KeyStroke>* getKeyStrokeEvent() override {
			return &keyStrokeEvent;
		}

		virtual void poll() override {}

		xe::input2::KeyboardStatus status;
		xe::input2::Event<xe::input2::KeyStroke> keyStrokeEvent;
	};

	class MouseGLFW : public xe::input2::IMouse {
	public:
		virtual xe::input2::MouseStatus getStatus() override {
			return status;
		}

		virtual void poll() override {}

		xe::input2::MouseStatus status;
	};

	class InputManagerGLFW : public xe::input2::IInputManager {
	public:
		InputManagerGLFW();
		explicit InputManagerGLFW(GLFWwindow* window);

		virtual ~InputManagerGLFW() {}

		virtual KeyboardGLFW* getKeyboard() override {
			return &keyboard;
		}

		virtual MouseGLFW* getMouse() override {
			return &mouse;
		}

		void setWindow(GLFWwindow *window);

		GLFWwindow* getWindow() {
			return this->window;
		}

		const GLFWwindow* getWindow() const {
			return this->window;
		}

		virtual void poll() override;

	private:
		GLFWwindow *window = nullptr;
		KeyboardGLFW keyboard;
		MouseGLFW mouse;
	};
}}

#endif 
