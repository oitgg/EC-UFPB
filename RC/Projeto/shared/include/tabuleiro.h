#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reseta o arquivo de jogadores
void iniciar_tabuleiro();
void zerar_tabuleiro(char tabuleiro[10]);

// Salva a última jogada no arquivo
void jogada(int posicao);

int get_posicao();

int validar_jogada(char tabuleiro[10], char posicao);

// Verifica se o jogo acabou após o movimento
// 0 - não acabou
// 1 - empate
// 2 - vitória
// 3 - derrota
int verificar_fim(char tabuleiro[10], char peca, char peca_oponente);

#endif // TABULEIRO_H
