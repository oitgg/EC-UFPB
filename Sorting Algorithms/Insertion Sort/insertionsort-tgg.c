/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Insertion Sort*/


#include <stdio.h>

void insertion(int array[], int tamanho) {
      int i, j, tmp;
      for (i = 1; i < tamanho; i++) {
            j = i;
            while (j > 0 && array[j - 1] > array[j]) {
                  tmp = array[j];
                  array[j] = array[j - 1];
                  array[j - 1] = tmp;
                  j--;
            }
      }
}

int main(int argc, char** argv)
{
   int array[100], tamanho, ordem;
   printf("Insira o numero de termos:");
   scanf("%d", &tamanho);
   printf("\nInsira os elementos do array\n");
   for(int i = 0; i < tamanho;i++){
      printf("Digite o %do numero:",i+1);
      scanf("%d",&array[i]);
                                  }
  {
      insertion(array,tamanho);
      printf("\nArray processado: ");
      for(int i=0; i<tamanho; i++){
      printf("\n%d", array[i]);
        }
      }
   return 0;
}