/*
Aluno: Thiago Gonzaga Gomes
Matr�cula: 11504760
Disciplina: Linguagem de Programa��o I
Professor: Carlos Eduardo Batista

Primeiro Trabalho - Canvas

-Escrito no Sublime Text + Atom
-Compilado/Debuggado no Codeblocks
-Utiliza a biblioteca <locale.h> para permitir a utiliza��o em UTF-8 de caracteres especiais do idioma portugu�s por meio da fun��o setlocale()
*/




#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <fstream>

using namespace std;

class canvas
{
    private:
        int pixelsize[2];
        int tipo[100];
/* tipo 0 = sem pol�gono | tipo 2 = retangulo | tipo 3 = circulo | tipo 4 = triandulo | tipo 5 = hexagono */


//Na classe canvas, s�o utilizadas fun��es get e set para obter e definir o tamanho, em pixels, da altura e largura do canvas\\

    public:
    canvas (int x, int y)
    {
        pixelsize[0]=x;
        pixelsize[1]=y;
    }
    int gettipo (int i)
    {
       return tipo[i];
    }
    void settipo (int i,int x)
    {
        tipo[i]=x;
    }
       int altura ()
        {
           return pixelsize[0];
        }
        int largura ()
       {
            return pixelsize[1];
        }
        int retornapoligonos (int coord)
        {
            return tipo[coord];
        }
        void verpoligonos (int contador)
        {
        	// Uma fun��o contador � iniciada chamando o incremento de todos os elementos (4 tipos de pol�gonos) com valor inicial igual a 0\\

            int retangulo=0, circulo=0, triangulo=0, hexagono=0;
            for (int i=0; i<contador;i++)
            {
                switch (tipo[i])
                {
                    case 2:
                        retangulo++;
                        break;
                    case 3:
                        circulo++;
                        break;
                    case 4:
                        triangulo++;
                        break;
                    case 5:
                        hexagono++;
                        break;
                }
            }

            cout << "Ret�ngulos: " << retangulo <<endl;
            cout << "C�rculos: " << circulo << endl;
            cout << "Tri�ngulos: " << triangulo << endl;
            cout << "Hex�gonos: " << hexagono << endl;

        }
};

class poligono
{
    private:
        int coordcentro [2];
        int Zindex;
        string cor;

/*

-Na classe pol�gono, s�o instanciados os 4 tipos de pol�gonos que ser�o utilizados no decorrer do c�digo (Ret�ngulo, C�rculo, Tri�ngulo e Hex�gono).
-Fun��es get e set, utilizando os par�metros de coordenadas do canvas, adicionam os pol�gonos no canvas, juntamente com suas informa��es (centro [x,y] cor, �rea, per�metro).
-O c�lculo da �rea e do per�metro � feito automaticamente no momento de inser��o do valor correspondente ao tipo de pol�gono (altura e base pra ret�ngulo | raio e pi para c�rculo | etc).

*/
    public:
        void setcentro (int x, int y)
        {
            coordcentro[0]=x;
            coordcentro[1]=y;
        }
        int centrox ()
        {
            return coordcentro[0];
        }
        int centroy ()
        {
            return coordcentro[1];
        }
        void setcor (string collor)
        {
            cor=collor;
        }
        void setZ (int z)
        {
            Zindex=z;
        }
        void retornarcentro (int *x ,int *y)
        {
            *x=coordcentro[0];
            *y=coordcentro[1];
        }
        string retornacor ()
        {
            return cor;
        }

};

class retangulo:public poligono
{
   private:
    int base, altura;

   public:
    retangulo ()
    {}
    int getaltura ()
    {
        return altura;
    }
    int getbase ()
    {
        return base;
    }
    void setbase (int x)
    {
        base=x;
    }
    void setaltura(int y)
    {
        altura=y;
    }
    int retornaarea ()
    {
        return base*altura;
    }

    int retornaperimetro ()
    {
        return (2*base)+(2*altura);
    }
};

class circulo:public poligono
{
    private:
        int raio;

    public:
        circulo ()
        {}
        int getraio()
        {
            return raio;
        }
        void setraio (int r)
        {
            raio=r;
        }
        int retornaarea ()
        {
        return raio*raio*3.14;
        }
        int retornaperimetro ()
        {
            return 2*3.14*raio;
        }

};

class triangulo:public poligono
{
    private:
        int base, altura;

    public:
        triangulo ()
        {}
        void setbase(int x)
        {
            base=x;
        }
        void setaltura (int y)
        {
            altura=y;
        }
        int getaltura ()
        {
            return altura;
        }
        int getbase ()
        {
            return base;
        }
        int retornaarea ()
        {
            return base*altura;
        }
        int retornaperimetro ()
        {
            return base*3;
        }

};

class hexagono:public poligono
{
    private:
        int lado;

    public:
        void setlado (int l)
        {
            lado=l;
        }
        int getlado ()
        {
            return lado;
        }
        int retornaarea ()
        {
            return (6*lado*lado*(sqrt(3)))/4;

        }
        int retornaperimetro ()
        {
            return lado*6;
        }
};


/*

A fun��o infocanvas retorna os valores de altura e largura do canvas.

*/

void infocanvas (canvas a,int x)
{
    int altura, largura;
    altura=a.altura();
    largura=a.largura();
    cout << "============================Informa��es do Canvas==============================="<<endl;
    cout << "Altura do Canvas: "<<altura << "\t\tLargura do Canvas: " << largura <<endl<<endl;
    a.verpoligonos(x);
    cout << "\n================================================================================"<<endl;
}


/*

As fun��es inserirretangulo() | inserircirrculo() | inserirtriangulo() e inserirhexagono(), atrav�s de m�todos get e set, utilizando par�metros de compara��o
com as infoam��es predefinidas do canvas, adquire os valores de altura, base, raio, largura etc - assim como o centro e cor - para a constru��o dos pol�gonos.

*/

void inserirretangulo (retangulo *p, canvas t)
{
    int a, b, centrox, centroy, restoaltura, restobase;
    char opcao;
    cout << "-------------------------------Inserir Ret�ngulo--------------------------------"<<endl;
    cout << "Digite o comprimento base do ret�ngulo: ";
    cin >> a;
    cout <<endl;
    do{
    if (a>=t.largura())
    {
        cout << "Valor grande demais, defina um tamanho menor para a base: ";
        cin >> a;
        cout<<endl;
    }
    }while(a>=t.largura());
    cout << "Digite a altura do ret�ngulo: ";
    cin >> b;
    cout <<endl;
    do{
    if (b>=t.altura())
    {
        cout<<"Valor grande demais, defina um tamanho menor para a altura: ";
        cin >>b;
        cout<<endl;
    }
    }while(a>=t.altura());

    p->setbase(a);
    p->setaltura(b);
    cout <<"Quais as coordenadas do centro do ret�ngulo? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restoaltura=t.altura()-p->getaltura()/2;
    restobase=t.largura()-p->getbase()/2;
    if ((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy)
    {
        cout<<"O ret�ngulo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;


    }
    }while((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy);
    p->setcentro(centrox,centroy);
    cout << "Este pol�gono est� sobreposto a algum outro? (S ou N) ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Est� sobreposto a quantos pol�gonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
            break;
        }
    else if (opcao=='N' || opcao=='n')
        {
        p->setZ(0);
        break;
        }
    else {cout <<"Op��o inv�lida, digite uma op��o v�lida"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do pol�gono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------Ret�ngulo adicionado com sucesso--------------------------"<<endl;

}

void inserircirculo (circulo *p, canvas t)
{
    int r, centrox, centroy, restoraio1, restoraio2;
    char opcao;
    string cor;
   cout << "--------------------------------Inserir C�rculo---------------------------------"<<endl;
    cout<<"Qual o comprimento do raio? ";
    cin>>r;
    cout<<endl;
    do{
    if(2*r>t.altura() || 2*r>t.altura())
    {
        cout << "O raio � muito grande, digite um valor menor: ";
        cin>> r;
        cout<<endl;
    }
    }while(2*r>t.altura() || 2*r>t.altura());
    p->setraio(r);
    cout <<"Quais as coordenadas do centro do c�rculo? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restoraio1=t.altura()-p->getraio();
    restoraio2=t.largura()-p->getraio();
    if (p->getraio()>=centrox || p->getraio()>=centroy || restoraio1<=centrox || restoraio2<=centroy)
    {
        cout<<"O c�rculo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;
}
}while(p->getraio()>=centrox || p->getraio()>=centroy || restoraio1<=centrox || restoraio2<=centroy);
p->setcentro(centrox,centroy);
cout << "Este pol�gono est� sobreposto a algum outro? (S ou N) ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Est� sobreposto a quantos pol�gonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
            break;
        }
    else if (opcao=='N' || opcao=='n')
        {
        p->setZ(0);
        break;
        }
    else {cout <<"Op��o inv�lida, digite uma op��o v�lida!"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do pol�gono? ";
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
     cout << "-----------------------C�rculo adicionado com sucesso---------------------------"<<endl;
}

void inserirtriangulo (triangulo *p, canvas t)
{
    int a, b, centrox, centroy,restoaltura, restobase;;
    char opcao;
     cout << "-------------------------------Inserir Tri�ngulo--------------------------------"<<endl;
    cout << "Digite a base do tri�ngulo: ";
    cin >> a;
    cout <<endl;
    do{
    if (a>t.largura())
    {
        cout << "Valor grande demais, defina um tamanho menor para a base: ";
        cin >> a;
        cout<<endl;
    }
    }while(a>t.largura());
    cout << "Digite a altura do tri�ngulo: ";
    cin >> b;
    cout <<endl;
    do{
    if (b>t.altura())
    {
        cout<<"Valor grande demais, defina um tamanho menor para a altura: ";
        cin >>b;
        cout<<endl;
    }
    }while(a>t.altura());

    p->setbase(a);
    p->setaltura(b);
    cout <<"Quais as coordenadas do centro do ret�ngulo? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restoaltura=t.altura()-p->getaltura()/2;
    restobase=t.largura()-p->getbase()/2;
    if ((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy)
    {
        cout<<"O tri�ngulo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;

    }
    }while((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy);
    p->setcentro(centrox,centroy);
       cout << "Este pol�gono est� sobreposto a algum outro? (S ou N): ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Est� sobreposto a quantos pol�gonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
            break;
        }
    else if (opcao=='N' || opcao=='n')
        {
        p->setZ(0);
        break;
        }
    else {cout <<"Op��o inv�lida, digite uma op��o v�lida"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do pol�gono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------Tri�ngulo adicionado com sucesso-------------------------"<<endl;


}

void inserirhexagono (hexagono *p, canvas t)
{
    int l, centrox, centroy, restolado1, restolado2;
    char opcao;
     cout << "-------------------------------Inserir Hex�gono---------------------------------"<<endl;
    cout << "Digite o comprimento de um dos lados do hex�gono: ";
    cin >> l;
    cout <<endl;
    do{
    if ((l*2)>t.largura())
    {
        cout << "Valor grande demais, defina um comprimento menor para o lado: ";
        cin >> l;
        cout<<endl;
    }
    }while((l*2)>t.largura());
    p->setlado(l);

    cout <<"Quais as coordenadas do centro do hex�gono? \n";
    cout<<"A coordenada x: ";
    cin>>centrox;
    cout<<endl;
    cout<<"A coordenada y: ";
    cin >>centroy;
    cout<<endl;
    do{
    restolado1=t.altura()-p->getlado();
    restolado2=t.largura()-p->getlado();
    if (p->getlado()>=centrox || p->getlado()>=centroy || restolado1<=centrox || restolado2<=centroy)
    {
        cout<<"O hex�gono ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;

    }
    }while(p->getlado()>=centrox || p->getlado()>=centroy || restolado1<=centrox || restolado2<=centroy);
    p->setcentro(centrox,centroy);
       cout << "Este pol�gono est� sobreposto a algum outro? (S ou N) ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Est� sobreposto a quantos pol�gonos? ";
            cin >> z;
            cout<<endl;
            p->setZ(z);
            break;
        }
    else if (opcao=='N' || opcao=='n')
        {
        p->setZ(0);
        break;
        }
    else {cout <<"Op��o inv�lida, digite uma op��o v�lida"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do pol�gono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------Hex�gono adicionado com sucesso------------------------"<<endl;

}

/*

A fun��o infopoligono() retorna os valores/informa��es sobre todos os pol�gonos inseridos pelo usu�rio, e ao mesmo tempo que faz isso, usando o m�todo ofstream, salva a sa�da da fun��o
em um arquivo de texto "InfoPol�gonos.txt", atualizando o mesmo, em tempo real, assim que alterado.
O arquivo � criado no momento que o usu�rio solicita a fun��o de listar os pol�gonos (com informa��es).

*/


void infopoligono (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{
    ofstream arquivo;

    if (i==0) {
    arquivo.open("InfoPol�gonos.txt", std::ios_base::out | std::ios_base::ate);}

    else {
    arquivo.open("InfoPol�gonos.txt", std::ios_base::out | std::ios_base::app | std::ios_base::ate);
    }
    switch (p->gettipo(i))
    {
    case 0:
        break;
    case 2:
        cout<<"Ret�ngulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"�rea: "<<a->retornaarea()<<"\t"<<"Per�metro: "<<a->retornaperimetro()<<endl;
        arquivo<<"Ret�ngulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"�rea: "<<a->retornaarea()<<"\t"<<"Per�metro: "<<a->retornaperimetro()<<endl;
        break;
    case 3:
        cout<<"C�rculo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"�rea: "<<b->retornaarea()<<"\t"<<"Per�metro: "<<b->retornaperimetro()<<endl;
        arquivo<<"C�rculo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"�rea: "<<b->retornaarea()<<"\t"<<"Per�metro: "<<b->retornaperimetro()<<endl;
        break;
    case 4:
        cout<<"Tri�ngulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"�rea: "<<c->retornaarea()<<"\t"<<"Per�metro: "<<c->retornaperimetro()<<endl;
        arquivo<<"Tri�ngulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"�rea: "<<c->retornaarea()<<"\t"<<"Per�metro: "<<c->retornaperimetro()<<endl;
        break;
    case 5:
        cout<<"Hex�gono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"�rea: "<<d->retornaarea()<<"\t"<<"Per�metro: "<<d->retornaperimetro()<<endl;
        arquivo<<"Hex�gono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"�rea: "<<d->retornaarea()<<"\t"<<"Per�metro: "<<d->retornaperimetro()<<endl;
        break;
    default: cout << "\n\nPol�gono n�o identificado!\n"<<endl;
    }

   }


/*

A fun��o excluirpoligono() retorna os pol�gonos listados, e por ordem de inser��o, oferece ao usu�rio a possibilidade de excluir os mesmos.

*/

void excluirpoligono (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{

    char opcao;
    if (p->gettipo(i)==2)
    {
        cout<<"Ret�ngulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"�rea: "<<a->retornaarea()<<"\t"<<"Perimetro: "<<a->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse pol�gono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}
    }
    else if (p->gettipo(i)==3)
    {
        cout<<"Circulo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"�rea: "<<b->retornaarea()<<"\t"<<"Per�metro: "<<b->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse pol�gono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}
    }
    else if (p->gettipo(i)==4)
    {
        cout<<"Triangulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"�rea: "<<c->retornaarea()<<"\t"<<"Per�metro: "<<c->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse pol�gono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}
    }
    else if (p->gettipo(i)==5)
    {
        cout<<"Hexagono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"�rea: "<<d->retornaarea()<<"\t"<<"Per�metro: "<<d->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse pol�gono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}

    }


}

/*

A fun��o somaarea() retorna o valor da �rea, previamente calculada no momento de inser��o dos valores do pol�gono.

*/

int somaarea (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{
    switch (p->gettipo(i))
    {
    case 0:
        break;
    case 2:
        return a->retornaarea();
        break;
    case 3:
        return b->retornaarea();
        break;
    case 4:
        return c->retornaarea();
        break;
    case 5:
        return d->retornaarea();
        break;
}
}

/*

A fun��o somaperimetro() retorna o valor do per�metro, previamente calculada no momento de inser��o dos valores do pol�gono.

*/


int somaperimetro(retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{
    switch (p->gettipo(i))
    {
    case 0:
        break;
    case 2:
        return a->retornaperimetro();
        break;
    case 3:
        return b->retornaperimetro();
        break;
    case 4:
        return c->retornaperimetro();
        break;
    case 5:
        return d->retornaperimetro();
        break;
}
}

/*

- Na main(), foram setados 4 arrays, 1 para cada tipo de pol�gono, e neles, foram setados os valores de 1000 elementos.
- Os menus s�o apresentados de forma interativa, com as op��es listadas de acordo com a funcionalidade que o usu�rio procura.
- Utilizando as fun��es system(), a cada chamada de case, ap�s o mesmo ser executado, o retorno para o menu principal � oferecido ao usu�rio.
- Um int 'contapoligonos' foi criado para definir o valor inicial de pol�gonos, e, baseando-se nele, incrementos e decrementos s�o feitos no �ndice geral (para inclus�o, exclus�o e listagem).

*/

int main ()
{


    setlocale(LC_ALL, "Portuguese");

    int opcao1, continuador;
    retangulo r[1000];
    circulo c[1000];
    triangulo t[1000];
    hexagono h[1000];
    do{
    system("cls");
    int contapoligonos=0, opcao;;
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XX                                                                            XX";
    cout << "XX      Canvas Edit - Programa para cria��o e manipula��o de pol�gonos        XX";
    cout << "XX                       Aluno: Thiago Gonzaga Gomes                          XX";
    cout << "XX                           Matr�cula: 11504760                              XX";
    cout << "XX                                                                            XX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" << endl;
    int x,y;
    cout<<"\n1- Configurar o Canvas\n2- SAIR\n"<<endl;;
    do{
    cin>>opcao1;
    if (opcao1==1){
    cout << "================================================================================"<<endl;
    cout << "Para come�ar � preciso criar um Canvas (tela) de desenho para os pol�gonos,\n   ap�s ter criado o Canvas, o usu�rio ter� acesso ao menu principal\n"<<endl;
    cout << "================================================================================"<<endl;
    cout << "Digite a altura, em pixels, desejada para o Canvas: ";
    cin >> x;
    cout <<endl;
    cout << "Digite a largura, em pixels, desejada para o Canvas: ";
    cin >> y;
    cout<<endl;
    }
    else if(opcao1==2){break;}
    else {cout <<"Op��o inv�lida! Digite uma opc�o v�lida!\n"; continue; }
    }while(opcao1!=1 && opcao1!=2);
    canvas b (x, y);
    do{
    if (opcao1==2){break;}
    system("cls");
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XX                                                                            XX";
    cout << "XX      Canvas Edit - Programa para cria��o e manipula��o de pol�gonos        XX";
    cout << "XX                       Aluno: Thiago Gonzaga Gomes                          XX";
    cout << "XX                           Matr�cula: 11504760                              XX";
    cout << "XX                                                                            XX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" << endl;
    cout << "=================================MENU PRINCIPAL================================="<<endl;
    cout << "1- Exibir informa��es do Canvas\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "2- Inserir Ret�ngulo\n"<<endl;
    cout << "3- Inserir C�rculo\n"<<endl;
    cout << "4- Inserir Tri�ngulo\n"<<endl;
    cout << "5- Inserir Hex�gono\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "6- Listar pol�gonos (com informa��es)\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "7- Excluir pol�gono\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "8- Soma das �reas dos pol�gonos do Canvas\n"<<endl;
    cout << "9- Soma dos per�metros dos pol�gonos do Canvas\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "10- Sair do Menu\n"<<endl;
    cout << "================================================================================"<<endl;
    do{
    if (opcao1==2){break;}
    cin >> opcao;
    if (opcao==1)
    {
        infocanvas(b,contapoligonos);
        system("pause");
        break;
    }
    if (opcao==2)
    {
        inserirretangulo(&r[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==3)
    {
        inserircirculo(&c[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==4)
    {
        inserirtriangulo(&t[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==5)
    {
        inserirhexagono(&h[contapoligonos],b);
        b.settipo(contapoligonos,opcao);
        contapoligonos++;
        system("pause");
        break;
    }
    else if (opcao==6)
    {
        cout << "============================Detalhes dos Pol�gonos=============================="<<endl;
        if (contapoligonos==0){cout<<"Sem informa��es... Adicione pelo menos um pol�gono antes!\n"<<endl;}
        for(int i=0;i<contapoligonos;i++)
        {
            infopoligono(&r[i],&c[i],&t[i],&h[i],&b,i);
        }
    cout << "================================================================================"<<endl;
    system("pause");
    break;
    }
    else if (opcao==7)
    {
        cout << "=============================Excluir Pol�gonos================================="<<endl;
        if (contapoligonos==0){cout<<"\nVoc� ainda n�o adicionou nenhum pol�gono\n\n";  cout << "================================================================================"<<endl; system("pause");  break;}
        cout << "Qual pol�gono, de acordo com a ordem de inser��o, voc� deseja excluir?"<<endl;
        cout<<"Voc� possui ("<<contapoligonos<<") pol�gonos adicionados.\n\n"<<endl;
        int e;
        cin>>e;
        excluirpoligono(&r[e-1],&c[e-1],&t[e-1],&h[e-1],&b,e-1);
        cout << "\n==============================Exclu�do com sucesso============================="<<endl;
        system("pause");
        break;
    }
    else if(opcao==8)
    {
        int somadasareas=0;
        for(int i=0; i<contapoligonos;i++)
        {
            somadasareas+=somaarea(&r[i],&c[i],&t[i],&h[i],&b,i);
        }
    cout << "=========================Soma das �reas dos Pol�gonos==========================="<<endl;
        cout << "A soma das �reas dos pol�gonos contidos no Canvas �: "<<somadasareas<<endl<<endl;
    cout << "================================================================================"<<endl;
        system("pause");
        break;
    }
    else if(opcao==9)
    {
        int somadosperimetros=0;
        for (int i=0; i<contapoligonos;i++)
        {
            somadosperimetros+=somaperimetro(&r[i],&c[i],&t[i],&h[i],&b,i);
        }
        cout << "=======================Soma do Per�metro dos Pol�gonos=========================="<<endl;
        cout << "A soma dos per�metros dos pol�gonos contidos no Canvas �: "<<somadosperimetros<<endl<<endl;
        cout << "================================================================================"<<endl;
        system("pause");
        break;
    }
    else if(opcao==10)
    {
        break;
    }
    else {cout<<"Op��o inv�lida! Digite uma op��o v�lida!\n"; continue;}
    }while(opcao!=10);
     if (opcao1==2){break;}
    }while(opcao!=10);
     if (opcao1==2){break;}
    }while (opcao1!=0);

}
