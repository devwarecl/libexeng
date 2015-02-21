
#ifndef __EXENG_EXCEPTION_HPP__
#define __EXENG_EXCEPTION_HPP__

#include <string>
#include <stdexcept>

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

#define EXENG_THROW_EXCEPTION(Message) throw exeng::Exception(Message, __FILE__, __LINE__)
#define EXENG_THROW(Message, ExceptionClass) throw ExceptionClass(Message, __FILE__, __LINE__)

#endif // __EXENG_EXCEPTION_HPP__
