#include <stdio.h>
 
#define TRUE              1
#define FALSE             0
#define IMP(b1, b2)       (b1 && !b2 ? FALSE : TRUE)
#define VARS              3
#define P                 0
#define Q                 1
#define R                 2
 
 
char nome[VARS];
int I[VARS];
 
 
void inicializa_formula()
{
  nome[P] = 'P';
  nome[Q] = 'Q';
  nome[R] = 'R';
 
  for (int c = 0; c < VARS; c++)
    I[c] = FALSE;
}
 
int ultima_interpretacao()
{
  int res = 1;
 
  for (int c = 0; c < VARS; c++)
  {
    res = res && I[c];
  }
 
  return res;
}
 
 
void proxima_interpretacao()
{
  int c = VARS - 1;
 
  while (c >= 0 && I[c] != 0)
  {
    I[c--] = 0;
  }
 
  if (c >= 0)
    I[c] = 1;
}
 
int valor_formula()
{
  return IMP(I[P], (I[R] && (I[Q] || I[R]))) && (!I[Q] || IMP(!I[Q], (I[R] && I[P])));
 
  //(P -> (R ^ (Q v R))) ^ (~Q v (~Q -> (R ^ P))
}
 
void mostra_tabela()
{
  int fim = FALSE;
 
  inicializa_formula();
 
  printf("FÃ³rmula Proposicional:\n");
  printf("(P -> (R ^ (Q v R))) ^ (~Q v (~Q -> (R ^ P))\n\n");
  
  for (int c = 0; c < VARS; c++)
  {
    printf(" %c |", nome[c]);
  }
  printf(" H\n");
 
  for (int c = 0; c < 4 * VARS + 3; c++)
    printf("-");
  printf("\n");
 
  while (!fim)
  {
     for (int c = 0; c < VARS; c++)
    {
      if (I[c])
        printf(" 1 |");
      else
        printf(" 0 |");
    }
 
    if (valor_formula())
      printf(" 1\n");
    else
      printf(" 0\n");
 
    if (ultima_interpretacao())
      fim = TRUE;
    else
      proxima_interpretacao();
  }
}
 
int main()
{
  
  printf("*******************************\n");
  printf("*  Calculo da Tabela Verdade  *\n");
  printf("*******************************\n\n\n");
 
  mostra_tabela();
 
  return 0;
}