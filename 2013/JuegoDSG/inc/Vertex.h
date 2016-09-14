#pragma once
#include "Point3.h"

class Vertex
{
public:
	// Variables
	long m_vid;
	Point3 m_v;
	Point3 m_vt;
	Point3 m_vn;
	float m_weight;
	bool m_normal;

	// Constructor
	Vertex();
	Vertex(long vid, float v[], float vt[], float vn[], bool normal);
	~Vertex(void);

	// Methods
	string toString(void);
};

