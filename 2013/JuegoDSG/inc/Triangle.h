#pragma once
#include "../stdafx.h"
#include "Vertex.h"
class Triangle
{
public:
	// Constructor
	Triangle();
	Triangle(Vertex v1, Vertex v2, Vertex v3);
	~Triangle(void);

	// Variables
	Vertex m_v1;
	Vertex m_v2;
	Vertex m_v3;
	bool m_normals;
	
	// Methods
	Vertex& operator[] (const int index);
	Vertex& getElement(const int index);
	
	friend ostream& operator<<(ostream& os, Triangle& t);
	string toString();
};

