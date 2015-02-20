
#ifndef __EXENG_RESOURCELOADER_HPP__
#define __EXENG_RESOURCELOADER_HPP__

#include <memory>
#include <string>
#include <exeng/Config.hpp>
#include <exeng/Resource.hpp>

namespace exeng {
	/**
	 * @brief Resource loader interface.
	 */
	class EXENGAPI ResourceLoader {
	public:
		virtual ~ResourceLoader();

		virtual bool tryLoad(const std::string &filename) = 0;
		virtual std::unique_ptr<Resource> load(const std::string &filename) = 0;
	};
}

#endif
