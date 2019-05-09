#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <math.h>
#include <climits>
#include <cstdlib>
#include <time.h>
#include "include/Conjunto.h"

#define ALPHA 0.75
#define GRASP_ITERACOES 20

using namespace std;


// Fun��o que carrega a inst�ncia no vetor de objetos
vector <Conjunto> CarregaArquivo(string arquivo, int *range, int *facilidades)
{

    ifstream file;
    try
    {
        file.open(arquivo, ios::in);
        Conjunto auxiliar;
        vector <Conjunto> retorno;

        file >> (*facilidades) >> (*range);

        while (!file.eof())
        {

            file >> auxiliar.coord_x >> auxiliar.coord_y;
            auxiliar.visitado = false;
            auxiliar.facilidade = false;
            retorno.push_back(auxiliar);
        }
        return retorno;
    }

    catch (bad_alloc& e)
    {
        cerr << "Erro ao tentar acessar arquivo!" << endl;
    }
}



//Fun��o geradora de solu��o com fator de aleatoriedade
void Heuristica_Construtora_Grasp (int facilidades, int range, vector <Conjunto> &pontos, vector <int> *solucao)
{

    for (int i = 0; i < facilidades; i++)
    {
        //cout << "Gerando solucao da facilitadora: " << i << endl;

        //Esse vetor vai salvar o numero de n�s que cada n� consegue cobrir caso ele fosse uma facilitadora
        int cobertura[pontos.size()];

        //Inicializa o vetor com 0 para todos os valores
        for (int j = 0; j < pontos.size(); j++)
        {
            cobertura[j] = 0;
        }

        //gera vetor com quantidade de n�s que cada n� cobre
        for (int k = 0; k < pontos.size(); k++)
        {

            for (int l = 0; l < pontos.size(); l++)
            {

                if(pontos[k].visitado == false)
                {

                    //Calculo da hipotenusa para a dist�ncia entre dois pontos no plano 2D
                    float distancia = sqrt(pow((pontos[k].coord_x - pontos[l].coord_x), 2) + pow((pontos[k].coord_y - pontos[l].coord_y), 2));

                    //Se o n� analisado estiver dentro do range, incrementa o vetor correspondente
                    if (distancia <= range)
                        cobertura[k]++;
                }

            }

        }

        int maior_cobertura = 0, menor_cobertura = INT_MAX;
        int no_maior, no_menor;

        //pesquisa e salva no vetor, os n�s com a maior e a menor cobertura
        for (int j = 0; j < pontos.size(); j++)
        {

            if(cobertura[j] > maior_cobertura && pontos[j].visitado == false)
            {

                maior_cobertura = cobertura[j];
                no_maior = j;
            }
        }

        //variavel que vai salvar a media dos n�s cobertos pelo de maior e menor cobertura
        //a vari�vel ter� influencia na gera��o da solucao
        int valor_intermediario = maior_cobertura*ALPHA;

        //Gera um valor aleat�rio entre o primeiro e ultimo n�
        int nova_facilidade = (rand()%(pontos.size()-1));

        //Aqui entra a influencia do valor intermediario
        //Se a nova facilidade n�o tiver cobertura acima da media, uma nova facilidade aleatoria � gerada
        while (cobertura[nova_facilidade] < valor_intermediario)
        {

            nova_facilidade = (rand()%(pontos.size()-1));

        }

        //achado um elemento que satisfa�a a condi��o de parada, ele � adicionada a solucao como facilitadora (sempre o primeiro)
        solucao[i].push_back(nova_facilidade);
        pontos[nova_facilidade].facilidade = true;  //e marcado como facilidade
        pontos[nova_facilidade].visitado = true;    //e visitado

        //Ent�o adicionada a facilitadora, os demais pontos que estao cobertos pelo seu range e que n�o pertencerem � uma solu��o pr�via sao adicionados � solu��o
        for (int j = 0; j < pontos.size(); j++)
        {

            if (pontos[j].visitado == false)
            {

                float distancia = sqrt(pow((pontos[nova_facilidade].coord_x - pontos[j].coord_x), 2) + pow((pontos[nova_facilidade].coord_y - pontos[j].coord_y), 2));

                if (distancia <= range)
                {

                    solucao[i].push_back(j);
                    pontos[j].visitado = true;

                }
            }
        }
    }
}


//Fun��o geradora de solu��o
void Heuristica_Construtora_Gulosa (int facilidades, int range, vector <Conjunto> &pontos, vector <int> *solucao)
{

    for (int i = 0; i < facilidades; i++)
    {
        //cout << "Gerando solucao da facilitadora: " << i << endl;

        //Esse vetor vai salvar o numero de n�s que cada n� consegue cobrir caso ele fosse uma facilitadora
        int cobertura[pontos.size()];

        //Inicializa o vetor com 0 para todos os valores
        for (int j = 0; j < pontos.size(); j++)
        {
            cobertura[j] = 0;
        }

        for (int k = 0; k < pontos.size(); k++)
        {

            for (int l = 0; l < pontos.size(); l++)
            {

                if(pontos[k].visitado == false)
                {

                    //Calculo da hipotenusa para a dist�ncia entre dois pontos no plano 2D
                    float distancia = sqrt(pow((pontos[k].coord_x - pontos[l].coord_x), 2) + pow((pontos[k].coord_y - pontos[l].coord_y), 2));

                    //Se o n� analisado estiver dentro do range, incrementa o vetor correspondente
                    if (distancia <= range)
                        cobertura[k]++;
                }

            }

        }

        int maior_cobertura = 0;
        int nova_facilidade;

        //pesquisa e salva no vetor, os n�s com a maior e a menor cobertura
        for (int j = 0; j < pontos.size(); j++)
        {

            if(cobertura[j] > maior_cobertura && pontos[j].visitado == false)
            {

                maior_cobertura = cobertura[j];
                nova_facilidade = j;
            }
        }

        //achado o elemento de maior cobertura, ele � adicionada a solucao como facilitadora (sempre o primeiro)
        solucao[i].push_back(nova_facilidade);
        pontos[nova_facilidade].facilidade = true;  //e marcado como facilidade
        pontos[nova_facilidade].visitado = true;    //e visitado


        //Ent�o adicionada a facilitadora, os demais pontos que estao cobertos pelo seu range e que n�o pertencerem � uma solu��o pr�via sao adicionados � solu��o
        for (int j = 0; j < pontos.size(); j++)
        {

            if (pontos[j].visitado == false)
            {

                float distancia = sqrt(pow((pontos[nova_facilidade].coord_x - pontos[j].coord_x), 2) + pow((pontos[nova_facilidade].coord_y - pontos[j].coord_y), 2));

                if (distancia <= range)
                {

                    solucao[i].push_back(j);
                    pontos[j].visitado = true;

                }
            }
        }
    }
}


//Fun��o de movimenta��o que busca uma nova facilidade a partir dos n�s que sobraram (n�o foram visitados e nem s�o facilidades)
void Movimentacao_Local (int facilidades, int range, vector <Conjunto> &pontos, vector <int> *solucao)
{

    for (int i = 0; i < facilidades; i++)
    {

        //remove a facilidade i do conjunto de solu��es
        pontos[solucao[i][0]].facilidade = false;

        for (int j = 0; j < solucao[i].size(); j++)
        {

            //limpa completamente o conjunto de n�s cobertos pela facilidade i
            pontos[solucao[i][j]].visitado = false;

        }

        solucao[i].clear();

        //Esse vetor vai salvar o numero de n�s que cada n� consegue cobrir caso ele fosse uma facilitadora
        int cobertura[pontos.size()];

        //Inicializa o vetor com 0 para todos os valores
        for (int j = 0; j < pontos.size(); j++)
        {
            cobertura[j] = 0;
        }

        for (int k = 0; k < pontos.size(); k++)
        {

            if (pontos[k].visitado == false)
            {

                for (int l = 0; l < pontos.size(); l++)
                {

                    if(pontos[k].visitado == false)
                    {

                        //Calculo da hipotenusa para a dist�ncia entre dois pontos no plano 2D
                        float distancia = sqrt(pow((pontos[k].coord_x - pontos[l].coord_x), 2) + pow((pontos[k].coord_y - pontos[l].coord_y), 2));

                        //Se o n� analisado estiver dentro do range, incrementa o map correspondente
                        if (distancia <= range)
                            cobertura[k]++;

                    }
                }
            }
        }

        int maior_cobertura = 0;
        int nova_facilidade;

        //pesquisa e salva no vetor, os n�s com a maior e a menor cobertura
        for (int j = 0; j < pontos.size(); j++)
        {

            if(cobertura[j] > maior_cobertura && pontos[j].visitado == false)
            {

                maior_cobertura = cobertura[j];
                nova_facilidade = j;
            }
        }

        //achado o elemento de maior cobertura, ele � adicionada a solucao como facilitadora (sempre o primeiro)
        solucao[i].push_back(nova_facilidade);
        pontos[nova_facilidade].facilidade = true;  //e marcado como facilidade
        pontos[nova_facilidade].visitado = true;    //e visitado


        //Ent�o adicionada a facilitadora, os demais pontos que estao cobertos pelo seu range e que n�o pertencerem � uma solu��o pr�via sao adicionados � solu��o
        for (int j = 0; j < pontos.size(); j++)
        {

            if (pontos[j].visitado == false)
            {

                float distancia = sqrt(pow((pontos[nova_facilidade].coord_x - pontos[j].coord_x), 2) + pow((pontos[nova_facilidade].coord_y - pontos[j].coord_y), 2));

                if (distancia <= range)
                {

                    solucao[i].push_back(j);
                    pontos[j].visitado = true;

                }
            }
        }
    }
}


//Fun��o de movimenta��o que busca uma nova facilidade em todos os n�s, exceto os que j� s�o facilidades
void Movimentacao_Global (int facilidades, int range, vector <Conjunto> &pontos, vector <int> *solucao)
{

    for (int i = 0; i < facilidades; i++)
    {

        //remove a facilidade i do conjunto de solu��es
        pontos[solucao[i][0]].facilidade = false;

        for (int j = 0; j < solucao[i].size(); j++)
        {

            //limpa completamente o conjunto de n�s cobertos pela facilidade i
            pontos[solucao[i][j]].visitado = false;

        }

        solucao[i].clear();

        //Esse vetor vai salvar o numero de n�s que cada n� consegue cobrir caso ele fosse uma facilitadora
        int cobertura[pontos.size()];

        //Inicializa o mapa com 0 para todos os valores
        for (int j = 0; j < pontos.size(); j++)
        {
            cobertura[j] = 0;
        }

        for (int k = 0; k < pontos.size(); k++)
        {

            if (pontos[k].facilidade == false)
            {

                for (int l = 0; l < pontos.size(); l++)
                {

                    if(pontos[l].visitado == false)
                    {

                        //Calculo da hipotenusa para a dist�ncia entre dois pontos no plano 2D
                        float distancia = sqrt(pow((pontos[k].coord_x - pontos[l].coord_x), 2) + pow((pontos[k].coord_y - pontos[l].coord_y), 2));

                        //Se o n� analisado estiver dentro do range, incrementa o map correspondente
                        if (distancia <= range)
                            cobertura[k]++;

                    }
                }
            }
        }

        int maior_cobertura = 0;
        int nova_facilidade;

        //pesquisa e salva no map, os n�s com a maior e a menor cobertura
        for (int j = 0; j < pontos.size(); j++)
        {

            if(cobertura[j] > maior_cobertura && pontos[j].visitado == false)
            {

                maior_cobertura = cobertura[j];
                nova_facilidade = j;
            }
        }

        //remove a facilidade da solu��o
        if (pontos[nova_facilidade].visitado == true)
        {
            for (int j = 0; j < facilidades; j++)
            {

                for (int k = 0; k < solucao[j].size(); k++)
                {

                    if(solucao[j][k] == nova_facilidade)
                    {

                        //remove a nova facilidade de uma solu��o pr�via caso esse ponto j� tenha sido mapeado
                        solucao[j].erase(solucao[j].begin() + k);
                        pontos[nova_facilidade].visitado = false;
                        break;
                    }
                }
            }
        }


        //achado o elemento de maior cobertura, ele � adicionada a solucao como facilitadora (sempre o primeiro)
        solucao[i].push_back(nova_facilidade);
        pontos[nova_facilidade].facilidade = true;  //e marcado como facilidade
        pontos[nova_facilidade].visitado = true;    //e visitado


        //Ent�o adicionada a facilitadora, os demais pontos que estao cobertos pelo seu range e que n�o pertencerem � uma solu��o pr�via sao adicionados � solu��o
        for (int j = 0; j < pontos.size(); j++)
        {

            if (pontos[j].visitado == false)
            {

                float distancia = sqrt(pow((pontos[nova_facilidade].coord_x - pontos[j].coord_x), 2) + pow((pontos[nova_facilidade].coord_y - pontos[j].coord_y), 2));

                if (distancia <= range)
                {

                    solucao[i].push_back(j);
                    pontos[j].visitado = true;

                }
            }
        }
    }
}


//Fun��o que executa o VND(Variable Neighborhood Descent)
int VND (int facilidades, int range, vector <Conjunto> pontos, vector <int> *solucao)
{

    vector <Conjunto> solucao_inicial = pontos;
    int solucao1_valor = 0;

    //Gera��o de uma solu��o inicial qualquer
    Heuristica_Construtora_Grasp(facilidades, range, solucao_inicial, solucao);

    //salva o numero de pontos que foram cobertos pela solu��o inicial
    for (int i = 0; i < facilidades; i++)
    {
        solucao1_valor += solucao[i].size() - 1;
    }

    //cout << "Solucao 1: " << solucao1_valor << endl;
    //Contante do VND que representa o numero de movimenta��es sem sucesso sucessivas m�ximas que podem ser feitas
    int k = 0;
    while (k < 2)
    {

        vector <int> solucao_candidata [facilidades];

        for (int i = 0; i < facilidades; i++)
        {
            solucao_candidata[i] = solucao[i];
        }

        vector <Conjunto> pontos_candidatos = solucao_inicial;
        int solucao2_valor = 0;

        //Verifica o numero de erros consecutivos, se foi baixo, efetua uma movimenta��o local, se foi alto, uma movimenta��o global
        if (k == 0)
        {
            //cout << "Fazendo movimentacao local!" << endl;
            Movimentacao_Local(facilidades, range, pontos_candidatos, solucao_candidata);
        }
        else
        {
            //cout << "Fazendo movimentacao global!" << endl;
            Movimentacao_Global(facilidades, range, pontos_candidatos, solucao_candidata);
        }

        //salva o numero de pontos que foram cobertos pela solu��o candidata
        for (int i = 0; i < facilidades; i++)
        {
            solucao2_valor += solucao_candidata[i].size() - 1;
        }
        if (solucao2_valor > solucao1_valor)
        {

            for (int i = 0; i < facilidades; i++)
            {
                solucao[i] = solucao_candidata[i];
            }

            solucao_inicial = pontos_candidatos;
            solucao1_valor = solucao2_valor;

            k = 0;
            //cout << "melhorou!" << endl;
            //cout << "Solucao nova: " << solucao2_valor << endl;


        }
        else
        {

            k++;

        }
    }

    return solucao1_valor;
}


//Meta-heur�stica Grasp
void Grasp (int facilidades, int range, vector <Conjunto> pontos, vector <int> *solucao_final){

    //usa o tempo atual como semente da randomiza��o
    time_t tempo;
    srand(time(&tempo));

    //gera primeira solu��o com VND, usando fator de randomicidade ALPHA
    int valor_final = VND(facilidades, range, pontos, solucao_final);

    //cout << "\nEncontrou solucao de cobertura: " << valor_final << endl;

    //Inicia o loop do Grasp
    for (int i = 0; i < GRASP_ITERACOES; i++){

        vector <int> solucao_candidata [facilidades];

        //Procura uma nova solu��o aleat�ria e faz movimento de vizinhan�a pra melhorar
        int valor_candidato = VND(facilidades, range, pontos, solucao_candidata);

        //cout << "\nEncontrou solucao de cobertura: " << valor_candidato << endl;

        //Se a solu��o for melhor que a anterior, troca, se n�o, mant�m
        if (valor_candidato > valor_final){

            for (int j = 0; j < facilidades; j++){

                solucao_final[j] = solucao_candidata[j];

            }
            //cout << "\nTrocando! " << valor_final << " -> " << valor_candidato << endl;
            valor_final = valor_candidato;
        }
    }
}



int main()
{
    vector <Conjunto> pontos;
    int range, facilidades;

    //Carrega arquivo no vector de objetos "pontos"
    pontos = CarregaArquivo("instancia818.txt", &range, &facilidades);

    vector <int> solucao[facilidades];

    clock_t tempo = clock();

    //Grasp(facilidades, range, pontos, solucao);
    Heuristica_Construtora_Gulosa(facilidades, range, pontos, solucao);

    cout << "Duracao da execucao: " << (clock() - tempo) / (double)CLOCKS_PER_SEC << endl;

    cout << "\nSOLUCAO: " << endl;
    int cobertura = 0;
    for(int i = 0; i < facilidades; i++)
    {
        /*cout << "\n\nFacilidade no ponto: " << solucao[i][0] << " \nDe coordenadas: (" <<pontos[ ((solucao[i])[0]) ].coord_x << ", " << pontos[ ((solucao[i])[0]) ].coord_y << ")\nPontos Cobertos pela Facilidade: ";
        for(int j = 1; j < solucao[i].size(); j++)
        {
            cout<< ((solucao[i])[j]) << ", ";
        }*/
        cobertura += (solucao[i]).size()-1;
    }
    cout << "\n\nTotal obtido: "<< cobertura <<" pontos cobertos!\n";

    return 0;
}
