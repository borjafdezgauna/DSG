#pragma once
#include "Triangle.h"
#include "FixedArray.h"
class SmoothGroup
{
public:
	typedef FixedArray<Triangle*> TriangleList;

	// Constructor
	SmoothGroup(int smoothId);
	~SmoothGroup(void);

	// Variables
	int m_smoothId;
	bool m_has_vn;
	TriangleList* m_triangles;

	// Methods
	string toString(void);
	void generateNormals(void);
	void setTriangles(SmoothGroup::TriangleList* triangles);
	void setHasVn(bool has_vn);
	int getId();
	void setTriangleList( FixedArray<Triangle*>* param1 );
};