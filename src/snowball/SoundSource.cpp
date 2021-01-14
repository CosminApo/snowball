#include "soundSource.h"
#include "core.h"
#include "entity.h"
#include <iostream>
#include "Player.h"
#include "Camera.h"

namespace snowball
{
	void SoundSource::onInitialize(const std::string _path)
	{		
		std::shared_ptr<Sound> sound = getEntity()->getCore()->getRm()->load<Sound>(_path); // Load a sound stored in a specific path.
		alGenSources(1, &sid); // Generate OpenAL source.
		alSourcei(sid, AL_BUFFER, sound->getID()); // Get the buffer location.
		alSourcef(sid, AL_GAIN, 1); // Set the volume to 1.0
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED); // Set the distance model.
	}
	void SoundSource::setDirectional(bool _flag)
	{
		directional = _flag; // Set directional sound.
	}
	void SoundSource::onTick()
	{
		if (directional) // If the sound is directional.
		{
			glm::vec3 entityPos = getEntity()->getComponent<Player>()->getTransform()->getPosition(); // Get the location of the source.
			glm::vec3 listenerPos = listener->getTransform()->getPosition(); // Get the location of the listener.
			alListener3f(AL_POSITION, listenerPos.x, listenerPos.y, listenerPos.z); // Set the listener position.
			alSource3f(sid, AL_POSITION, entityPos.x, entityPos.y, entityPos.z); // Set the source position.
		}
	}
	void SoundSource::playSound()
	{
		ALint state = 0; // Used to store the current state (based on openAL codes).
		alGetSourcei(sid, AL_SOURCE_STATE, &state); // Get the state of the sound source (Playing, Stopped, etc.).
		if (!(state == AL_PLAYING)) // If the sound is not already playing
		{		
			alSourcePlay(sid);
		}
	}
	void SoundSource::setListener(std::shared_ptr<Camera> _listener)
	{
		listener = _listener; // Store a reference to the listener object.
	}
}