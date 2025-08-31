int g_posicao_x = 10;
int g_posicao_y = 10;
int g_largura = 800;
int g_altura = 600;
char g_titulo[] = "Bob Esponja 3D";
int g_idle = 0;
int g_timer = 0;
int g_timer_value = 1;

void gTempoExecucao (int valor);

GLfloat g_janela = 1.0;
// Definição do Observador
GLfloat g_obs_xi, g_obs_xf, g_obs_yi, g_obs_yf, g_obs_zi, g_obs_zf;
GLfloat g_obs_rotacao_xi, g_obs_rotacao_xf, g_obs_rotacao_yi, g_obs_rotacao_yf;
// Definição da Perspectiva de Visualização
GLfloat g_angulo_visao, g_z_proximo, g_z_distante;

//////////////////////////////////////////////////////////////////////////////
GLbyte g_obs_operacao; // (r)otação (t)translação (a)fasta/(a)proxima
GLint g_mouse_x, g_mouse_y;

// Variáveis para controle do Braço
GLint g_bracoD = 0, g_bracoE = 0, g_ombroD = 0, g_ombroE = 0;

void gSalvaParametrosObservador (int x, int y) {
	g_mouse_x = x;
	g_mouse_y = y;
	g_obs_xi = g_obs_xf;
	g_obs_yi = g_obs_yf;
	g_obs_rotacao_xi = g_obs_rotacao_xf;
	g_obs_rotacao_yi = g_obs_rotacao_yf;
}

void gRotacionaObservador (int x, int y) {
	float sensor = 3;
	g_obs_rotacao_xf = g_obs_rotacao_xi - ((g_mouse_y - y) / sensor);
	g_obs_rotacao_yf = g_obs_rotacao_yi - ((g_mouse_x - x) / sensor);
}

void gDistanciaObservador (int direcao) {
	float sensor = (g_janela / 10) * direcao;
	g_obs_zf += sensor;
}

void gTransladaObservador (int x, int y) {
	float sensor = 2;
	g_obs_xf = g_obs_xi - ((g_mouse_x - x) / sensor);
	g_obs_yf = g_obs_yi - ((g_mouse_y - y) / sensor);
}

void gInicializaPerspectiva () {
	g_angulo_visao = 60;
	g_z_proximo = (g_janela / 1);
	g_z_distante = (g_janela * 10);
}

void gInicializaObservador (void) {
	g_obs_xf = -1;
	g_obs_yf = 1.2;
	g_obs_zf = -g_janela * 3;
	g_obs_rotacao_xf = 10;
	g_obs_rotacao_yf = 8;
}

void gPosicionaObservador (void) {
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	glTranslatef (g_obs_xf, g_obs_yf, g_obs_zf);
	glRotatef (g_obs_rotacao_xf, 1, 0, 0);
	glRotatef (g_obs_rotacao_yf, 0, 1, 0);
}

void desenhaCuboComContorno(float x, float y, float z, float tamanho, float r, float g, float b) {
    // Cubo principal
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(tamanho);
    glPopMatrix();

    // Contorno preto (ligeiramente maior)
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutWireCube(tamanho * 1.01);  // ligeiramente maior para evitar z-fighting
    glPopMatrix();
}

void desenhaCuboComContornoW(float x, float y, float z, float tamanho, float r, float g, float b) {
    // Cubo principal
    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidCube(tamanho);
    glPopMatrix();

    // Contorno preto (ligeiramente maior)
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutWireCube(tamanho * 1.01);  // ligeiramente maior para evitar z-fighting
    glPopMatrix();
}

void desenhaBob() {
    glPushMatrix();
    glTranslatef(1, -0.9, 0.0);

    // Corpo (amarelo)
    glPushMatrix();
    glScalef(1.0, 1.3, 0.4);
    desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    glPopMatrix();
    
    // Listra da camisa (branca)
	glColor3f(1.0, 1.0, 1.0); // Branco
	glPushMatrix();
	glTranslatef(0.0, -0.4, 0.0); // Posição entre corpo e calça
	glScalef(1.02, 0.1, 0.42); // Achatado na vertical
	//glutSolidCube(1.0);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
	glPopMatrix();

    // Calça (marrom)
    glPushMatrix();
    glTranslatef(0.0, -0.6, 0);
    glScalef(1.02, 0.3, 0.42);
    desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 0.4, 0.2, 0.0);
    glPopMatrix();
    
    glColor3f(0.0, 0.0, 0.0);
    
    // Pernas da calça (marrons)
	glPushMatrix();
	glTranslatef(-0.2, -0.82, 0); // Esquerda
	glScalef(0.3, 0.15, 0.3);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 0.4, 0.2, 0.0); // Marrom
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.2, -0.82, 0); // Direita
	glScalef(0.3, 0.15, 0.3);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 0.4, 0.2, 0.0); // Marrom
	glPopMatrix();
	
	// Cinto - quadrados pretos
	glColor3f(0.0, 0.0, 0.0);
	
	// Esquerda
	glPushMatrix();
	glTranslatef(-0.35, -0.6, 0.2); // Z maior: na frente da calça
	glScalef(0.1, 0.1, 0.05);
	glutSolidCube(1.0);
	glPopMatrix();

	// Meio esquerdo
	glPushMatrix();
	glTranslatef(-0.15, -0.6, 0.2);
	glScalef(0.1, 0.1, 0.05);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// Meio direito
	glPushMatrix();
	glTranslatef(0.15, -0.6, 0.2);
	glScalef(0.1, 0.1, 0.05);
	glutSolidCube(1.0);
	glPopMatrix();
	
	// Direita
	glPushMatrix();
	glTranslatef(0.35, -0.6, 0.2);
	glScalef(0.1, 0.1, 0.05);
	glutSolidCube(1.0);
	glPopMatrix();

    // Gravata (vermelha)
    glPushMatrix();
	glTranslatef(0.0, -0.4, 0.23);
	glScalef(0.9, 0.9, 0.3);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 0.1, 1.0, 0.0, 0.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0, -0.57, 0.23);
	glScalef(0.9, 2.5, 0.3);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 0.1, 1.0, 0.0, 0.0);
	glPopMatrix();

	// Olhos (brancos - esferas)
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(-0.2, 0.3, 0.2);
	glutSolidSphere(0.1, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2, 0.3, 0.2);
	glutSolidSphere(0.1, 30, 30);
	glPopMatrix();
	
	// Pupilas (pretas - esferas menores)
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-0.2, 0.3, 0.28); // Mais à frente
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.2, 0.3, 0.28);
	glutSolidSphere(0.05, 20, 20);
	glPopMatrix();

    // Dentes (brancos)
	desenhaCuboComContorno(-0.05, -0.1, 0.22, 0.08, 1.0, 1.0, 1.0);
	desenhaCuboComContorno(0.05, -0.1, 0.22, 0.08, 3.0, 1.0, 1.0);

    // Nariz (amarelo)
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.15, 0.3); // Saindo do rosto
	glScalef(0.1, 0.1, 0.3); // Estica para frente
	desenhaCuboComContorno(0.00, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
	glPopMatrix();

	// Boca (preta)
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, -0.05, 0.2); // Um pouco abaixo dos dentes
	glScalef(0.3, 0.05, 0.05); // Larga e fina
	glutSolidCube(1.0);
	glPopMatrix();
	
	// Manga esquerda (branca)
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 0.0); // Mais perto do corpo
	glRotatef(90, 0, 0, 1);
	glScalef(0.25, 0.3, 0.3); // Um pouco menor que o braço
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
	glPopMatrix();

	// Manga direita (branca)
	glPushMatrix();
	glTranslatef(0.5, 0.0, 0.0);
	glRotatef(90, 0, 0, 1);
	glScalef(0.25, 0.3, 0.3);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
	glPopMatrix();
	
	// Bra�o esquerdo
    glPushMatrix();
    	//Ombro
	    glTranslatef(-0.58, -0.05, 0.0);
	    glRotatef (g_ombroE, 0.0, 0.0, 1.0);
	    glPushMatrix();
		    glTranslatef(0.0, -0.3, 0.0);
		    glScalef(0.1, 0.5, 0.1);
		    desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
	    glPopMatrix();
	    
	    // Antebra�o esquerdo
	    glTranslatef(0.0, -0.48, 0.0);
	    glRotatef(g_bracoE, 0, 0, 1);
	    glPushMatrix();
			glTranslatef(0.0, -0.25, 0.0);
			glScalef(0.1, 0.5, 0.1);
		    desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
	    glPopMatrix();
    glPopMatrix();
	
    // Bra�o direito 
    glPushMatrix();
		//Ombro
	    glTranslatef(0.58, -0.05, 0.0);
	    glRotatef (g_ombroD, 0.0, 0.0, 1.0);
	    glPushMatrix();
		    glTranslatef(0.0, -0.3, 0.0);
		    glScalef(0.1, 0.5, 0.1);
		    desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
	    glPopMatrix();
	    
	    // Antebra�o direito (amarelo)
	    glTranslatef(0.0, -0.48, 0.0);
	    glRotatef(g_bracoD, 0, 0, 1);
	    glPushMatrix();
		    glTranslatef(0.0, -0.25, 0.0);
		    glScalef(0.1, 0.5, 0.1);
		    desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    	glPopMatrix();
	glPopMatrix();
    
	// Perna esquerda (amarelo)
	glPushMatrix();
	glTranslatef(-0.2, -1.0, 0);
	glScalef(0.10, 0.55, 0.1);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
	glPopMatrix();

	// Perna direita (amarelo)
	glPushMatrix();
	glTranslatef(0.2, -1.0, 0);
	glScalef(0.10, 0.55, 0.1);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0); // <-- AMARELO
	glPopMatrix();
		
	// Meia esquerda (branca)
	glPushMatrix();
	glTranslatef(-0.2, -1.3, 0);
	glScalef(0.12, 0.1, 0.12);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0); // Branco com contorno preto
	glPopMatrix();
	
	// Meia direita (branca)
	glPushMatrix();
	glTranslatef(0.2, -1.3, 0);
	glScalef(0.12, 0.1, 0.12);
	desenhaCuboComContorno(0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0); // Branco com contorno preto
	glPopMatrix();
	
    // Sapato esquerdo (preto)
    glPushMatrix();
    glTranslatef(-0.2, -1.4, 0.09);
    glScalef(0.2, 0.1, 0.35);
    desenhaCuboComContornoW(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    glPopMatrix();

    // Sapato direito (preto)
    glPushMatrix();
    glTranslatef(0.2, -1.4, 0.09);
    glScalef(0.2, 0.1, 0.35);
    desenhaCuboComContornoW(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
    glPopMatrix();

    // Bochecha esquerda (rosa claro)
    glColor3f(1.0, 0.7, 0.7);
    glPushMatrix();
    glTranslatef(-0.3, 0.15, 0.2);
    glutSolidSphere(0.05, 20, 20);
    glPopMatrix();

    // Bochecha direita
    glPushMatrix();
    glTranslatef(0.3, 0.15, 0.2);
    glutSolidSphere(0.05, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

void gMeusDesenhos (void) {
	desenhaBob ();
}

void gDesenha (void) {
	glEnable (GL_DEPTH_TEST); // Habilita buffer de profundidade
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicialização
	glMatrixMode (GL_MODELVIEW); // Sistema de Coordenadas do modelo
	gMeusDesenhos (); // FUNÇÃO QUE CONTERÁ OS DESENHOS
	glutSwapBuffers ();
	gPosicionaObservador ();
}

void gRedimensiona (GLsizei largura, GLsizei altura) {
	float aspecto;
	aspecto = (largura <= altura) ? (altura / largura) : (largura / altura);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glViewport (0, 0, largura, altura);
	//gluPerspective (g_angulo_visao, aspecto, g_z_proximo, g_z_distante);
	gluPerspective(g_angulo_visao, 800.0/600.0, 1.0, 100.0);
	gPosicionaObservador ();
}

void gTeclado (unsigned char tecla, int x, int y) {
	if (tecla == 27) exit (0);
	else if (tecla == 'r') g_obs_operacao = 'r';
	else if (tecla == 't') g_obs_operacao = 't';
	else if (tecla == 'a') g_obs_operacao = 'a';
	
    else if (tecla == 'b') {
		g_bracoD = (g_bracoD + 5);// % 360;
		g_bracoE = (g_bracoE - 5);// % 360;
	}
    else if (tecla == 'B') {
		g_bracoD = (g_bracoD - 5);// % 360;
		g_bracoE = (g_bracoE + 5);// % 360;
	}
    else if (tecla == 'o') {
		g_ombroD = (g_ombroD + 5);// % 360;
		g_ombroE = (g_ombroE - 5);// % 360;
	}
    else if (tecla == 'O') {
		g_ombroD = (g_ombroD - 5);// % 360;
		g_ombroE = (g_ombroE + 5);// % 360;
	}
    
    printf ("%c \n", tecla);
	glutPostRedisplay ();
}

void gEspeciais (int tecla, int x, int y) {
	if (tecla == GLUT_KEY_UP) {;}
	if (tecla == GLUT_KEY_DOWN) {;}
	if (tecla == GLUT_KEY_RIGHT) {;}
	if (tecla == GLUT_KEY_LEFT) {;}
	glutPostRedisplay ();
}

void gMouse (int botao, int estado, int x, int y) {
	printf ("%d.%d mouse\n", x, y);
	if (botao == GLUT_LEFT_BUTTON) {
		if (estado == GLUT_DOWN) gSalvaParametrosObservador (x, y);
	}
}

void gMousePressionado (int x, int y) {
	printf ("%d.%d pressionado\n", x, y);
	if (g_obs_operacao == 'r') gRotacionaObservador (x, y);
	else if (g_obs_operacao == 't') gTransladaObservador (x, y);
	gPosicionaObservador ();
	glutPostRedisplay ();
}

void gMouseLiberado (int x, int y) {;}

void gMouseScroll (int botao, int direcao, int x, int y) {
	printf ("%d \n", direcao);
	if (g_obs_operacao == 'a') {
		gDistanciaObservador (direcao);
		gPosicionaObservador ();
	}
	glutPostRedisplay ();
}

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
