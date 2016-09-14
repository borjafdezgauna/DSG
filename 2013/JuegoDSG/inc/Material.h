#pragma once
#include "MaterialTexture.h"
#include "ReflectionTexture.h"
class Material
{	
private:
	void initialize();
public:
	struct MaterialColor{
		float m_ambientColor[3];//ka
		float m_diffuseColor[3];//kd
		float m_specularColor[3];//ks
	};
	
	struct MaterialIllum{
		float m_transmissionFilter[3];//tf
		int m_illum; //illum model from 0 to 10
		float m_dissolveAmount;
		bool m_dhalo;
		int m_specularExponent;
		int m_sharpness;//from 0 to 1000->default is 60
		float m_opticalDensity;
	};
	
	struct MaterialMapping{
		MaterialTexture* m_ambientMaterial;//map_ka material ambient is multiplied by the texture value
		MaterialTexture* m_diffuseMaterial;//map_kd material diffuse is multiplied by the texture value
		MaterialTexture* m_specularMaterial;//map_ks material specular is multiplied by the texture value
		MaterialTexture* m_specularExponentMaterial;//map_NS material specular exponent is multiplied by the texture value
		MaterialTexture* m_disolveMaterial;//map_d material dissolve is multiplied by the texture value
		bool m_antialiasing;// Turns on anti-aliasing of textures in this material without anti-aliasing all textures in the scene.

		MaterialTexture* m_decalMaterial;// uses a scalar value to deform the surface of an object to create surface roughness
		MaterialTexture* m_displacementMaterial;//Specifies that a scalar texture is used to deform the surface of an object, creating surface roughness.
		MaterialTexture* m_bumpMaterial;
		float m_bumpMultiplier;//bumpMaterihal multiplier added because is not included on MaterialTexture
		ReflectionTexture* m_reflectionTexture; 
	};
	
	
	string m_name;

	MaterialColor m_color;
	MaterialIllum m_illum;
	MaterialMapping m_mapping;

	string toString();
	
	Material(string m_name);
	Material();
	~Material();
};