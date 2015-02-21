
#include "Exception.hpp"

#include <sstream>

namespace exeng {

	std::string formatMessage(const std::string &msg, const std::string &fileName, int line)
	{
		std::stringstream ss;
		ss << fileName << ":" << line << ": " << msg;
		return ss.str();
	}

	Exception::Exception(const std::string &msg) 
		: std::runtime_error(msg)
	{
	}

	Exception::Exception(const std::string &msg, const std::string &functionName, int line) 
		: std::runtime_error(formatMessage(msg, functionName, line))
	{
	}
}
