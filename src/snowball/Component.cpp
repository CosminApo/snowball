#include "component.h"
#include "entity.h"

namespace snowball 
{

	void Component::tick()
	{
		onTick(); // Call to the overwritten function for handling events every tick.
	}

	void Component::render()
	{
		onRender(); // Call to the overwritten function for handling events every frame.
	}

	// Virtual functions instantiated to empty.
	void Component::onInitialize() { } 
	void Component::onTick() { }
	void Component::onRender() { }

	std::shared_ptr<Entity> Component::getEntity()
	{
		return entity.lock(); // Returns the Entity stored.
	}

	std::shared_ptr<Core> Component::getCore()
	{
		return getEntity()->getCore(); // Returns the Core stored in the linked Entity.
	}
	std::shared_ptr<Transform> Component::getTransform()
	{
		return getEntity()->getComponent<Transform>(); // Returns the Transform Component of the same Entity.
	}
}