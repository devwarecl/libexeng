
#pragma once

#ifndef __xe_collection_hpp__
#define __xe_collection_hpp__

#include <string>

namespace xe {
	template<typename Object, typename ObjectPtr>
	class Collection {
	public:
		Collection() {}
		~Collection() {}

		virtual int getCount() const = 0;
		virtual Object* get(const int index) const = 0;
		virtual Object* get(const std::string &name) const = 0;

		virtual void add(ObjectPtr object) = 0;
		virtual void add(ObjectPtr object, const std::string &name) = 0;

		virtual void remove(ObjectPtr object) = 0;
		virtual void remove(const std::string &name);
		virtual void remove(const int index) = 0;
	};
}

#endif
