#pragma once
#include <vector>
#include "../../tinyxml2/tinyxml2.h"
#include "../../Debug/tinyxml2.lib"

class ColladaModel
{
	std::vector<double> m_positions;
	std::vector<double> m_normals;
	std::vector<double> m_textCoords;
	int textureId;
	std::vector<int> m_indexCoords;


public:
	ColladaModel(char *filename);
	virtual ~ColladaModel();

private:
	void parseXMLFloatArray(tinyxml2::XMLElement * pFloatArray, std::vector<double>& vector);

	void parseXMLIntArray(tinyxml2::XMLElement * pFloatArray, std::vector<int>& vector);

};
