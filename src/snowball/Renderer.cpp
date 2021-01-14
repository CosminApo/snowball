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
	}

	void Renderer::onRender()
	{
		if (getEntity()->getComponent<UIElement>()) // If its an UI object then render it as such.
		{
			std::shared_ptr<UIElement> UIobj = getEntity()->getComponent<UIElement>(); // Get a reference to the UI object.
			std::shared_ptr<Camera> cam = getCore()->getCamera(); // Get a reference to the current Camera.
			if (cam->getRenderTexture()) // If the camera has a Render Texture.
			{
				if (cam->getRenderTexture() == UIobj->getRenderTexture()) // If the Render Texture stored in the Camera 
																		  // is the same as the one stored in the UI object
				{
					glm::mat4 id(1.0f); // Create an identity matrix.
					shader->setMesh(shape); // Set the current model.
					shader->setUniform("u_View", id); // Set the view matrix to the identity matrix
					shader->setUniform("u_Model", getEntity()->getComponent<Transform>()->getModelMat()); // Get the model matrix from the Tranform Component.
					shader->setUniform("u_Projection", getEntity()->getCore()->getScreen()->getOrthoMat()); // Get the Orthographic projection matrix from the Tranform Component.
					shader->render(cam->getRenderTexture()); // Render the object on the Render Texture.
				}
			}
		}
		else // Normal rendering for 3D objects.
		{
			shader->setMesh(shape); // Set the current model.
			shader->setUniform("u_View", getEntity()->getCore()->getCamera()->getView()); // Get the view matrix from the Camera Component.
			shader->setUniform("u_Model", getEntity()->getComponent<Transform>()->getModelMat()); // Get the model matrix from the Tranform Component.
			shader->setUniform("u_Projection", getEntity()->getCore()->getScreen()->getProjMat()); // Get the Perspective projection matrix from the Tranform Component.
			shader->render(); // Render the object to the entire output.
		}
	}

	void Renderer::setModel(std::string _path)
	{
		std::shared_ptr<Model> modelLoader = getEntity()->getCore()->getRm()->load<Model>(_path); // Load the model at the specific path.
		shape = modelLoader->getModel(); // Store the model locally.
	}

	void Renderer::setShader(std::string _path)
	{
		std::shared_ptr<Shader> shaderLoader = getEntity()->getCore()->getRm()->load<Shader>(_path); // Load the shader at the specific path.
		shader = shaderLoader->getShader(); // Store the shader locally.
	}
	void Renderer::setTexture(std::string _path)
	{
		std::shared_ptr<Texture> textureLoader = getEntity()->getCore()->getRm()->load<Texture>(_path); // Load the texture at the specific path.
		tex = textureLoader->getTexture(); // Store the Texture locally.
		shape->setTexture("u_Texture", tex); //NOTE, the name is the uniform name in the shader 

	}
	std::shared_ptr<rend::Mesh> Renderer::getShape()
	{
		return shape; // Return the stored model.
	}
}