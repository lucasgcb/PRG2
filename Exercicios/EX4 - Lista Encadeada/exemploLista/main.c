#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"
#include "no.h"

int main()
{
    no_t* elemento = NULL;
    lista_enc_t* lista = NULL;

    char nome_1[] = "IFSC";
    char nome_2[] = "DAELN";
    char nome_3[] = "Eletronica";

    lista = cria_lista_enc();

    elemento = cria_no((void*)nome_1);
    add_cauda(lista, elemento);

    elemento = cria_no((void*)nome_2);
    add_cauda(lista, elemento);

    elemento = cria_no((void*)nome_3);
    add_cauda(lista, elemento);


    printf("%s", lista.cauda.dados);
    return 0;
}
