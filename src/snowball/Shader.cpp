#include "Shader.h"
#include <iostream>
#include <fstream>
#include "ResourceManager.h"
#include "Core.h"

namespace snowball
{
	void Shader::onLoad(const std::string _path)
	{
		shader = getRm()->getCore()->context->createShader();

		std::ifstream file(_path); //note that this only works for VS
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
		shader->parse(content);
	}
	std::shared_ptr<rend::Shader> Shader::getShader()
	{
		return shader;
	}
}