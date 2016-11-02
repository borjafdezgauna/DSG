#include "stdafx.h"
#include "ColladaModel.h"

char* file;

ColladaModel::ColladaModel(char *filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	tinyxml2::XMLElement* pRoot = doc.FirstChildElement("COLLADA");

	tinyxml2::XMLElement* pLibraryImages = pRoot->FirstChildElement("library_images")->FirstChildElement("image")->FirstChildElement("init_from");
	const char* fileName = &(pLibraryImages->GetText()[8]);
	file = strdup(fileName);

	tinyxml2::XMLElement* pMesh = pRoot->FirstChildElement("library_geometries")->FirstChildElement("geometry")->FirstChildElement("mesh");
	tinyxml2::XMLElement* pSourcePOS = pMesh->FirstChildElement("source");
	tinyxml2::XMLElement* pSourceNRM = pSourcePOS->NextSiblingElement("source");
	tinyxml2::XMLElement* pSourceUV = pSourceNRM->NextSiblingElement("source");
	tinyxml2::XMLElement* pMesh1 = pRoot->FirstChildElement("library_geometries")->FirstChildElement("geometry")->FirstChildElement("mesh");
	tinyxml2::XMLElement* pVertex = pMesh1->FirstChildElement("triangles")->FirstChildElement("p");
	
	parseXMLFloatArray(pSourcePOS->FirstChildElement("float_array"), m_positions);
	parseXMLFloatArray(pSourceNRM->FirstChildElement("float_array"), m_normals);
	parseXMLFloatArray(pSourceUV->FirstChildElement("float_array"), m_textCoords);
	parseXMLIntArray(pVertex, m_indexCoords);
	

}


ColladaModel::~ColladaModel()
{
}

void ColladaModel::parseXMLFloatArray(tinyxml2::XMLElement *pFloatArray, std::vector<double> &vector)
{
	char* pCharArray = (char*)pFloatArray->GetText();
	char* nextToken;
	char* pt = strtok_s(pCharArray, " ", &nextToken);
	while (pt != 0)
	{
		vector.push_back(atof(pt));
		pt = strtok_s(0, " ", &nextToken);
	}
}

void ColladaModel::parseXMLIntArray(tinyxml2::XMLElement *pFloatArray, std::vector<int> &vector)
{
	char* pCharArray = (char*)pFloatArray->GetText();
	char* nextToken;
	char* pt = strtok_s(pCharArray, " ", &nextToken);
	while (pt != 0)
	{
		vector.push_back(atoi(pt));
		pt = strtok_s(0, " ", &nextToken);
	}
}

void ColladaModel::setTexture() {
	textureId = SOIL_load_OGL_texture(file, 0, 0, 0);
	//textureId = SOIL_load_OGL_texture("Venom_D.tga", 0, 0, 0);
	//textureId = SOIL_load_OGL_texture("EM208_heavy_D.tga", 0, 0, 0);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
}

void ColladaModel::draw() {
	glPushMatrix();
	glRotated(-75, 1, 0, 0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_TRIANGLES);
	//int index;
	for (int i = 0; i < m_indexCoords.size(); i++) {
		int index = m_indexCoords[i];
		glNormal3f(m_normals[index * 3], m_normals[index * 3 + 1], m_normals[index * 3 + 2]);
		glTexCoord2f(m_textCoords[index*2], 1-m_textCoords[index*2 + 1]);
		glVertex3f(m_positions[index * 3], m_positions[index * 3 + 1], m_positions[index * 3 + 2]);
	}
	glEnd();
	glPopMatrix();
}
