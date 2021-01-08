#include "Model.h"
#include <iostream>
#include <fstream>
#include "ResourceManager.h"
#include "Core.h"


namespace snowball
{
	void Model::onLoad(const std::string _path)
	{
		model = getRm()->getCore()->context->createMesh();

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
		model->parse(content);
	}

	std::shared_ptr<rend::Mesh> Model::getModel()
	{
		return model;
	}

}
