#include "renderer.h"
#include "Core.h"

namespace snowball
{
	void Renderer::onInitialize()
	{
		std::cout << "Initializing..." << std::endl;
		const char* src =
		"\n#ifdef VERTEX\n							" \
		"attribute vec2 a_Position;					" \
		"											" \
		"void main()								" \
		"{											" \
		" gl_Position = vec4(a_Position, 0, 1);		" \
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
		shape->add(glm::vec2(0, 0.5f));
		shape->add(glm::vec2(-0.5f, -0.5f));
		shape->add(glm::vec2(0.5f, -0.5f));

	}
	void Renderer::onRender()
	{
		shader->setAttribute("a_Position", shape);
		shader->render();

	}
}