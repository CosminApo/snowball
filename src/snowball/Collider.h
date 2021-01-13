#include "Component.h"

namespace snowball
{
	struct Collider : public Component
	{
		void onInitialize(bool _collisionEnabled);
		bool getCollision();
	private:
		bool collision;
	};
}