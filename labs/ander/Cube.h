#pragma once
class Cube
{
	double m_x, m_y, m_z;
	double m_yaw, m_pitch, m_roll;
	double m_scalex, m_scaley, m_scalez;
	float m_colorr, m_colorg, m_colorb;

public:
	Cube();
	virtual ~Cube();

	void draw();
	void setPosition(double m_x, double m_y, double m_z);
	void setRotation(double pitch, double yaw, double roll);
	void setScale(double m_x, double m_y, double m_z);
	void setColor(float r, float g, float b);
	void ApplyObjectTransformation();
	
	
};

