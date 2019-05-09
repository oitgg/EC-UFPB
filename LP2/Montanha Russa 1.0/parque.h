#ifndef PARQUE_H_
#define PARQUE_H_

class Parque {
  public:
    int numPessoas;
    Parque(int);
	virtual ~Parque();

    int getPessoasParque();
};

#endif /* PARQUE_H_ */
