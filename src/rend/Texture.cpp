#include "Texture.h"
#include "Context.h"
#include "Exception.h"
// Needs to be defined before the include in exactly one comp unit
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace rend
{

Texture::Texture() {}

Texture::~Texture()
{
  GLuint delId = id;
  glDeleteTextures(1, &delId);
  pollForError();
}

Texture::Texture(const std::string _path)
{

    unsigned char* data = {}; //where the data loaded is stored
    int width = 0; //the width of the image
    int heigth = 0; //the height of the image

    if (_path != "")    //if there is a path
    {
        data = stbi_load(       //load the file
            (_path).c_str(),    //at this path
            &width,             //store the width
            &heigth,            //store the height
            NULL,               //dont force format
            4                   //RGBA, 4 channels
        );
        if (data == NULL) //error check
        {
            throw Exception("Texture could not be loaded");
        }
    }

    
    glGenTextures(1, &id); //create an opengl texture and store id
    if (!id) //error check
    {
        throw Exception("Texture could not be created");
    }

    ////glActiveTexture(GL_TEXTURE0 + 1); multitexture
    glBindTexture(GL_TEXTURE_2D, id);

    //upload the image data to the bound texture unit in the gpu
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, heigth, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //free the loaded data cause its now on the gpu
    free(data);

    //generate mipmap
    glGenerateMipmap(GL_TEXTURE_2D);


    size = ivec2(width, heigth);
    dirty = false;
}




GLuint Texture::getTexId()
{
  return getId();
}

GLuint Texture::getId()
{
  if(dirty)
  {
    glBindTexture(GL_TEXTURE_2D, id);
    pollForError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_FLOAT, &data.at(0));
    pollForError();

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    pollForError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    pollForError();

    glGenerateMipmap(GL_TEXTURE_2D);
    pollForError();

    glBindTexture(GL_TEXTURE_2D, 0);
    pollForError();

    dirty = false;
  }

  return id;
}

ivec2 Texture::getSize() const
{
  return size;
}

int Texture::getWidth() const
{
  return size.x;
}

int Texture::getHeight() const
{
  return size.y;
}

void Texture::setSize(unsigned int width, unsigned int height)
{
  dirty = false;
  size = ivec2(width, height);
  data.resize(width * height);
}

void Texture::setPixel(unsigned int x, unsigned int y, vec3 rgb)
{
  setPixel(x, y, vec4(rgb, 1));
  bpp = 3;
}

void Texture::setPixel(unsigned int x, unsigned int y, vec4 rgba)
{
  dirty = false;
  bpp = 4;
  data.at(size.x * (size.y - 1 - y) + x) = rgba;
}

vec4 Texture::getPixel(unsigned int x, unsigned int y) const
{
  return data.at(size.x * y + x);
}

}
