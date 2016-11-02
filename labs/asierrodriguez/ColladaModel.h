#pragma once
#include <vector>
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
};
