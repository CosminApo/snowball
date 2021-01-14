#include "component.h" /* Included for inheritance */


namespace snowball
{
	/**
	* \brief Provides a base class for a Player object.
	*
	* The player class has some special interaction with other Components, therfore
	* a base class is provided.
	*/
	struct Player : public Component
	{
		void onInitialize(); ///< Base initialize function inherited from Component. Used for creating the object.
		void onTick(); ///< Base tick function inherited from Component. Used for updates every frame.
	};
}