#include "component.h" /* Included for inheritance */
#include <AL/al.h> /* Loading in sound */
#include <memory> /* smart pointers */
#include <string> /* std::string */
#include "sound.h" /* Loading in sound*/
#include "glm/glm.hpp" /* glm::vec3*/

namespace snowball
{
	// Forward declared structures.
	struct Camera;
	/**
	* \brief The class responsible for playing sounds.
	* 
	* This class loads in sounds using the Sound class from the Resource system.
	* It is also able to play the sound, and enable directional sound given a listener.
	* (The Entity it is attached to is considered the source)
	*/
	struct SoundSource : public Component
	{
		void onInitialize(const std::string _path); ///< Base initialize function inherited from Component. Used for creating the object.
		void setDirectional(bool _flag); ///< Enables directional sound.
		void onTick(); ///< Base tick function inherited from Component. Used for updates every frame.
		void playSound(); ///< Plays the stored sound.
		void setListener(std::shared_ptr<Camera> _listener); ///< Sets a reference to a specific object to use as a listener.
	private:
		ALuint sid; ///< Stores the ID of the buffer containing the sound data.
		std::weak_ptr<Sound> sound; ///< Stores the sound loader.
		bool directional; ///< Stores whether sound is directional or not.
		std::shared_ptr<Camera> listener; ///< Stores a reference to a specific object to use as a listener.
	};
}