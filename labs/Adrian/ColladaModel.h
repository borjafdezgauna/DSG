#pragma once
#include <vector>

class ColladaModel {
	std::vector<double> m_positions;
	std::vector<double> m_normals;
	std::vector<double> m_index;
	std::vector<double> m_texCoords;
	int textureId;



public:
	ColladaModel();
	virtual ~ColladaModel();

	void draw();
	void parseXMLFloatArray(tinyxml2::XMLElement * pFloatArray, std::vector<double>& vector);
	void parseXMLIntArray(tinyxml2::XMLElement * pFloatArray, std::vector<int>& vector);
};