#include "stdafx.h"
#include "ColladaModel.h"
#include <vector>
#include "../../tinyxml2/tinyxml2.h"
#pragma comment (lib, "Debug/tinyxml2.lib")
#include "../../Simple OpenGL Image Library/src/SOIL.h"
#pragma comment(lib,"../../Debug/SOIL.lib")

ColladaModel::ColladaModel(char* filename) 
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	tinyxml2::XMLElement* pRoot = doc.FirstChildElement("COLLADA");
	tinyxml2::XMLElement* pLibraryImages = pRoot->FirstChildElement("library_images");
	tinyxml2::XMLElement* pImage = pLibraryImages->FirstChildElement("image");
	tinyxml2::XMLElement* pInitFrom = pImage->FirstChildElement("init_from");
	textura = strdup(&(pInitFrom->GetText()[8]));
	

	tinyxml2::XMLElement* pLibraryGeometries = pRoot->FirstChildElement("library_geometries");
	tinyxml2::XMLElement* pGeometry = pLibraryGeometries->FirstChildElement("geometry");
	tinyxml2::XMLElement* pMesh = pGeometry->FirstChildElement("mesh");
	tinyxml2::XMLElement* pSource_pos = pMesh->FirstChildElement("source");
	tinyxml2::XMLElement* pFloat_array_pos = pSource_pos->FirstChildElement("float_array");
	parseXMLFloatArray(pFloat_array_pos, m_positions);
	
	tinyxml2::XMLElement* pSource_nrm = pSource_pos->NextSiblingElement();
	tinyxml2::XMLElement* pFloat_array_nrm = pSource_nrm->FirstChildElement("float_array");
	parseXMLFloatArray(pFloat_array_nrm, m_normals);

	tinyxml2::XMLElement* pSource_index = pSource_nrm->NextSiblingElement();
	tinyxml2::XMLElement* pFloat_array_ind = pSource_index->FirstChildElement("float_array");
	parseXMLFloatArray(pFloat_array_ind, m_texCoords);

	tinyxml2::XMLElement* pVert = pMesh->FirstChildElement("triangles");
	tinyxml2::XMLElement* pInd = pVert->FirstChildElement("p");
	parseXMLIntArray(pInd, m_index);
}

ColladaModel::~ColladaModel()
{
}

void ColladaModel::draw() {
	glPushMatrix();
	glRotated(-75, 1, 0, 0);
	glTranslated(0, -1, -1);
	GLfloat mat_ambient[] = { 1,1,1,1.0 };
	GLfloat mat_diffuse[] = { 1,1,1,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_TRIANGLES);
	for (int ind = 0; ind < m_index.size(); ind++) {
		int index = m_index[ind];
			glNormal3f(m_normals[index * 3 + 0], m_normals[index * 3 + 1], m_normals[index * 3 + 2]);
			glTexCoord2f(m_texCoords[index * 2 + 0], 1 - m_texCoords[index * 2 + 1]);
			glVertex3f(m_positions[index * 3 + 0], m_positions[index * 3 + 1], m_positions[index * 3 + 2]);		
	}
	glEnd();
	glPopMatrix();
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

void ColladaModel::setIdTexture()
{
	textureId= SOIL_load_OGL_texture(textura, 0, 0, 0);
}