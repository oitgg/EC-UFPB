#ifndef JOGADOR_H
#define JOGADOR_H

#include "defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct jogador
{
    char nome[MAXNAMESIZE];
};

// Reseta o arquivo de jogadores
void iniciar_jogadores();

// Retorna o número de jogadores da sessão
int get_num_jogadores();

// Salva um jogador no arquivo
int inserir_jogador(char* nome);

//char* get_nome_oponente(char *nome_jogador);
void get_nome_oponente(char *nome_jogador, char*nome_oponente);

#endif // JOGADOR_H
