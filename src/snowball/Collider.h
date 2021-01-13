#include "Component.h"

namespace snowball
{
	struct Collider : public Component
	{
		void onInitialize(bool _collisionEnabled);
		bool getCollision();
		virtual void onCollision() = 0;
	private:
		bool collision;
	};
}