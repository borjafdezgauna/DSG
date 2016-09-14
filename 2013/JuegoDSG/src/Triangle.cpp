#include "../inc/Triangle.h"
#include <sstream>


//Triangle::Triangle(void)
//{
//}


Triangle::Triangle(){}

Triangle::Triangle(Vertex v1, Vertex v2, Vertex v3)
{
	m_v1 = v1;
	m_v2 = v2;
	m_v3 = v3;
	m_normals = false;
}

Triangle::~Triangle(void){

}

string Triangle::toString(){
	ostringstream output;
	output << "Triangle:\n  " << m_v1.toString() << "\n  " << m_v2.toString() << "\n  " << m_v3.toString();
	return output.str();
}

Vertex& Triangle::operator[](const int index){
	return getElement(index);
}
Vertex& Triangle::getElement(const int index){
	switch(index){
		case 0: return m_v1;break;
		case 1: return m_v2;break;
		case 2: return m_v3;break;
		default: return m_v3;break;
	} 
}
ostream& operator<<(ostream& os, Triangle& t){
	os << t.toString();
	return os;
}
