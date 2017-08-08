#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG 1
void lerString(char *, char *);
FILE * criarArquivo(char *);

struct Aluno
{
    char nome[255];
    char sobrenome[255];
    int matricula;
    float nota;
};

int main()
{
    char * nomeArquivo = NULL;
    lerString(nomeArquivo, "Digite o nome do arquivo:");
    FILE * arquivo = criarArquivo(nomeArquivo);
    fclose(arquivo);
    return 0;
}
void lerString(char *destino, char *mensagem)
{
    char entrada[255];
    printf("%s\n", mensagem);
    fgets(entrada, 254, stdin);
    strcpy(destino, strtok(entrada, "\n"));
}

FILE * criarArquivo(char *nome)
{
    FILE *arquivo = fopen(nome, "w");
    if (arquivo==NULL)
    {
        printf("Não foi possível criar o arquivo");
        exit(EXIT_FAILURE);
    }
    else
    {
       return arquivo;
    }
}
