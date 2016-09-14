#pragma once
#include "../stdafx.h"
#include "../inc/Material.h"
#include "../inc/Vertex.h"
#include "../inc/Triangle.h"
#include "../inc/FixedArray.h"

using namespace std;

class Group
{
public :
	#ifdef TEST
		typedef FixedArray<Triangle, 128> TriangleList;
	#else
		typedef FixedArray<Triangle*> TriangleList;
	#endif // TEST

private:
	Material* m_material;
	TriangleList* m_triangles;

public:
	string m_name;
	// Constructors
	Group();
	Group(string name);
	Group(string name, Group::TriangleList* triangles);
	~Group(void);


	// Methods
	string toString();
	string getName();
	void setMaterial(Material* m);
	void setTriangleList(TriangleList* triangleList);
	TriangleList* getTriangleList();
	Material* getMaterial();
};