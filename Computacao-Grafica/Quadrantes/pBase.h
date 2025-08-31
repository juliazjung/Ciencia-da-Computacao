int g_posicao_x = 10;
int g_posicao_y = 10;
int g_largura = 400;
int g_altura = 400;
char g_titulo[] = "Projeto Aula 8";
int g_idle = 0;
int g_timer = 0;
int g_timer_value = 1;

void gTempoExecucao (int valor);

GLfloat g_janela = 10.0;
// Definição do Observador
GLfloat g_obs_xi, g_obs_xf, g_obs_yi, g_obs_yf, g_obs_zi, g_obs_zf;
GLfloat g_obs_rotacao_xi, g_obs_rotacao_xf, g_obs_rotacao_yi, g_obs_rotacao_yf;
// Definição da Perspectiva de Visualização
GLfloat g_angulo_visao, g_z_proximo, g_z_distante;

void gInicializaPerspectiva () {
	g_angulo_visao = 45;
	g_z_proximo = (g_janela / 10);
	g_z_distante = (g_janela * 5);
}

void gInicializaObservador (void) {
	g_obs_xf = 0;
	g_obs_yf = 0;
	g_obs_zf = -g_janela * 3;
	g_obs_rotacao_xf = 20;
	g_obs_rotacao_yf = 25;
}

void gPosicionaObservador (void) {
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef (g_obs_xf, g_obs_yf, g_obs_zf);
	glRotatef (g_obs_rotacao_xf, 1, 0, 0);
	glRotatef (g_obs_rotacao_yf, 0, 1, 0);
}

void gMeusDesenhos() {
    float desloc = 3.0;

    glColor3f(0, 0, 1);

    // 4 chaleiras na parte inferior (altura yBaixo)
    glPushMatrix(); glTranslatef(-desloc, -desloc,  desloc); glutSolidTeapot(1); glPopMatrix();  // frente esquerda
    glPushMatrix(); glTranslatef( desloc, -desloc,  desloc); glutSolidTeapot(1); glPopMatrix();  // frente direita
    glPushMatrix(); glTranslatef(-desloc, -desloc, -desloc); glutSolidTeapot(1); glPopMatrix();  // trás esquerda
    glPushMatrix(); glTranslatef( desloc, -desloc, -desloc); glutSolidTeapot(1); glPopMatrix();  // trás direita

    glColor3f(0, 1, 0);

    // 4 chaleiras na parte superior (altura yCima)
    glPushMatrix(); glTranslatef(-desloc, desloc,  desloc); glutSolidTeapot(1); glPopMatrix();  // frente esquerda
    glPushMatrix(); glTranslatef( desloc, desloc,  desloc); glutSolidTeapot(1); glPopMatrix();  // frente direita
    glPushMatrix(); glTranslatef(-desloc, desloc, -desloc); glutSolidTeapot(1); glPopMatrix();  // trás esquerda
    glPushMatrix(); glTranslatef( desloc, desloc, -desloc); glutSolidTeapot(1); glPopMatrix();  // trás direita
    
    
    glColor3f (1, 0, 0);
    glPushMatrix();
		glBegin (GL_LINES);
			glVertex3f (-g_janela, 0.0, 0.0); glVertex3f (g_janela, 0.0, 0.0);
			glVertex3f (0.0, -g_janela, 0.0); glVertex3f (0.0, g_janela, 0.0);
			glVertex3f (0.0, 0.0, -g_janela); glVertex3f (0.0, 0.0, g_janela);
		glEnd ();
	
		glColor3f (1, 0, 1);
		glBegin (GL_QUADS);
			glVertex3f (-3.0, 0.0, 	3.0); glVertex3f ( 3.0, 0.0,  3.0);
			glVertex3f ( 3.0, 0.0, -3.0); glVertex3f (-3.0, 0.0, -3.0);
		glEnd ();
		
		glColor3f (0, 1, 1);
		glBegin (GL_QUADS);
			glVertex3f (0.0, -3.0, 	3.0); glVertex3f (0.0,  3.0,  3.0);
			glVertex3f (0.0,  3.0, -3.0); glVertex3f (0.0, -3.0, -3.0);
		glEnd ();
		
		glColor3f (1, 1, 0);
		glBegin (GL_QUADS);
			glVertex3f (0.0, 0.0, 0.0); glVertex3f (3.0, 0.0, 0.0);
			glVertex3f (3.0, 3.0, 0.0); glVertex3f (0.0, 3.0, 0.0);
		glEnd ();
	
		glBegin (GL_QUADS);
			glVertex3f ( 0.0, 0.0, 0.0); glVertex3f ( 0.0, 3.0, 0.0);
			glVertex3f (-3.0, 3.0, 0.0); glVertex3f (-3.0, 0.0, 0.0);
		glEnd ();
		
		glBegin (GL_QUADS);
			glVertex3f ( 0.0, 0.0, 0.0); glVertex3f ( 0.0, -3.0, 0.0);
			glVertex3f (-3.0, -3.0, 0.0); glVertex3f (-3.0, 0.0, 0.0);
		glEnd ();
	glPopMatrix();
}


void gDesenha (void) {
	glEnable (GL_DEPTH_TEST); // Habilita buffer de profundidade
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicialização
	glMatrixMode (GL_MODELVIEW); // Sistema de Coordenadas do modelo
	gMeusDesenhos (); // FUNÇÃO QUE CONTERá OS DESENHOS
	glutSwapBuffers ();
	gPosicionaObservador ();
}

void gRedimensiona (GLsizei largura, GLsizei altura) {
	float aspecto;
	aspecto = (largura <= altura) ? (altura / largura) : (largura / altura);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glViewport (0, 0, largura, altura);
	gluPerspective (g_angulo_visao, aspecto, g_z_proximo, g_z_distante);
	gPosicionaObservador ();
}

void gTeclado (unsigned char tecla, int x, int y) {
	if (tecla == 27) exit (0);
}

void gEspeciais (int tecla, int x, int y) {
	if (tecla == GLUT_KEY_UP) {;}
	if (tecla == GLUT_KEY_DOWN) {;}
	if (tecla == GLUT_KEY_RIGHT) {;}
	if (tecla == GLUT_KEY_LEFT) {;}
	glutPostRedisplay ();
}

void gMouse (int botao, int estado, int x, int y) {
}

void gMousePressionado (int x, int y) {;
}

void gMouseLiberado (int x, int y) {;}

void gMouseScroll (int botao, int direcao, int x, int y) {;}

void gSistemaOcioso (void) {
	glutPostRedisplay ();
}

void gTempoExecucao (int valor) {
	glutPostRedisplay ();
	if (g_timer) glutTimerFunc (g_timer_value, gTempoExecucao, 1);
}

void gMenuTeclado (void) {;}

void gMenuJanela (void) {;}

void gInicializa (void) {
	glClearColor (1, 1, 1, 0);
	glMatrixMode (GL_PROJECTION);
	gInicializaPerspectiva ();
	gInicializaObservador ();
}
