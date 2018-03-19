#include <iostream>
#include <ctime>
#include <cstdlib>
#include <pthread.h>

#define DIM 200
#define NUM_THREADS 4
using namespace std;


int matriz_A[DIM][DIM];
int matriz_B[DIM][DIM];
int produto[DIM][DIM];

int main()
{
    srand(time(0));

    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            matriz_A[i][j] = rand()%10+1;
            matriz_B[i][j] = rand()%10+1;
        }
    }

    cout << "Matriz A:\n" << endl;
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            cout << matriz_A[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Matriz B:\n" << endl;
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            cout << matriz_B[i][j] <<" ";
        }
        cout << endl;
    }
    cout << endl;


    for(int i = 0; i < DIM ; i++){
        for(int j = 0; j < DIM; j++){
            for(int k = 0; k < DIM; k++){
            produto[i][j] += matriz_A[i][k] * matriz_B[k][j];
            }
        }
    }

    cout << "Matriz Produto:\n" << endl;
    for(int i = 0; i < DIM; i++){
        for(int j = 0; j < DIM; j++){
            cout << produto[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
