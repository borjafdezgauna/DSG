#pragma once
class Cube
{
	double x, y, z;
	double yaw, pitch, roll;
	double scaleX, scaleY, scaleZ;
	double red, green, blue;

public:
	Cube();
	~Cube();

	void draw();

	void setPosition(double x, double y, double z);

	void setRotation(double yaw, double pitch, double roll);

	void setScale(double scaleX, double scaleY, double scaleZ);

	void setColor(double red, double green, double blue);
};

