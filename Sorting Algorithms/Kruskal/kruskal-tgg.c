#include<stdio.h>

/*Aluno: Thiago Gonzaga Gomes
Matricula: 11504760
Análise e Projeto de Algoritmos
Implementação do Algoritmo de Kruskal*/


#define MAX 11
#define NumeroDeVerticesGrafo 8

typedef struct Aresta
{
  int SaiDe, ChegaEm, ValorAresta;
}Aresta;

typedef struct ListaDeAresta
{
  Aresta aresta[MAX];
  int NumeroAresta;
}ListaDeAresta;

ListaDeAresta listaAresta, arestasArvoreMinima;

int MatrizGrafo[MAX][MAX] = {
  {2,3,3,4,4,7,7,7,8,8,8},    //VALOR ARESTA
  {6,0,0,0,5,4,4,5,2,2,3},    //SAI DE
  {7,1,3,2,6,6,7,7,4,5,5},    //CHEGA EM
};

int NumeroDeVertices = NumeroDeVerticesGrafo;

void OrdenaPorValorArestaCrescente()
{
  int i,j;
  Aresta temp;

  for(i = 1; i < listaAresta.NumeroAresta; i++)
  {
    for(j = 0; j < listaAresta.NumeroAresta-1; j++)
    {
      if(listaAresta.aresta[j].ValorAresta > listaAresta.aresta[j+1].ValorAresta)
      {
          temp = listaAresta.aresta[j];
          listaAresta.aresta[j] = listaAresta.aresta[j+1];
          listaAresta.aresta[j+1] = temp;
      }
    }
  }
}

void TirarVerticeJaFoiVetor(int VetorJaFoiSoSai[],int saiDe,int ChegaEm)
{
  int i;

  for(i = 0; i < NumeroDeVertices; i++)
  {
    if(VetorJaFoiSoSai[i] == ChegaEm)
      VetorJaFoiSoSai[i] = saiDe;
  }
}

int ProcuraValorVetorJaFoiSoSai(int VetorJaFoiSoSai[],int NumeroVertice)
{
  return(VetorJaFoiSoSai[NumeroVertice]);
}

void kruskalMagic()
{
  int VetorJaFoiSoSai[MAX], i, saiDe, ChegaEm;
  listaAresta.NumeroAresta = 0;

  for(i = 0; i < MAX; i++)
  {
    listaAresta.aresta[listaAresta.NumeroAresta].ValorAresta = MatrizGrafo[0][i];
    listaAresta.aresta[listaAresta.NumeroAresta].SaiDe = MatrizGrafo[1][i];
    listaAresta.aresta[listaAresta.NumeroAresta].ChegaEm = MatrizGrafo[2][i];
    listaAresta.NumeroAresta++;
  }

  //OrdenaPorValorArestaCrescente();      //Não precisa devido a já mandar a matriz em ordem crescente do valor da aresta

  arestasArvoreMinima.NumeroAresta = 0;

  for(i = 0; i < NumeroDeVertices; i++)
      VetorJaFoiSoSai[i] = i;

  for(i = 0; i < listaAresta.NumeroAresta; i++)
  {
    saiDe = ProcuraValorVetorJaFoiSoSai(VetorJaFoiSoSai, listaAresta.aresta[i].SaiDe);
    ChegaEm = ProcuraValorVetorJaFoiSoSai(VetorJaFoiSoSai, listaAresta.aresta[i].ChegaEm);

    if(saiDe != ChegaEm)
    {
      arestasArvoreMinima.aresta[arestasArvoreMinima.NumeroAresta] = listaAresta.aresta[i];
      arestasArvoreMinima.NumeroAresta = arestasArvoreMinima.NumeroAresta + 1;
      TirarVerticeJaFoiVetor(VetorJaFoiSoSai, saiDe, ChegaEm);
    }
  }
}

void ImprimirArestasECusto()
{
  int i,cost=0;

  printf("\nSai de\t|Chega em \t|Valor Aresta");
  for(i=0; i < arestasArvoreMinima.NumeroAresta; i++)
  {
    printf("\n%d\t|%d       \t|%d",arestasArvoreMinima.aresta[i].SaiDe,arestasArvoreMinima.aresta[i].ChegaEm,arestasArvoreMinima.aresta[i].ValorAresta);
    cost=cost+arestasArvoreMinima.aresta[i].ValorAresta;
  }

  printf("\n\nCusto da arvore minima = %d",cost);
}

void main()
{
  kruskalMagic();
  ImprimirArestasECusto();
}
