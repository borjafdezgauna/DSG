#pragma once
#include "../stdafx.h"
#include <exception>

using namespace std;
class MaterialTexture
{

public:

	//////    Exceptions    //////////////////////////////////////////////////
	class TextureFileNotFound : public runtime_error{
	public:
		TextureFileNotFound::TextureFileNotFound(string filename) 
			: std::runtime_error("Texture file does not exist"){};
	};

	MaterialTexture(bool m_blendu,bool m_blendv,float m_bumpMultiplier,bool m_cc,bool m_clamp,int m_mm[2],int m_o[3],int m_s[3],int m_t[3],int m_texres,std::string filename);
	MaterialTexture(void);
	void loadTexture();
	~MaterialTexture(void);

	// Variables
	bool m_blendu; //The default is on
	bool m_blendv; //The default is on
	float m_bumpMultiplier;
	bool m_cc;
	bool m_clamp;//The default is off.
	//IMFCHAN falta por poner
	int m_mm[2];//The default base[0]=0 gain[1]=1
	int m_offset[3];// The default is 0, 0, 0.
	int m_scale[3];//The default is 1, 1, 1.
	int m_turbulence[3];//The default is 0, 0, 0
	int m_resolution;
	std::string m_filename;
	unsigned int m_textureId;
};

