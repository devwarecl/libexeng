
#include "MessageBox.hpp"
#include <xe/Config.hpp>

#if defined(EXENG_WINDOWS)
#  include <Windows.h>
#  undef MessageBox
#else 
#  include <iostream>
#endif

namespace xe { namespace util {
#if defined(EXENG_WINDOWS)
	void MessageBox::show(const std::string &title, const std::string &message, MessageBoxIcon::Enum icon)
	{
		UINT flags = MB_OK;
		switch (icon) {
			case MessageBoxIcon::Information:	flags |= MB_ICONINFORMATION;	break;
			case MessageBoxIcon::Exclamation:	flags |= MB_ICONEXCLAMATION;	break;
			case MessageBoxIcon::Error:			flags |= MB_ICONERROR;			break;
		}

		::MessageBoxA(NULL, message.c_str(), title.c_str(), flags);
	}
#else 
	void MessageBox::show(const std::string &title, const std::string &message, MessageBoxIcon::Enum icon)
	{
		std::string iconStr;

		switch (icon) {
			case MessageBoxIcon::Information:	iconStr = "[Information]";	break;
			case MessageBoxIcon::Exclamation:	iconStr = "[Exclamation]";	break;
			case MessageBoxIcon::Error:			iconStr = "[Error]      ";	break;
		}

		std::cout << title << " " << iconStr << ": " << message << std::endl;
	}
#endif
}}
