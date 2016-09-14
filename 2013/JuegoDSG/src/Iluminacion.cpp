//Iluminacion.cpp
//Autor: Borja Pérez Sánchez

#include "../stdafx.h"
#include "../inc/Iluminacion.h"
#include "../inc/FrameRate.h"
#include "../inc/Personaje.h"
#include "../inc/Escenario.h"
#include "../inc/Fantasma.h"

/* Características de la iluminación
------------------------------------
- Luces:
GL_LIGHT0: Luz direccional proveniente de arriba que durante la partida será tenue para evitar la oscuridad total y
cuando el personaje gane se intensificará para hacer un efecto especial, consistente en iluminar todo el escenario de
forma fija primero y luego con un parpadeo
GL_LIGHT1: Foco de luz que seguirá en todo momento al personaje hasta que gane
GL_LIGHT2: Foco de luz que iluminará a un malo atrapado. Durante el proceso de eliminación del malo este foco primero
se mantendrá fijo y luego parpadeará. Justo cuando acabe este efecto especial el malo desaparecerá
GL_LIGHT3, GL_LIGHT4, GL_LIGHT5 y GL_LIGHT6: Focos de luz que forman parte del segundo efecto especial cuando el 
personaje ha ganado, consistente en 2 focos horizontales y 2 focos verticales que se mueven cíclicamente por el 
escenario hasta que se cierre el juego

- La velocidad del parpadeo de las luces es directamente proporcional a los FPS (división entera FPS / 4 parpadeos por 
segundo)
*/

float ancho; //Ancho del escenario (eje X)
float alto; //Alto del escenario (eje Y)
const float ALTURA = 20.0f; //Altura fija a la que están los focos (eje Z)
const float FOCO_P = 1.4f; //Medio ángulo del foco del personaje (ajustar según el modelo del personaje)
const float FOCO_M = 1.7f; //Medio ángulo del foco del malo (ajustar según el modelo del malo)
int fps; //Frame rate
int segundo; //Supone aprox. 1 segundo de ejecución, en base a los FPS
const int FIJO_M = 1; //Segundos que dura el foco fijo sobre un malo
const int PARPADEANTE_M = 1; //Segundos que dura el foco parpadeante sobre un malo
const int FIJO_V = 2; //Segundos que dura la luz direccional fija cuando se gana
const int PARPADEANTE_V = 1; //Segundos que dura la luz direccional parpadeante cuando se gana
float foco_f; //Medio ángulo de los focos finales (depende de las dimensiones del escenario)
const int TIEMPO = 2; //Segundos que tardan en recorrer el escenario los focos finales
CPersonaje* personaje;
Escenario* escenario;

//Propiedades de la luz direccional (GL_LIGHT0)
const float light_position0[] = {0.0, 0.0, 1.0, 0.0}; //Luz direccional (w = 0) apuntando al eje Z negativo 
const float light_ambient0[] = { 0.1, 0.1, 0.1, 1.0 }; //Luz ambiental blanca muy floja, para que lo no iluminado 
//esté más oscuro
const float light_specular0[] = { 0.0, 0.0, 0.0, 1.0 }; //Luz especular (brillos)

//Propiedades del foco sobre el personaje (GL_LIGHT1)
const float light_ambient1[] = { 0.1, 0.1, 0.1, 1.0 }; 
const float light_diffuse1[] = { 1.0, 1.0, 1.0, 1.0 }; //Luz difusa blanca al máximo
const float light_specular1[] = { 0.0, 0.0, 0.0, 1.0 }; 
const float light_spot_direction1[] = { 0.0, 0.0, -1.0 }; //Dirección del foco (mira al eje Z negativo)

//Propiedades del foco sobre un malo (GL_LIGHT2)
const float light_ambient2[] = { 0.1, 0.1, 0.1, 1.0 };
const float light_diffuse2[] = { 1.0, 1.0, 1.0, 1.0 };
const float light_specular2[] = { 0.0, 0.0, 0.0, 1.0 };
const float light_spot_direction2[] = { 0.0, 0.0, -1.0 };

//Propiedades del primer foco final (vertical 1) (GL_LIGHT3)
float x_foco3; //Posición X del foco 3
float y_foco3; //Posición Y del foco 3 que se actualizará dinámicamente en cada frame
const float light_ambient3[] = { 0.1, 0.1, 0.1, 1.0 };
const float light_diffuse3[] = { 1.0, 1.0, 1.0, 1.0 };
const float light_specular3[] = { 0.0, 0.0, 0.0, 1.0 };
const float light_spot_direction3[] = { 0.0, 0.0, -1.0 };
bool adelante3 = true;

//Propiedades del segundo foco final (vertical 2) (GL_LIGHT4)
float x_foco4; //Posición X del foco 4
float y_foco4; //Posición Y del foco 4 que se actualizará dinámicamente en cada frame
const float light_ambient4[] = { 0.1, 0.1, 0.1, 1.0 };
const float light_diffuse4[] = { 1.0, 1.0, 1.0, 1.0 };
const float light_specular4[] = { 0.0, 0.0, 0.0, 1.0 };
const float light_spot_direction4[] = { 0.0, 0.0, -1.0 };
bool adelante4 = true;

//Propiedades del tercer foco final (horizontal 1) (GL_LIGHT5)
float x_foco5; //Posición X del foco 5 que se actualizará dinámicamente en cada frame
float y_foco5; //Posición Y del foco 5
const float light_ambient5[] = { 0.1, 0.1, 0.1, 1.0 };
const float light_diffuse5[] = { 1.0, 1.0, 1.0, 1.0 };
const float light_specular5[] = { 0.0, 0.0, 0.0, 1.0 };
const float light_spot_direction5[] = { 0.0, 0.0, -1.0 };
bool adelante5 = true;

//Propiedades del cuarto foco final (horizontal 2) (GL_LIGHT6)
float x_foco6; //Posición X del foco 6 que se actualizará dinámicamente en cada frame
float y_foco6; //Posición Y del foco 6
const float light_ambient6[] = { 0.1, 0.1, 0.1, 1.0 };
const float light_diffuse6[] = { 1.0, 1.0, 1.0, 1.0 };
const float light_specular6[] = { 0.0, 0.0, 0.0, 1.0 };
const float light_spot_direction6[] = { 0.0, 0.0, -1.0 };
bool adelante6 = true;

bool empezado = false; //Sirve para saber cuándo estamos en la primera llamada al método (primer frame)
bool efectoMalo = false; //Indica si se está eliminando a un malo
int indice = 0; //Para recorrer el array global de malos para ver si hay alguno atrapado
int cont1Malo = 1; //Para la duración del proceso de "comer" a un malo
int cont2Malo = 1; //Para el parpadeo de la luz al "comer" a un malo
int malos_muertos = 0; //Contador para controlar los malos que se van eliminando
bool ganado = false; //Sirve para saber si el personaje acaba de ganar
bool direccional = false; //Cuando se ha ganado, indica si está activada la luz direccional o los focos
int cont1Victoria = 1; //Para las fases de los efectos especiales de la luz al ganar
int cont2Victoria = 1; //Para el parpadeo de la luz direccional al ganar
bool ajuste1 = false; //Supone un ajuste para la segunda cámara en el momento justo de ganar
bool ajuste2 = false; //Supone un ajuste para la segunda cámara en la transición entre la luz direccional y los focos cuando ha ganado
bool direccionalFloja = false; //Para evitar la oscuridad total al ganar

//Devuelve true si se está eliminando a un malo, false en caso contrario
bool getEfectoMalo() {
	return efectoMalo;
}

//Ilumina la escena (en el render de cada frame, tras posicionar la cámara y antes de dibujar todo). Hay que indicar en cuál de las 
//dos llamadas en un mismo frame estamos, por la existencia de dos cámaras simultáneas
void iluminar(bool primeraLlamada) {
	
	if (!empezado) { //La primera vez que se llama al método

		//Obtenemos el frame rate
		fps = getFPS();
		segundo = (fps % 4)?fps-2:fps; //Se hace un pequeño ajuste para que el parpadeo del foco del malo 
		//acabe en encendido y la desaparición del malo sea más limpia
		
		//Obtenemos el personaje
		personaje = CPersonaje::Instance();

		//Obtenemos los datos del escenario e inicializamos valores
		escenario = Escenario::getInstance();
		ancho = escenario->getLadoX();
		alto = escenario->getLadoZ();
		foco_f = min(ancho,alto) / 3.5f;
		x_foco3 = ancho/4;
		y_foco3 = alto;
		x_foco4 = 3 * ancho/4;
		y_foco4 = 0.0;
		x_foco5 = ancho;
		y_foco5 = 3 * alto/4;
		x_foco6 = 0.0;
		y_foco6 = alto/4;

		glShadeModel(GL_SMOOTH); //La luz se distribuye en cada vértice
		glEnable(GL_LIGHTING); //Activamos la iluminación

		//Luz direccional
		glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient0);
		float light_diffuse0[] = { 0.3, 0.3, 0.3, 1.0 }; //Luz difusa tenue sobre el escenario
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
		glEnable(GL_LIGHT0);
		
		//Foco sobre el personaje
		float light_position1[] = {personaje->getPositionRealX(), personaje->getPositionRealY(), ALTURA, 1.0}; //Luz posicional (w = 1)
		glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spot_direction1);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, FOCO_P);
		glEnable(GL_LIGHT1);
		
		//Foco sobre un malo
		glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, FOCO_M);
		
		//Primer foco final (vertical 1)
		glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient3);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse3);
		glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular3);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, foco_f);

		//segundo foco final (vertical 2)
		glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient4);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse4);
		glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular4);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, foco_f);

		//Tercer foco final (horizontal 1)
		glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient5);
		glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse5);
		glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular5);
		glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, foco_f);

		//Cuarto foco final (horizontal 2)
		glLightfv(GL_LIGHT6, GL_AMBIENT, light_ambient6);
		glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse6);
		glLightfv(GL_LIGHT6, GL_SPECULAR, light_specular6); 
		glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, foco_f);
						
		empezado = true;

	} else { //A partir de la segunda llamada al método

		if(malos_muertos < g_num_malos || ajuste1) {

			//Actualizamos en cada frame el foco sobre el personaje
			float light_position1[] = {personaje->getPositionRealX(), personaje->getPositionRealY(), ALTURA, 1.0};
			glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_spot_direction1);

			if(ajuste1) ajuste1 = false;
			
			if(!efectoMalo && primeraLlamada) { //Si no estamos con un malo y es la primera llamada

				//Recorremos el array global de malos para ver si alguno ha sido atrapado
				while(!efectoMalo && indice < g_num_malos) {
					if(g_fantasmas[indice].getAtrapado() && g_fantasmas[indice].getVivo()) { //Si el malo ha sido atrapado y está vivo
						efectoMalo = true;
						float light_position2[] = {g_fantasmas[indice].getPosRealX(), g_fantasmas[indice].getPosRealZ(), ALTURA, 1.0};
						glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
						glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_spot_direction2);
						glEnable(GL_LIGHT2);
					} else {
						indice++;
					}
				}
				if(indice == g_num_malos) indice = 0;

			}

			if(efectoMalo) { //Si estamos con un malo

				//Posicionamos en cada frame el foco sobre el malo para que en caso de movimientos de cámara durante el
				//proceso, el foco siga en todo momento encima del malo
				float light_position2[] = {g_fantasmas[indice].getPosRealX(), g_fantasmas[indice].getPosRealZ(), ALTURA, 1.0};
				glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
				glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_spot_direction2);
				
				//Dejamos el foco del malo activado durante aprox. FIJO_M segundos
			
				//Activamos y desactivamos el foco del malo durante aprox. PARPADEANTE_M segundos (sólo se actualiza en la primera llamada)
				if(primeraLlamada) {
					if (((FIJO_M*segundo) < cont1Malo) && (cont1Malo <= ((FIJO_M+PARPADEANTE_M)*segundo+1))) { 
						if (cont2Malo == 1) {
							if (glIsEnabled(GL_LIGHT2)) glDisable(GL_LIGHT2);
							else glEnable(GL_LIGHT2);
						}
						cont2Malo++;
						if(cont2Malo > 2) cont2Malo = 1;
					}
			
					cont1Malo++;

					if(cont1Malo > ((FIJO_M+PARPADEANTE_M)*segundo+1)) {
						efectoMalo = false;
						glDisable(GL_LIGHT2);
						g_fantasmas[indice].setVivo(false);
						malos_muertos++;
						indice = 0;
						cont1Malo = 1;
						cont2Malo = 1;
						if(malos_muertos == g_num_malos) ajuste1 = true;
					}
				}
			}
				
		} else { //Si se ha ganado
			
			if(!ganado) { //Cuando el personaje acaba de ganar
				glDisable(GL_LIGHT1); //Desactivamos el foco del personaje
				float light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 }; //Intensificamos la luz direccional
				glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
				ganado = true;
				direccional = true;
			}

			if (direccional || ajuste2) { //Actúa la luz direccional
				
				if(ajuste2) ajuste2 = false;

				//Dejamos la luz direccional activada durante aprox. FIJO_V segundos
			
				//Activamos y desactivamos la luz direccional durante aprox. PARPADEANTE_V segundos (sólo se actualiza en la primera llamada)
				if(primeraLlamada) {
					if (((FIJO_V*segundo) < cont1Victoria) && (cont1Victoria <= ((FIJO_V+PARPADEANTE_V)*segundo+1))) { 
						if (cont2Victoria == 1) {
							if (!direccionalFloja) {
								float light_diffuse0[] = { 0.1, 0.1, 0.1, 1.0 }; //Atenuamos la luz direccional
								glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
								direccionalFloja = true;
							} else {
								float light_diffuse0[] = { 1.0, 1.0, 1.0, 1.0 };
								glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
								direccionalFloja = false;
							}
						}
						cont2Victoria++;
						if(cont2Victoria > 2) cont2Victoria = 1;
					}
			
					cont1Victoria++;

					if(cont1Victoria > ((FIJO_V+PARPADEANTE_V)*segundo+1)) {
						float light_diffuse0[] = { 0.1, 0.1, 0.1, 1.0 };
						glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse0);
						direccional = false;
						ajuste2 = true;
					}
				}

			} else { //Actúan los 4 focos finales, moviéndose cíclicamente por el escenario hasta que el juego se cierre
			
				//Primer foco (vertical 1 / foco 3)

				//Posicionar en este frame
				float light_position3[] = {x_foco3, y_foco3, ALTURA, 1.0};
				glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
				glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_spot_direction3);
				if(!glIsEnabled(GL_LIGHT3)) glEnable(GL_LIGHT3);
					
				//Calcular la posición en el siguiente frame (sólo se actualiza en la segunda llamada)
				if(!primeraLlamada) {
					if(adelante3) {
						y_foco3 -= alto / (TIEMPO * segundo);
						if(y_foco3 < 0.0) y_foco3 = 0.0;
						if(y_foco3 == 0.0) adelante3 = false;
					} else {
						y_foco3 += alto / (TIEMPO * segundo);
						if(y_foco3 > alto) y_foco3 = alto;
						if(y_foco3 == alto) adelante3 = true;
					}
				}

				//Segundo foco (vertical 2 / foco 4)

				float light_position4[] = {x_foco4, y_foco4, ALTURA, 1.0};
				glLightfv(GL_LIGHT4, GL_POSITION, light_position4);
				glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, light_spot_direction4);
				if(!glIsEnabled(GL_LIGHT4)) glEnable(GL_LIGHT4);

				if(!primeraLlamada) {
					if(adelante4) {
						y_foco4 += alto / (TIEMPO * segundo);
						if(y_foco4 > alto) y_foco4 = alto;
						if(y_foco4 == alto) adelante4 = false;
					} else {
						y_foco4 -= alto / (TIEMPO * segundo);
						if(y_foco4 < 0.0) y_foco4 = 0.0;
						if(y_foco4 == 0.0) adelante4 = true;
					}
				}

				//Tercer foco (horizontal 1 / foco 5)

				float light_position5[] = {x_foco5, y_foco5, ALTURA, 1.0};
				glLightfv(GL_LIGHT5, GL_POSITION, light_position5);
				glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, light_spot_direction5);
				if(!glIsEnabled(GL_LIGHT5)) glEnable(GL_LIGHT5);

				if(!primeraLlamada) {
					if(adelante5) {
						x_foco5 -= ancho / (TIEMPO * segundo);
						if(x_foco5 < 0.0) x_foco5 = 0.0;
						if(x_foco5 == 0.0) adelante5 = false;
					} else {
						x_foco5 += ancho / (TIEMPO * segundo);
						if(x_foco5 > ancho) x_foco5 = ancho;
						if(x_foco5 == ancho) adelante5 = true;
					}
				}

				//Cuarto foco (horizontal 2 / foco 6)

				float light_position6[] = {x_foco6, y_foco6, ALTURA, 1.0};
				glLightfv(GL_LIGHT6, GL_POSITION, light_position6);
				glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, light_spot_direction6);
				if(!glIsEnabled(GL_LIGHT6)) glEnable(GL_LIGHT6);

				if(!primeraLlamada) {
					if(adelante6) {
						x_foco6 += ancho / (TIEMPO * segundo);
						if(x_foco6 > ancho) x_foco6 = ancho;
						if(x_foco6 == ancho) adelante6 = false;
					} else {
						x_foco6 -= ancho / (TIEMPO * segundo);
						if(x_foco6 < 0.0) x_foco6 = 0.0;
						if(x_foco6 == 0.0) adelante6 = true;
					}
				}
	
			}

		}

	}

}