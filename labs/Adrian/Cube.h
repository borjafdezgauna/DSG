#pragma once
class Cube
{
	double m_x, m_y, m_z;
	double m_yaw, m_pitch, m_roll;
	double m_sx, m_sy, m_sz;
	int m_r, m_g, m_b;
public:
	Cube();
	virtual ~Cube();

	void draw();
	void setPosition(double x, double y, double z);
	void setRotation(double pitch, double yaw, double roll);
	void setScale(double x, double y, double z);
	void setColor(double r, double g, double b);
};

