
#include "Document.hpp"

namespace xmlpp {
	int Document::refCount = 0;

	Document::Document(xmlDocPtr document)
	{
		Document::refCount++;
		this->document = document;
	}

	Document::~Document()
	{
		::xmlFreeDoc(document);

		if ((--Document::refCount) == 0) {
			::xmlCleanupParser();
		}
	}

	NodeRef xmlpp::Document::GetRootNode() const
	{
		return ::xmlDocGetRootElement(document);
	}
}
