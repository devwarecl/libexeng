
#include "InputManagerGLFW.hpp"

#include "GraphicsDriverGL3.hpp"

namespace xe { namespace gfx {

	void xe_handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_REPEAT) {
            return;
        }
        
		auto driver = static_cast<xe::gfx::gl3::GraphicsDriverGL3*>(::glfwGetWindowUserPointer(window));
		auto manager = static_cast<InputManagerGLFW*>(driver->getInputManager());

		// determine key code
		auto code = xe::input2::KeyCode::Unknown;

        switch (key) {
            case GLFW_KEY_ESCAPE:	code = xe::input2::KeyCode::KeyEsc;		break;
            case GLFW_KEY_LEFT:		code = xe::input2::KeyCode::KeyLeft;	break;
            case GLFW_KEY_RIGHT:	code = xe::input2::KeyCode::KeyRight;	break;
            case GLFW_KEY_UP:		code = xe::input2::KeyCode::KeyUp;		break;
            case GLFW_KEY_DOWN:		code = xe::input2::KeyCode::KeyDown;	break;
            case GLFW_KEY_ENTER:	code = xe::input2::KeyCode::KeyEnter;	break;
        }

		// determine key status
        auto status = xe::input2::KeyStatus::Unknown;
		
		switch (action) {
            case GLFW_RELEASE:  status = xe::input2::KeyStatus::Release;    break;
            case GLFW_PRESS:    status = xe::input2::KeyStatus::Press;      break;
		}
		
		// set the key status
		manager->getKeyboard()->getStatus()->setKeyStatus(code, status);
		
		/*
		else if (action == GLFW_REPEAT) {
			xe::input2::KeyStroke keyStroke;
			keyStroke.code = code;
			keyStroke.status = status;

			manager->getKeyboard()->getKeyStrokeEvent()->raise(keyStroke);
		}
		*/
	}

	InputManagerGLFW::InputManagerGLFW() {}

	InputManagerGLFW::InputManagerGLFW(GLFWwindow* window) {
		this->setWindow(window);
	}

	void InputManagerGLFW::poll() {
		::glfwPollEvents();
	}

	void InputManagerGLFW::setWindow(GLFWwindow *window) {
		::glfwSetKeyCallback(window, xe_handle_key);
		this->window = window;
	}
}}
