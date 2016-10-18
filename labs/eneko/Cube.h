#pragma once
class Cube
{
	double mx, my, mz;
	double myaw, mpitch, mroll;
	double esX, esY, esZ;
	double c1, c2, c3;
public:
	Cube();
	virtual ~Cube();
	void draw();
	void setPosition(double x, double y, double z);
	void setRotation(double pitch, double yaw, double row);
	void setScale(double x, double y, double z);
	void setColor(double color1, double color2, double color3);
};

