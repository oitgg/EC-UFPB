#include <bits/stdc++.h>
using namespace std;

// tamanho máximo da matriz (12, 20, 40, 80, 100, 120, 160, 200)
#define MAX 20

// numero máximo de threads
#define MAX_THREAD 50

int matA[MAX][MAX];
int matB[MAX][MAX];
int matP[MAX][MAX];
int passo_incr = 0; //começando do passo incremental = 0

void* multiplicacao(void* arg)
{
    int comp = passo_incr++; //incrementa o passo atual de acordo com o computo individual de cada thread 

    // cada thread calcula 1/n da multiplicação (n = num de threads)
    for (int i = comp * MAX / 50; i < (comp + 1) * MAX / 50; i++)
        for (int j = 0; j < MAX; j++)
            for (int k = 0; k < MAX; k++)
                matP[i][j] += matA[i][k] * matB[k][j];
}

int main()
{
    // gera valores aleatorios pra colocar na matriz A e na matriz B
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }

    // print da matriz a
    cout << endl
         << "Matriz A" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matA[i][j] << " ";
        cout << endl;
    }

    // print da matriz b
    cout << endl
         << "Matriz B" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matB[i][j] << " ";
        cout << endl;
    }

    // declara o numero de threads predeterminado
    pthread_t threads[MAX_THREAD];

    // cria a quantidade predefinida de threads, cada uma avaliando sua própria parte
    for (int i = 0; i < MAX_THREAD; i++) {
        int* p;
        pthread_create(&threads[i], NULL, multiplicacao, (void*)(p));
    }

    // juntando as threads e esperando as outras terminarem
    for (int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);

    // print do resultado
    cout << endl
         << "Matriz Produto" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matP[i][j] << " ";
        cout << endl;
    }
    return 0;
}