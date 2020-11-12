#include "resource.h"
#include <AL/al.h>



namespace snowball
{
	struct Sound : public Resource
	{
		ALuint getID(); //tbf, swap get to friend class to avoid bad boys
		void onLoad(const std::string _path);
		void loadOgg(const std::string& _fileName, std::vector<char>& buffer, ALenum& format, ALsizei& freq);
	private:
		ALuint id;
	};
}