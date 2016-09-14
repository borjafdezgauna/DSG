#ifndef __FANTASMA__
#define __FANTASMA__
#define MAX_NUM_MALOS 10
//Tambien se puede poner en lugar de esto el #pragma once

#define IZQUIERDA 0
#define ARRIBA 1
#define DERECHA 2
#define ABAJO 3

class ObjModel;

class Fantasma 
{
	//Pos int en cada momento
	int m_pos_x;
	int m_pos_y;

	//Pos real en cada momento
	double m_pos_real_x;
	double m_pos_real_y;

	//Posiciones reales de destino e inicio
	float m_posInicio[2];
	float m_posDestino[2];

	float angulo;

	//BANDERAS
	//bool m_mov_arriba;
	//bool m_mov_abajo;
	//bool m_mov_delante;
	//bool m_mov_tras;
	bool movs[4];

	//enMovimiento
	bool m_movimiento;
	
	bool m_atrapado;

	bool m_vivo;


	//static ObjModel* m_pObjModel;
	static int m_modelDisplayList;

public:
	//Constructor
	Fantasma();

	//Destructor
	~Fantasma();

	static void loadModel();
	
	//Metodos propios de la clase
	//Añadir el fantasma
	static void addFantasma(int x, int y);

	static void comenzarMovimiento();

	//Establecer un recorrido para el fantasma
	void moverFantasma();
	
	//Mueve el fantasma en posicion real
	void moverPosReal();

	//Coger coordenada X
	int getPosX();

	//Coger coordenada Z
	int getPosZ();

	void SetPos(int x,int y){m_pos_x= x;m_pos_y=y;}
	void SetPosReal(double x,double y){m_pos_real_x= x;m_pos_real_y=y;}
	void SetPosRealDestino(float x, float y){m_posDestino[0]=x;m_posDestino[1]=y;}
	void SetPosRealX(double x){m_pos_real_x=x;}
	void SetPosRealY(double y){m_pos_real_y=y;}

	//Devuelve la coordenada X modificada con el incremento/decremento
	float getPosRealX();

	//Devuelve la coordenada Z modificada con el incremento/decremento
	float getPosRealZ();

	//Saber si un fantasma ha sido atrapado
	bool getAtrapado();

	void setAtrapado(bool x);

	//Modificar en caso de que atrapen a un fantasma
	void setVivo(bool vida);

	//Saber si un fantasma esta vivo
	bool getVivo();

	static void draw();
//	void setRotation();
	
	/*
	Funcion que comprueba los huecos libres y actualiza la banderas
	*/
	void comprobarAlrededor(int x, int y);

	/*
		Devuelve lo que hay en cada casilla
	*/
	char getC(int x, int y);
	
	/*
		Devolver el numero de malos
	*/

	int getNumMalos();

	void esPillado(int x);

};

extern int g_num_malos;
extern Fantasma g_fantasmas[MAX_NUM_MALOS];


#endif