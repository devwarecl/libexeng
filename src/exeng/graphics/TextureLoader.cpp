
#include "TextureLoader.hpp"

namespace exeng { namespace graphics {

	TextureLoader::TextureLoader() {}
	
	TextureLoader::TextureLoader(GraphicsDriver *graphicsDriver)
	{
		this->setGraphicsDriver(graphicsDriver);
	}

	void TextureLoader::setGraphicsDriver(GraphicsDriver *graphicsDriver)
	{
		this->graphicsDriver = graphicsDriver;
	}

	GraphicsDriver* TextureLoader::getGraphicsDriver()
	{
		return this->graphicsDriver;
	}
}}
