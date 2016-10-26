#pragma once
class Cube
{
	double m_x, m_y, m_z;
	double m_yaw, m_pitch, m_roll;
	double m_scale_x, m_scale_y, m_scale_z;
	double c1, c2, c3;

public:
	Cube();
	virtual ~Cube();
	void draw();
	void setPosition(double x, double y, double z);
	void setRotation(double pitch, double yaw, double roll);
	void setScale(double x, double y, double z);
	void setColor(double color1, double color2, double color3);
};

