#include "UIElement.h"
#include "Renderer.h"
#include "Entity.h"
#include "Core.h"
#include "Texture.h"
#include "Model.h"

namespace snowball
{
	void UIElement::onInitialize(std::shared_ptr<rend::RenderTexture> _renderTexture, std::string _texturePath, int _width, int _height, int _xPos, int _yPos)
	{
		self = std::make_shared<UIElement>(); // Instantiate a new object.

		/* Store parameters in the object*/
		self->isClicked = false; 
		self->self = self;
		self->width = _width;
		self->height = _height;
		self->xpos = _xPos;
		self->ypos = _yPos;
		self->renderTexture = _renderTexture;

		std::shared_ptr<Renderer> rend = getEntity()->getComponent<Renderer>(); // Gets the Renderer attached to this Entity.
		if (!rend) // Error checking to see if a renderer exists.
		{
			throw snowball::Exception("FATAL: Failed to get renderer component. Hierarchy Broke!");
		}
		rend->shape = std::make_shared<rend::Mesh>(); // Initialize the Shape attribute.

		std::shared_ptr<Model> modelLoader = getEntity()->getCore()->getRm()->load<Model>("cube.obj"); // Load the model.
		rend->shape = modelLoader->getModel(); // Store the model in the renderer.

		/* Set the properties of the model to match those of the UI element */
		getEntity()->getComponent<Transform>()->setScale(glm::vec3(_width, _height, 1.f)); 
		getEntity()->getComponent<Transform>()->setPosition(glm::vec3(_xPos + _width, _yPos + _height, 0.f));

		std::shared_ptr<Texture> textureLoader = getEntity()->getCore()->getRm()->load<Texture>(_texturePath); // Load the texture.
		rend->tex = textureLoader->getTexture(); // Store the texture in the renderer.
		rend->shape->setTexture("u_Texture", rend->tex); //NOTE, the name is the uniform name in the shader 

		getCore()->addButton(self); // Add a reference to itself to the list of UI elements of core.
	}

	std::shared_ptr<rend::RenderTexture> UIElement::getRenderTexture()
	{
		return self->renderTexture; // Return the Render Texture of this object.
	}
	int UIElement::getXpos()
	{
		return xpos; // Return the Render Texture of this object.
	}

	int UIElement::getYpos()
	{
		return ypos; // Return the Y position of this object.
	}

	int UIElement::getWidth()
	{
		return width; // Return the X position of this object.
	}

	int UIElement::getHeight()
	{
		return height; // Return the height of this object.
	}
	bool UIElement::getIsClicked()
	{
		return self->isClicked; // Return the width of this object.
	}
	void UIElement::setIsClicked(bool _isClicked)
	{
		self->isClicked = _isClicked; // Return whether this object was clicked last frame or not.
	}
}