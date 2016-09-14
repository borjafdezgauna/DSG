#include "../inc/MaterialTexture.h"

MaterialTexture::MaterialTexture(void)
{
	m_blendu= true;
	m_blendv= true;
	m_clamp= false;
	m_cc= false;
	m_mm[0]=0;
	m_mm[1]=1;
	m_offset[0]=0;
	m_offset[1]=0;
	m_offset[2]=0;
	m_scale[0]=1;
	m_scale[1]=1;
	m_scale[2]=1;
	m_turbulence[0]=0;
	m_turbulence[1]=0;
	m_turbulence[2]=0;
	m_bumpMultiplier=-1;
	m_textureId = 0;
}

MaterialTexture::MaterialTexture(bool blendu,bool blendv,float bumpMultiplier,bool cc,bool clamp,int mm[2],int o[3],int s[3],int t[3],int texres,std::string filename)
{
	m_blendu=blendu;
	m_blendv=blendv;
	m_bumpMultiplier=bumpMultiplier;
	m_cc=cc;
	m_clamp=clamp;
	memcpy(m_mm,mm,2);
	memcpy(m_offset,o,3);
	memcpy(m_scale,s,3);
	memcpy(m_turbulence,t,3);
	m_resolution=texres;
	m_filename=filename;

}

void MaterialTexture::loadTexture()
{
	char textureName[256];

	if(m_filename!=""){
		sprintf_s(textureName,256,"texturas/%s",m_filename.c_str());
		m_textureId= SOIL_load_OGL_texture( textureName,SOIL_LOAD_RGBA,0,SOIL_FLAG_INVERT_Y);
		if(m_textureId==0){
			throw TextureFileNotFound(m_filename);
		}
		else{
			std::cout << "Texture file: " << m_filename << " loaded successfully" << std::endl;
		}
	}
}

MaterialTexture::~MaterialTexture(void)
{
}



