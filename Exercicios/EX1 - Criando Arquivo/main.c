#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#ifdef _WIN32
#include <conio.h>
#endif 
#define TAMANHO_STRING 255


int lerInteiro(char *);
float lerFloat(char *);
void aplicarString(char *, char *);
//void criarCaminho(char *, char *);
void limparTela();
void limparEntrada();
void inscreverAlunos(int, FILE *);
FILE * criarArquivo(char *);

typedef struct Aluno
{
    char nome[TAMANHO_STRING];
    char sobrenome[TAMANHO_STRING];
    int matricula;
    float nota;
} Aluno;

void imprimirAlunos(Aluno *, int, FILE *);
Aluno * alocarStruct(int);

int main()
{
	setlocale(LC_CTYPE, "");
	int numeroAlunos;
	char nomeArquivo[TAMANHO_STRING];
	FILE * arquivo;
	
	aplicarString(nomeArquivo,"Digite o nome do arquivo:");
	arquivo = criarArquivo(nomeArquivo);
    numeroAlunos = lerInteiro("Digite o número de alunos a cadastrar:");
    inscreverAlunos(numeroAlunos,arquivo);
    
    fclose(arquivo);
    return 0;
}


Aluno* alocarStruct(int posicoes)
{
	Aluno * retorno;
	retorno = malloc(sizeof(Aluno)*posicoes);
	if(!retorno)
	{
			printf("Erro ao alocar matriz");
			exit(EXIT_FAILURE);
	}
	
    return retorno;
}

void imprimirAlunos(Aluno * alunos, int numeroAlunos, FILE * arquivo)
{
	int contador;
	for(contador=0;contador<numeroAlunos;contador++)
	{
		fprintf(arquivo, "###Aluno Matricula No %d###\n",alunos[contador].matricula);
		fprintf(arquivo, "Nome: %s %s\n", alunos[contador].nome, alunos[contador].sobrenome);
		fprintf(arquivo,"Nota: %.2f\n", alunos[contador].nota);
	}
}
void inscreverAlunos(int numeroAlunos, FILE * arquivo)
{
	Aluno * alunos = alocarStruct(numeroAlunos);
	int contador;
	
	for(contador=0;contador<numeroAlunos;contador++)
	{
		printf("### Aluno %d ###\n", contador+1);
		aplicarString(alunos[contador].nome,"Digite o nome do aluno");
		aplicarString(alunos[contador].sobrenome,"Digite o sobrenome do aluno:");
		alunos[contador].matricula=lerInteiro("Digite a matrícula do aluno:");
		alunos[contador].nota=lerFloat("Digite a nota do aluno:");
		limparTela();
	}
	imprimirAlunos(alunos,numeroAlunos,arquivo);
}

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
	getchar();
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
    printf("%s\n", mensagem);
	fgets(entrada, TAMANHO_STRING-1, stdin);
	entrada[strlen(entrada) - 1] = '\0'; //retira \n do fgets()
	strcpy(destino, entrada);
}

FILE * criarArquivo(char *nome)
{
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
