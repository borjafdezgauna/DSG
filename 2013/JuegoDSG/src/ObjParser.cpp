#include "../inc/ObjParser.h"
#include "../inc/MaterialParser.h"
#include <fstream>
#include <cstring>
//#include <array>


ObjParser::ObjParser() : Parser("None"){
	m_convertPoly = true;
	mt_materialList = NULL;
}
ObjParser::ObjParser(string filename, bool convertPolygonToTriangles, bool generateNormals) : Parser(filename){
	m_convertPoly = convertPolygonToTriangles;
	m_generateNormals = generateNormals;

	m_convertPoly = true;
	m_objModel = new ObjModel(filename);
	m_lineIndex = 0;
	
	m_currentMaterial = NULL;
	m_currentGroup = new Group("Default");
	m_modelGroups = m_objModel->m_textureGroups;

	mt_needsNormals = false;
	if(m_generateNormals){
		mt_smoothGroupList = new FitArray<SmoothGroup*>(8,32);
		mt_currentSmoothGroup = new SmoothGroup(1);
		mt_smoothGroupList->push_back(mt_currentSmoothGroup);
		mt_currentSmoothGroupTriangleList = new FitArray<Triangle*>(1024,32);
	}
	else{
		mt_smoothGroupList = NULL;
		mt_currentSmoothGroup = NULL;
		mt_currentSmoothGroupTriangleList = NULL;
	}
	mt_currentGroupTriangleList = new FitArray<Triangle*>(512,32);
	mt_groupList = new FitArray<Group*>(8,64);
	mt_materialList = NULL;
	//m_smoothGroups = vector<SmoothGroup>();
	m_vList = vector<float*>();
	m_vtList = vector<float*>();
	m_vnList = vector<float*>();
}

ObjParser::~ObjParser(){
	/* Mandamos a fregar a las variables temporales */
	delete mt_groupList;
	delete mt_currentGroupTriangleList;
	delete mt_materialList;
}

void ObjParser::processStatement(Parser::Statement* statement){
	if(statement->command == "v")
		processVertex(&m_vList, &statement->arguments, 3, 4, 1.0f);
	else if(statement->command == "vt")
		processVertex(&m_vtList, &statement->arguments, 1);
	else if(statement->command == "vn")
		processVertex(&m_vnList, &statement->arguments, 3);
	else if(statement->command == "f")
		processFace(&statement->arguments);
	else if(statement->command == "g")
		processTextureGroup(&statement->arguments);
	else if(statement->command == "s")
		processSmoothGroup(&statement->arguments);
	else if(statement->command == "usemtl"){
		try{
			processSetMtl(&statement->arguments);
		}
		catch(InvalidMaterial& ex){
			// Si queremos que el programa casque cuando no encuentre el material
			// quitamos este try catch
			cout << "Warning: " << ex.what() << endl;
		}
	}
	else if(statement->command == "mtllib")
		processMaterialLib(&statement->arguments);

}

void ObjParser::endFile(){
	m_currentGroup->setTriangleList(mt_currentGroupTriangleList->getData());
	m_currentGroup->setMaterial(m_currentMaterial);
	mt_groupList->push_back(m_currentGroup);
	m_objModel->setGroups(mt_groupList->getData());
	if(m_generateNormals && mt_needsNormals){
		mt_currentSmoothGroup->setTriangleList(mt_currentSmoothGroupTriangleList->getData());
		cout << "Generating normals..." << endl;
		for (int i=0;i<mt_smoothGroupList->size();i++){
			mt_smoothGroupList->at(i)->generateNormals();
		}
		cout << "Done" << endl;
	}
	//m_objModel->m_textureGroups->at(0)->getMaterial()->m_mapping.m_ambientMaterial->loadTexture();
	for (int i = 0; i < m_objModel->m_textureGroups->size(); i++){
		Material* material = m_objModel->m_textureGroups->at(i)->getMaterial();
		if(material != NULL){
			if(material->m_mapping.m_ambientMaterial!=NULL)	{
				material->m_mapping.m_ambientMaterial->loadTexture();
			}
			if(material->m_mapping.m_diffuseMaterial!=NULL){
				material->m_mapping.m_diffuseMaterial->loadTexture();
			}
		//if(material->m_mapping.m_displacementMaterial!=NULL){
		//	material->m_mapping.m_displacementMaterial->loadTexture();
	//	}
		/*
		if(material->m_mapping.m_specularExponentMaterial!=NULL){
			material->m_mapping.m_specularExponentMaterial->loadTexture();
		}
		if(material->m_mapping.m_disolveMaterial!=NULL){
			material->m_mapping.m_disolveMaterial->loadTexture();
		}
		if(material->m_mapping.m_decalMaterial!=NULL){
			material->m_mapping.m_decalMaterial->loadTexture();
		}
		if(material->m_mapping.m_displacementMaterial!=NULL){
			material->m_mapping.m_displacementMaterial->loadTexture();
		}
		if(material->m_mapping.m_bumpMaterial){
			material->m_mapping.m_bumpMaterial->loadTexture();
		}
		*/
		}
	}
}
void ObjParser::processVertex(vector<float*>* vertexList, Parser::Arguments* arguments, unsigned int required, unsigned int datalen/*=3*/, float def/*=0.0*/ )
{
	float* v = new float[datalen];
	if(arguments->size()>=required && arguments->size()<=datalen)
	{
		try{
			for(size_t x = 0; x < datalen; x++){
				if(x >= arguments->size())
					v[x] = def;
				else
					v[x] = atof((*arguments)[x].c_str());
			}
			vertexList->push_back(v);
		}
		catch(invalid_argument){
			throwSyntaxError();
		}
	}
	else{
		for(size_t i=0;i<datalen;i++)
			v[i]=0;
		vertexList->push_back(v);
		throwSyntaxError();
	}
}


void ObjParser::processFace(Parser::Arguments* arguments)
{
	//for(string s : (*arguments)){
	if(arguments->size()==3){
		Vertex faceVertexes[3];
		for(int i=0; i<3; i++){
			string s = arguments->at(i);
			Parser::Arguments vertexStatement;
			split(vertexStatement,s,'/',false);
			faceVertexes[i] = getFaceVertex(&vertexStatement);
		}
		Triangle* t = new Triangle(faceVertexes[0],faceVertexes[1],faceVertexes[2]);
		mt_currentGroupTriangleList->push_back(t);
		if(m_generateNormals)
			mt_currentSmoothGroupTriangleList->push_back(t);
	}
	else if(arguments->size()>3 && m_convertPoly){
		Vertex* faceVertexes = new Vertex[arguments->size()];
		for(int i=0; i<arguments->size(); i++){
			string s = arguments->at(i);
			Parser::Arguments vertexStatement;
			split(vertexStatement,s,'/',false);
			faceVertexes[i] = getFaceVertex(&vertexStatement);
		}
		int pivot = 0;
		for (int v = 0; v < arguments->size()-2; v++){
			Triangle* subTriangle = new Triangle(faceVertexes[pivot], faceVertexes[pivot+v+1],faceVertexes[pivot+v+2]);
			mt_currentGroupTriangleList->push_back(subTriangle);
		}
	}
	else{
		throwSyntaxError();
	}
}

Vertex ObjParser::getFaceVertex(Parser::Arguments* arguments)
{
	try{
		int vid = atoi((*arguments)[0].c_str());
		float* v = m_vList[vid-1];
		float* vt = new float[3];
		for(int i = 0; i < 3; i++)
			vt[i] = 0;
		float* vn = new float[3];
		for(int i = 0; i < 3; i++)
			vn[i] = 0;
		bool normal = false;
		if(arguments->size()>=2){
			if(arguments->at(1)!=""){
				int vtid = atoi((*arguments)[1].c_str());
				vt = m_vtList[vtid-1];
			}
		}
		if(arguments->size()==3){
			if(arguments->at(2)!=""){
				int vnid = atoi((*arguments)[2].c_str());
				vn = m_vnList[vnid-1];
				normal = true;
			}
		}
		if(!normal && m_generateNormals){
			mt_needsNormals = true;
			mt_currentSmoothGroup->setHasVn(false);
		}
		Vertex vertex = Vertex(vid,v,vt,vn,normal);
		return vertex;
	}
	catch(invalid_argument){
		throwSyntaxError();
		return Vertex();
	}
}

void ObjParser::processTextureGroup(Parser::Arguments* arguments)
{
	string groupName = "Default";
	if(arguments->size()>=1){
		groupName = arguments->at(0);
	}
	cout << "Processing group " << mt_groupList->size() << " : " << groupName << endl;
	if(m_currentGroup == NULL){
		m_currentGroup = new Group(groupName);
	}
	else{
		Group* txGroup = NULL;
		for(size_t i=0;i<mt_groupList->size() && txGroup == NULL;i++){
			if(groupName == mt_groupList->at(i)->getName()){
				txGroup = mt_groupList->at(i);
			}
		}
		if(txGroup == NULL){
			m_currentGroup->setTriangleList(mt_currentGroupTriangleList->getData());
			m_currentGroup->setMaterial(m_currentMaterial);
			mt_groupList->push_back(m_currentGroup);
			m_currentGroup = new Group(groupName);
			mt_currentGroupTriangleList = new FitArray<Triangle*>(512,32);
		}
	}
}

void ObjParser::processSmoothGroup(Parser::Arguments* arguments)
{
	if(!m_generateNormals)
		return;
	if(arguments->size()>=1){
		try{
			int smoothId = atoi((*arguments)[0].c_str());
			SmoothGroup* smGroup = NULL;
			for(size_t i=0;i<mt_smoothGroupList->size() && smGroup == NULL;i++){
				if(mt_smoothGroupList->at(i)->getId() == smoothId){
					smGroup = mt_smoothGroupList->at(i);
				}
			}
			if(smGroup == NULL){
				mt_currentSmoothGroup->setTriangleList(mt_currentSmoothGroupTriangleList->getData());
				mt_smoothGroupList->push_back(mt_currentSmoothGroup);
				mt_currentSmoothGroup = new SmoothGroup(smoothId);
				mt_currentSmoothGroupTriangleList = new FitArray<Triangle*>(512,32);
			}
			else{
				mt_currentSmoothGroup = smGroup;
			}

		}catch(invalid_argument){
			throwSyntaxError();
		}
	}
	else{
		throwSyntaxError();
	}
}

void ObjParser::processMaterialLib(Parser::Arguments* arguments )
{
	MaterialParser mtlparser(string("models/") + arguments->at(0));
	mtlparser.load();
	mt_materialList = mtlparser.getMaterials();
	for ( std::map<string,Material*>::iterator it = mt_materialList->begin(); it != mt_materialList->end(); ++it )
		cout << it->second->m_name << endl;
}

ObjModel* ObjParser::getObjModel()
{
	return m_objModel;
}

void ObjParser::processSetMtl( Arguments* arguments )
{
	if (mt_materialList == NULL ){
		throw InvalidMaterial(arguments->at(0));
	}
	if(mt_materialList->find(arguments->at(0)) == mt_materialList->end()){
		throw InvalidMaterial(arguments->at(0));
	}
	else{
		map<std::string,Material*>::iterator it( mt_materialList->find(arguments->at(0)));
		m_currentMaterial = it->second;
	}
}


