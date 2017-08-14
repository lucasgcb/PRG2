#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#define PRINCIPAL -1
#define IMPRIMIR 1
#define BUSCAR 2
#define SAIR 0
//#define DEBUG

#define ARQUIVOCSV DEFINIR_STRING(medalhas) //parametro é o nome do arquivo
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
int buscarMedalhas(Medalhas *, int);
void menu();
Medalhas * alocarStruct(int);
int main()
{
	setlocale(LC_CTYPE, "");
	
	int numeroCompetidores = 0;
	char nomeArquivo[TAMANHO_STRING];
	FILE * arquivo;
	bool sair = false;

	strcpy(nomeArquivo, ARQUIVOCSV);
	arquivo = abrirArquivoCSV(nomeArquivo);
	
	numeroCompetidores = lerNumeroLinhas(arquivo)-1;//menos cabeçalho
	Medalhas * competidores = alocarStruct(numeroCompetidores); 
    inserirMedalhas(competidores, numeroCompetidores, arquivo);
    
	
	while(!sair)
	{
		menu(PRINCIPAL);
		switch(lerInteiro("\n#Digite uma opção:\n"))
		{
			case IMPRIMIR: 
					imprimirMedalhas(competidores, numeroCompetidores);
					esperarInput(NULL);
					break;
			case BUSCAR:
					menu(BUSCAR);
					buscarMedalhas(competidores, numeroCompetidores);
					esperarInput(NULL);
					break;
			case SAIR: 
					printf("Adeus.\n");
					sair = true;
					break;
			default:
					printf("Não implementado.\n");
					esperarInput(NULL);
		}
	}
    fclose(arquivo);
    return EXIT_SUCCESS;
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
		token = strtok(linha,";");
		competidores[contador].posicao=atoi(token);
		token = strtok(NULL,";");
		if(token[0]==' ')//Verifica se há espaço em branco no inicio
		{
			strcpy(competidores[contador].nome,token+1); //Shift de 1 caractere
		}
		else
		{
			strcpy(competidores[contador].nome,token);
		}
		token = strtok(NULL,";");
		competidores[contador].ouro=atoi(token);
		token = strtok(NULL,";");
		competidores[contador].prata=atoi(token);
		token = strtok(NULL,";");
		competidores[contador].bronze=atoi(token);
		contador++;
		
	}
}

void imprimirMedalhas(Medalhas * competidores, int numeroCompetidores)
{
	int contador;
	for(contador=0;contador<numeroCompetidores;contador++)
	{
		printf("#%d - %s \n ** Ouro: %d\n  ** Prata: %d\n   ** Bronze: %d\n", contador, competidores[contador].nome,
		competidores[contador].ouro, competidores[contador].prata, competidores[contador].bronze);
	}
}

int buscarMedalhas(Medalhas * competidores, int numeroCompetidores)
{
	int valorMaisProximo = 0;
	int proximidade = 0;
	int soma = 0;
	char * nomeMaisProximo;
	char * sigla;
	char stringAuxiliar[TAMANHO_STRING];
	char nomeCompleto[TAMANHO_STRING];
	char pesquisa[TAMANHO_STRING];
	aplicarString(pesquisa, "Entre o nome do competidor ou sua sigla para pesquisar:\n");
	int contador;
	for(contador=0;contador<numeroCompetidores;contador++)
	{
		strcpy(stringAuxiliar, competidores[contador].nome);
		strcpy(nomeCompleto, competidores[contador].nome);
		strtok(nomeCompleto,"(");
		if(nomeCompleto[strlen(nomeCompleto)]==' ');
		{
			nomeCompleto[strlen(nomeCompleto)-1]=0; //remove o espaço seguido por (
		}
		sigla=strtok(stringAuxiliar,"(");
		sigla=strtok(NULL, ")");
		#ifdef DEBUG
			printf("SIGLA: %s\n",sigla);
			printf("Pais: %s\n", competidores[contador].nome); 
			printf("regex test: %d\n", contarCaracteres(competidores[contador].nome,' '));
			printf("Pesquisa: %s, Comparacao: %d\n", pesquisa, strcmp(pesquisa,nomeCompleto));
			printf("String: %s\n", nomeCompleto);
		#endif
		if(strcasecmp(pesquisa,nomeCompleto)==0 || strcasecmp(pesquisa,sigla)==0)
		{
			soma = competidores[contador].ouro + competidores[contador].prata + competidores[contador].bronze;
			printf("Total de medalhas de %s: \n ** %d", competidores[contador].nome, soma);
			return soma;
		}
		else
		{
			proximidade = abs(strcasecmp(pesquisa,nomeCompleto));
			if(proximidade > valorMaisProximo)
			{
				valorMaisProximo = proximidade;
				nomeMaisProximo = competidores[contador].nome;
				soma = competidores[contador].ouro + competidores[contador].prata + competidores[contador].bronze;
			}
		}
		
	}
	printf("O termo %s não retornou resultados.\n", pesquisa);
	printf("Nome mais próximo: %s\n", nomeMaisProximo);
	printf("Total de medalhas de %s: \n ** %d\n", nomeMaisProximo, soma);
	return soma;
}

void menu(int tipo)
{
	char separador[] = "*************************************";
	limparTela(); 
    switch(tipo)
    {
        case PRINCIPAL:
            printf("\n%s\n", separador);
            printf("%d - Imprimir Ranking \n", IMPRIMIR);
            printf("%d - Buscar time\n", BUSCAR);
            printf("%d - Sair \n", SAIR);
            printf("\n%s\n", separador);
            break;
        case BUSCAR:
			printf("\n%s\n", separador);
			printf("Buscar - ");
			break;
        default: printf("ue");
    }
}

