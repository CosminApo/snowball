#include "Model.h"
#include <iostream>
#include <fstream>
#include "ResourceManager.h"
#include "Core.h"


namespace snowball
{
	void Model::onLoad(const std::string _path)
	{
		model = getRm()->getCore()->context->createMesh(); // Create a mesh using the rend context

		std::ifstream file(_path); // Open the file at the specified path.
								   // Note that this only works for Windows
		if (!file.is_open()) // If the file was not opened.
		{
			std::cout << "Failed to open model: " << _path << std::endl;
		}

		std::string content;
		std::string line;
		while (!file.eof()) // Loop through the file.
		{
			std::getline(file, line);
			content += line + "\n"; // Adds it contents line by line to the content variable.
		}
		model->parse(content); // Parse the data loaded in. 
	}

	std::shared_ptr<rend::Mesh> Model::getModel()
	{
		return model; // Return the model stored. 
	}

}
