#include "sound.h"
#include <rend/rend.h>
#include "stb_vorbis.h"

namespace snowball
{
	ALuint Sound::getID()
	{
		return id; // Returns the stored ID
	}
	void Sound::onLoad(const std::string _path)
	{
		alGenBuffers(1, &id); // Generate a buffer.

		ALenum format = 0; 
		ALsizei freq = 0;
		std::vector<char> bufferData;
		loadOgg(_path + ".ogg", bufferData, format, freq); // Load in the file. NOTE: only .ogg files allowed.
		alBufferData(id, format, &bufferData.at(0), static_cast<ALsizei>(bufferData.size()), freq); // Generates buffer.
	}
	void Sound::loadOgg(const std::string& _fileName, std::vector<char>& _buffer, ALenum& _format, ALsizei& _freq)
	{
		int channels = 0; // 1 = mono, 2 = stereo
		int sampleRate = 0; 
		short* output = NULL; // Where the output is stored.
		size_t samples = stb_vorbis_decode_filename(_fileName.c_str(), &channels, &sampleRate, &output); // Decode the file.

		if (samples == -1) // If there are no samples it means it didn't decode.
		{
			throw rend::Exception("Failed to open file '" + _fileName + " '");
		}

		// Note: vorbis only loads 16bit +, so format is always 16bit 
		if (channels == 1)
		{
			_format = AL_FORMAT_MONO16;
		}
		else
		{
			_format = AL_FORMAT_STEREO16;
		}

		_freq = sampleRate;

		_buffer.resize(samples * 2); // Always set the buffer to samples * 2.
									 // Small memory optimization to set it to * 2 only for stereo.
		memcpy(&_buffer.at(0), output, _buffer.size());

		free(output); // Free data after it's finished.
	}
}