#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "carro.h"
#include <cstdlib> //Função rand

class Passageiro {
    Carro &carro;
    FAClass &fetchandadd;
    int id;

 public:
    Passageiro(Carro &c, FAClass &a);
    virtual ~Passageiro();
    void Run(int);
    void Entrada();
	void EsperaVolta();
	void Saida();
	void RandomWalk();
	bool FecharParque();
};

#endif /* PASSAGEIRO_H_ */
