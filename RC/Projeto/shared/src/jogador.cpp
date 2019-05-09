#include "jogador.h"

void iniciar_jogadores()
{
    FILE *fp = fopen(J_DIRETORIO, "w");
    fclose(fp);
}

int get_num_jogadores()
{
    int ch;
    int num = 0;
    FILE *fp = fopen(J_DIRETORIO, "r");
    while (!feof(fp))
    {
        ch = fgetc(fp);
        if (ch == '\n')
            num++;
    }
    fclose(fp);
    return num;
}

// Salva um jogador no arquivo. Retorna 1 caso não possa inserir
int inserir_jogador(char* nome)
{
    if (get_num_jogadores() < 2)
    {
        FILE *fp = fopen(J_DIRETORIO, "a");
        fprintf(fp, "%s\n", nome);
        fclose(fp);
        return 0;
    }
    return 1;
}

// Busca o nome do oponente no arquivo
void get_nome_oponente(char *nome_jogador, char*nome_oponente)
{
    char *nome;
    nome = static_cast<char*>(calloc(20, sizeof(char)));
    FILE *fp = fopen(J_DIRETORIO, "r");
    (void) fscanf(fp, "%s\n",  nome);
    if (strcmp(nome, nome_jogador) == 0)
    {
        (void) fscanf(fp, "%s\n", nome);
    }
    strcpy(nome_oponente, nome);
    fclose(fp);
}
