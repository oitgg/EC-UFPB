#ifndef CARRO_H_
#define CARRO_H_

#include <iostream>
#include <thread>
#include <pthread.h>
#include "parque.h"
#include <mutex>

#define TEMP_VOLTA 2
#define MAX_NUM_VOLTAS 5

class FETCHANDADD { //Classe da função atômica Fetch-and-Add.

  public:

    std::mutex lock_mutex, print_mutex;

    FETCHANDADD() {
    }
      int fetchandadd(int &var, int incr){
        lock_mutex.lock();
        int tmp = var;
        var = var + incr;
        lock_mutex.unlock();
        return tmp;
    }
};

class Carro {
    static int capacidade;
	int voltas;
	bool Final;
	Parque &parque;
	FETCHANDADD &fetchandadd;

 public:
    int numPassageiros;
    Carro( Parque &p, FETCHANDADD &a );
	virtual ~Carro();
	void AguardaEntrada();
	void IniciaCorrida();
	void AguardaSaida();
    void SomaPassageiros(int);
	int getNumVoltas();
    int getCapacidade();
    int getNumPassageiros();
	Parque &getParque();
    void run();

	bool lock;

    int prox, *volta;
};

#endif /* CARRO_H_ */
