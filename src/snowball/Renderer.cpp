#include "renderer.h"
#include "core.h"
#include "entity.h"
#include "Camera.h"

#include <fstream>

namespace snowball
{
	void Renderer::onInitialize()
	{
		std::cout << "Initializing..." << std::endl;
		const char* src =
			"\n#ifdef VERTEX\n							" \
			"uniform mat4 u_Projection;				" \
			"uniform mat4 u_Model;						" \
			"uniform mat4 u_View;						" \
			"											" \
			"attribute vec3 a_Position;				    " \
			"attribute vec3 a_Normal;				    " \
			"attribute vec2 a_TexCoord;					" \
			"											" \
			"varying vec2 v_TexCoord;					" \
			"											" \
			"void main()								" \
			"{											" \
			" gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1);		" \
			" v_TexCoord = a_TexCoord;  " \
			" if (a_Normal.x == 43) gl_Position.x = 6;  " \
			"}											" \
			"											" \
			"\n#endif\n									" \
			"\n#ifdef FRAGMENT\n						" \
			"varying vec2 v_TexCoord;					" \
			"											" \
			"void main()								" \
			"{											" \
			" gl_FragColor = vec4(v_TexCoord, 0, 1);			" \
			"}										    " \
			"											" \
			"\n#endif\n                                 ";
		
		shader = getCore()->context->createShader();
		shader->parse(src);

		shape = getCore()->context->createMesh();

		std::ifstream file("../curuthers/curuthers.obj"); //note that this only works for VS
		if (!file.is_open())
		{
			throw snowball::Exception("Failed to open model file");
		}

		std::string content;
		std::string line;
		while (!file.eof())
		{
			std::getline(file, line);
			content += line + "\n";
		}
		shape->parse(content);
	}
	void Renderer::onRender()
	{
		shader->setMesh(shape);	
		shader->setUniform("u_View", getEntity()->getCore()->getCamera()->getView());
		shader->setUniform("u_Model", getEntity()->getComponent<Transform>()->getModelMat());
		shader->setUniform("u_Projection",	getEntity()->getCore()->getScreen()->getProjMat());
		
		shader->render();

	}
}