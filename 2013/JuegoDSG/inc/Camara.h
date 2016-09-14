#pragma once

class CCamara
{
	int m_h;
	int m_w;
	double m_x;
	double m_y;
	double m_z;
	double m_pitch;
	double m_yaw;
	double m_roll;
	float m_xfinal;
	float m_yfinal;
	bool m_avancex;
	bool m_avancey;
	float m_vec_x;
	float m_vec_y;
	

public: CCamara();
		~CCamara();

void setPosition(double x, double y, double z);
void setRotation(double pitch, double yaw, double roll);
void setDimension(int h, int w);
void setPositionFinal(float posxfinal, float posyfinal);
void avance(bool sobrex, bool sobrey);
void setAngulo(float angulo);

//void camaraGeneral(float g_w,float g_h,float g_roll, float g_yaw,float g_pitch,float g_x,float g_y,float g_z);
//void camaraPersonaje(float g_w,float g_h,float g_roll,float g_yaw,float g_pitch,float g_x,float g_y,float g_z, bool T_atras);
void camara( bool mapa);
void camPPers(float pposx,float pposy,int pangulo); //camara en primera persona

};
