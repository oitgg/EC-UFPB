#include <stdio.h>
#include <time.h>

/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Merge Sort*/

int countfile(char * str, int * max){
    FILE *f;
    f = fopen(str, "r");
    int size = 0;
    int aux;

    while(!feof (f))
    {
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

void MergeSort(int * arr, int st, int end){

    if(st < end){
        //Escolhe o elemento do meio do array para fazer a divisão
        int aux[end - st + 1];
        int m = (st + end)/2;
        int a = st;
        int b = m+1;
        int i = 0;
        //Chama o merge sort para o lado esquerdo e depois para o direito
        MergeSort(&arr[0], st, m);
        MergeSort(&arr[0], m+1, end);


        //Início do Merge
        //Percorre os dois pedaços separados do array com "a" e "b"
          while(a <= m && b < end+1){
            //Pega o menor valor dos dois e coloca no array auxiliar
            if(*(arr+a) <= *(arr+b)){
                *(aux+i) = *(arr+a);
                a++;
                i++;
            }
            else{
                *(aux+i) = *(arr+b);
                b++;
                i++;
            }
        }
        while(a <= m){
            *(aux+i) = *(arr+a);
            a++;
            i++;
        }

        while(b < end+1){
            *(aux+i) = *(arr+b);
            b++;
            i++;
        }

        for(i = st; i <= end; i++){
        *(arr+i) = *(aux+ i - st);
        }
    }
}


void main(){

    clock_t start, end;
    double cpu_time_used;
    int max = 0;

    int size = countfile("instancias-num/num.1000.1.in", &max);

    printf("\nTamanho do Array: %d, Valor Maximo: %d \n\n", size, max);

    int arr[size];
    int i;

    GetNumbersfromFile("instancias-num/num.1000.1.in", &arr[0]);

    printf("\nArray Inicial: {");
    for(i = 0; i < size; i++)
            printf("%d ", arr[i]);

    printf("}\n");

//Chamada do Merge Sort

	start = clock();
    MergeSort(&arr[0], 0, size-1);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    printf("\nMerge Sort Completo\n\n");
	printf("Tempo de Execucao %f segundo(s).\n\n", cpu_time_used);
    printf("Array Ordenado: {");

    for(i = 0; i < size; i++)
            printf("%d ", arr[i]);

    printf("}\n");

}