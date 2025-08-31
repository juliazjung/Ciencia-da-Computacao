#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

#include "pBase.h"

int main (int argc, char *argv[]) {
	
	// Instru��es de inicializa��o da utiliza��o da api
	
	glutInit (&argc, argv); // Inicializa��o da GLUT
	// buffer duplo para constru��o de imagem
	// remo��o de superf�cies escondidas e sistema cor
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	// posi��o da imagem - canto superior esquerdo (x,y)
	glutInitWindowPosition (g_posicao_x, g_posicao_y);
	// defini��o da largura e altura da janela
	glutInitWindowSize (g_largura, g_altura);
	// t�tulo e cria��o da janela
	glutCreateWindow (g_titulo);
	
	// Declara��o de callbacks
	
	// desenho de objetos gr�ficos
	glutDisplayFunc (gDesenha);
	// redimensionamento da janela de exibi��o
	glutReshapeFunc (gRedimensiona);
	// pressionamento de teclas comuns
	glutKeyboardFunc (gTeclado);
	// pressionamento de teclas especiais
	glutSpecialFunc (gEspeciais);
	// eventos de pressionamento/libera��o mouse
	glutMouseFunc (gMouse);
	// movimento do mouse enquanto pressionado
	glutMotionFunc (gMousePressionado);
	// movimento do mouse enquanto liberado
	glutPassiveMotionFunc (gMouseLiberado);
	// eventos do mouse scroll
	glutMouseWheelFunc (gMouseScroll);
	
	// Callbacks e Fun��es auxiliares
	if (g_idle) glutIdleFunc (gSistemaOcioso); // Quando da ociosidade do sistema
	if (g_timer) glutTimerFunc (g_timer_value, gTempoExecucao, 1); // Quando trabalhar com anima���o
	
	gMenuTeclado ();
	gMenuJanela ();
	gInicializa ();
	
	glutMainLoop ();
	
	system ("pause");
	return 0;
}
