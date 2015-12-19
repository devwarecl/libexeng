
#include "TextureLoader.hpp"

namespace xe { namespace gfx {
	TextureLoader::TextureLoader() {}
	
	TextureLoader::TextureLoader(GraphicsDriver *graphicsDriver) {
		this->setGraphicsDriver(graphicsDriver);
	}

	void TextureLoader::setGraphicsDriver(GraphicsDriver *graphicsDriver) {
		this->graphicsDriver = graphicsDriver;
	}

	GraphicsDriver* TextureLoader::getGraphicsDriver() {
		return this->graphicsDriver;
	}

	const GraphicsDriver* TextureLoader::getGraphicsDriver() const {
		return this->graphicsDriver;
	}
}}
