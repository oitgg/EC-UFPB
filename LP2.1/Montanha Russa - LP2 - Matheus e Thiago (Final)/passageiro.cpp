#include "passageiro.h"
#include <windows.h>
#include <iostream>

int TempoRand, ficha = 1; //Inicializa a variável do tempo aleatório e inicializa a ficha com 1.

Passageiro::Passageiro(Caror &c, FETCHANDADD &a) : carro(c), fetchandadd(a) {
}

Passageiro::~Passageiro() {
}

void Passageiro::Entrada() { //Permite a entrada do passageiro com fichas em número crescente a partir de 1.
    Sleep(500);
    fetchandadd.print_mutex.lock();
    std::cerr << "O passageiro " << id << " entrou com a ficha " << carro.volta[id] << "." << std::endl;
    fetchandadd.print_mutex.unlock();

    carro.SomaPassageiros(1);

    if (carro.getNumPassageiros() < carro.getCapacidade()) //Recebe passageiros até encher o carro.
        carro.prox++;

    while (!carro.lock);
}

void Passageiro::EsperaVolta() { //Aguarda a volta do carro.
    while (carro.lock);
}

void Passageiro::Saida() {
    fetchandadd.print_mutex.lock();
    TempoRand = (int (rand()) / float (RAND_MAX)) * 7 + 3; // Variando em tempos aleatórios.
    fetchandadd.print_mutex.unlock();

    fetchandadd.print_mutex.lock();
    std::cerr << "O passageiro " << id << " saiu do carro." << std::endl;
    fetchandadd.print_mutex.unlock();

    fetchandadd.fetchandadd(carro.numPassageiros, -1); //Decremta o número de passageiros no carro.
}

void Passageiro::RandomWalk() {
    std::this_thread::sleep_for(std::chrono::seconds(TempoRand)); //Passageiro passeia pelo parque por TempoRand segundos.
}

bool Passageiro::FecharParque() {
	if (carro.getNumVoltas() <= MAX_NUM_VOLTAS) //Fecha o parque após 5 voltas.
		return false;

        return true;
}

void Passageiro::Run(int i) { //Inicia a rotina de voltas.
    id = i;

	while (!FecharParque()) {

        if(ficha == MAX_NUM_VOLTAS * carro.getCapacidade() + 1)
            break;

        carro.volta[id] = fetchandadd.fetchandadd(ficha, 1);

        while (carro.volta[id] != carro.prox);
		Entrada(); //Aguarda o carro encher.

		EsperaVolta(); //Aguarda o carro dar uma volta.

		Saida(); // Aguarda a saída de todos os passageiros.

		RandomWalk(); // Passeio pelo parque.
	}

	Parque *parque = &carro.getParque();

	fetchandadd.print_mutex.lock();
	std::cerr << "O passageiro " << id << " saiu do parque." << std::endl;
	fetchandadd.print_mutex.unlock();

	fetchandadd.fetchandadd(parque->numPessoas, -1); //Decrementa o número de pessoas no parque.
}
