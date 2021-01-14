#include "Component.h" /* Included for inheritance */
#include <rend/rend.h> /* rend::RenderTexture */

namespace snowball
{
	/**
	* \brief The class responsible for making an Entity a part of the UI.
	*
	* This class allows an Entity to become an UI element by acting as a flag for the renderer.
	* It also stores information about where to render the UI element, to which output
	* and with what properties.
	*/
	struct UIElement : public Component
	{
		void onInitialize(std::shared_ptr<rend::RenderTexture> _renderTexture, std::string _texturePath, int _width, int _height, int _xPos, int _yPos);  ///< Base initialize function inherited from Component. Overloaded with neccessary parameters.
		std::shared_ptr<rend::RenderTexture> getRenderTexture(); ///< Returns the stored Render Texture.
		int getXpos(); ///< Returns the X position of the UI element.
		int getYpos(); ///< Returns the Y position of the UI element.
		int getWidth(); ///< Returns the width of the UI element.
		int getHeight(); ///< Returns the height of the UI element.
		bool getIsClicked(); ///< Returns whether the UI element was clicked last frame or not.
		void setIsClicked(bool _isClicked); ///< Stores whether the UI element was clicked last frame or not.
	private:
		std::shared_ptr<rend::RenderTexture> renderTexture; ///< Stores whether the Render Texture to use as render output for the UI.
		int width, height, xpos, ypos;  ///< Stores various properties of the UI element.
		std::shared_ptr<UIElement> self; ///< Stores a smart pointer to itself. (Used as a better "this" keyword)
		bool isClicked = false; ///< Stores whether the UI element was clicked last frame or not.
	};
}