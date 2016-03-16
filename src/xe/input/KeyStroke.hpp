
#pragma once 

#ifndef __xe_input2_ed_keystroke_hpp__
#define __xe_input2_ed_keystroke_hpp__

#include <xe/input/KeyCode.hpp>
#include <xe/input/KeyStatus.hpp>

namespace xe { namespace input2 {
	struct KeyStroke {
		KeyCode::Enum code = KeyCode::Unknown;
		KeyStatus::Enum status = KeyStatus::Release;

		KeyStroke() {}
		KeyStroke(KeyCode::Enum code_, KeyStatus::Enum status_) : code(code_), status(status_) {}
	};
}}

#endif 
