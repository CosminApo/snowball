#include "soundSource.h"
#include "core.h"
#include "entity.h"
#include <iostream>


namespace snowball
{
	void SoundSource::onInitialize(const std::string _path)
	{
		std::shared_ptr<Sound> sound = getEntity()->getCore()->getRm()->load<Sound>(_path);
		alGenSources(1, &sid);
		std::cout << sid;
		alSourcei(sid, AL_BUFFER, sound->getID());
		std::cout << sound->getID();

	}
	void SoundSource::onTick()
	{

	
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
}