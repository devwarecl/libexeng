
#pragma once

#ifndef __XMLPP_NODE_HPP__
#define __XMLPP_NODE_HPP__

#include <list>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <libxml/parser.h>
#include <libxml/tree.h>

namespace xmlpp {

    template<typename Type>
    struct ArrayParser {
        static std::vector<Type> parse(const std::string &content, const std::string &separator) {
            std::vector<std::string> splitted;

            boost::split(splitted, content, boost::is_any_of(separator));

            std::vector<Type> values;
            for (int i=0; i<static_cast<int>(splitted.size()); ++i) {
                values[i] = boost::lexical_cast<Type>(splitted[i]);
            }

            return values;
        }
    };

    template<>
    struct ArrayParser<std::string> {
        static std::vector<std::string> parse(const std::string &content, const std::string &separator) {
            std::vector<std::string> splitted;

            boost::split(splitted, content, boost::is_any_of(separator));

            return splitted;
        }
    };

	class NodeRef;
	typedef std::list<NodeRef> NodeRefList;

	class NodeRef {
	public:
		NodeRef(::xmlNode *node);

		std::string getName() const;

		std::string getAttribute(const std::string &attrName) const;

		bool hasAttribute(const std::string &attrName) const;

		std::string getContent() const;

		NodeRefList getChilds() const;

		NodeRefList getChilds(const std::string &name) const;

		NodeRef getChild(const std::string &name) const;

		template<typename Type>
		std::vector<Type> getAttribute(const std::string &name, const std::string &separator) const {
			std::string attribute = this->getAttribute(name);
			std::vector<Type> result = ArrayParser<Type>::parse(attribute, separator);

			return result;
		}

		template<typename Type>
		Type getAttribute(const std::string &name) const {
			std::string attribute = this->getAttribute(name);
			Type result = boost::lexical_cast<Type>(attribute);
			
			return result;
		}

	private:
		::xmlNode *node = nullptr;
	};

}

#endif	
