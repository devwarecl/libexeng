
#pragma once

#ifndef __XMLPP_DOCUMENT_HPP__
#define __XMLPP_DOCUMENT_HPP__

#include <libxml/parser.h>
#include "NodeRef.hpp"

namespace xmlpp {

	class Document {
	public:
		Document(xmlDocPtr document);

		~Document();

		NodeRef GetRootNode() const;

	private:
		xmlDocPtr document = nullptr;

	private:
		static int refCount;
	};
}

#endif
