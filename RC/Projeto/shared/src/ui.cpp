#include "ui.h"

void print_title(const char* title)
{
    size_t i;
    size_t text_size = strlen(title);
    for (i = 0; i < 40-text_size/2-1; i++)
    {
        printf("_");
    }
    printf(" %s ", title);
    if (text_size % 2 == 0)
    {
        for (i = 40+text_size/2+1; i < 80; i++)
        {
            printf("_");
        }
    }
    else
    {
        for (i = 40+text_size/2+1; i < 79; i++)
        {
            printf("_");
        }
    }
    printf("\n\n");
}

void print_menu()
{
    system("clear");
    print_title("Menu");
    printf(" 1 - Novo jogo\n\n");
    printf(" 2 - Ajuda\n\n");
    printf(" 3 - Sair\n\n");
    printf(" Opção escolhida > ");
}

void print_ajuda()
{
    system("clear");
    print_title("Ajuda do jogo da velha");
    printf(" As regras são as mesmas do jogo da velha tradicional.\n\n");
    printf(" Após se conectar, escolha um nome e aguarde outro jogador logar.\n\n");
    printf(" Para fazer sua jogada, basta digitar a coordenada desejada, como no tabuleiro: \n\n");
    print_tabuleiro("123456789");
    printf("\n Tecle enter para voltar > ");
    std::cin.get();
    getchar();
}

void print_setup()
{
    system("clear");
    print_title("Novo jogo");
    printf(" Digite seu nome > ");
}

void print_tela_jogo(char tabuleiro[10], char *nome, char peca, char *oponente, char peca_oponente)
{
    system("clear");
    print_title("Jogo da velha");
    printf(" Você (%s) está jogando com [%c]\n", nome, peca);
    printf(" Seu oponente (%s) está jogando com [%c]\n", oponente, peca_oponente);
    print_tabuleiro(tabuleiro);
    printf("\n");
}

void print_tabuleiro(const char tabuleiro[10])
{
    char espacos[] = "                                 ";
    std::string tabuleiro_str[9] = { };
    for (int i = 0; i < 9; i++)
    {
        tabuleiro_str[i] = " ";
        tabuleiro_str[i] += tabuleiro[i];
        tabuleiro_str[i] += " ";
        if (tabuleiro[i] != ' ')
        {
            if (
                    ((i == 0 || i == 1 || i == 2) && (tabuleiro[0] == tabuleiro[1] && tabuleiro[0] == tabuleiro[2])) ||
                    ((i == 0 || i == 3 || i == 6) && (tabuleiro[0] == tabuleiro[3] && tabuleiro[0] == tabuleiro[6])) ||
                    ((i == 0 || i == 4 || i == 8) && (tabuleiro[0] == tabuleiro[4] && tabuleiro[0] == tabuleiro[8])) ||
                    ((i == 1 || i == 4 || i == 7) && (tabuleiro[1] == tabuleiro[4] && tabuleiro[1] == tabuleiro[7])) ||
                    ((i == 2 || i == 4 || i == 6) && (tabuleiro[2] == tabuleiro[4] && tabuleiro[2] == tabuleiro[6])) ||
                    ((i == 2 || i == 5 || i == 8) && (tabuleiro[2] == tabuleiro[5] && tabuleiro[2] == tabuleiro[8])) ||
                    ((i == 3 || i == 4 || i == 5) && (tabuleiro[3] == tabuleiro[4] && tabuleiro[3] == tabuleiro[5])) ||
                    ((i == 6 || i == 7 || i == 8) && (tabuleiro[6] == tabuleiro[7] && tabuleiro[6] == tabuleiro[8]))
                )
            {
                tabuleiro_str[i] = "[";
                tabuleiro_str[i] += tabuleiro[i];
                tabuleiro_str[i] += "]";
            }
        }
    }
    printf("%s     |     |     \n", espacos);
    printf("%s %3s | %3s | %3s \n", espacos, tabuleiro_str[0].c_str(), tabuleiro_str[1].c_str(), tabuleiro_str[2].c_str());
    printf("%s_____|_____|_____\n", espacos);
    printf("%s     |     |     \n", espacos);
    printf("%s %3s | %3s | %3s \n", espacos, tabuleiro_str[3].c_str(), tabuleiro_str[4].c_str(), tabuleiro_str[5].c_str());
    printf("%s_____|_____|_____\n", espacos);
    printf("%s     |     |     \n", espacos);
    printf("%s %3s | %3s | %3s \n", espacos, tabuleiro_str[6].c_str(), tabuleiro_str[7].c_str(), tabuleiro_str[8].c_str());
    printf("%s     |     |     \n", espacos);
}
