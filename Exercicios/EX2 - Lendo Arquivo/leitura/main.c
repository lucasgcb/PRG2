#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

typedef struct medalhas
{
    int posicao;
    char nome[TAMANHO_STRING];
    int ouro;
    int prata;
    int bronze;
} Medalhas;

void lerMedalhas(int, FILE *);
void imprimirMedalhas(Medalhas *, int, FILE *);
void menu();
Medalhas * alocarStruct(int);



int main()
{
	setlocale(LC_CTYPE, "");
	int numeroCompetidores;
	char nomeArquivo[TAMANHO_STRING];
	FILE * arquivo;

	aplicarString(nomeArquivo,"Digite o primeiro nome do arquivo:\n");
	arquivo = abrirArquivoCSV(nomeArquivo);
    numeroCompetidores = lerNumeroLinhas(arquivo) - 1;
    printf("Numero de competidores: %d", numeroCompetidores);

    switch(lerInteiro("Digite uma opção:"))
    {
        case 0:
    }

    fclose(arquivo);
    return 0;
}


Medalhas* alocarStruct(int posicoes)
{
	Medalhas * retorno;
	retorno = malloc(sizeof(Medalhas)*posicoes);
	if(!retorno)
	{
			printf("Erro ao alocar matriz");
			exit(EXIT_FAILURE);
	}
    return retorno;
}

void imprimirMedalhas(Medalhas * competidores, int numeroCompetidores, FILE * arquivo)
{
	int contador;
	for(contador=0;contador<numeroCompetidores;contador++)
	{
		printf("test");
	}
}

void menu(int tipo)
{
    enum tipos{PRINCIPAL = 0, IMPRESSAO = 1, BUSCA = 2};
    switch(tipo)
    {
        case PRINCIPAL:
            printf("*************************************");
            printf("1 - Imprimir Ranking \n");
            printf("2 - Buscar time\n");
            printf("0 - Sair");
        default: "ue";
    }
}

