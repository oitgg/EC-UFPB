#include "parque.h"

Parque::Parque(int num) { //Contador de pessoas presentes no parque.
	numPessoas = num;
}

Parque::~Parque() {
	// TODO Auto-generated destructor stub
}

int Parque::getPessoasParque() { //Recebe quantas pessoas est�o no parque.
	return numPessoas;
}
