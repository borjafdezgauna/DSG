#include "stdafx.h"
#include "ColladaModel.h";

ColladaModel::ColladaModel(char* modelo)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(modelo);
	tinyxml2::XMLElement* pRoot = doc.FirstChildElement("COLLADA");
	tinyxml2::XMLElement* mesh = pRoot->FirstChildElement("library_geometries")->FirstChildElement("geometry")->FirstChildElement("mesh");

	//Cargamos la textura
	tinyxml2::XMLElement* init_from = pRoot->FirstChildElement("library_images")->FirstChildElement("image")->FirstChildElement("init_from");
	texturaPath = strdup(&(init_from->GetText()[8]));

	//cargamos las posiciones

	tinyxml2::XMLElement* pos = mesh->FirstChildElement("source");
	parseXMLFloatArray(pos->FirstChildElement("float_array"), positions);
	tinyxml2::XMLElement* nrm = pos->NextSiblingElement("source");
	parseXMLFloatArray(nrm->FirstChildElement("float_array"), normals);
	tinyxml2::XMLElement* UV = nrm->NextSiblingElement("source");
	parseXMLFloatArray(UV->FirstChildElement("float_array"), texCoords);

	//cargamos el indice
	parseXMLIntArray(mesh->FirstChildElement("triangles")->FirstChildElement("p"), indices);
}

ColladaModel::~ColladaModel()
{
}

void ColladaModel::cargarTextura() {
	textureId= SOIL_load_OGL_texture(texturaPath, 0, 0, 0);
}


void ColladaModel::draw()
{
	glPushMatrix();

	glRotated(-75, 1, 0, 0);
	glTranslated(0, -1, -1);


	GLfloat mat_ambient[] = { 1,1,1,1.0 };
	GLfloat mat_diffuse[] = { 1,1,1,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glBindTexture(GL_TEXTURE_2D, textureId);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < indices.size(); i++) {
		int indice = indices[i];
		int indice3 = indice * 3;
		int indice2 = indice * 2;
		glNormal3f(normals[indice3 + 0], normals[indice3 + 1], normals[indice3 + 2]);
		glTexCoord2f(texCoords[indice2 + 0], 1-texCoords[indice2 + 1]);
		glVertex3f(positions[indice3 + 0], positions[indice3 + 1], positions[indice3 + 2]);
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
