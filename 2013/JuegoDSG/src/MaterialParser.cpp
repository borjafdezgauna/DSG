#include "../inc/MaterialParser.h"
#include "../inc/Material.h"
#include "../inc/MaterialTexture.h"
#include "../inc/MaterialParser.h"
#include "../inc/ReflectionTexture.h"
#include <map>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>

//using namespace std;

MaterialParser::MaterialParser(string filename): Parser(filename){
	m_lineIndex=0;
	m_materials = new map<string, Material*>;
}

MaterialParser::~MaterialParser(void)
{
}

void FN_ToLower(string &s)
{
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void MaterialParser::processStatement(Parser::Statement* statement){
	
	//FN_ToLower((statement->command));
	std::transform(statement->command.begin(), statement->command.end(), statement->command.begin(), ::tolower);
	//cout << statement->command<<endl;
	if(statement->arguments.size()==0){
		//cout<<"0 arguments";
	}
	else if(statement->command=="newmtl"){
		if(statement->arguments[0].size()==0)
			throwSyntaxError();
		m_material = new Material(statement->arguments[0]);//se podria omitir? <-- No
		(*m_materials)[statement->arguments[0]] = m_material;
	}
	else if(statement->command == "ka"){
		if(statement->arguments.size()==1){
			m_material->m_color.m_ambientColor[0]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_ambientColor[1]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_ambientColor[2]=stringToFloat(statement->arguments[0]);
		}else if(statement->arguments.size()==3){
			m_material->m_color.m_ambientColor[0]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_ambientColor[1]=stringToFloat(statement->arguments[1]);
			m_material->m_color.m_ambientColor[2]=stringToFloat(statement->arguments[2]);
		}else{
			throwSyntaxError();
		}
	}
	else if(statement->command == "kd"){
		if(statement->arguments.size()==1){
			m_material->m_color.m_diffuseColor[0]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_diffuseColor[1]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_diffuseColor[2]=stringToFloat(statement->arguments[0]);
		}else if(statement->arguments.size()==3){
			m_material->m_color.m_diffuseColor[0]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_diffuseColor[1]=stringToFloat(statement->arguments[1]);
			m_material->m_color.m_diffuseColor[2]=stringToFloat(statement->arguments[2]);
		}
		else{
			throwSyntaxError();
		}
	}
	else if(statement->command == "ks"){
		if(statement->arguments.size()==1){
			m_material->m_color.m_specularColor[0]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_specularColor[1]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_specularColor[2]=stringToFloat(statement->arguments[0]);
		}else if(statement->arguments.size()==3){
			m_material->m_color.m_specularColor[0]=stringToFloat(statement->arguments[0]);
			m_material->m_color.m_specularColor[1]=stringToFloat(statement->arguments[1]);
			m_material->m_color.m_specularColor[2]=stringToFloat(statement->arguments[2]);
		}else{
			throwSyntaxError();
		}
	}
	else if(statement->command == "tf"){
		if(statement->arguments.size()==1){
			m_material->m_illum.m_transmissionFilter[0]=stringToFloat(statement->arguments[0]);
			m_material->m_illum.m_transmissionFilter[1]=stringToFloat(statement->arguments[0]);
			m_material->m_illum.m_transmissionFilter[2]=stringToFloat(statement->arguments[0]);
		}else if(statement->arguments.size()==3){
			m_material->m_illum.m_transmissionFilter[0]=stringToFloat(statement->arguments[0]);
			m_material->m_illum.m_transmissionFilter[1]=stringToFloat(statement->arguments[1]);
			m_material->m_illum.m_transmissionFilter[2]=stringToFloat(statement->arguments[2]);
		}else{
			throwSyntaxError();
		}
	}
	else if(statement->command == "illum"){
		m_material->m_illum.m_illum=atoi(statement->arguments[0].c_str());
	}
	// Segun wikipedia, algunas implementaciones usan "Tr" en vez de "d"
	else if(statement->command == "d" || statement->command == "tr"){
		if (statement->arguments[0]=="-halo"){
			m_material->m_illum.m_dissolveAmount=stringToFloat(statement->arguments[1]);
			m_material->m_illum.m_dhalo=true;
		}
		else{
			m_material->m_illum.m_dissolveAmount=stringToFloat(statement->arguments[0]);
			m_material->m_illum.m_dhalo=false;
		}
	}
	else if(statement->command == "ns"){
		m_material->m_illum.m_specularExponent=atoi(statement->arguments[0].c_str());
	}
	else if(statement->command== "sharpness"){
		m_material->m_illum.m_sharpness=atoi(statement->arguments[0].c_str());
	}
	else if(statement->command== "ni"){
		m_material->m_illum.m_opticalDensity=stringToFloat(statement->arguments[0]);
	}
	else if(statement->command=="map_ka"){
		m_material->m_mapping.m_ambientMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_ambientMaterial);
	}
	else if(statement->command=="map_kd"){
		m_material->m_mapping.m_diffuseMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_diffuseMaterial);
	}
	else if(statement->command=="map_ks"){
		m_material->m_mapping.m_specularMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_specularMaterial);
	}
	else if(statement->command=="map_ns"){
		m_material->m_mapping.m_specularExponentMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_specularExponentMaterial);
	}
	else if(statement->command=="map_d"){
		m_material->m_mapping.m_disolveMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_disolveMaterial);
	}
	else if(statement->command=="decal"){
		m_material->m_mapping.m_decalMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_decalMaterial);
	}
	else if(statement->command=="disp"){
		m_material->m_mapping.m_displacementMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_displacementMaterial);
	}
	else if(statement->command=="bump"){
		m_material->m_mapping.m_bumpMaterial = new MaterialTexture();
		processMaterialTexture(&statement->arguments, m_material->m_mapping.m_bumpMaterial);
		float m_mult;
	}
	/*
	else if(statement->command=="refl"){
		if(statement->arguments[1]=="sphere"){
			m_material->m_mapping.m_reflectionTexture = new ReflectionTexture();
			m_material->m_mapping.m_reflectionTexture->m_reflectionType=ReflectionTexture::ReflectionType::CUBE;
			MaterialTexture reflectionTexture;
			processMaterialTexture(&statement->arguments,&reflectionTexture);
			m_material->m_mapping.m_reflectionTexture->m_textures.push_back(reflectionTexture);
		}
		else {
			m_MaterialcubeTexture = new MaterialTexture();
			m_cubeTextures[statement->arguments[1]]=m_MaterialcubeTexture;
			processMaterialTexture(&statement->arguments, m_MaterialcubeTexture);
		}
		
	}*/
	else{
		//printf("%s not parsed \n",statement->command.c_str());
	}
}

void MaterialParser::endFile(){}

void MaterialParser::processMaterialTexture(vector<string>* params, MaterialTexture* currentTexture){
	for (int i = 0; i < params->size(); i++)
		//for(Statement stat:statement->arguments)
	{
		if((*params)[i]=="-blendu"){
			proccesBlendClamp(currentTexture,params,i);
		}
		if((*params)[i]=="-blendv"){
			proccesBlendClamp(currentTexture,params,i);
		}
		else if((*params)[i]=="-clamp"){
			proccesBlendClamp(currentTexture,params,i);
		}
		else if((*params)[i]=="-imfchan"){
			//to-do
		}
		else if((*params)[i]=="-mm"){
			try{
				currentTexture->m_mm[0]=atoi((*params)[i+1].c_str());
				currentTexture->m_mm[1]=atoi((*params)[i+2].c_str());
			}catch (invalid_argument){
				throwSyntaxError();
			}

		}
		else if((*params)[i]=="-o" ||(*params)[i]=="-s"||(*params)[i]=="-t"){
			proccesOST(currentTexture,params,i);
		}				

		else if((*params)[i]=="-texres"){
			currentTexture->m_resolution=atoi((*params)[i++].c_str());
		}

		else{
			currentTexture->m_filename=(*params)[params->size()-1];		
		}
	
	}
}
void MaterialParser::proccesBlendClamp(MaterialTexture* texture ,vector<string>* params,int index){
	if((*params)[index]=="-blendu"){
		if((*params)[index+1]=="on"){
			texture->m_blendu=true;
		}
		else if((*params)[index+1]=="off"){
			texture->m_blendu=false;
		}
		else{
			throwSyntaxError();
		}
	}
	else if((*params)[index]=="-blendv"){
		if((*params)[index+1]=="on"){
			texture->m_blendu=true;
		}
		else if((*params)[index+1]=="off"){
			texture->m_blendu=false;
		}
		else{
			throwSyntaxError();
		}
	}else if((*params)[index]=="-clamp"){
		if((*params)[index+1]=="on"){
			texture->m_clamp=true;
		}
		else if((*params)[index+1]=="off"){
			texture->m_clamp=false;
		}
		else{
			throwSyntaxError();
		}

	}
}
void MaterialParser::proccesOST(MaterialTexture* texture ,vector<string>* params,int index){
	for (int i = index; i < params->size(); i++){
		if((*params)[i]=="-o"){
			try{
				texture->m_offset[0]=atoi((*params)[i+1].c_str());
			}
			catch (invalid_argument){
				throwSyntaxError();
			}try{
				texture->m_offset[1]=atoi((*params)[i+2].c_str());
				try{
					texture->m_offset[2]=atoi((*params)[i+3].c_str());
				}catch(invalid_argument){
					continue;
				}
			}catch(invalid_argument){
				continue;
			}
		}
		else if((*params)[i]=="-s"){
			try{
				texture->m_scale[0]=atoi((*params)[i+1].c_str());
			}
			catch (invalid_argument){
				throwSyntaxError();
			}try{
				texture->m_scale[1]=atoi((*params)[i+2].c_str());
				try{
					texture->m_scale[2]=atoi((*params)[i+3].c_str());
				}catch(invalid_argument){
					continue;
				}
			}catch(invalid_argument){
				continue;
			}
		}
		else if((*params)[i]=="-t"){
			try{
				texture->m_turbulence[0]=atoi((*params)[i+1].c_str());
			}
			catch (invalid_argument){
				throwSyntaxError();
			}try{
				texture->m_turbulence[1]=atoi((*params)[i+2].c_str());
				try{
					texture->m_turbulence[2]=atoi((*params)[i+3].c_str());
				}catch(invalid_argument){
					continue;
				}
			}catch(invalid_argument){
				continue;
			}

		}

		}

	}
Material* MaterialParser::getMaterialModel()
{
	return m_material;
}

map<string,Material*>* MaterialParser::getMaterials()
{
	return m_materials;
}

/**
void MaterialParser::initializeDefaultVariables(Material *material){
	material->m_illum.m_dissolveAmount=1.0;
	material->m_illum.m_sharpness=60;
	//Temporal: material components inicialized with -1 can be depreciated
	material->m_illum.m_transmissionFilter[0]=-1;
	material->m_illum.m_transmissionFilter[1]=-1;
	material->m_illum.m_transmissionFilter[2]=-1;
	material->m_illum.m_specularExponent=-1;
	material->m_illum.m_sharpness=-1;
	material->m_illum.m_opticalDensity=-1;
	material->m_mapping.m_antialiasing=false;
	material->m_mapping.m_bumpMultiplier=false;
	material->m_mapping.m_reflectionTexture.m_reflectionType=ReflectionTexture::NONE;

	//Ambient material
	initializeMaterialTextureDefault(&(m_material->m_mapping.m_ambientMaterial));
	/*m_material->m_mapping.m_ambientMaterial.m_blendu= true;
	m_material->m_mapping.m_ambientMaterial.m_blendv= true;
	m_material->m_mapping.m_ambientMaterial.m_clamp= false;
	m_material->m_mapping.m_ambientMaterial.m_cc= false;
	m_material->m_mapping.m_ambientMaterial.m_mm[0]=0;
	m_material->m_mapping.m_ambientMaterial.m_mm[1]=1;
	m_material->m_mapping.m_ambientMaterial.m_o[0]=0;
	m_material->m_mapping.m_ambientMaterial.m_o[1]=0;
	m_material->m_mapping.m_ambientMaterial.m_o[2]=0;
	m_material->m_mapping.m_ambientMaterial.m_s[0]=1;
	m_material->m_mapping.m_ambientMaterial.m_s[1]=1;
	m_material->m_mapping.m_ambientMaterial.m_s[2]=1;
	m_material->m_mapping.m_ambientMaterial.m_t[0]=0;
	m_material->m_mapping.m_ambientMaterial.m_t[1]=0;
	m_material->m_mapping.m_ambientMaterial.m_t[2]=0;*/
//	initializeMaterialTextureDefault(&(m_material->m_mapping.m_diffuseMaterial));

	//diffuse material
	/*
	m_material->m_mapping.m_diffuseMaterial.m_blendu= true;
	m_material->m_mapping.m_diffuseMaterial.m_blendv= true;
	m_material->m_mapping.m_diffuseMaterial.m_clamp= false;
	m_material->m_mapping.m_diffuseMaterial.m_cc= false;
	m_material->m_mapping.m_diffuseMaterial.m_mm[0]=0;
	m_material->m_mapping.m_diffuseMaterial.m_mm[1]=1;
	m_material->m_mapping.m_diffuseMaterial.m_o[0]=0;
	m_material->m_mapping.m_diffuseMaterial.m_o[1]=0;
	m_material->m_mapping.m_diffuseMaterial.m_o[2]=0;
	m_material->m_mapping.m_diffuseMaterial.m_s[0]=1;
	m_material->m_mapping.m_diffuseMaterial.m_s[1]=1;
	m_material->m_mapping.m_diffuseMaterial.m_s[2]=1;
	m_material->m_mapping.m_diffuseMaterial.m_t[0]=0;
	m_material->m_mapping.m_diffuseMaterial.m_t[1]=0;
	m_material->m_mapping.m_diffuseMaterial.m_t[2]=0;*/
	//specular Material
//	initializeMaterialTextureDefault(&(m_material->m_mapping.m_specularMaterial));
	/*
	m_material->m_mapping.m_specularMaterial.m_blendu= true;
	m_material->m_mapping.m_specularMaterial.m_blendv= true;
	m_material->m_mapping.m_specularMaterial.m_clamp= false;
	m_material->m_mapping.m_specularMaterial.m_cc= false;
	m_material->m_mapping.m_specularMaterial.m_mm[0]=0;
	m_material->m_mapping.m_specularMaterial.m_mm[1]=1;
	m_material->m_mapping.m_specularMaterial.m_o[0]=0;
	m_material->m_mapping.m_specularMaterial.m_o[1]=0;
	m_material->m_mapping.m_specularMaterial.m_o[2]=0;
	m_material->m_mapping.m_specularMaterial.m_s[0]=1;
	m_material->m_mapping.m_specularMaterial.m_s[1]=1;
	m_material->m_mapping.m_specularMaterial.m_s[2]=1;
	m_material->m_mapping.m_specularMaterial.m_t[0]=0;
	m_material->m_mapping.m_specularMaterial.m_t[1]=0;
	m_material->m_mapping.m_specularMaterial.m_t[2]=0;
	*/
	//specular exponent 
//	initializeMaterialTextureDefault(&(m_material->m_mapping.m_specularExponentMaterial));
	/*
	m_material->m_mapping.m_specularExponentMaterial.m_blendu= true;
	m_material->m_mapping.m_specularExponentMaterial.m_blendv= true;
	m_material->m_mapping.m_specularExponentMaterial.m_clamp= false;
	m_material->m_mapping.m_specularExponentMaterial.m_cc= false;
	m_material->m_mapping.m_specularExponentMaterial.m_mm[0]=0;
	m_material->m_mapping.m_specularExponentMaterial.m_mm[1]=1;
	m_material->m_mapping.m_specularExponentMaterial.m_o[0]=0;
	m_material->m_mapping.m_specularExponentMaterial.m_o[1]=0;
	m_material->m_mapping.m_specularExponentMaterial.m_o[2]=0;
	m_material->m_mapping.m_specularExponentMaterial.m_s[0]=1;
	m_material->m_mapping.m_specularExponentMaterial.m_s[1]=1;
	m_material->m_mapping.m_specularExponentMaterial.m_s[2]=1;
	m_material->m_mapping.m_specularExponentMaterial.m_t[0]=0;
	m_material->m_mapping.m_specularExponentMaterial.m_t[1]=0;
	m_material->m_mapping.m_specularExponentMaterial.m_t[2]=0;
	*/
	//disolve material
//	initializeMaterialTextureDefault(&(m_material->m_mapping.m_disolveMaterial));
	/*
	m_material->m_mapping.m_disolveMaterial.m_blendu= true;
	m_material->m_mapping.m_disolveMaterial.m_blendv= true;
	m_material->m_mapping.m_disolveMaterial.m_clamp= false;
	m_material->m_mapping.m_disolveMaterial.m_cc= false;
	m_material->m_mapping.m_disolveMaterial.m_mm[0]=0;
	m_material->m_mapping.m_disolveMaterial.m_mm[1]=1;
	m_material->m_mapping.m_disolveMaterial.m_o[0]=0;
	m_material->m_mapping.m_disolveMaterial.m_o[1]=0;
	m_material->m_mapping.m_disolveMaterial.m_o[2]=0;
	m_material->m_mapping.m_disolveMaterial.m_s[0]=1;
	m_material->m_mapping.m_disolveMaterial.m_s[1]=1;
	m_material->m_mapping.m_disolveMaterial.m_s[2]=1;
	m_material->m_mapping.m_disolveMaterial.m_t[0]=0;
	m_material->m_mapping.m_disolveMaterial.m_t[1]=0;
	m_material->m_mapping.m_disolveMaterial.m_t[2]=0;*/
	//decal Material
//	initializeMaterialTextureDefault(&(m_material->m_mapping.m_decalMaterial));
	/*
	m_material->m_mapping.m_decalMaterial.m_blendu= true;
	m_material->m_mapping.m_decalMaterial.m_blendv= true;
	m_material->m_mapping.m_decalMaterial.m_clamp= false;
	m_material->m_mapping.m_decalMaterial.m_cc= false;
	m_material->m_mapping.m_decalMaterial.m_mm[0]=0;
	m_material->m_mapping.m_decalMaterial.m_mm[1]=1;
	m_material->m_mapping.m_decalMaterial.m_o[0]=0;
	m_material->m_mapping.m_decalMaterial.m_o[1]=0;
	m_material->m_mapping.m_decalMaterial.m_o[2]=0;
	m_material->m_mapping.m_decalMaterial.m_s[0]=1;
	m_material->m_mapping.m_decalMaterial.m_s[1]=1;
	m_material->m_mapping.m_decalMaterial.m_s[2]=1;
	m_material->m_mapping.m_decalMaterial.m_t[0]=0;
	m_material->m_mapping.m_decalMaterial.m_t[1]=0;
	m_material->m_mapping.m_decalMaterial.m_t[2]=0;
	*/
	//diplacement material
//	initializeMaterialTextureDefault(&(m_material->m_mapping.m_displacementMaterial));
	/*
	m_material->m_mapping.m_displacementMaterial.m_blendu= true;
	m_material->m_mapping.m_displacementMaterial.m_blendv= true;
	m_material->m_mapping.m_displacementMaterial.m_clamp= false;
	m_material->m_mapping.m_displacementMaterial.m_cc= false;
	m_material->m_mapping.m_displacementMaterial.m_mm[0]=0;
	m_material->m_mapping.m_displacementMaterial.m_mm[1]=1;
	m_material->m_mapping.m_displacementMaterial.m_o[0]=0;
	m_material->m_mapping.m_displacementMaterial.m_o[1]=0;
	m_material->m_mapping.m_displacementMaterial.m_o[2]=0;
	m_material->m_mapping.m_displacementMaterial.m_s[0]=1;
	m_material->m_mapping.m_displacementMaterial.m_s[1]=1;
	m_material->m_mapping.m_displacementMaterial.m_s[2]=1;
	m_material->m_mapping.m_displacementMaterial.m_t[0]=0;
	m_material->m_mapping.m_displacementMaterial.m_t[1]=0;
	m_material->m_mapping.m_displacementMaterial.m_t[2]=0;
	*/
	//bump material
//	initializeMaterialTextureDefault(&(m_material->m_mapping.m_bumpMaterial));
	/*
	m_material->m_mapping.m_bumpMaterial.m_blendu= true;
	m_material->m_mapping.m_bumpMaterial.m_blendv= true;
	m_material->m_mapping.m_bumpMaterial.m_clamp= false;
	m_material->m_mapping.m_bumpMaterial.m_cc= false;
	m_material->m_mapping.m_bumpMaterial.m_mm[0]=0;
	m_material->m_mapping.m_bumpMaterial.m_mm[1]=1;
	m_material->m_mapping.m_bumpMaterial.m_o[0]=0;
	m_material->m_mapping.m_bumpMaterial.m_o[1]=0;
	m_material->m_mapping.m_bumpMaterial.m_o[2]=0;
	m_material->m_mapping.m_bumpMaterial.m_s[0]=1;
	m_material->m_mapping.m_bumpMaterial.m_s[1]=1;
	m_material->m_mapping.m_bumpMaterial.m_s[2]=1;
	m_material->m_mapping.m_bumpMaterial.m_t[0]=0;
	m_material->m_mapping.m_bumpMaterial.m_t[1]=0;
	m_material->m_mapping.m_bumpMaterial.m_t[2]=0;
	*//*
}
*/