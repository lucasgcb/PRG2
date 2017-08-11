#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <conio.h>
#endif
typedef unsigned char bool; //Cria tipo booleano para C
#define true 1
#define false 0
#define TAMANHO_STRING 255




int lerInteiro(char *);

float lerFloat(char *);

void aplicarString(char *, char *);
void limparTela();
void limparEntrada();

FILE * criarArquivoTexto(char *);
FILE * abrirArquivoCSV(char *);

void limparEntrada()
{
	fflush(stdin);
    #ifdef linux
	getchar();
	#endif
}

int lerNumeroLinhas(FILE *arquivo)
{
    int linhas=0;
    char caractere;
    while(!feof(arquivo))
    {
        caractere=fgetc(arquivo);
        if(caractere=='\n')
        {
            linhas++;
        }
    }
    rewind(arquivo);
    return linhas;
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

FILE * criarArquivoTexto(char *nome)
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

FILE * abrirArquivoCSV(char *nome)
{
    strcat(nome,".csv");
    FILE *arquivo = fopen(nome, "r");
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
