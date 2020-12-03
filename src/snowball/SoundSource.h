#include "component.h"
#include <AL/al.h>
#include <memory>
#include <string>
#include "sound.h"

namespace snowball
{
	

	struct SoundSource : public Component
	{
	
		void onInitialize(const std::string _path);
		void onTick();
		void playSound();
	private:
		ALuint sid;
		std::weak_ptr<Sound> sound;
	};

}