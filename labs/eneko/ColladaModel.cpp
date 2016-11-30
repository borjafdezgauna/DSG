#include "stdafx.h"
#include "ColladaModel.h"
//#include "tinyxml2/tinyxml2.h"

ColladaModel::ColladaModel(char* cargaDae)
{

	doc.LoadFile(cargaDae);
	tinyxml2::XMLElement* pRoot = doc.FirstChildElement("COLLADA");
	//Imagen del .dae
	tinyxml2::XMLElement* pLibraryImages = pRoot->FirstChildElement("library_images");
	&(pLibraryImages[8]);
	tinyxml2::XMLElement* pImage = pLibraryImages->FirstChildElement("image");
	tinyxml2::XMLElement* pInitFrom = pImage->FirstChildElement("init_from");
	const char* rImage = pInitFrom->GetText();
	
	&(rImage[8]);
	//Geometria del .dae
	tinyxml2::XMLElement* pLibraryGeometries = pRoot->FirstChildElement("library_geometries");
	tinyxml2::XMLElement* pGeometry = pLibraryGeometries->FirstChildElement("geometry");
	tinyxml2::XMLElement* pMesh = pGeometry->FirstChildElement("mesh");
	tinyxml2::XMLElement* pSource = pMesh->FirstChildElement("source");
	tinyxml2::XMLElement* pFloatArrayPos = pSource->FirstChildElement("float_array");
	parseXMLFloatArray(pFloatArrayPos, m_positions);
	tinyxml2::XMLElement* pSource2 = pSource->NextSiblingElement("source");
	tinyxml2::XMLElement* pfloatArrayNrm = pSource2->FirstChildElement("float_array");
	parseXMLFloatArray(pfloatArrayNrm, m_normals);
	tinyxml2::XMLElement* pSource3 = pSource2->NextSiblingElement("source");
	tinyxml2::XMLElement* pfloatArrayUv = pSource3->FirstChildElement("float_array");
	parseXMLFloatArray(pfloatArrayUv, m_textCoords);
	//Indices triangulos dae
	tinyxml2::XMLElement* pTriangles = pMesh->FirstChildElement("triangles");
	tinyxml2::XMLElement* pP = pTriangles->FirstChildElement("p");
	parseXMLIntArray(pP, m_indices);
}
void ColladaModel::draw()
{
	m_indices;
	m_normals;
	m_positions;
	m_textCoords;
	
	glPushMatrix();
	glRotated(-75, 1, 0, 0);
	glTranslated(mx,my,mz);
	glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_TRIANGLES);
	GLfloat mat_ambient[] = { 1,1,1,1.0 };
	GLfloat mat_diffuse[] = { 1,1,1,1.0 };
	GLfloat mat_especular[] = { 0,0,0,0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_especular);

	int tamaño = m_indices.size();
	int j = 0;
	for (int i = 0; i < tamaño; i++) {
		j = m_indices[i];
		glNormal3f(m_normals[3*j], m_normals[3*j + 1], m_normals[3*j + 2]);	
		glTexCoord2f(m_textCoords[2*j], 1-m_textCoords[2*j + 1]);
		glVertex3f(m_positions[3 * j], m_positions[3 * j + 1], m_positions[3 * j + 2]);
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

void ColladaModel::setIdenti(int ida)
{
	id = ida;
}
void ColladaModel::setPosition(double x, double y, double z)
{
	mx = x;
	my = y;
	mz = z;
}