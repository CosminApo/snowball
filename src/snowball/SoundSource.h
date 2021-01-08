#include "component.h"
#include <AL/al.h>
#include <memory>
#include <string>
#include "sound.h"
#include "glm/glm.hpp"


namespace snowball
{
	
	struct Camera;
	struct SoundSource : public Component
	{

		void onInitialize(const std::string _path);
		void setDirectional(bool _flag);
		void onTick();
		void playSound();
		void setListener(std::shared_ptr<Camera> _listener);
	private:
		ALuint sid;
		std::weak_ptr<Sound> sound;
		bool directional;
		std::shared_ptr<Camera> listener;

	};

}