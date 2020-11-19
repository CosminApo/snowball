#include "renderer.h"
#include "core.h"
#include "entity.h"

#include <fstream>

namespace snowball
{
	void Renderer::onInitialize()
	{
		std::cout << "Initializing..." << std::endl;
		const char* src =
			"\n#ifdef VERTEX\n							" \
			"uniform mat4 in_Projection;				" \
			"uniform mat4 in_Model;						" \
			"											" \
			"attribute vec3 a_Position;				    " \
			"attribute vec3 a_Normal;				    " \
			"attribute vec2 a_TexCoord;					" \
			"											" \
			"varying vec2 v_TexCoord;					" \
			"											" \
			"void main()								" \
			"{											" \
			" gl_Position = in_Projection * in_Model * vec4(a_Position, 1);		" \
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
		//shape = getCore()->context->createBuffer();
		//shape->add(glm::vec3(0.f, 0.5f, -10.5f)); //vec2 works, assumes z = 0
		//shape->add(glm::vec3(-0.5f, -0.5f, -10.5f));
		//shape->add(glm::vec3(0.5f, -0.5f, -10.5f));

		std::ifstream file("../curuthers/curuthers.obj"); //note that this only works for VS
		if (!file.is_open())
		{
			throw rend::Exception("Failed to open model file");
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
		//shader->setAttribute("a_Position", shape);
		shader->setUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMat());
		shader->setUniform("in_Projection",	getEntity()->getCore()->getScreen()->getProjMat());
		
		shader->render();

	}
}