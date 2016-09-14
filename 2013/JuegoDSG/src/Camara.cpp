#include "../stdafx.h"
#include "../inc/Camara.h"
//Se ha hecho una unica clase para las camaras. Para indicar que la del plano principal o la 
//secundaria, se modifican los valores para cada una de ellas cuando se crean en el main

CCamara::CCamara()
{
	m_h=0;	//dimensiones de la camara
	m_w=0;
	m_x=0;	//posicion de la camara
	m_y=0;
	m_z=0;
	m_pitch=0.0;	//rotacion
	m_yaw=0.0;
	m_roll=0.0;
	m_xfinal = 0.0;
	m_yfinal = 0.0;
	m_vec_x= 0.0;
	m_vec_y= 0.0;
	

}
CCamara::~CCamara()
{
}
void CCamara::setDimension(int h, int w)
{
	m_h = h;
	m_w= w;
	
}

void CCamara::setPosition(double x, double y, double z)
{
	m_x = x;
	m_y= y;
	m_z = z;
	
}
void CCamara::setRotation(double pitch, double yaw, double roll)
{
	m_pitch = pitch;
	m_yaw = yaw;
	m_roll = roll;
}

void CCamara::setPositionFinal(float posxfinal, float posyfinal){
	m_xfinal = posxfinal;
	m_yfinal = posyfinal;
}
void CCamara::avance(bool sobrex, bool sobrey){
	m_avancex= sobrex;
	m_avancey= sobrey;
}
void CCamara::setAngulo(float angulo){
	m_vec_x= cos((angulo-90.f)*(2*3.141516)/360.f);
	m_vec_y= sin((angulo-90.f)*(2*3.141516)/360.f);
}
void CCamara::camara(bool mapa)
{
	if (mapa== false){ //camara del personaje
		//set projection matrix
		glViewport(0, 0, (GLsizei) m_w, (GLsizei) m_h); 
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		glFrustum (-1.0, 1.0, -1.0, 1.0, 3.5, 20.0);		
		
		//la vision del cubo es normal, no hay que modificar los ejes
		glMatrixMode (GL_MODELVIEW);
		glLoadIdentity ();
		
		float xtempo=m_x-m_vec_x*5;
		float ytempo=m_y-m_vec_y*5;
		
		gluLookAt(xtempo, ytempo, 5, m_x, m_y, 0, 0, 0, 1);

	}
	else{ //la camara secundaria, la de la vista general
		 
		glViewport(0.65*(float)m_w, 0.65*(float)m_h, 0.30*(float)m_w,0.33*(float)m_h);
		glMatrixMode (GL_PROJECTION); //Donde proyecta la camara	
		glLoadIdentity ();
		glFrustum (-1.0, 1.0, -1.0, 1.0, 2.5, 30.0);
	
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		gluLookAt(5, 1, 22.5, 5.000001, 5.000001, 0, 0, 0, 1);


	}
}

void CCamara::camPPers(float pposx,float pposy,int pangulo){

	double dangulo = (double)pangulo;
	double vec_x = cos(dangulo);
	double vec_y = sin(dangulo);

	float pp_x = pposx - vec_x*2.0;
	float pp_y = pposy - vec_y;

	
	gluLookAt(pp_x, pp_y, 0.0, pposx,pposy, 0.0, 0.0, 0.0, 0.0);








}




