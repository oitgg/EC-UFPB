#ifndef UI_H
#define UI_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <string>

void print_title(const char* title);
void print_menu();
void print_setup();
void print_ajuda();
void print_tabuleiro(const char tabuleiro[]);
void print_tela_jogo(char tabuleiro[10], char *nome, char peca, char *oponente, char peca_oponente);

#endif // UI_H
