#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>

#include "pBase.h"

int main (int argc, char *argv[]) {
	
	// Instruções de inicialização da utilização da api
	
	glutInit (&argc, argv); // Inicialização da GLUT
	// buffer duplo para construção de imagem
	// remoção de superfícies escondidas e sistema cor
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	// posição da imagem - canto superior esquerdo (x,y)
	glutInitWindowPosition (g_posicao_x, g_posicao_y);
	// definição da largura e altura da janela
	glutInitWindowSize (g_largura, g_altura);
	// título e criação da janela
	glutCreateWindow (g_titulo);
	
	// Declaração de callbacks
	
	// desenho de objetos gráficos
	glutDisplayFunc (gDesenha);
	// redimensionamento da janela de exibição
	glutReshapeFunc (gRedimensiona);
	// pressionamento de teclas comuns
	glutKeyboardFunc (gTeclado);
	// pressionamento de teclas especiais
	glutSpecialFunc (gEspeciais);
	// eventos de pressionamento/liberação mouse
	glutMouseFunc (gMouse);
	// movimento do mouse enquanto pressionado
	glutMotionFunc (gMousePressionado);
	// movimento do mouse enquanto liberado
	glutPassiveMotionFunc (gMouseLiberado);
	// eventos do mouse scroll
	glutMouseWheelFunc (gMouseScroll);
	
	// Callbacks e Funções auxiliares
	if (g_idle) glutIdleFunc (gSistemaOcioso); // Quando da ociosidade do sistema
	if (g_timer) glutTimerFunc (g_timer_value, gTempoExecucao, 1); // Quando trabalhar com animaçção
	
	gMenuTeclado ();
	gMenuJanela ();
	gInicializa ();
	
	glutMainLoop ();
	
	system ("pause");
	return 0;
}
