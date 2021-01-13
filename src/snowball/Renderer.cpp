#include "renderer.h"
#include "core.h"
#include "entity.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "UIElement.h"

namespace snowball
{
	void Renderer::onInitialize()
	{
		std::cout << "Initializing..." << std::endl;
	}

	void Renderer::onRender()
	{


		if (getEntity()->getComponent<UIElement>()) //if its an UI object then render it as such
		{
			std::shared_ptr<UIElement> UIobj = getEntity()->getComponent<UIElement>();
			std::shared_ptr<Camera> cam = getCore()->getCamera();
			if (cam->getRenderTexture())
			{
				if (cam->getRenderTexture() == UIobj->getRenderTexture())
				{
					glm::mat4 id(1.0f);
					shader->setMesh(shape);
					shader->setUniform("u_View", id);
					shader->setUniform("u_Model", getEntity()->getComponent<Transform>()->getModelMat());
					shader->setUniform("u_Projection", getEntity()->getCore()->getScreen()->getOrthoMat());
					shader->render(cam->getRenderTexture());
				}
			
			}
		}
		else //normal rendering for 3D models
		{
			shader->setMesh(shape);
			shader->setUniform("u_View", getEntity()->getCore()->getCamera()->getView());
			shader->setUniform("u_Model", getEntity()->getComponent<Transform>()->getModelMat());
			shader->setUniform("u_Projection", getEntity()->getCore()->getScreen()->getProjMat());
			std::shared_ptr<Camera> cam = getCore()->getCamera();
			shader->render();


		}



	}

	void Renderer::setModel(std::string _path)
	{
		std::shared_ptr<Model> modelLoader = getEntity()->getCore()->getRm()->load<Model>(_path); //load model
		shape = modelLoader->getModel(); //asign model
	}

	void Renderer::setShader(std::string _path)
	{
		std::shared_ptr<Shader> shaderLoader = getEntity()->getCore()->getRm()->load<Shader>(_path);
		shader = shaderLoader->getShader();
	}
	void Renderer::setTexture(std::string _path)
	{
		std::shared_ptr<Texture> textureLoader = getEntity()->getCore()->getRm()->load<Texture>(_path);
		tex = textureLoader->getTexture();
		shape->setTexture("u_Texture", tex); //NOTE, the name is the uniform name in the shader 

	}
	std::shared_ptr<rend::Mesh> Renderer::getShape()
	{
		return shape;
	}
}