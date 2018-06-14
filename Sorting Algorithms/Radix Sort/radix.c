/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Radix Sort*/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int acharmaior(int vetor[], int tamanho)
{
  int aux=0;
  for(int i=0; i<tamanho; i++)
  {
    if(vetor[i] > aux)
      aux = vetor[i];
  }
  return aux;
}

void printvetor(int vetor[], int tamanho)
{
	for( int i = 0; i < tamanho; i++ )
		printf("%d ", vetor[i]);
}


void countingsort(int vetor[], int tamanho, int exp)
{
  int b[10];
  int b1[10];

  for(int i=0; i<10; i++)
  {
    b[i]=0;
    b1[i]=0;
  }

  int c[tamanho];

  for(int i=0; i<tamanho; i++)
  {
    c[i] = 0;
  }


  for (int i = 0; i < tamanho; i++)
  {
    if(vetor[i] >= 0)
    {
      int k = (vetor[i]/exp)%10;
      b[k]++;
    }
    else
    {
      int k = (-1*(vetor[i]/exp)%10);
      b1[k]++;
    }
  }


  for(int i = 8; i >= 0 ; i--)
  {
    b1[i] = b1[i] + b1[i+1];
  }

  b[0] = b[0] + b1[0];

  for(int i = 1; i < 10 ; i++)
  {
      b[i] =  b[i] + b[i-1];
  }

  for (int j=tamanho-1; j >= 0; j--)
  {
    if(vetor[j] >= 0)
    {
      c[ b[ (vetor[j]/exp)%10 ] -1] = vetor[j];
      b[ (vetor[j]/exp)%10 ] = b[(vetor[j]/exp)%10 ] - 1;
    }
    else
    {
      c[ b1[ (-1*(vetor[j]/exp)%10) ] -1] = vetor[j];
      b1[ (-1*(vetor[j]/exp)%10) ] = b1[ (-1*(vetor[j]/exp)%10) ] - 1;
    }
  }


  for (size_t i = 0; i < tamanho; i++)
  {
    vetor[i] = c[i];
  }

}

void radix(int vetor[], int tamanho)
{

  int k = acharmaior(vetor,tamanho);

  for(int i=1; k/i > 0; i*=10)
    countingsort(vetor, tamanho, i);
}



int main( void )
{
  clock_t Ticks[2];
  char url[] = "Instancias/num.10000.3.in";
  FILE *arq;
  arq = fopen(url, "r");
  char info1[15],info2[15];
  int i=0,tamanho=0;

  if(arq == NULL)
  {
			printf("Erro, nao foi possivel abrir o arquivo\n");
  }
  else
  {
      fgets(info1, sizeof(info1), arq);
      tamanho = atoi(info1);
  }

  int vetor[tamanho];

  while(fgets(info2, sizeof(info2), arq) != NULL)
  {
    vetor[i] = atoi(info2);
    i++;
  }

  printf("\nVetor: ");

  printvetor(vetor, tamanho);

  Ticks[0] = clock();
  radix(vetor, tamanho);
  Ticks[1] = clock();

  double Tempo = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;

  printf("\n\nVetor processado: ");

  printvetor(vetor, tamanho);

  printf("\n\nTempo gasto: %g ms.", Tempo);

  printf("\n\n");

  return 0;
}
