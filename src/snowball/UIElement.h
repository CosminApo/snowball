#include "Component.h"
#include <rend/rend.h>

namespace snowball
{
	struct UIElement : public Component
	{
		void onInitialize(std::shared_ptr<rend::RenderTexture> _renderTexture, std::string _texturePath, int _width, int _height, int _xPos, int _yPos);
		std::shared_ptr<rend::RenderTexture> getRenderTexture();
		void onClick();
		int getXpos();
		int getYpos();
		int getWidth();
		int getHeight();
	private:
		std::shared_ptr<rend::RenderTexture> renderTexture;
		int width, height, xpos, ypos;
		std::shared_ptr<UIElement> self;
	};
}