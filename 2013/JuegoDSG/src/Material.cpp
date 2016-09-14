#include "../inc/Material.h"
#include <string.h>
#include <algorithm>
#include <sstream>


	
Material::Material(void){
	initialize();
}

Material::Material(string name)
{
	m_name=name;
	initialize();
}

void Material::initialize(){
	m_illum.m_dissolveAmount=1.0;
	m_illum.m_sharpness=60;
	//Temporal: material components inicialized with -1 can be depreciated
	m_illum.m_transmissionFilter[0]=-1;
	m_illum.m_transmissionFilter[1]=-1;
	m_illum.m_transmissionFilter[2]=-1;
	m_illum.m_specularExponent=-1;
	m_illum.m_sharpness=-1;
	m_illum.m_opticalDensity=-1;

	
	m_mapping.m_ambientMaterial = NULL;//map_ka material ambient is multiplied by the texture value
	m_mapping.m_diffuseMaterial = NULL;//map_kd material diffuse is multiplied by the texture value
	m_mapping.m_specularMaterial = NULL;//map_ks material specular is multiplied by the texture value
	m_mapping.m_specularExponentMaterial = NULL;//map_NS material specular exponent is multiplied by the texture value
	m_mapping.m_disolveMaterial = NULL;//map_d material dissolve is multiplied by the texture value
	m_mapping.m_decalMaterial = NULL;// uses a scalar value to deform the surface of an object to create surface roughness
	m_mapping.m_displacementMaterial = NULL;//Specifies that a scalar texture is used to deform the surface of an object, creating surface roughness.
	m_mapping.m_bumpMaterial = NULL;
	m_mapping.m_reflectionTexture = NULL; 

	m_mapping.m_antialiasing=false;
	m_mapping.m_bumpMultiplier=false;
}

Material::~Material(void)
{
}
string Material::toString(){
	ostringstream output;
	output << "Material: " << endl << 
		    "Filename: " << m_name << endl << 
			"		: "  <<""<< endl <<
			"MaterialColor: " << "" << endl <<
			"		: "  <<""<< endl <<
			"    AmbientColor: " <<""<< endl << m_color.m_ambientColor[0]<< endl <<
			"		2 " << m_color.m_ambientColor[1]<< endl <<
			"		3 " << m_color.m_ambientColor[2]<< endl <<
			"		: "  <<""<< endl <<
			"    DiffusseColor: " << "" << endl <<
			"		1 " << m_color.m_diffuseColor[0]<< endl <<
			"		2 " << m_color.m_diffuseColor[1]<< endl <<
			"		3 " << m_color.m_diffuseColor[2]<< endl <<
			"		: "  <<""<< endl <<
			"    SpecularColor: " << " "<< endl <<
			"		1 " << m_color.m_specularColor[0]<< endl <<
			"		2 " << m_color.m_specularColor[1]<< endl <<
			"		3 " << m_color.m_specularColor[2]<< endl <<
			"		: "  <<""<< endl <<
			"MaterialIllum: " << "" << endl <<
			"		: "  <<""<< endl <<
			"    TransmissionFilter: " <<""<< endl <<
			"		: "  <<""<< endl <<
			"		1 " << m_illum.m_transmissionFilter[0]<< endl <<
			"		2 " << m_illum.m_transmissionFilter[1]<< endl <<
			"		3 " << m_illum.m_transmissionFilter[2]<< endl <<
			"		: "  <<""<< endl <<
			"    IlluminationModel: " <<m_illum.m_illum<< endl <<
			"    DissolveAmount: " <<m_illum.m_dissolveAmount<< endl <<
			"    DissolveHalo: " <<m_illum.m_dhalo<< endl <<
			"    SpecularExponent: " <<m_illum.m_specularExponent<< endl <<
			"    Sharpness: " <<m_illum.m_sharpness<< endl <<
			"    OpicalDensity: " <<m_illum.m_opticalDensity<< endl <<
			"		: "  <<""<< endl <<
			"MaterialMapping: " <<""<< endl <<
			"		: "  <<""<< endl;
			if(m_mapping.m_ambientMaterial !=NULL ){
			output << 
			"    AmbientMaterial: " << endl <<
			"		Blendu: "  <<m_mapping.m_ambientMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_ambientMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_ambientMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_ambientMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_ambientMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_ambientMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_ambientMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_ambientMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_ambientMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_ambientMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_ambientMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_ambientMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_ambientMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_ambientMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_ambientMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_ambientMaterial->m_turbulence[2]<< endl <<
			"		Filename: "  <<m_mapping.m_ambientMaterial->m_filename<< endl <<
			"		: "  <<""<< endl;
			}
			if(m_mapping.m_diffuseMaterial !=NULL ){
			output << 
			"    DiffuseMaterial: " <<""<< endl <<
			"		Blendu: "  <<m_mapping.m_diffuseMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_diffuseMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_diffuseMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_diffuseMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_diffuseMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_diffuseMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_diffuseMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_diffuseMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_diffuseMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_diffuseMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_diffuseMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_diffuseMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_diffuseMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_diffuseMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_diffuseMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_diffuseMaterial->m_turbulence[2]<< endl <<

			"		Filename: "  <<m_mapping.m_diffuseMaterial->m_filename<< endl <<
			"		: "  <<""<< endl;
			}
			if(m_mapping.m_specularMaterial != NULL){
			output <<
			"    SpecularMaterial: " <<""<< endl <<
			"		Blendu: "  <<m_mapping.m_specularMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_specularMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_specularMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_specularMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_specularMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_specularMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_specularMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_specularMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_specularMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_specularMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_specularMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_specularMaterial->m_turbulence[2]<< endl <<
	
			"		Filename: "  <<m_mapping.m_specularMaterial->m_filename<< endl <<
			"		: "  <<""<< endl;
			}
			if(m_mapping.m_specularExponentMaterial != NULL){
			output <<
			"    SpecularExponentMaterial: " <<""<< endl <<
			"		Blendu: "  <<m_mapping.m_specularExponentMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_specularExponentMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_specularExponentMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_specularExponentMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_specularExponentMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularExponentMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_specularExponentMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularExponentMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_specularExponentMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_specularExponentMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularExponentMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_specularExponentMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_specularExponentMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_specularExponentMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_specularExponentMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_specularExponentMaterial->m_turbulence[2]<< endl <<
			
			"		Filename: "  <<m_mapping.m_specularExponentMaterial->m_filename<< endl <<
			"		: "  <<""<< endl;
			}
			if(m_mapping.m_disolveMaterial != NULL){
			output <<
			"    DisolveMaterial: " <<""<< endl <<
			"		Blendu: "  <<m_mapping.m_disolveMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_disolveMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_disolveMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_disolveMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_disolveMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_disolveMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_disolveMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_disolveMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_disolveMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_disolveMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_disolveMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_disolveMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_disolveMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_disolveMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_disolveMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_disolveMaterial->m_turbulence[2]<< endl <<
			
			"		Filename: "  <<m_mapping.m_disolveMaterial->m_filename<< endl <<
 			"		: "  <<""<< endl;
			}
			if(m_mapping.m_decalMaterial != NULL){
			output <<
			"    DecalMaterial: " <<""<< endl <<
			"		Blendu: "  <<m_mapping.m_decalMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_decalMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_decalMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_decalMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_decalMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_decalMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_decalMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_decalMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_decalMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_decalMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_decalMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_decalMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_decalMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_decalMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_decalMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_decalMaterial->m_turbulence[2]<< endl <<
			
			"		Filename: "  <<m_mapping.m_decalMaterial->m_filename<< endl <<
			"		: "  <<""<< endl;
			}
			if(m_mapping.m_displacementMaterial != NULL){
			output <<
			"    DisplacementMaterial: " << endl <<
			"		Blendu: "  <<m_mapping.m_displacementMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_displacementMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_displacementMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_displacementMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_displacementMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_displacementMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_displacementMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_displacementMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_displacementMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_displacementMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_displacementMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_displacementMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_displacementMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_displacementMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_displacementMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_displacementMaterial->m_turbulence[2]<< endl <<
			
			"		Filename: "  <<m_mapping.m_displacementMaterial->m_filename<< endl <<
			"		: "  <<""<< endl;
			}
			if(m_mapping.m_bumpMaterial != NULL){
				output <<
			"    BumpMaterial: " <<""<< endl <<
			"		Blendu: "  <<m_mapping.m_bumpMaterial->m_blendu<< endl <<
			"		Blendv: "  <<m_mapping.m_bumpMaterial->m_blendv<< endl <<
			"		BumpMultiplier: "  <<m_mapping.m_bumpMaterial->m_bumpMultiplier<< endl <<
			"		CC: "  <<m_mapping.m_bumpMaterial->m_cc<< endl <<
			"		Clamp: "  <<m_mapping.m_bumpMaterial->m_clamp<< endl <<
			"		MM: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_bumpMaterial->m_mm[0]<< endl <<
			"			2: "  <<m_mapping.m_bumpMaterial->m_mm[1]<< endl <<
			"		O: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_bumpMaterial->m_offset[0]<< endl <<
			"			2: "  <<m_mapping.m_bumpMaterial->m_offset[1]<< endl <<
			"			3: "  <<m_mapping.m_bumpMaterial->m_offset[2]<< endl <<

			"		S: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_bumpMaterial->m_scale[0]<< endl <<
			"			2: "  <<m_mapping.m_bumpMaterial->m_scale[1]<< endl <<
			"			3: "  <<m_mapping.m_bumpMaterial->m_scale[2]<< endl <<

			"		T: "  <<""<< endl <<
			"			1: "  <<m_mapping.m_bumpMaterial->m_turbulence[0]<< endl <<
			"			2: "  <<m_mapping.m_bumpMaterial->m_turbulence[1]<< endl <<
			"			3: "  <<m_mapping.m_bumpMaterial->m_turbulence[2]<< endl <<
			

			"		Filename: "  <<m_mapping.m_bumpMaterial->m_filename<<endl<<  //<<
			"reflectionType: "  <<m_mapping.m_reflectionTexture->m_reflectionType<<endl; //<<
//			"		vectorSize: "  <<m_mapping.m_reflectionTexture.m_textures.size()  <<endl; //<<
			}
			/*)
			std::vector<MaterialTexture>::iterator itr;
			for ( itr = m_mapping.m_reflectionTexture.m_textures.begin(); itr < m_mapping.m_reflectionTexture.m_textures.end(); ++itr )
			{
				output <<"  " << " "<< endl<<
				"		Blendu: "  <<(*itr).m_blendu<< endl <<
				"		Blendv: "  <<(*itr).m_blendv<< endl <<
				"		BumpMultiplier: "  <<(*itr).m_bumpMultiplier<< endl <<
				"		CC: "  <<(*itr).m_cc<< endl <<
				"		Clamp: "  <<(*itr).m_clamp<< endl <<
				"		MM: "  <<""<< endl <<
				"			1: " << (*itr).m_mm[0]<< endl <<
				"			2: "  <<(*itr).m_mm[1]<< endl <<
				"		O: "  <<""<< endl <<
				"			1: "  <<(*itr).m_offset[0]<< endl <<
				"			2: "  <<(*itr).m_offset[1]<< endl <<
				"			3: "  <<(*itr).m_offset[2]<< endl <<
	
				"		S: "  <<""<< endl <<
				"			1: "  <<m_mapping.m_bumpMaterial->m_scale[0]<< endl <<
				"			2: "  <<m_mapping.m_bumpMaterial->m_scale[1]<< endl <<
				"			3: "  <<m_mapping.m_bumpMaterial->m_scale[2]<< endl <<

				"		T: "  <<""<< endl <<
				"			1: "  <<m_mapping.m_bumpMaterial->m_turbulence[0]<< endl <<
				"			2: "  <<m_mapping.m_bumpMaterial->m_turbulence[1]<< endl <<
				"			3: "  <<m_mapping.m_bumpMaterial->m_turbulence[2]<< endl <<
			

				"		Filename: "  <<m_mapping.m_bumpMaterial->m_filename<<endl;  //<<


			}
			//"		Filename: "  <<m_mapping.m_reflectionTexture.m_textures[0].m_mm[0]<< endl; //<<

			*/
			
			//output << endl;

			
	
	
	return output.str();
	
}



