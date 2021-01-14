#include <memory> /* smart pointers */


namespace snowball
{
	struct Entity;
	struct CollisionUTILS
	{
		static bool checkXCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2); ///< Checks for collision in the X axis.
		static bool checkYCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2); ///< Checks for collision in the Y axis.
		static bool checkZCollision(std::shared_ptr<Entity> _e1, std::shared_ptr<Entity> _e2); ///< Checks for collision in the Z axis.
	};
}