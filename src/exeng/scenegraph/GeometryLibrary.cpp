
#include "GeometryLibrary.hpp"

#include <cassert>
#include <map>

namespace exeng { namespace scenegraph {
	using namespace exeng::graphics;

	struct GeometryLibrary::Private {
		std::map<std::string, GeometryPtr> geometries;
		VertexFormat format;
	};

	GeometryLibrary::GeometryLibrary() {
		this->impl = new GeometryLibrary::Private();
	}

	GeometryLibrary::~GeometryLibrary() {
		delete this->impl;
	}

	void GeometryLibrary::initialize(const VertexFormat &format) {
		assert(this->impl != nullptr);

		this->impl->geometries = std::map<std::string, GeometryPtr>();
		this->impl->format = format;
	}

	void GeometryLibrary::addGeometry(const std::string &name, GeometryPtr geometry) {
		assert(this->impl != nullptr);

		this->impl->geometries[name] = std::move(geometry);
	}

	Geometry* GeometryLibrary::getGeometry(const std::string &name) {
		assert(this->impl != nullptr);

		return this->impl->geometries[name].get();
	}

	VertexFormat GeometryLibrary::getFormat() const {
		assert(this->impl != nullptr);

		return this->impl->format;
	}
}}
