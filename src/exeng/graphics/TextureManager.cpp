
#include "TextureManager.hpp"

namespace exeng { namespace graphics {

	GraphicsDriver* TextureManager::getGraphicsDriver()
	{
		return this->graphicsDriver;
	}

	const GraphicsDriver* TextureManager::getGraphicsDriver() const
	{
		return this->graphicsDriver;
	}

	void TextureManager::setGraphicsDriver(GraphicsDriver *graphicsDriver)
	{
		for (ResourceLoader* resourceLoader : this->getLoaders()) {
			TextureLoader* textureLoader = static_cast<TextureLoader*>(resourceLoader);
			textureLoader->setGraphicsDriver(graphicsDriver);
		}
		
		this->graphicsDriver = graphicsDriver;
	}

	Texture* TextureManager::get(const std::string &uri)
	{
		return static_cast<Texture*>(ResourceManager::get(uri));
	}

	const Texture* TextureManager::get(const std::string &uri) const
	{
		return static_cast<const Texture*>(ResourceManager::get(uri));
	}

	void TextureManager::addLoader(TextureLoader *loader)
	{
		ResourceManager::addLoader(loader);
		loader->setGraphicsDriver(this->graphicsDriver);
	}

	void TextureManager::removeLoader(TextureLoader *loader)
	{
		ResourceManager::removeLoader(loader);
	}
}}
