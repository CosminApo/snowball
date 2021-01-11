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
		std::shared_ptr<Renderer> rend = getEntity()->getComponent<Renderer>(); //gets the renderer attached to this object
		if (!rend)
		{
			throw snowball::Exception("Failed to get renderer component");
		}
		rend->shape = std::make_shared<rend::Mesh>();//init shape
	//	std::shared_ptr<rend::Buffer> bf = getCore()->context->createBuffer(); //init buffer
		//bf->setId(getQuadVAO());
	//	rend->shape->setBuffer("u_Model", bf);

		std::shared_ptr<Model> modelLoader = getEntity()->getCore()->getRm()->load<Model>("cube.obj"); //load model
		rend->shape = modelLoader->getModel(); //asign model
		getEntity()->getComponent<Transform>()->setScale(glm::vec3(_width, _height, 1.f));
		getEntity()->getComponent<Transform>()->setPosition(glm::vec3(_xPos, _yPos, 0.f));

		std::shared_ptr<Texture> textureLoader = getEntity()->getCore()->getRm()->load<Texture>(_texturePath);
		rend->tex = textureLoader->getTexture();
		rend->shape->setTexture("u_Texture", rend->tex); //NOTE, the name is the uniform name in the shader 
		renderTexture = _renderTexture;
		
	}
	std::shared_ptr<rend::RenderTexture> UIElement::getRenderTexture()
	{
		return renderTexture;
	}
	GLuint UIElement::getQuadVAO()
	{
		GLuint quadVAO = 0;
		GLuint quadVBO;
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		//set up vao
		glGenVertexArrays(1, &quadVAO);
		//set up vbo
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		//upload data to vbo
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		//upload data to vao
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		return quadVAO;
	}
}