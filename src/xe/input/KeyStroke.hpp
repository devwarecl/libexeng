
#pragma once 

#ifndef __xe_input_keystroke__
#define __xe_input_keystroke__

#include <xe/input/KeyCode.hpp>
#include <xe/input/KeyStatus.hpp>

namespace xe { namespace input {
	struct KeyStroke {
		KeyCode::Enum code = KeyCode::Unknown;
		KeyStatus::Enum status = KeyStatus::Release;

		KeyStroke() {}
		KeyStroke(KeyCode::Enum code_, KeyStatus::Enum status_) : code(code_), status(status_) {}
	};
}}

#endif 
