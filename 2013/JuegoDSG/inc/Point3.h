#pragma once
#include <string>
using namespace std;
class Point3
{
public:
	// Variables 
	float m_x;
	float m_y;
	float m_z;	

	// Constructor
	Point3(void);
	Point3(float x, float y, float z);
	~Point3(void);

	// Methods
	Point3 operator+ (Point3);
	Point3 operator- (Point3);
	Point3 operator* (float);
	Point3 operator/ (float);
	void normalize(void);
	Point3 crossProduct(Point3);
	string toString(void);
	
	static Point3 getVector(Point3 p1,Point3 p2);
};