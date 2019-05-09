/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Selection Sort*/

/*
cria um array com N elementos
1. lê o array
2. repete passo 3,4,5 e 6 desde i=0 até n-1
3. define min = arr[i] e define loc=i
4. repete passo 5 para j=i+1 até n
5. se min > arr[j], então:
            a) define min=arr[j]
            b) define loc=j
    ~FIM DO IF~
    ~FIM DO LOOP DO PASSO 4~
6. intercala arr[i] e arr[loc] usando variavel temporaria
    ~FIM DO LOOP DO PASSO 2            
7. fim
*/


#include<stdio.h>

int main()
{
    int i,j,n,loc,temp,min,array[150];
    printf("Insira o numero de elementos:");
    scanf("%d",&n);
    printf("\nInsira os elementos\n");

    for(i=0;i<n;i++){
        scanf("%d",&array[i]);
    }

    for(i=0;i<n-1;i++){
        min=array[i];
        loc=i;
        for(j=i+1;j<n;j++){
            if(min>array[j]){
                min=array[j];
                loc=j;
            }
        }

        temp=array[i];
        array[i]=array[loc];
        array[loc]=temp;
    }

    printf("\nArray processado:\n");
    for(i=0;i<n;i++){
        printf("%d ",array[i]);
    }
    return 0;
}