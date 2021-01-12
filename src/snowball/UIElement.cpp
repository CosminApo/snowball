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
		self = std::make_shared<UIElement>();
		self->width = _width;
		self->height = _height;
		self->xpos = _xPos;
		self->ypos = _yPos;
		std::shared_ptr<Renderer> rend = getEntity()->getComponent<Renderer>(); //gets the renderer attached to this object
		if (!rend)
		{
			throw snowball::Exception("Failed to get renderer component");
		}
		rend->shape = std::make_shared<rend::Mesh>();//init shape

		std::shared_ptr<Model> modelLoader = getEntity()->getCore()->getRm()->load<Model>("cube.obj"); //load model
		rend->shape = modelLoader->getModel(); //asign model
		getEntity()->getComponent<Transform>()->setScale(glm::vec3(_width, _height, 1.f));
		getEntity()->getComponent<Transform>()->setPosition(glm::vec3(_xPos + _width, _yPos + _height, 0.f));


		std::shared_ptr<Texture> textureLoader = getEntity()->getCore()->getRm()->load<Texture>(_texturePath);
		rend->tex = textureLoader->getTexture();
		rend->shape->setTexture("u_Texture", rend->tex); //NOTE, the name is the uniform name in the shader 
		self->renderTexture = _renderTexture;
		getCore()->addButton(self);
	}
	std::shared_ptr<rend::RenderTexture> UIElement::getRenderTexture()
	{
		return self->renderTexture;
	}

	void UIElement::onClick()
	{
		std::cout << "Hello, I am a button located at: " << xpos << " , " << ypos << std::endl;
	}

	int UIElement::getXpos()
	{
		return xpos;
	}

	int UIElement::getYpos()
	{
		return ypos;
	}

	int UIElement::getWidth()
	{
		return width;
	}

	int UIElement::getHeight()
	{
		return height;
	}
	
}