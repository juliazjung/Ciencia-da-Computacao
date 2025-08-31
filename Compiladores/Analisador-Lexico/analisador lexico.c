/*
  Autor : Alessandro
  Micro Analisador Léxico
*/
#include <stdio.h>
#include "af_aula2.h"

int main (void)
{
	int estados_finais[50], i, x, deriva, analise_sintatica;
	char texto[50];
	
	while (1)
	{
		system ("cls");
		linguagem ();
		i = x = deriva = analise_sintatica = 0;
		printf ("Informe o texto a ser analisado: \n");
		texto[i] = getchar();
		while (texto[i] != '\n')
			texto[++i] = getchar();
		texto[i++] = B;
		texto[i] = '\0';
		printf ("\nMostra Derivacao (processo de reconhecimento) 1-Sim 0-Nao: ");
		scanf  ("%d", &deriva);
	  		for ( i = 0; i < 50; i++ )
  			estados_finais[i] = 0;
			for ( i = 0; texto[i] != '\0'; i++ )
		{
			fita_entrada[x] = texto[i];
			if ( texto[i] == B )
			{
				estados_finais[analise_sintatica++] = f_analisa_lexica (deriva);
				if ( estados_finais[analise_sintatica-1] == V )
					printf ("\nERRO LEXICO - Simbolo NAO Pertence ao Alfabeto...\n\n");
				else if ( estados_finais[analise_sintatica-1] == 0 )
					printf ("\nERRO LEXICO - TRANSICAO - Palavra NAO Pertence a Linguagem...\n\n");
				else
					printf ("\nPalavra Pertence a Linguagem...\n\n");
				x = V;
			}
			x++;
		}
		printf ("\nAnalise Sintatica <= ");
		for ( i = 0; i < analise_sintatica; i++ )
			printf ("%d ", estados_finais[i]);
		fflush (stdin);
		printf ("\n\nTecle <Enter> para Continuar ou <Ctrl-C> para sair...!!!");
		getchar ();
	}
	return (0);
}
