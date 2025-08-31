// IDENTIFICADORES COMPLEMENTARES AO AUTOMATO FINITO ********************************
#define TAM_FITA 50		// tamanho da fita
#define QTD_SIMBOLO 18	// quantidade de simbolos do alfabeto (inclusive o Epsilon)
#define QTD_ESTADO 17	// quantidade de estados
#define B ' '	// símbolo do alfabeto auxiliar (Epsilon) "término da cadeia"
#define V -1	// estado de parada (final) - indica o aceite da cadeia
#define F -2	// erro de transicao

// AUTOMATO FINITO - TABELA DE TRANSIÇÃO e CABEÇALHO DA TABELA CONTENDO O ALFABETO

int cabeca_fita, estado_maquina, posicao_simbolo_lido;

char fita_entrada[TAM_FITA]; // conterá a palavra a ser analisada

char alfabeto[] = 
	{	B, 'a', 'd', 'e', 'i', 'j', 'r', 't', 'v', 'w', 'x', 'y', '0', '1', '=', '+', '(', ')'	};

int tabela_transicao[QTD_ESTADO][QTD_SIMBOLO] = {
    {	F,	 F,	  F,   F,  14,  14,   1,   F,  14,   5,  14,  14,  17,  17,  10,  11,  12,  13	},	//0
	{	F,	 F,	  F,   2,   F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//1
	{	F,	 3,	  F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//2
	{	F,	 F,	  4,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//3
	{	V,	 F,	  F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//4
	{	F,	 F,	  F,   F,	F,   F,   6,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//5
	{	F,	 F,	  F,   F,	7,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//6
	{	F,	 F,	  F,   F,	F,   F,   F,   8,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//7
	{	F,	 F,	  F,   9,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//8
	{	V,	 F,	  F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//9
	{	V,	 F,	  F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//10
	{	V,	 F,	  F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//11
	{	V,	 F,	  F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//12
	{	V,	 F,	  F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	},	//13
	{	V,	 F,	  F,   F,  15,  15,   F,   F,  15,   F,  15,  15,	F,   F,   F,   F,	F,   F	},	//14
	{	V,	 F,	  F,   F,  16,  16,   F,   F,  16,   F,  16,  16,	F,   F,   F,   F,	F,   F	},	//15
	{	V,	 F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F,   F,   F,	F,   F	}	//16
};

void f_mostra_derivacao (void) // opcional - mostra o processo de reconhecimento (derivação)
{
	int i;
	printf ("\n");
	for ( i = 0; i < cabeca_fita; i++ )
		printf ("%c ", fita_entrada[i]);
	printf ("%d_", estado_maquina);
	for ( i = cabeca_fita; fita_entrada[i] != B && fita_entrada[i] != '\0'; i++ )
		printf ("%c ", fita_entrada[i]);
}

int f_analisa_lexica (int _deriva) // Aplica a função de programa e retorna FALSO caso palavra válida
{
	int i;
	cabeca_fita = estado_maquina = 0;
	while ( 1 ) // a leitura da fita tende ao infinito
	{
		if ( _deriva )
			f_mostra_derivacao ();
		for ( i = 0, posicao_simbolo_lido = V; i < QTD_SIMBOLO; i++ ) // le o símbolo da fita
			if ( fita_entrada[cabeca_fita] == alfabeto[i] )
				posicao_simbolo_lido = i;
		if ( posicao_simbolo_lido == V ) // Erro léxico = Símbolo não Pertence ao Alfabeto
			return (V);
		else if ( tabela_transicao[estado_maquina][posicao_simbolo_lido] == F ) // Erro de Transição
			return (0);
		else if ( tabela_transicao[estado_maquina][posicao_simbolo_lido] == V ) // Aceita a Palavra
			return (estado_maquina);
		cabeca_fita++; // movimenta a cabeça da fita para direita (para ler o próximo símbolo)
		estado_maquina = tabela_transicao[estado_maquina][posicao_simbolo_lido]; // novo estado da máquina
    }
}

void linguagem (void) {
	printf ("Analise Lexica - L = { int text input print + - = ( ) ; id ln }\n");
  	printf ("        id = Identificadores iniciando com v seguidos de vogais\n");
  	printf ("        ln = Literais numericas compostas de algarismo arabicos\n");
  	printf ("        Tamanho máximo de id/ln = 3, ou seja = |id| = |ln| = 3\n\n");
}
