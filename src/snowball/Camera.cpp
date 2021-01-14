#include "Camera.h"
#include "Core.h"
#include "Entity.h"
#include "RenderTexture.h"
#include <iostream>

namespace snowball
{
	void Camera::onInitialize()
	{
		std::shared_ptr<Camera> self = getEntity()->getComponent<Camera>(); // Initialize a pointer to it self.
		if (self == NULL) // Error checking.
		{
			std::cout << "Camera could not be created. " << std::endl;
		}
		else
		{
			getCore()->cameras.push_back(self); // Store a reference to yourself in core.
		}
	}
	void Camera::onInitialize(bool _isMain)
	{
		std::shared_ptr<Camera> self = getEntity()->getComponent<Camera>();  // Initialize a pointer to it self.
		if (self == NULL) // Error checking.
		{
			std::cout << "Camera could not be created. " << std::endl;
		}
		else
		{
			getCore()->cameras.push_back(self); // Store a reference to yourself in core.
			getCore()->setMainCamera(self); // Set this camera as the main camera.
		}
	}
	rend::mat4 Camera::getView()
	{
		return rend::inverse(getTransform()->getModelMat()); // Create a view matrix by inverting the model matrix.
	}
	std::shared_ptr<rend::RenderTexture> Camera::getRenderTexture()
	{
		return renderTexture; // Return the stored Render Texture.
	}
	void Camera::addRenderTexture()
	{
		std::shared_ptr<RenderTexture> textureLoader = getEntity()->getCore()->getRm()->load<RenderTexture>(); // Create a new Render texture using the Resource Loader.
		if (textureLoader == NULL) // Error checking.
		{
			std::cout << "Render texture could not be created. " << std::endl;
		}
		else
		{
			renderTexture = textureLoader->getTexture(); // Store the Render Texture locally.
		}
	}
}