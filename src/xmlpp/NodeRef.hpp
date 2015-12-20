
#pragma once

#ifndef __XMLPP_NODE_HPP__
#define __XMLPP_NODE_HPP__

#include <list>
#include <libxml/parser.h>
#include <libxml/tree.h>

namespace xmlpp {
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

	private:
		::xmlNode *node = nullptr;
	};
}

#endif	
