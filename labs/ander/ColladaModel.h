#pragma once
#include <vector>
#pragma comment(lib, "../../Debug/tinyxml2.lib")
#include "../../tinyxml2/tinyxml2.h"
class ColladaModel
{
	char* modelo;
	std::vector<double> m_positions;
	std::vector<double> m_normals;
	std::vector<double> m_texCoords;
	std::vector<int> m_index;
	int textureId;

public:
	ColladaModel(char* fileName);
	~ColladaModel();
	void draw();
	
	void parseXMLFloatArray(tinyxml2::XMLElement * pFloatArray, std::vector<double>& vector);
	void parseXMLIntArray(tinyxml2::XMLElement * pFloatArray, std::vector<int>& vector);
};

