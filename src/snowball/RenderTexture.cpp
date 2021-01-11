#include "RenderTexture.h"
#include "ResourceManager.h"
#include "Core.h"

namespace snowball
{
	void RenderTexture::onLoad(const std::string _path)
	{
		tex = getRm()->getCore()->context->createRenderTexture();
	}
	std::shared_ptr<rend::RenderTexture> RenderTexture::getTexture()
	{
		return tex;
	}
}