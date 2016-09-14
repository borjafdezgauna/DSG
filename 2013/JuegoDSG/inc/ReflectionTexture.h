#pragma once
#include "MaterialTexture.h"
#include <vector>
using namespace std;
class ReflectionTexture
{	
public:
	ReflectionTexture();

	enum ReflectionType{NONE,SPHERE,CUBE};
	vector<MaterialTexture> m_textures;
	//ReflectionTexture(ReflectionType m_reflectionType,vector<MaterialTexture> m_textures);
	~ReflectionTexture();
	ReflectionType m_reflectionType;


};

