#ifndef __Personaje__
#define __Personaje__

class ObjModel;

//Definimos la clase personaje mediante un patr�n Singleton
class CPersonaje
{
	
	float realX;		//Las variables realX y realY las utilizaremos para concretar la posici�n real del personaje
	float realY;
	float actualX;		//Las variables actualX y actualY indican la celda en la que se encuentra el personaje
	float actualY;
	float finalX;		//Las variables finalX y finalY indican la celda de destino
	float finalY;
	float angulo;		//Dos �ngulos que nos servir�n para indicar cu�l es el �ngulo actual y cu�l el siguiente
	float anguloSig;
	bool enMovimiento;	//Esta variable nos indicar� si est� en movimiento cuando est� girando
	bool avanzandoX;	//avanzandoX nos indica si se mueve en el eje X
	bool avanzandoY;	//avanzandoY nos indica si se mueve en el eje Y
	bool teclaA;		//teclaA y teclaD corresponden a las teclas de direcci�n que utilizamos para girar
	bool teclaD;
	bool teclaW;		//teclaW y teclaS se utilizan para saber si va hacia delante o hacia atr�s
	bool teclaS;
	int frps;			//En esta variable guardaremos los frames por segundo
	int dir;			//dir puede ser 0,1,2 o 3; dependiendo de la direcci�n a la que mire
	

//A�adimos como public todos los m�todos a os que tendr�n acceso el resto de clases, as� como el constructor de la instancia,
//cuyo m�todo devuelve un puntero a la instancia (que ser� �nica).
public:
	
	void setPositionRealXY(float x, float y);
	void setPositionActualXY(float x, float y);
	void setPositionFinalXY(float x, float y);
	float getPositionRealX(void);
	float getPositionRealY(void);
	float getPositionActualX(void);
	float getPositionFinalX(void);
	float getPositionActualY(void);
	float getPositionFinalY(void);
	float getAngulo(void);
	void setPosition(float x, float y);
	void setRotation(void);
	void moverDerecha(void);
	void moverIzquierda(void);
	void moverRecto(void);
	void moverAtras(void);
	bool hayParedDelante(float x, float y);
	bool hayParedDetras(float x, float y);
	void draw(void);
	void actualizar(void);
	void encontrarFantasma(void);
	static CPersonaje* Instance();
	static void loadModel();
	bool avanceX(void);
	bool avanceY(void);

//Como protected, declararemos el constructor y el destructor 
protected:
	CPersonaje(void);
	~CPersonaje(void);
	CPersonaje(const CPersonaje & );
    CPersonaje &operator= (const CPersonaje & );

//Declaramos como private un puntero est�tico privado a su instancia
private:
	static CPersonaje* pinstance;
	static int m_modelDisplayList;
};

#endif