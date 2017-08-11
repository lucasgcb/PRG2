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

void inserirMedalhas(Medalhas * , int , FILE * );
void lerMedalhas(int, FILE *);
void imprimirMedalhas(Medalhas *, int);
void menu();
Medalhas * alocarStruct(int);

int main()
{
	setlocale(LC_CTYPE, "");
	
	int numeroCompetidores = 0;
	char nomeArquivo[TAMANHO_STRING];
	FILE * arquivo;
	bool sair = false;

	aplicarString(nomeArquivo,"Digite o primeiro nome do arquivo:\n");
	arquivo = abrirArquivoCSV(nomeArquivo);
	numeroCompetidores = lerNumeroLinhas(arquivo)-1;
    Medalhas * competidores = alocarStruct(numeroCompetidores); //menos cabeçalho
    inserirMedalhas(competidores, numeroCompetidores, arquivo);
    printf("Numero de competidores: %d", numeroCompetidores);
	
	
	while(!sair)
	{
		switch(lerInteiro("\n#Digite uma opção:\n"))
		{
			case 1: imprimirMedalhas(competidores, numeroCompetidores);
					break;
			case 0: 
					sair = true;
					break;
			default: printf("Não implementado");
		}
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

void inserirMedalhas(Medalhas * competidores, int numeroCompetidores, FILE * arquivo)
{
	int contador = 0;
	char *token = NULL;
	char linha[TAMANHO_STRING];
	
	fgets(linha,sizeof(linha), arquivo);
	while((!feof(arquivo)) && (fgets(linha,sizeof(linha), arquivo)!=NULL))
	{
		if(contador > numeroCompetidores)
			return;
		printf("Linha: %s\n", linha);
		token = strtok(linha,";");
		printf("Token: %s\n", token);
		token = strtok(NULL,";");
		printf("Token 2: %s\n", token);
		contador++;
		
	}
}

void imprimirMedalhas(Medalhas * competidores, int numeroCompetidores)
{
	int contador;
	for(contador=0;contador<numeroCompetidores;contador++)
	{
		printf("%d %s", contador, competidores[contador].nome);
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
            break;
        default: printf("ue");
    }
}

