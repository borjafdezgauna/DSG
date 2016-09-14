#include <iostream>
#include <GL/glut.h>
#include "../inc/Escenario.h"

void manageKeyboard(unsigned char key, int mouseX, int mouseY) {  // si se pulsa 1 zoom out , 2 para zoom in
	if (key=='1') {
		glScaled(0.95f,0.95f,0.95f);
		glutPostRedisplay();
		return;
	}
	if (key=='2') {
		glScaled(1.95f, 1.95f, 1.95f);
		glutPostRedisplay();
		return;
	}
	if (key=='a') {
		glRotatef(5,0,1,0);
		glutPostRedisplay();
		return;
	}
	if (key=='d') {
		glRotatef(5,0,-1,0);
		glutPostRedisplay();
		return;
	}

	if (key=='s') {
		glRotatef(5,-1,0,0);
		glutPostRedisplay();
		return;
	}

	if (key=='w') {
		glRotatef(5,1,0,0);
		glutPostRedisplay();
		return;
	}
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Escenario::getInstance()->drawFloor();
	Escenario::getInstance()->drawBlock(0,0);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		cout << "Error, tienes que especificar la ruta al fichero de mapa" << endl;
		return 1;
	}

	char* fichero = argv[1];
	if (!Escenario::getInstance()->cargarEscenario(fichero)) {
		cout << "Error no se encuentra el fichero de escenario \"" << fichero << "\""  << endl;
		return 1;
	}

	Escenario::getInstance()->mostrarEscenario();

	glutInit(&argc, argv); // inicializamos GLUT
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800,600);
	glutCreateWindow("Test del Escenario");

	glEnable(GL_TEXTURE_2D);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(manageKeyboard);

	glutMainLoop();

	return 0;
}
