#include <stdio.h>
#include <stdlib.h>

#define TRUE    1
#define FALSE   0


#define IMPVAL(b1, b2)       (b1 && !b2 ? FALSE : TRUE)
#define BIMPVAL(b1, b2)      (b1 == b2)


typedef enum tagTipo
{
  NEG, AND, OR, IMP, BIMP, P, Q, R
} Tipo;

typedef struct tagForm
{
  Tipo tipo;
  struct tagForm *dir;
  struct tagForm *esq;
} Formula;

#define VARS   3
#define PIND   0
#define QIND   1
#define RIND   2

char nome[VARS];
int I[VARS];

void inicializa_formula()
{
  nome[PIND] = 'P';
  nome[QIND] = 'Q';
  nome[RIND] = 'R';

  for (int c = 0; c < VARS; c++)
    I[c] = FALSE;
}

Formula* cria_formula(Tipo tipo, Formula *dir, Formula *esq)
{
  Formula *res = (Formula*) malloc(sizeof(Formula));

  if (res == NULL)
    return NULL;

  res->tipo = tipo;
  res->dir = dir;
  res->esq = esq;

  return res;
}

Formula* neg(Formula *e)
{
  return cria_formula(NEG, e, NULL);
}

Formula* andF(Formula *d, Formula *e)
{
  return cria_formula(AND, d, e);
}

Formula* orF(Formula *d, Formula *e)
{
  return cria_formula(OR, d, e);
}

Formula* imp(Formula *d, Formula *e)
{
  return cria_formula(IMP, d, e);
}

Formula* bimp(Formula *d, Formula *e)
{
  return cria_formula(BIMP, d, e);
}

Formula* var_p()
{
  return cria_formula(P, NULL, NULL);
}

Formula* var_q()
{
  return cria_formula(Q, NULL, NULL);
}

Formula* var_r()
{
  return cria_formula(R, NULL, NULL);
}


void destroi_formula(Formula *f)
{
  if (f != NULL)
  {
    switch(f->tipo)
    {
    case AND:
    case OR:
    case IMP:
    case BIMP:
      destroi_formula(f->dir);
      destroi_formula(f->esq);
      break;

    case NEG:
      destroi_formula(f->dir);
      break;
    }

    free(f);
  }
}

int indice_variavel(Tipo tipo)
{
  switch(tipo)
  {
  case P:
    return PIND;

  case Q:
    return QIND;

  case R:
    return RIND;

  default:
    return -1;
  }
}

int valor_formula(Formula *f)
{
  switch(f->tipo)
  {
  case P:
  case Q:
  case R:
    return I[indice_variavel(f->tipo)];

  case NEG:
    return !valor_formula(f->dir);

  case AND:
    return valor_formula(f->dir) &&
           valor_formula(f->esq);

  case OR:
    return valor_formula(f->dir) ||
           valor_formula(f->esq);

  case IMP:
    return IMPVAL(valor_formula(f->dir),
                    valor_formula(f->esq));

  case BIMP:
    return BIMPVAL(valor_formula(f->dir),
                   valor_formula(f->esq));
  }
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

void mostra_tabela(Formula *f)
{
  int fim = FALSE;

  inicializa_formula();

  printf("Formula:\n");
  printf("(P -> (R ^ (Q v R))) ^ (~Q v (~Q -> (R ^ P))\n\n");

  for (int c = 0; c < VARS; c++) {
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

      if (valor_formula(f))
      printf(" 1\n");
      else
      printf(" 0\n");

      if (ultima_interpretacao())
      fim = TRUE;
      else
      proxima_interpretacao();
  }
}

int main(int argc, char **argv)
{

  Formula *f = andF( imp(var_p(), andF(var_r(),orF(var_q(),var_r()))),
               orF(neg(var_q()),imp(neg(var_q()),andF(var_r(),var_p())) ) );

  printf("*******************************\n");
  printf("*  Calculo da Tabela Verdade  *\n");
  printf("*******************************\n\n\n");

  mostra_tabela(f);

  destroi_formula(f);

  return 0;
}