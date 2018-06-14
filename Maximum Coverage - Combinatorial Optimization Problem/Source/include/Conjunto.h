#ifndef CONJUNTO_H
#define CONJUNTO_H

//Classe que cont�m todos os pontos que se deseja cobrir e que podem virar facilidades
class Conjunto
{
    public:
        //Contrutor padr�o
        Conjunto();

        //Destrutor virtual padr�o
        virtual ~Conjunto();

        int coord_x;
        int coord_y;
        bool facilidade;
        bool visitado;
};

#endif // CONJUNTO_H
