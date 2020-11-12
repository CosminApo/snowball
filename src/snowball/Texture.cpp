#include "texture.h"
#include <iostream>
// Needs to be defined before the include in exactly one comp unit
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace snowball
{
	void Texture::onLoad(const std::string& _path)
	{
		//load image
		data = stbi_load((_path).c_str(), &width, &height, NULL, 4);

		//create and bind a texture
		id = 0;
		glGenTextures(1, &id);
		if (!id)
		{
			std::cout << "Texture could not be created" << std::endl;
			throw std::exception();
		}

		//glActiveTexture(GL_TEXTURE0 + 1); multitexture
		glBindTexture(GL_TEXTURE_2D, id);

		//upload the image data to the bound texture unit in the gpu
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		//free the loaded data cause its now on the gpu
		free(data);

		//generate mipmap
		glGenerateMipmap(GL_TEXTURE_2D);




		//unbind the texture because we are done operating
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}