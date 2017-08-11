#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAMANHO_STRING 255
#ifdef _WIN32
#include <conio.h>
#endif

int lerInteiro(char *);
float lerFloat(char *);
void aplicarString(char *, char *);
//void criarCaminho(char *, char *);
void limparTela();
void limparEntrada();
FILE * criarArquivo(char *);


/*void criarCaminho(char* entrada, char* nomePasta)
{
		#ifdef _WIN32
		strcat(nomePasta,"\\");
		#endif
		#ifdef linux
		strcat(nomePasta,"/");
		#endif
		strcat(entrada,nomePasta);
}*/
void limparEntrada()
{


	fflush(stdin);
    #ifdef linux
	getchar();
	#endif
}

void limparTela()
{
	#ifdef _WIN32
	system("cls");
	#endif
	#ifdef linux
	system("clear");
	#endif
}

int lerInteiro(char *mensagem)
{
	int numero;
	int retorno;
	printf("%s", mensagem);
	retorno = scanf("%d", &numero);
	while(retorno!=1)
	{
		limparTela();
		limparEntrada();
		printf("%s", mensagem);
		retorno = scanf("%d", &numero);
	}
	limparEntrada();
	return numero;
}

float lerFloat(char *mensagem)
{
	float numero;
	int retorno;
	printf("%s", mensagem);
	retorno = scanf("%f", &numero);
	while(retorno!=1)
	{
		limparTela();
		limparEntrada();
		printf("%s", mensagem);
		retorno = scanf("%f", &numero);
	}
	limparEntrada();
	return numero;
}


void aplicarString(char *destino, char *mensagem)
{
	// https://stackoverflow.com/questions/25798977/returning-string-from-c-function
    // static char entrada[255]; impossivel reutilizar sem liberar memoria // alocação dinamica anonima
    char entrada[TAMANHO_STRING];
    printf("%s", mensagem);
	fgets(entrada, TAMANHO_STRING-1, stdin);
	entrada[strlen(entrada) - 1] = '\0'; //retira \n do fgets()
	strcpy(destino, entrada);
}

FILE * criarArquivo(char *nome)
{
    #ifdef _WIN32
    strcat(nome,".txt");
    #endif // _WIN32
    FILE *arquivo = fopen(nome, "w");
    if (arquivo==NULL)
    {
        perror("Não foi possível criar o arquivo");
        exit(EXIT_FAILURE);
    }
    else
    {
       return arquivo;
    }
}

#endif
