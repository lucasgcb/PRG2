#include <stdio.h>
#include <stdlib.h>


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
void adicionarNode(Lista*, int);
int main()
{
    Lista *listaPtr=alocarLista();
	Node *cabeca=alocarNode();
	listaPtr->cabeca=cabeca;
	listaPtr->rabo=cabeca;
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
    
    adicionarNode(listaPtr, 10);
    adicionarNode(listaPtr, 20);
    imprime_lista(listaPtr);
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

void adicionarNode(Lista* lista, int dado)
{
	Node *novoNode = alocarNode();
	novoNode->dado = dado;
	novoNode->proximo = NULL;
	lista->rabo->proximo=novoNode;
	lista->rabo=novoNode;
	lista->tamanho++;
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
