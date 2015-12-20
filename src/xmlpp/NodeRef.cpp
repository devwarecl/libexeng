
#include "NodeRef.hpp"

namespace xmlpp {

	NodeRef::NodeRef(::xmlNode *node)
	{
		this->node = node;
	}

	std::string NodeRef::getName() const
	{
		return (const char*)(this->node->name);
	}

	std::string NodeRef::getAttribute(const std::string &attrName) const
	{
		return (const char*)(::xmlGetProp(this->node, (const xmlChar*)attrName.c_str()));
	}

	bool NodeRef::hasAttribute(const std::string &attrName) const
	{
		const void* raw = (::xmlGetProp(this->node, (const xmlChar*)attrName.c_str()));
		return raw != nullptr;
	}

	std::string NodeRef::getContent() const
	{
		return (const char*)::xmlNodeGetContent(this->node);
	}

	xmlpp::NodeRefList NodeRef::getChilds(const std::string &name) const
	{
		NodeRefList childs;

		for (::xmlNode *child = this->node->children; child; child = child->next) {
			if (child->type != XML_ELEMENT_NODE) {
				continue;
			}

			if (::xmlStrcmp(child->name, (const xmlChar*)name.c_str()) == 0) {
				childs.push_back(child);
			}
		}

		return childs;
	}

	xmlpp::NodeRefList NodeRef::getChilds() const
	{
		NodeRefList childs;

		for (::xmlNode *child = this->node->children; child; child = child->next) {
			if (child->type != XML_ELEMENT_NODE) {
				continue;
			}

			childs.push_back(child);
		}

		return childs;
	}

	xmlpp::NodeRef NodeRef::getChild(const std::string &name) const
	{
		auto &childs = this->getChilds(name);

		return *childs.begin();
	}
}
