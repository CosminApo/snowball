#include "Shader.h"
#include <iostream>
#include <fstream>
#include "ResourceManager.h"
#include "Core.h"

namespace snowball
{
	void Shader::onLoad(const std::string _path)
	{
		shader = getRm()->getCore()->context->createShader(); // Create a shader using rend.

		std::ifstream file(_path); // Open the file at the specified path.
								   // Note that this only works for Windows
		if (!file.is_open()) // If the file was not opened.
		{
			throw snowball::Exception("Failed to open model file");
		}

		std::string content;
		std::string line;
		while (!file.eof()) // Loop through the file.
		{
			std::getline(file, line);
			content += line + "\n"; // Adds it contents line by line to the content variable.
		} 
		shader->parse(content); // Parse the data loaded in. 
	}
	std::shared_ptr<rend::Shader> Shader::getShader()
	{
		return shader; // Return the model stored. 
	}
}