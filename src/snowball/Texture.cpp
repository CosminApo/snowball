#include "Texture.h"
#include <iostream>
#include <fstream>
#include "ResourceManager.h"
#include "Core.h"

namespace snowball
{

	void Texture::onLoad(const std::string _path)
	{
		
		tex = getRm()->getCore()->context->createTexture(_path);
		
	}
	std::shared_ptr<rend::Texture> Texture::getTexture()
	{
		return tex;
	}
}