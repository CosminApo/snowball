#include "resource.h"  /* Included for inheritance */
#include <AL/al.h> /* Loading in sound */

namespace snowball
{
	/**
	* \brief The class responsible for loading in sound files.
	* 
	* This class loads in .ogg sound files using the OpenAL library.
	* It also stores the data in memory and returns an ID for where to find it.
	*/
	struct Sound : public Resource
	{
		ALuint getID(); ///< Returns the ID of the buffer generated.
		void onLoad(const std::string _path); ///< Base loading function inherited from Resource. 
		void loadOgg(const std::string& _fileName, std::vector<char>& _buffer, ALenum& _format, ALsizei& _freq); ///< Function for loading in .ogg files
	private:
		ALuint id; ///< Stores the ID used to locate the generated buffer.
	};
}