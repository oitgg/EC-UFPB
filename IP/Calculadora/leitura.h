/****
 *
 * Título: LeituraFacil
 *
 * Autor: Ulysses de Oliveira
 *
 * Data de Criação: 15/07/2012
 * Última modificação: 15/07/2012
 *
 * Descrição: Definição do módulo da biblioteca LeituraFacil
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
