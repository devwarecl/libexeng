
#include <list>
#include <xe/sys/Plugin.hpp>
#include <xe/sg/SceneLoader.hpp>

#include "xmlpp/Document.hpp"

namespace xe { namespace sg {

	class SceneLoaderXML : public SceneLoader {
	public:
		virtual ~SceneLoaderXML() {}

		virtual bool isSupported(const std::string &file) {
			return true;
		}

		virtual ScenePtr load(const std::string &file) {
			return nullptr;
		}

	private:

	};
}}
