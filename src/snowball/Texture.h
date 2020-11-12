#include "resource.h"
#include <GL/glew.h> /*Open GL drawing operations*/


namespace snowball
{
	struct Texture : public Resource
	{
		void onLoad(const std::string& _path);
	private:
		unsigned char* data;
		int width, height;
		GLuint id;
	};
}