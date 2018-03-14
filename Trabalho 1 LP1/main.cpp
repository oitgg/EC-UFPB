/*
Aluno: Thiago Gonzaga Gomes
Matrícula: 11504760
Disciplina: Linguagem de Programação I
Professor: Carlos Eduardo Batista

Primeiro Trabalho - Canvas

-Escrito no Sublime Text + Atom
-Compilado/Debuggado no Codeblocks
-Utiliza a biblioteca <locale.h> para permitir a utilização em UTF-8 de caracteres especiais do idioma português por meio da função setlocale()
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
/* tipo 0 = sem polígono | tipo 2 = retangulo | tipo 3 = circulo | tipo 4 = triandulo | tipo 5 = hexagono */


//Na classe canvas, são utilizadas funções get e set para obter e definir o tamanho, em pixels, da altura e largura do canvas\\

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
        	// Uma função contador é iniciada chamando o incremento de todos os elementos (4 tipos de polígonos) com valor inicial igual a 0\\

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

            cout << "Retângulos: " << retangulo <<endl;
            cout << "Círculos: " << circulo << endl;
            cout << "Triângulos: " << triangulo << endl;
            cout << "Hexágonos: " << hexagono << endl;

        }
};

class poligono
{
    private:
        int coordcentro [2];
        int Zindex;
        string cor;

/*

-Na classe polígono, são instanciados os 4 tipos de polígonos que serão utilizados no decorrer do código (Retângulo, Círculo, Triângulo e Hexágono).
-Funções get e set, utilizando os parâmetros de coordenadas do canvas, adicionam os polígonos no canvas, juntamente com suas informações (centro [x,y] cor, área, perímetro).
-O cálculo da área e do perímetro é feito automaticamente no momento de inserção do valor correspondente ao tipo de polígono (altura e base pra retângulo | raio e pi para círculo | etc).

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

A função infocanvas retorna os valores de altura e largura do canvas.

*/

void infocanvas (canvas a,int x)
{
    int altura, largura;
    altura=a.altura();
    largura=a.largura();
    cout << "============================Informações do Canvas==============================="<<endl;
    cout << "Altura do Canvas: "<<altura << "\t\tLargura do Canvas: " << largura <<endl<<endl;
    a.verpoligonos(x);
    cout << "\n================================================================================"<<endl;
}


/*

As funções inserirretangulo() | inserircirrculo() | inserirtriangulo() e inserirhexagono(), através de métodos get e set, utilizando parâmetros de comparação
com as infoamções predefinidas do canvas, adquire os valores de altura, base, raio, largura etc - assim como o centro e cor - para a construção dos polígonos.

*/

void inserirretangulo (retangulo *p, canvas t)
{
    int a, b, centrox, centroy, restoaltura, restobase;
    char opcao;
    cout << "-------------------------------Inserir Retângulo--------------------------------"<<endl;
    cout << "Digite o comprimento base do retângulo: ";
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
    cout << "Digite a altura do retângulo: ";
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
    cout <<"Quais as coordenadas do centro do retângulo? \n";
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
        cout<<"O retângulo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;


    }
    }while((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy);
    p->setcentro(centrox,centroy);
    cout << "Este polígono está sobreposto a algum outro? (S ou N) ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Está sobreposto a quantos polígonos? ";
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
    else {cout <<"Opção inválida, digite uma opção válida"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do polígono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------Retângulo adicionado com sucesso--------------------------"<<endl;

}

void inserircirculo (circulo *p, canvas t)
{
    int r, centrox, centroy, restoraio1, restoraio2;
    char opcao;
    string cor;
   cout << "--------------------------------Inserir Círculo---------------------------------"<<endl;
    cout<<"Qual o comprimento do raio? ";
    cin>>r;
    cout<<endl;
    do{
    if(2*r>t.altura() || 2*r>t.altura())
    {
        cout << "O raio é muito grande, digite um valor menor: ";
        cin>> r;
        cout<<endl;
    }
    }while(2*r>t.altura() || 2*r>t.altura());
    p->setraio(r);
    cout <<"Quais as coordenadas do centro do círculo? \n";
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
        cout<<"O círculo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;
}
}while(p->getraio()>=centrox || p->getraio()>=centroy || restoraio1<=centrox || restoraio2<=centroy);
p->setcentro(centrox,centroy);
cout << "Este polígono está sobreposto a algum outro? (S ou N) ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Está sobreposto a quantos polígonos? ";
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
    else {cout <<"Opção inválida, digite uma opção válida!"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do polígono? ";
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
     cout << "-----------------------Círculo adicionado com sucesso---------------------------"<<endl;
}

void inserirtriangulo (triangulo *p, canvas t)
{
    int a, b, centrox, centroy,restoaltura, restobase;;
    char opcao;
     cout << "-------------------------------Inserir Triângulo--------------------------------"<<endl;
    cout << "Digite a base do triângulo: ";
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
    cout << "Digite a altura do triângulo: ";
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
    cout <<"Quais as coordenadas do centro do retângulo? \n";
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
        cout<<"O triângulo ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;

    }
    }while((p->getaltura()/2)>=centrox || p->getbase()/2>=centroy || restoaltura<=centrox || restobase<=centroy);
    p->setcentro(centrox,centroy);
       cout << "Este polígono está sobreposto a algum outro? (S ou N): ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Está sobreposto a quantos polígonos? ";
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
    else {cout <<"Opção inválida, digite uma opção válida"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do polígono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------Triângulo adicionado com sucesso-------------------------"<<endl;


}

void inserirhexagono (hexagono *p, canvas t)
{
    int l, centrox, centroy, restolado1, restolado2;
    char opcao;
     cout << "-------------------------------Inserir Hexágono---------------------------------"<<endl;
    cout << "Digite o comprimento de um dos lados do hexágono: ";
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

    cout <<"Quais as coordenadas do centro do hexágono? \n";
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
        cout<<"O hexágono ficou fora do canvas, digite outra coordenada x: ";
        cin>>centrox;
        cout<<endl;
        cout<<"Digite outra coordenada y: ";
        cin>>centroy;
        cout<<endl;

    }
    }while(p->getlado()>=centrox || p->getlado()>=centroy || restolado1<=centrox || restolado2<=centroy);
    p->setcentro(centrox,centroy);
       cout << "Este polígono está sobreposto a algum outro? (S ou N) ";
    cin >> opcao;
    cout<<endl;
    do{
    if (opcao=='S' || opcao=='s')
        {   int z;
            cout << "Está sobreposto a quantos polígonos? ";
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
    else {cout <<"Opção inválida, digite uma opção válida"<<endl; cin>>opcao; continue;}
    }while(opcao!='s'||opcao!='n'||opcao!='S'||opcao!='N');
    cout << "Qual a cor do polígono? ";
    string cor;
    cin >> cor;
    cout<<endl;
    p->setcor(cor);
    cout << "----------------------Hexágono adicionado com sucesso------------------------"<<endl;

}

/*

A função infopoligono() retorna os valores/informações sobre todos os polígonos inseridos pelo usuário, e ao mesmo tempo que faz isso, usando o método ofstream, salva a saída da função
em um arquivo de texto "InfoPolígonos.txt", atualizando o mesmo, em tempo real, assim que alterado.
O arquivo é criado no momento que o usuário solicita a função de listar os polígonos (com informações).

*/


void infopoligono (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{
    ofstream arquivo;

    if (i==0) {
    arquivo.open("InfoPolígonos.txt", std::ios_base::out | std::ios_base::ate);}

    else {
    arquivo.open("InfoPolígonos.txt", std::ios_base::out | std::ios_base::app | std::ios_base::ate);
    }
    switch (p->gettipo(i))
    {
    case 0:
        break;
    case 2:
        cout<<"Retângulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"Área: "<<a->retornaarea()<<"\t"<<"Perímetro: "<<a->retornaperimetro()<<endl;
        arquivo<<"Retângulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"Área: "<<a->retornaarea()<<"\t"<<"Perímetro: "<<a->retornaperimetro()<<endl;
        break;
    case 3:
        cout<<"Círculo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"Área: "<<b->retornaarea()<<"\t"<<"Perímetro: "<<b->retornaperimetro()<<endl;
        arquivo<<"Círculo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"Área: "<<b->retornaarea()<<"\t"<<"Perímetro: "<<b->retornaperimetro()<<endl;
        break;
    case 4:
        cout<<"Triângulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"Área: "<<c->retornaarea()<<"\t"<<"Perímetro: "<<c->retornaperimetro()<<endl;
        arquivo<<"Triângulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"Área: "<<c->retornaarea()<<"\t"<<"Perímetro: "<<c->retornaperimetro()<<endl;
        break;
    case 5:
        cout<<"Hexágono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"Área: "<<d->retornaarea()<<"\t"<<"Perímetro: "<<d->retornaperimetro()<<endl;
        arquivo<<"Hexágono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"Área: "<<d->retornaarea()<<"\t"<<"Perímetro: "<<d->retornaperimetro()<<endl;
        break;
    default: cout << "\n\nPolígono não identificado!\n"<<endl;
    }

   }


/*

A função excluirpoligono() retorna os polígonos listados, e por ordem de inserção, oferece ao usuário a possibilidade de excluir os mesmos.

*/

void excluirpoligono (retangulo *a,circulo *b, triangulo *c, hexagono *d,canvas *p,int i)
{

    char opcao;
    if (p->gettipo(i)==2)
    {
        cout<<"Retângulo\t"<<"Centro: "<<a->centrox()<<", "<<a->centroy()<<"\t"<<"Cor: "<<a->retornacor()<<"\t"<<"Área: "<<a->retornaarea()<<"\t"<<"Perimetro: "<<a->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse polígono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}
    }
    else if (p->gettipo(i)==3)
    {
        cout<<"Circulo\t"<<"Centro: "<<b->centrox()<<", "<<b->centroy()<<"\t"<<"Cor: "<<b->retornacor()<<"\t"<<"Área: "<<b->retornaarea()<<"\t"<<"Perímetro: "<<b->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse polígono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}
    }
    else if (p->gettipo(i)==4)
    {
        cout<<"Triangulo\t"<<"Centro: "<<c->centrox()<<", "<<c->centroy()<<"\t"<<"Cor: "<<c->retornacor()<<"\t"<<"Área: "<<c->retornaarea()<<"\t"<<"Perímetro: "<<c->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse polígono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}
    }
    else if (p->gettipo(i)==5)
    {
        cout<<"Hexagono\t"<<"Centro: "<<d->centrox()<<", "<<d->centroy()<<"\t"<<"Cor: "<<d->retornacor()<<"\t"<<"Área: "<<d->retornaarea()<<"\t"<<"Perímetro: "<<d->retornaperimetro()<<endl;
        cout<<"\nDeseja excluir esse polígono? (S ou N)   ";
        cin>>opcao;
        if (opcao=='S' || opcao=='s') {p->settipo(i,0);}
        else {system("pause");}

    }


}

/*

A função somaarea() retorna o valor da área, previamente calculada no momento de inserção dos valores do polígono.

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

A função somaperimetro() retorna o valor do perímetro, previamente calculada no momento de inserção dos valores do polígono.

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

- Na main(), foram setados 4 arrays, 1 para cada tipo de polígono, e neles, foram setados os valores de 1000 elementos.
- Os menus são apresentados de forma interativa, com as opções listadas de acordo com a funcionalidade que o usuário procura.
- Utilizando as funções system(), a cada chamada de case, após o mesmo ser executado, o retorno para o menu principal é oferecido ao usuário.
- Um int 'contapoligonos' foi criado para definir o valor inicial de polígonos, e, baseando-se nele, incrementos e decrementos são feitos no índice geral (para inclusão, exclusão e listagem).

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
    cout << "XX      Canvas Edit - Programa para criação e manipulação de polígonos        XX";
    cout << "XX                       Aluno: Thiago Gonzaga Gomes                          XX";
    cout << "XX                           Matrícula: 11504760                              XX";
    cout << "XX                                                                            XX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" << endl;
    int x,y;
    cout<<"\n1- Configurar o Canvas\n2- SAIR\n"<<endl;;
    do{
    cin>>opcao1;
    if (opcao1==1){
    cout << "================================================================================"<<endl;
    cout << "Para começar é preciso criar um Canvas (tela) de desenho para os polígonos,\n   após ter criado o Canvas, o usuário terá acesso ao menu principal\n"<<endl;
    cout << "================================================================================"<<endl;
    cout << "Digite a altura, em pixels, desejada para o Canvas: ";
    cin >> x;
    cout <<endl;
    cout << "Digite a largura, em pixels, desejada para o Canvas: ";
    cin >> y;
    cout<<endl;
    }
    else if(opcao1==2){break;}
    else {cout <<"Opção inválida! Digite uma opcão válida!\n"; continue; }
    }while(opcao1!=1 && opcao1!=2);
    canvas b (x, y);
    do{
    if (opcao1==2){break;}
    system("cls");
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XX                                                                            XX";
    cout << "XX      Canvas Edit - Programa para criação e manipulação de polígonos        XX";
    cout << "XX                       Aluno: Thiago Gonzaga Gomes                          XX";
    cout << "XX                           Matrícula: 11504760                              XX";
    cout << "XX                                                                            XX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n" << endl;
    cout << "=================================MENU PRINCIPAL================================="<<endl;
    cout << "1- Exibir informações do Canvas\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "2- Inserir Retângulo\n"<<endl;
    cout << "3- Inserir Círculo\n"<<endl;
    cout << "4- Inserir Triângulo\n"<<endl;
    cout << "5- Inserir Hexágono\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "6- Listar polígonos (com informações)\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "7- Excluir polígono\n"<<endl;
    cout << "--------------------------------------------------------------------------------"<<endl;
    cout << "8- Soma das áreas dos polígonos do Canvas\n"<<endl;
    cout << "9- Soma dos perímetros dos polígonos do Canvas\n"<<endl;
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
        cout << "============================Detalhes dos Polígonos=============================="<<endl;
        if (contapoligonos==0){cout<<"Sem informações... Adicione pelo menos um polígono antes!\n"<<endl;}
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
        cout << "=============================Excluir Polígonos================================="<<endl;
        if (contapoligonos==0){cout<<"\nVocê ainda não adicionou nenhum polígono\n\n";  cout << "================================================================================"<<endl; system("pause");  break;}
        cout << "Qual polígono, de acordo com a ordem de inserção, você deseja excluir?"<<endl;
        cout<<"Você possui ("<<contapoligonos<<") polígonos adicionados.\n\n"<<endl;
        int e;
        cin>>e;
        excluirpoligono(&r[e-1],&c[e-1],&t[e-1],&h[e-1],&b,e-1);
        cout << "\n==============================Excluído com sucesso============================="<<endl;
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
    cout << "=========================Soma das Áreas dos Polígonos==========================="<<endl;
        cout << "A soma das áreas dos polígonos contidos no Canvas é: "<<somadasareas<<endl<<endl;
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
        cout << "=======================Soma do Perímetro dos Polígonos=========================="<<endl;
        cout << "A soma dos perímetros dos polígonos contidos no Canvas é: "<<somadosperimetros<<endl<<endl;
        cout << "================================================================================"<<endl;
        system("pause");
        break;
    }
    else if(opcao==10)
    {
        break;
    }
    else {cout<<"Opção inválida! Digite uma opção válida!\n"; continue;}
    }while(opcao!=10);
     if (opcao1==2){break;}
    }while(opcao!=10);
     if (opcao1==2){break;}
    }while (opcao1!=0);

}
