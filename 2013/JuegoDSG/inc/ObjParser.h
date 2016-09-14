#pragma once
#include "../stdafx.h"
#include <map>
#include "Parser.h"
#include "Vertex.h"
#include "Triangle.h"
#include "SmoothGroup.h"
#include "Group.h"
#include "ObjModel.h"
#include "FixedArray.h"
#include "FitArray.h"


using namespace std;

class ObjParser : public Parser
{
public:
	//////    Exceptions    //////////////////////////////////////////////////
	class InvalidMaterial : public Parser::ParseException{
	public:
		InvalidMaterial::InvalidMaterial(string materialname) 
			: Parser::ParseException("Material \""+materialname+"\" does not exist"){};
	};
private:
	// Variables
	string m_filename;
	string m_currentLine;
	bool m_convertPoly;

	// Punteros("Array") de floats
	vector<float*> m_vList;
	vector<float*> m_vtList;
	vector<float*> m_vnList;

	//vector<SmoothGroup> m_smoothGroups;
	
	// Variables que apuntan al modelo
	ObjModel::GroupList* m_modelGroups;
	Group* m_currentGroup;

	// Temporales
	bool mt_needsNormals;
	FitArray<Triangle*>* mt_currentGroupTriangleList;
	FitArray<Triangle*>* mt_currentSmoothGroupTriangleList;
	FitArray<Group*>* mt_groupList;
	FitArray<SmoothGroup*>* mt_smoothGroupList;
	map<string,Material*>* mt_materialList;

	ObjModel* m_objModel;
	Material* m_currentMaterial;
	SmoothGroup* mt_currentSmoothGroup;
	bool m_generateNormals;
	
	Parser::Statement parseStatement(string line, const char delim=' ');

	// Methods
	void processStatement(Parser::Statement* statement);
	void endFile();

	void ObjParser::processVertex( vector<float*>* vertexList, Parser::Arguments* params, unsigned int required, unsigned int datalen=3, float def=0.0 );
	void processFace(Parser::Arguments* params);
	void processTextureGroup(Parser::Arguments* params);
	void processSmoothGroup(Parser::Arguments* params);
	Vertex getFaceVertex(Parser::Arguments* params);

public:
	ObjParser::ObjParser();
	ObjParser(string filename, bool convertPolygonToTriangles=false ,bool generateNormals=false);
	~ObjParser(void);
	ObjModel* getObjModel();
	void processMaterialLib( Arguments* arguments );
	void processSetMtl( Arguments* arguments );
};