#include "Camera.h"
#include "Core.h"
#include "Entity.h"

namespace snowball
{
	void Camera::onInitialize()
	{
		std::shared_ptr<Camera> self = getEntity()->getComponent<Camera>();
		getCore()->cameras.push_back(self);
	}
	void Camera::onInitialize(bool _isMain)
	{
		std::shared_ptr<Camera> self = getEntity()->getComponent<Camera>();
		getCore()->cameras.push_back(self);
		getCore()->setMainCamera(self);
	}
	rend::mat4 Camera::getView()
	{
		return  rend::inverse(getTransform()->getModelMat());		
	}
}