#include "../inc/Vertex.h"
#include "../stdafx.h"
#include <sstream>

Vertex::Vertex(){}

Vertex::Vertex(long vid, float v[], float vt[], float vn[], bool normal)
{
	m_vid = vid;
	m_v = Point3(v[0],v[1],v[2]);
	m_vt = Point3(vt[0],vt[1],vt[2]);
	m_vn = Point3(vn[0],vn[1],vn[2]);
	m_normal = normal;
}

//TO-DO
Vertex::~Vertex(void){}

string Vertex::toString(){
	ostringstream output;
	output	<< "Vertex id " << m_vid
			<< "\n    v: " << m_v.toString()
			<< "\n    vt: " << m_vt.toString()
			<< "\n    vn: " << m_vn.toString()
			<< "\n    normal: " << m_normal;
	return output.str();
}