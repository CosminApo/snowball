#include "Component.h"
#include <rend/rend.h>

namespace snowball
{
	struct UIElement : public Component
	{
		void onInitialize(std::shared_ptr<rend::RenderTexture> _renderTexture, std::string _texturePath, int _width, int _height, int _xPos, int _yPos);
		std::shared_ptr<rend::RenderTexture> getRenderTexture();
	private:
		GLuint getQuadVAO();
		std::shared_ptr<rend::RenderTexture> renderTexture;
	};
}