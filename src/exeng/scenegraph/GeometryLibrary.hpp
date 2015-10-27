
#ifndef __EXENG_SCENEGRAPH_GEOMETRYLIBRARY_HPP__
#define __EXENG_SCENEGRAPH_GEOMETRYLIBRARY_HPP__

#include <memory>
#include <exeng/graphics/VertexFormat.hpp>
#include <exeng/scenegraph/Geometry.hpp>

namespace exeng { namespace scenegraph {

	class EXENGAPI GeometryLibrary {
	public:
		GeometryLibrary();
		~GeometryLibrary();

		void initialize(const exeng::graphics::VertexFormat &format);

		void addGeometry(const std::string &name, GeometryPtr geometry);

		Geometry* getGeometry(const std::string &name);

		exeng::graphics::VertexFormat getFormat() const;

	private:
		struct Private;
		Private *impl = nullptr;
	};

	typedef std::unique_ptr<GeometryLibrary> GeometryLibraryPtr;
}}

#endif	// __EXENG_SCENEGRAPH_GEOMETRYLIBRARY_HPP__
