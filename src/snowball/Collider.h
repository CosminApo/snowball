#include "Component.h" /* Included for inheritance */

namespace snowball
{
	/**
	* \brief The class responsible for enabling Bounding Box collision detection.
	*  
	* This class is used to enable collision for specific entities.
	*/
	struct Collider : public Component
	{
		void onInitialize(bool _collisionEnabled); ///< Base initialize function inherited from Component. Used for creating the object.
		bool getCollision(); ///< Returns true if collision is enabled, false if not.
		virtual void onCollision() = 0; ///< Function that handles events on collision. To be overwritten in child classes. 
	private:
		bool collision; ///< Stores true is collision is enabled, false if otherwise.
	};
}