/****
 *
 * T�tulo: LeituraFacil
 *
 * Autor: Ulysses de Oliveira
 *
 * Data de Cria��o: 15/07/2012
 * �ltima modifica��o: 15/07/2012
 *
 * Descri��o: Defini��o do m�dulo da biblioteca LeituraFacil
 *
 ****/

#ifndef _Leitura_H_
#define _Leitura_H_

extern int LeCaractere(void);
extern int LeInteiro(void);
extern double LeReal(void);
extern int LeString(char *ar, int nElementos);
extern int LeOpcao(const char *opcoes);

#endif
