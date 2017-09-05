#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

#define PRINCIPAL -1
#define IMPRIMIR 1
#define ADD 2
#define ADDC 3
#define REMOVER 4
#define BUSCAR 5
#define SAIR 0
//#define DEBUG

typedef struct no
{
   int dado;
   struct no * proximo;
} Node;

typedef struct lista
{
   struct no * cabeca;
   struct no * rabo;
   int tamanho;
} Lista;

int tamanhoLista(Lista* lista);
void imprime_lista(Lista*);
Lista * alocarLista();
Node * alocarNode();
int contem(Lista*,int);
int removerNo(Lista*, int );
void adicionarNode(Lista*, int);
void adicionarCabeca(Lista*, int);
void menu(int);
int vazia(Lista*);
int main()
{
    Lista *listaPtr=alocarLista();
    bool sair=0;
    /*(*listaPtr).tamanho = 0;
    (*noPtr).dado = 10;
    (*noPtr).proximo = NULL;
    (*listaPtr).cabeca = &noPtr;
    (*listaPtr).tamanho++;*/

    /*listaPtr->tamanho = 0;
    noPtr->dado = 10;
    noPtr->proximo = NULL;
    listaPtr->cabeca = noPtr;
    listaPtr->tamanho++;*/
    while(!sair)
	{
		menu(PRINCIPAL);
		switch(lerInteiro("\n#Digite uma opção:\n"))
		{
			case IMPRIMIR: 
					limparTela();
					imprime_lista(listaPtr);
					esperarInput(NULL);
					break;
			case BUSCAR:
					limparTela();
					if(contem(listaPtr, lerInteiro("Entre um numero para pesquisar: ")))
						printf("Entrada existe");
					else
						printf("Entrada não existe");
					esperarInput(NULL);
					break;
			case ADD:
					limparTela();
					adicionarNode(listaPtr, lerInteiro("Entre um numero para adicionar na lista: "));
					esperarInput(NULL);
					break;
			case ADDC:
					limparTela();
					adicionarCabeca(listaPtr, lerInteiro("Entre um numero para adicionar no topo da lista: "));
					esperarInput(NULL);
					break;
			case REMOVER:	
					limparTela();
					if(removerNo(listaPtr, lerInteiro("Entre um numero para retirar da lista: ")))
						printf("Numero removido\n");
					else
						printf("Numero não encontrado\n");
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
    return tamanhoLista(listaPtr);
}
	
void imprime_lista(Lista* lista)
{
	Node* cursor = lista->cabeca;
	while(cursor!=NULL)
	{
			printf("%d\n", cursor->dado);
			cursor = cursor->proximo;
	}
}
int tamanhoLista(Lista* lista)
{
	if(lista==NULL)
		exit(EXIT_FAILURE);
	return lista->tamanho;
}
Lista * alocarLista()
{
	Lista *lista = malloc(sizeof(Lista));
	if(lista==NULL)
		exit(EXIT_FAILURE);
	lista->cabeca=NULL;
	lista->rabo=NULL;
	lista->tamanho=0;
	return lista;
}

int contem(Lista *lista, int pesquisa)
{
	Node* cursor = lista->cabeca;
	while(cursor!=NULL)
	{
			if(pesquisa==cursor->dado)
				return true;
			cursor = cursor->proximo;
	}
	return false;
}

int removerNo(Lista *lista, int desejado)
{
	Node* aux = NULL;
	Node* cursor = lista->cabeca;
	if(cursor!=NULL && cursor->dado==desejado)
	{
		if(cursor->proximo==NULL)
		{
			free(cursor);
			cursor=aux;
			lista->cabeca=NULL;
			lista->tamanho--;
		}
		else
		{
			aux = cursor->proximo;
			lista->cabeca=cursor->proximo;
			free(cursor);
			lista->tamanho--;
		}
		return true;
	}
	while(cursor!=NULL)
	{
		if(cursor->proximo!=NULL)
		{
			if(cursor->proximo->dado==desejado)
			{
				if(cursor->proximo->proximo!=NULL)
				{
					aux=cursor->proximo->proximo;
					free(cursor->proximo);
					cursor->proximo=aux;
					lista->tamanho--;
				}
				else
				{
					free(cursor->proximo);
					cursor->proximo=aux;
					lista->rabo=cursor;
					lista->tamanho--;
				}
				return true;
			}
		}
		cursor = cursor->proximo;
	}
	return false;
}


void adicionarNode(Lista* lista, int dado)
{
	Node *novoNode = alocarNode();
	novoNode->dado = dado;
	novoNode->proximo = NULL;
	if(lista->cabeca==NULL)
		lista->cabeca=novoNode;
	if(lista->rabo!=NULL)
		lista->rabo->proximo=novoNode;
	lista->rabo=novoNode;
	lista->tamanho++;
}




void adicionarCabeca(Lista* lista, int dado)
{
	Node *novoNode = alocarNode();
	novoNode->dado = dado;
	if(lista->cabeca==NULL)
		novoNode->proximo = NULL;
	else
		novoNode->proximo = lista->cabeca;
	lista->cabeca=novoNode;
	if(lista->rabo==NULL)
			lista->rabo=novoNode;
	lista->tamanho++;
}

int vazia(Lista* lista)
{
	if(lista==NULL)
		return true;
	return false;
}

Node * alocarNode()
{
	Node *p = malloc(sizeof(Node));
	if(p==NULL)
		exit(EXIT_FAILURE);
		
	p->proximo = NULL;
	p->dado = 0;
	return p;
}

void menu(int tipo)
{
	char separador[] = "*************************************";
	limparTela(); 
    switch(tipo)
    {
        case PRINCIPAL:
            printf("\n%s\n", separador);
            printf("%d - Imprimir Lista\n", IMPRIMIR);
            printf("%d - Adicionar No\n", ADD);
            printf("%d - Adicionar Cabeca \n", ADDC);
            printf("%d - Remover No \n", REMOVER);
            printf("%d - Buscar Elemento No \n", BUSCAR);
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

