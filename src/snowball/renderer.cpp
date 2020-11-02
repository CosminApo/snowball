#include "renderer.h"
#include "core.h"
#include "entity.h"

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
		"attribute vec3 a_Position;				" \
		"attribute vec2 a_TexCoord;					" \
		"											" \
		"varying vec2 ex_TexCoord;					" \
		"											" \
		"void main()								" \
		"{											" \
		" gl_Position = in_Projection * in_Model * vec4(a_Position, 1);		" \
		"}											" \
		"											" \
		"\n#endif\n									" \
		"\n#ifdef FRAGMENT\n						" \
		"											" \
		"void main()								" \
		"{											" \
		" gl_FragColor = vec4(1, 0, 0, 1);			" \
		"}										    " \
		"											" \
		"\n#endif\n                                 ";

	    shader = getCore()->context->createShader();
		shader->parse(src);

		shape = getCore()->context->createBuffer();
		shape->add(glm::vec3(0.f, 0.5f, -10.5f));
		shape->add(glm::vec3(-0.5f, -0.5f, -10.5f));
		shape->add(glm::vec3(0.5f, -0.5f, -10.5f));

		//just to test mats
		/*float angle(1.0f);
		getEntity()->getComponent<Transform>()->setRotationAngle(&angle);*/
	}
	void Renderer::onRender()
	{
		shader->setUniform("in_Model", getEntity()->getComponent<Transform>()->getModelMat());
		shader->setUniform("in_Projection",	getEntity()->getCore()->getScreen()->getProjMat());
		shader->setAttribute("a_Position", shape);
		shader->render();

	}
}