#include <stdio.h>
#include <limits.h>

/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Algoritmo de Prim (MTSP = Minimum Spanning Tree)*/

void heapify(int * arr, int n, int i, int * key){
    int menor = i;  // Toma o primeiro elemento como sendo o menor
    int l = 2*i + 1;  // left = 2*i + 1
    int r = 2*i + 2;  // right = 2*i + 2

    // Troca se o filho da esquerda é menor que o atual "menor"
    if (l < n && key[arr[l]] < key[arr[menor]])
        menor = l;

    // Troca se o filho da direita for menor que o atual "menor"
    if (r < n && key[arr[r]] < key[arr[menor]])
        menor = r;

    // Se o "menor" não for a raiz da sub-árvore faz a troca
    if (menor != i)
    {
        int aux = arr[menor];
        arr[menor] = arr[i];
        arr[i] = aux;

        // Continua Consertando o heap
        heapify(arr, n, menor, key);
    }
}

void BuildMinHeap(int * heap, int size, int * key){
    int i;
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(heap, size, i, key);
}

int HeapExtMin(int * heap, int * size, int * key){
    int min = heap[0];

    heap[0] = heap[*(size) -1];
    *size = *size-1;

    heapify(heap, *size, 0, key);
    return min;
}

void HeapDecrease(int * heap, int a, int dec, int size, int * key){

    int i;//Encontrando o índice de a
    for(i = 0; i < size; i++){
        if(heap[i]==a)
            break;
    }


    if(key[a] < dec){
        ;
    }else{
        key[a] = dec;
        int parent = (i-1)/2;

        while(i > 0 && (key[heap[parent]] > key[heap[i]])){
            int aux = heap[i];
            heap[i] = heap[parent];
            heap[parent] = aux;
            i = parent;
            parent = (i-1)/2;
        }
    }
}

int GetV(char * str){

    FILE *f;
    f = fopen(str, "r");
    int aux;
    fscanf(f, "%d", &aux);

    fclose(f);

    return aux;


}

void FillTable(char * str, int * table){

    FILE *f;
    f = fopen(str, "r");

    int aux;
    int v;
    fscanf(f, "%d", &v);


    int i;
    for(i = 0; i < v; i++){

        int j;
        for(j = i; j < v; j++){

            if(j == i){
                *((table+j*v)+i) = 0;
            }else{

                fscanf(f,"%d", &aux);

                *((table+j*v)+i) = aux;
                *((table+i*v)+j) = aux;
            }
        }
    }
fclose(f);
}

void PrimMST(int * w, int size, int r){

    int i;
    int key[size];
    int father[size];
    int inmst[size];
    for(i = 0; i < size; i++){

        key[i] = INT_MAX;
        father[i] = -1;
        inmst[i] = 0;
    }
    key[r] = 0;
    inmst[r] = 1;

    int qsize = size;
    int q[size];
    //Preenchendo a queue
    for(i = 0; i<size; i++)
        q[i] = i;

    BuildMinHeap(&q[0], size, &key[0]);

    //Enquanto a fila não estiver vazia
    while(qsize > 0){


        int u = HeapExtMin(&q[0], &qsize, &key[0]);

        printf("\n Queue: {");
        for(i = 0; i < qsize; i++)
            printf(" (%d,%d)", q[i], key[q[i]]);
        printf("}\n\n");

        inmst[u] = 1;

        //Para cada vizinho de u:
        int v;
        for(v = 0; v < size; v++){

            if(u == v){
                ;
            }else{                          //w[u][v]
                if((inmst[v]==0) && (  (*((w+u*size)+v))  < (key[v]))){
                  //  printf("\nFather[%d] = %d\n", v, u);
                    father[v] = u;
                    //key[v] = *((w+u*size)+v);
                    HeapDecrease(&q[0], v, (*((w+u*size)+v))  , size, &key[0]);
                }
            }

        }
    }

    //Printando a MST
    int sum = 0;
    printf("Aresta          Custo\n\n");
    for(i = 1; i<size; i++){
        printf("%d ---- %d      %d\n", father[i], i, key[i]);
        sum = sum + key[i];
    }
    printf("\nCusto Total: %d\n\n", sum);
}

int main(){

    int size = GetV("dij40.txt");

    int table[size][size];

    FillTable("dij40.txt", &table[0][0]);

    int i,j;
    for(i = 0; i < size; i++){
        printf("\n");
        for(j = 0; j < size; j++){
            printf("\t[%d] ", table[i][j]);
        }
    }
    printf("\n\n");

    PrimMST(&table[0][0], size, 0);

    return 0;
}
