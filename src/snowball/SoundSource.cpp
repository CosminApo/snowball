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
		std::shared_ptr<Sound> sound = getEntity()->getCore()->getRm()->load<Sound>(_path);
		alGenSources(1, &sid);

		alSourcei(sid, AL_BUFFER, sound->getID());
		alSourcef(sid, AL_GAIN, 1);
		alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
	}
	void SoundSource::setDirectional(bool _flag)
	{
		directional = _flag;
	}
	void SoundSource::onTick()
	{
		if (directional)
		{
			glm::vec3 entityPos = getEntity()->getComponent<Player>()->getTransform()->getPosition();
			glm::vec3 listenerPos = listener->getTransform()->getPosition();
			alListener3f(AL_POSITION, listenerPos.x, listenerPos.y, listenerPos.z);
			alSource3f(sid, AL_POSITION, entityPos.x, entityPos.y, entityPos.z);

		}
	
	}
	void SoundSource::playSound()
	{
		ALint state = 0;
		alGetSourcei(sid, AL_SOURCE_STATE, &state);
		if (!(state == AL_PLAYING))
		{		
			alSourcePlay(sid);
		}
	}
	void SoundSource::setListener(std::shared_ptr<Camera> _listener)
	{
		listener = _listener;
	}
}