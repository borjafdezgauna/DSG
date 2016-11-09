#pragma once
#include <vector>
#include "../../tinyxml2/tinyxml2.h"
#pragma comment (lib,"Debug/tinyxml2.lib")

class ColladaModel
{
	std::vector<double> positions;
	std::vector<double> normals;
	std::vector<double> texCoords;
	std::vector<int> indices;
	unsigned int textureId;
	char * texturaPath;

public:
	ColladaModel(char* modelo);
	~ColladaModel();
	void draw();
	void cargarTextura();

	

private:
	void parseXMLFloatArray(tinyxml2::XMLElement * pFloatArray, std::vector<double>& vector);

	void parseXMLIntArray(tinyxml2::XMLElement * pFloatArray, std::vector<int>& vector);

};