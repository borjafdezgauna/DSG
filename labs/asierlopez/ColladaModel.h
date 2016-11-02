#pragma once
#include <vector>
#include "../../tinyxml2/tinyxml2.h"
#include "../../Debug/tinyxml2.lib"

class ColladaModel
{
	std::vector<double> positions;
	std::vector<double> normals;
	std::vector<double> texCoords;
	int textureId;

public:
	ColladaModel(char* modelo);
	~ColladaModel();
	void draw();

	

private:
	void parseXMLFloatArray(tinyxml2::XMLElement * pFloatArray, std::vector<double>& vector);

	void parseXMLIntArray(tinyxml2::XMLElement * pFloatArray, std::vector<int>& vector);

};