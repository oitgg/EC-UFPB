#include "tabuleiro.h"

void iniciar_tabuleiro()
{
    FILE *fp = fopen(T_DIRETORIO, "w");
    fclose(fp);
}

void zerar_tabuleiro(char tabuleiro[10])
{
    for (int i = 0; i < 10; i++)
    {
        tabuleiro[i] = ' ';
    }
}

void jogada(int posicao)
{
    FILE *fp = fopen(T_DIRETORIO, "w");
    fprintf(fp, "%d\n", posicao);
    fclose(fp);
}

int get_posicao()
{
    int posicao = -1;
    FILE *fp = fopen(T_DIRETORIO, "r");
    fscanf(fp, "%d", &posicao);
    fclose(fp);
    return posicao;
}

int validar_jogada(char tabuleiro[10], char posicao)
{
    if (posicao >= '1' && posicao <= '9')
    {
        if (tabuleiro[(posicao-48)-1] == ' ')
        {
            return 1;
        }
    }
    return 0;
}

int verificar_fim(char *tabuleiro, char peca, char peca_oponente)
{
    if ((tabuleiro[0] == peca && tabuleiro[1] == peca && tabuleiro[2] == peca) ||
        (tabuleiro[3] == peca && tabuleiro[4] == peca && tabuleiro[5] == peca) ||
        (tabuleiro[6] == peca && tabuleiro[7] == peca && tabuleiro[8] == peca) ||
        (tabuleiro[0] == peca && tabuleiro[3] == peca && tabuleiro[6] == peca) ||
        (tabuleiro[1] == peca && tabuleiro[4] == peca && tabuleiro[7] == peca) ||
        (tabuleiro[2] == peca && tabuleiro[5] == peca && tabuleiro[8] == peca) ||
        (tabuleiro[0] == peca && tabuleiro[4] == peca && tabuleiro[8] == peca) ||
        (tabuleiro[2] == peca && tabuleiro[4] == peca && tabuleiro[6] == peca))
    {
        return VITORIA;
    }
    if ((tabuleiro[0] == peca_oponente && tabuleiro[1] == peca_oponente && tabuleiro[2] == peca_oponente) ||
        (tabuleiro[3] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[5] == peca_oponente) ||
        (tabuleiro[6] == peca_oponente && tabuleiro[7] == peca_oponente && tabuleiro[8] == peca_oponente) ||
        (tabuleiro[0] == peca_oponente && tabuleiro[3] == peca_oponente && tabuleiro[6] == peca_oponente) ||
        (tabuleiro[1] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[7] == peca_oponente) ||
        (tabuleiro[2] == peca_oponente && tabuleiro[5] == peca_oponente && tabuleiro[8] == peca_oponente) ||
        (tabuleiro[0] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[8] == peca_oponente) ||
        (tabuleiro[2] == peca_oponente && tabuleiro[4] == peca_oponente && tabuleiro[6] == peca_oponente))
    {
        return DERROTA;
    }
    int i;
    for (i = 0; i < 9; i++)
    {
        if (tabuleiro[i] == ' ')
        {
            return NAO_ACABOU;
        }
    }
    return EMPATE;
}
