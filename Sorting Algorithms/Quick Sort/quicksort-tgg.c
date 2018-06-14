#include <stdio.h>
#include <time.h>

/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Quick Sort*/

int countfile(char * str, int * max){
    FILE *f;
    f = fopen(str, "r");
    int size = 0;
    int aux;

    while(!feof (f)){
        fscanf(f, "%d", &aux);
        size++;
        if(aux > *max)
            *max = aux;
    }
    fclose(f);

    return size;
}

void GetNumbersfromFile(char * str, int * arr){

    FILE *f;
    f = fopen(str, "r");
    int i = 0;

    while(!feof (f)){
        fscanf(f, "%d", arr+i);
        i++;
    }
    fclose(f);
}


void QuickSort(int * arr, int min, int max){

    int pivo = *(arr+(min + max)/2);
    int a = min;
    int b = max;

    while(a<=b){
        //Anda com "a" até encontrar um valor maior que o pivô
        while((*(arr+a) < pivo) && (a < max)){
            a++;
        }
        //Anda com "b" até encontrar um valor menor que o pivô
        while((*(arr+b) > pivo) && (b > min)){
            b--;
        }

        if(a<=b){//Faz a troca de lado entre dois elementos
            int aux = *(arr+a);
            *(arr+a) = *(arr+b);
            *(arr+b) = aux;
            a++;
            b--;
        }
    }

    if(b > min){
        QuickSort(arr, min, b);
    }

    if(a < max){
        QuickSort(arr, a, max);
    }
}


void main(){

    clock_t start, end;
    double cpu_time_used;
    int max = 0;

    int size = countfile("instancias-num/num.10000.1.in", &max);

    printf("Tamanho do Array: %d, Valor Maximo: %d \n\n", size, max);

    int arr[size];
    int i;

    GetNumbersfromFile("instancias-num/num.10000.1.in", &arr[0]);


    printf("Array Inicial:\n{");
    for(i = 0; i < size; i++)
            printf("%d ", arr[i]);

    printf("}\n");

//Chamada do Quick Sort
    start = clock();
    QuickSort(&arr[0], 0, size-1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    printf("\nQuick Sort Completo\n\n");
    printf("Tempo de Execucao %f segundo(s).\n\n", cpu_time_used);
    printf("Array Ordenado:\n{");

    for(i = 0; i < size; i++)
            printf("%d ", arr[i]);

    printf("}\n");
}