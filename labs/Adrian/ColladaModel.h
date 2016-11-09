#pragma once
#include <vector>
#include "../../tinyxml2/tinyxml2.h"
#pragma comment (lib, "Debug/tinyxml2.lib")

class ColladaModel {
	std::vector<double> m_positions;
	std::vector<double> m_normals;
	std::vector<int> m_index;
	std::vector<double> m_texCoords;
	char* textura;
	unsigned int textureId;

public:
	ColladaModel(char* filename);
	virtual ~ColladaModel();

	void draw();
	void parseXMLFloatArray(tinyxml2::XMLElement * pFloatArray, std::vector<double>& vector);
	void parseXMLIntArray(tinyxml2::XMLElement * pFloatArray, std::vector<int>& vector);
	void setIdTexture();
};