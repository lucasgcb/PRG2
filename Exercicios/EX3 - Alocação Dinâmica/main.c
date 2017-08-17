#include "utils.h"
float somarValores(float * , int );
float somarDiferenca(float * , int , float );
void inserirValores(float * , int );
void imprimirValores(float * , int );
void escreverImpares(float*, int);
int main()
{
   setlocale(LC_CTYPE, "");

   float varianca = 0;
   float media = 0;
   int posicoes = 0;

   posicoes = lerInteiro("Entre o número de posições:\n");
   float* numeros = malloc(sizeof(float) * posicoes);
   escreverImpares(numeros,posicoes);
   //inserirValores(numeros, posicoes);
   imprimirValores(numeros, posicoes);

   media = (somarValores(numeros, posicoes)) / posicoes;
   varianca = (somarDiferenca(numeros,posicoes,media)) / posicoes;

   printf("media: %f\n", media);
   printf("varianca: %f", varianca);

   return EXIT_SUCCESS;
}

void escreverImpares(float * numeros,int posicoes)
{
	float num = 0;
	int contador;
	while(contador<posicoes)
	{
		num++;
		if((int)num % 2 != 0)
		{
			numeros[contador]=num;
			contador++;
		}
	}
}

void imprimirValores(float * valores, int posicoes)
{
   int contador = 0;
   for(contador = 0 ; contador<posicoes ; contador++)
   {
      printf("Pos %d - ", contador+1);
      printf("%f\n", valores[contador]);
   }

}

void inserirValores(float * valores, int posicoes)
{
   int contador = 0;
   for(contador = 0 ; contador<posicoes ; contador++)
   {
      printf("Pos %d - ", contador+1);
      valores[contador] = lerFloat("Entre o número da posição:\n");
   }
}


float somarDiferenca(float * valores, int posicoes, float diferenca)
{
   float soma = 0;
   int contador = 0;
   for(contador = 0 ; contador<posicoes ; contador++)
   {
      soma += (valores[contador] - diferenca) * (valores[contador] - diferenca);
   }
   return soma;
}


float somarValores(float * valores, int posicoes)
{
   float soma = 0;
   int contador = 0;
   for(contador = 0 ; contador<posicoes ; contador++)
   {
      soma += valores[contador];
   }
   return soma;
}
