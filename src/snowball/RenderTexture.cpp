#include "RenderTexture.h"
#include "ResourceManager.h"
#include "Core.h"

namespace snowball
{
	void RenderTexture::onLoad()
	{
		tex = getRm()->getCore()->context->createRenderTexture(); // Create a Render Texture using Rend.
	}
	std::shared_ptr<rend::RenderTexture> RenderTexture::getTexture()
	{
		return tex; // Return the stored Render Texture.
	}
}