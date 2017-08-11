#include "utils.h"

typedef struct Aluno
{
    char nome[TAMANHO_STRING];
    char sobrenome[TAMANHO_STRING];
    int matricula;
    float nota;
} Aluno;

void inscreverAlunos(int, FILE *);
void imprimirAlunos(Aluno *, int, FILE *);
Aluno * alocarStruct(int);

int main()
{
	setlocale(LC_CTYPE, "");
	int numeroAlunos;
	char nomeArquivo[TAMANHO_STRING];
	FILE * arquivo;

	aplicarString(nomeArquivo,"Digite o primeiro nome do arquivo:\n");
	arquivo = criarArquivo(nomeArquivo);
    numeroAlunos = lerInteiro("Digite o número de alunos a cadastrar:\n");
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
		limparTela();
		printf("### Aluno %d ###\n", contador+1);
		aplicarString(alunos[contador].nome,"Digite o primeiro nome do aluno:\n");
		aplicarString(alunos[contador].sobrenome,"Digite o sobrenome do aluno:\n");
		alunos[contador].matricula=lerInteiro("Digite a matrícula do aluno:\n");
		do
        {
            alunos[contador].nota=lerFloat("Digite a nota do aluno:\n");
            limparTela();
            if(alunos[contador].nota<0.0 || alunos[contador].nota>10.0)
            {
                printf("### Aluno %d ###\n", contador+1);
                printf("Nota fora de escopo. Tente novamente.\n");
            }
        }while(alunos[contador].nota<0.0 || alunos[contador].nota>10.0);
	}
	imprimirAlunos(alunos,numeroAlunos,arquivo);
}

