#pragma once
#include "../stdafx.h"
#include <map>
#include <vector>
#include "../inc/parser.h"
#include "../inc/Material.h"
class MaterialParser : public Parser
{
private:
	map <string,Material*>* m_materials;
	map <string,MaterialTexture*> m_cubeTextures;
	
	Material* m_material;
	MaterialTexture* m_MaterialcubeTexture;

	Material::MaterialColor m_materialColor;
	Material::MaterialIllum m_materialIllum;
	Material::MaterialMapping m_materialMapping;

	// Metodos sobreescritos
	/** Sobreescribe Parser::processStatement*/
	void processStatement(Parser::Statement* statement);
	void endFile();

	// Metodos
	void processMaterialTexture(vector<string>* params, MaterialTexture* texture);
	void MaterialParser::proccesOST(MaterialTexture* texture ,vector<string>*params,int index);
	void MaterialParser::proccesBlendClamp(MaterialTexture* texture ,vector<string>* params,int index);
	Parser::Statement parseStatement(string line, const char delim=' ');
	Material* MaterialParser::getMaterialModel();
	//void initializeDefaultVariables(Material *material);
	//void initializeMaterialTextureDefault(MaterialTexture *texture);
	void FN_ToLower(string* s);


public:
	MaterialParser(string filename);
	~MaterialParser(void);
	map <string,Material*>* MaterialParser::getMaterials();
};