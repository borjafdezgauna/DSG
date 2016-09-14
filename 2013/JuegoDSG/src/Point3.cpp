#include "../inc/Point3.h"
#include <math.h>
#include <string>
#include <sstream>

Point3::Point3(){}

Point3::Point3(float x,float y,float z){
	m_x=x;
	m_y=y;
	m_z=z;
}

Point3::~Point3(void){}

Point3 Point3::operator+(Point3 other){
	Point3 temp = Point3(m_x + other.m_x,
						 m_y + other.m_y,
						 m_z + other.m_z);
	return temp;
}

Point3 Point3::operator-(Point3 other){
	Point3 temp = Point3(m_x - other.m_x,
						 m_y - other.m_y,
						 m_z - other.m_z);
	return temp;
}

Point3 Point3::operator*(float scalar){
	Point3 temp = Point3(m_x * scalar,
					     m_y * scalar,
						 m_z * scalar);
	return temp;
}

Point3 Point3::operator/(float scalar){
	Point3 temp = Point3(m_x / scalar,
					     m_y / scalar,
						 m_z / scalar);
	return temp;
}

void Point3::normalize(void){
	float module = sqrt(pow(m_x,2) + pow(m_y,2) + pow(m_z,2));
	m_x = m_x / module;
	m_y = m_y / module;
	m_z = m_z / module;
}

Point3 Point3::crossProduct(Point3 v){
	float cx = (m_y * v.m_z) - (v.m_y * m_z);
	float cy = -((m_x * v.m_z) - (v.m_x * m_z));
	float cz = (m_x * v.m_y) - (v.m_x * m_y);
	Point3 temp = Point3(cx,cy,cz);
	return temp;
}

string Point3::toString(){
	ostringstream output;
	output << "Point3: " << m_x << " " << m_y << " " << m_z;
	return output.str();
}

Point3 Point3::getVector(Point3 p1,Point3 p2){
	return p2 - p1;
}