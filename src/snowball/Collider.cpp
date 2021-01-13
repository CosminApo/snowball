#include "Collider.h"

namespace snowball
{
	void Collider::onInitialize(bool _collisionEnabled)
	{
		collision = _collisionEnabled;
	}
	bool Collider::getCollision()
	{
		return collision;
	}
}