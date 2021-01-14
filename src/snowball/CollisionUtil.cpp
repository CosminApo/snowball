#include "CollisionUtil.h"
#include "Renderer.h"
#include "Entity.h"

namespace snowball
{
	bool CollisionUTILS::checkXCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2)
	{
		bool rtn = false;

		float et_posX = _e1->getComponent<Transform>()->getPosition().x; // Get the X position of the Entity 1.
		float et_width = _e1->getComponent<Renderer>()->getShape()->getWidth(); // Get the width of the Entity 1.

		float eq_posX = _e2->getComponent<Transform>()->getPosition().x; // Get the X position of the Entity 2.
		float eq_width = _e2->getComponent<Renderer>()->getShape()->getWidth();  // Get the width of the Entity 2.

		/* Check for overlaps */
		if (et_posX - et_width / 2 < eq_posX + eq_width / 2)
		{
			if (et_posX + et_width / 2 > eq_posX - eq_width / 2)
			{
				rtn = true;
			}
		}

		return rtn;
	}
	bool CollisionUTILS::checkYCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2)
	{
		bool rtn = false;
		float et_posY = _e1->getComponent<Transform>()->getPosition().y; // Get the Y position of the Entity 1.
		float et_height = _e1->getComponent<Renderer>()->getShape()->getWidth(); // Get the height of the Entity 1.

		float eq_posY = _e2->getComponent<Transform>()->getPosition().y;  // Get the Y position of the Entity 2.
		float eq_height = _e2->getComponent<Renderer>()->getShape()->getWidth(); // Get the height of the Entity 1.

		/* Check for overlaps */
		if (et_posY + et_height > eq_posY - eq_height)
		{
			if (et_posY - et_height < eq_posY + eq_height)
			{
				rtn = true;
			}
		}
		return rtn;
	}
	bool CollisionUTILS::checkZCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2)
	{
		bool rtn = false;
		float et_posZ = _e1->getComponent<Transform>()->getPosition().z; // Get the Z position of the Entity 1.
		float et_depth = _e1->getComponent<Renderer>()->getShape()->getDepth(); // Get the depth of the Entity 1.

		float eq_posZ = _e2->getComponent<Transform>()->getPosition().z; // Get the Z position of the Entity 1.
		float eq_depth = _e2->getComponent<Renderer>()->getShape()->getDepth(); // Get the depth of the Entity 2.

		/* Check for overlaps */
		if (et_posZ + et_depth / 2 > eq_posZ - eq_depth / 2)
		{
			if (et_posZ - et_depth / 2 < eq_posZ + eq_depth / 2)
			{
				rtn = true;
			}
		}
		return rtn;
	}
}