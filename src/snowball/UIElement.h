#include "Component.h"
#include <rend/rend.h>

namespace snowball
{

	struct UIElement : public Component
	{
		void onInitialize(std::shared_ptr<rend::RenderTexture> _renderTexture, std::string _texturePath, int _width, int _height, int _xPos, int _yPos);
		std::shared_ptr<rend::RenderTexture> getRenderTexture();
		int getXpos();
		int getYpos();
		int getWidth();
		int getHeight();
		bool getIsClicked();
		void setIsClicked(bool _isClicked);
	private:
		std::shared_ptr<rend::RenderTexture> renderTexture;
		int width, height, xpos, ypos;
		std::shared_ptr<UIElement> self;
		bool isClicked = false;
	};
}