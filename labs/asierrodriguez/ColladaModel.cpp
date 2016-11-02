#include "stdafx.h"
#include "ColladaModel.h"


ColladaModel::ColladaModel(char *filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("");
	tinyxml2::XMLElement* pRoot = doc.FirstChildElement("COLLADA");
	tinyxml2::XMLElement* pLibraryImages = pRoot->FirstChildElement("library_images");
}


ColladaModel::~ColladaModel()
{
}