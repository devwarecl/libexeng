
#ifndef __EXENG_EXCEPTION_HPP__
#define __EXENG_EXCEPTION_HPP__

#include <string>
#include <stdexcept>
#include <sstream>

namespace exeng {
	/**
	 * @brief Root exception.
	 */
	class Exception : public std::runtime_error {
	public:
		Exception(const std::string &msg);
		Exception(const std::string &msg, const std::string &fileName, int line);
	};
}

namespace exeng {

	namespace __private {
		inline std::string formatMessage(const std::string &msg, const std::string &fileName, int line)
		{
			std::stringstream ss;
			ss << fileName << ":" << line << ": " << msg;
			return ss.str();
		}	
	}

	inline Exception::Exception(const std::string &msg) 
		: std::runtime_error(msg)
	{
	}

	inline Exception::Exception(const std::string &msg, const std::string &functionName, int line) 
		: std::runtime_error(__private::formatMessage(msg, functionName, line))
	{
	}
}

#define EXENG_THROW_EXCEPTION(Message) throw exeng::Exception(Message, __FILE__, __LINE__)
#define EXENG_THROW(Message, ExceptionClass) throw ExceptionClass(Message, __FILE__, __LINE__)

#endif // __EXENG_EXCEPTION_HPP__
