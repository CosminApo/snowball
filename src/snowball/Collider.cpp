#include "Collider.h"

namespace snowball
{
	void Collider::onInitialize(bool _collisionEnabled)
	{
		collision = _collisionEnabled; // Sets whether collision is enabled or not.
	}
	bool Collider::getCollision()
	{
		return collision; // Returns current collision state.
	}
}