#include <stdio.h>
#include <time.h>

/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Heap Sort */

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

//heap max = todos os nós da árvore tem um valor maior ou igual a cada filho desse nó

void heapify(int * arr, int n, int i){
    int maior = i;    // Toma o primeiro elemento como sendo o maior
    int l = 2*i + 1;  // Left = 2*i + 1  (raíz no índice [0]) // (raíz no índice [1] = 2*i)
    int r = 2*i + 2;  // Right = 2*i + 2 (raíz no indice [0]) // (raíz no índice [1] = 2*i + 1)

    // Troca se o filho da esquerda é maior que o atual "maior"
    if (l < n && *(arr+l) > *(arr+maior))
        maior = l;

    // Troca se o filho da direita for maior que o atual "maior"
    if (r < n && *(arr+r) > *(arr+maior))
        maior = r;

    // Se o "maior" não for a raiz da sub-árvore faz a troca
    if (maior != i)
    {
        int aux = *(arr+maior);
        *(arr+maior) = *(arr+i);
        *(arr+i) = aux;

        // Continua montando o heap recursivamente
        heapify(arr, n, maior);
    }
}

void HeapSort(int * arr, int size){

    int i;
    // Constrói o heap
    for (i = size / 2 - 1; i >= 0; i--) // Nó Pai para índice [0] = i-1/2 // Nó Pai para índice [1] = i/2
        heapify(arr, size, i);

    // Remove do Heap um elemento por vez
    for (i=size-1; i>=0; i--)
    {
        // Troca a raiz com o ultimo elemento verificado pela variável auxiliar
        int aux = *arr;
        *arr = *(arr+i);
        *(arr+i) = aux;

        // Reorganiza o heap e repete enquanto a árvore não obedecer as regras de uma max heap
        heapify(arr, i, 0);
    }


}


void main(){

    clock_t start, end;
    double cpu_time_used;
    int max = 0;

    int size = countfile("instancias-num/num.100000.1.in", &max);

    printf("\nTamanho do Array: %d, Valor Maximo: %d \n\n", size, max);

    int arr[size];
    int i;

    GetNumbersfromFile("instancias-num/num.100000.1.in", &arr[0]);

    printf("\nArray Inicial: {");
    for(i = 0; i < size; i++)
            printf("%d ", arr[i]);

    printf("}\n");

//Chamada do Heap Sort

	start = clock();

    HeapSort(&arr[0], size);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nHeap Sort Completo\n\n");
	printf("Tempo de Execucao %f segundo(s).\n\n", cpu_time_used);
    printf("Array Ordenado: {");

    for(i = 0; i < size; i++)
            printf("%d ", arr[i]);

    printf("}\n");
}
