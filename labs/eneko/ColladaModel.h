#pragma once
#include <vector>
#include "../../tinyxml2/tinyxml2.h"
#pragma comment (lib,"../../labs/eneko/Debug/tinyxml2.lib")
class ColladaModel
{
	std::vector<double> m_positions;
	std::vector<double> m_normals;
	std::vector<int> m_indices;
	std::vector<double> m_textCoords;
	int textureID;
	tinyxml2::XMLDocument doc;
	 int id;
	 double mx, my, mz;
public:
	ColladaModel(char* cargaDae);

	void draw();


	void setIdenti(int ida);

	void setPosition(double x, double y, double z);

private:
	void parseXMLFloatArray(tinyxml2::XMLElement * pFloatArray, std::vector<double>& vector);

	void parseXMLIntArray(tinyxml2::XMLElement * pFloatArray, std::vector<int>& vector);




};