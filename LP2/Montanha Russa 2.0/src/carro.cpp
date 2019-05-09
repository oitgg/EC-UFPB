#include "carro.h"
#include "passageiro.h"
#include <unistd.h>
#include <windows.h>
using namespace std;

int Carro::capacidade = 0;

Carro::Carro(Parque &p, FAClass &a) : parque(p), fetchandadd(a) {
	Carro::capacidade = 5; //Capacidade do carro.
	numPassageiros = 0; //Número inicial de passageiros.
	voltas = 1; //Número de voltas mínima por passageiro.
	prox = 1; //Contador individual de cada passageiro.
	lock = false; //Lock começa destravada.
	volta = new int [p.getPessoasParque() + 1]; //Cada pessoa dará uma volta.
}

Carro::~Carro() {
}

void Carro::AguardaEntrada() {
    while (numPassageiros != capacidade); //Aguarda a entrada dos 5 passageiros no carro.
    lock = true; //Trava o lock do carro para começar a viagem.
}

int Carro::getNumPassageiros() { //Recebe o número de passageiros no carro.
    return numPassageiros;
}

void Carro::SomaPassageiros(int num) { //Soma quantos passageiros estão no carro.
    numPassageiros += num;
}

int Carro::getCapacidade() { //Retorna a capacidade do carro.
    return capacidade;
}

Parque &Carro::getParque() { //Recebe as pessoas do parque.
	return parque;
}

void Carro::IniciaCorrida() { //Inicia a viagem.
    fetchandadd.print_mutex.lock();
    std::cerr << voltas << "a volta comecou." << std::endl;
    fetchandadd.print_mutex.unlock();

    fetchandadd.print_mutex.lock();
    std::cerr << "\nDANDO VOLTA, AGUARDE A VOLTA DO CARRINHO..." << std::endl;

    float progress = 0.0;
    while (progress < 1.0) {
    int barWidth = 20;
    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
    progress += 0.99;
}
std::cout << std::endl;

    std::this_thread::sleep_for( std::chrono::seconds(TEMP_VOLTA)); //Adormece a thread por 2 segundos.
    fetchandadd.print_mutex.unlock();

    fetchandadd.print_mutex.lock();
    std::cerr << voltas << "a volta terminou." << std::endl;
    fetchandadd.print_mutex.unlock();

    lock = false; //Destrava a lock e encerra a viagem.
}

void Carro::AguardaSaida(){ //Aguarda a saída de todos os passageiros.
    while (numPassageiros);
}

int Carro::getNumVoltas(){ //Recebe o número da volta atual.
	return voltas;
}

void Carro::run() {
	while (prox != MAX_NUM_VOLTAS * getCapacidade() + 1){ //Previne voltas consecutivas nas primeiras voltas.

		AguardaEntrada();  //Aguarda a entrada até ter 5 passageiros no carro.
		IniciaCorrida(); //Inicia a corrida.
		AguardaSaida(); //Aguarda a saída até ter 0 passageiros no carro.

		++voltas; //Incrementa o número de voltas.
		++prox; //Incrementa o contador individual de voltas de cada passageiro.
	}

	while (parque.getPessoasParque()); //Verifica se ainda existem pessoas no parque.

    fetchandadd.print_mutex.lock();
	std::cerr << std::endl << "Parque fechado." << std::endl;
	fetchandadd.print_mutex.unlock();
}
