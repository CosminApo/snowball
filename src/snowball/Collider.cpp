#include "Collider.h"
#include "Entity.h"

namespace snowball
{
	void Collider::onInitialize(bool _collisionEnabled)
	{
		collision = _collisionEnabled; // Sets whether collision is enabled or not.
		getEntity()->setCollider(true); // Enables the collider in the Entity.
	}
	bool Collider::getCollision()
	{
		return collision; // Returns current collision state.
	}
}