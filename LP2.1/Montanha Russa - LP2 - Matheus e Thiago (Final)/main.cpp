#include <iostream>
#include "passageiro.h"
#include "carro.h"
#include <thread>
#include <windows.h>
#include <cstdlib>


using namespace std;

int main() {
    Sleep(1000);
    std::cerr << "============================================" << std::endl;
    std::cerr << "          BEM VINDOS A MONTANHA RUSSA       " << std::endl;
    std::cerr << "         Organizacao: Matheus e Thiago.     " << std::endl;
    std::cerr << "============================================" << std::endl;

    std::cerr << "" << std::endl;

    int numPessoas = 13; //Número de pessoas no parque.

    Parque *parque = new Parque(numPessoas); //Prepara a thread do parque.
    FETCHANDADD *fetchandadd = new FETCHANDADD(); //Prepara o Fetch-And-Add (Ticket).
    Carro *carro = new Carro(*parque , *fetchandadd); //Cria um novo carro.
    Passageiro pass(*carro, *fetchandadd); //Inicializa a thread do passageiro.
    std::thread tCarro = std::thread(&Carro::run, carro); //Inicializa a rotina do carro.
    std::thread *tPassageiro = new std::thread [numPessoas]; //Inicializa a rotina dos pasaageiros.

    for (int i = 0; i < numPessoas; i++) {
        tPassageiro[i] = std::thread(&Passageiro::Run, pass, i+1); //Inicia a viagem do passageiro.
    }

    for (int i = 0; i < numPessoas; i++) { //Incrementa o número de pessoas no parque.
        tPassageiro[i].join();
    }

    tCarro.join();
    delete carro; //Deleta a thread do carro.

    return 0;
}
