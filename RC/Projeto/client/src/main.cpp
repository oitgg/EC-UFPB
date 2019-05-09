#include "main.h"

int main(int argc, char *argv[])
{
    // Variáveis de rede
    int socket_local;
    struct sockaddr_in endereco_remoto;
    struct hostent * he = gethostbyname("localhost");
    char *buf;
    char *_buf;
    char *mensagem;
    long num_bytes;
    // Variáveis do jogo
    char tabuleiro[] = "         ";
    char* nome_jogador = nullptr;
    char* nome_oponente = nullptr;
    char peca = X;
    char peca_oponente = O;
    int minha_vez;
    int fim;
    char coordenada;
    char opc = ' ';
    buf = static_cast<char*>(calloc(MAXDATASIZE, sizeof(char)));
    _buf = static_cast<char*>(calloc (MAXDATASIZE, sizeof(char)));
    mensagem = static_cast<char*>(calloc(MAXDATASIZE, sizeof(char)));
    nome_jogador = static_cast<char*>(calloc(MAXNAMESIZE, sizeof(char)));
    nome_oponente = static_cast<char*>(calloc(MAXNAMESIZE, sizeof(char)));
    if (argc == 2)
    {
        if ((he=gethostbyname(argv[1])) == nullptr)
        {
            gethostbyname_error();
        }
    }
    if ((socket_local = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        socket_error();
    }
    endereco_remoto.sin_family = AF_INET;
    endereco_remoto.sin_port = htons(PORTA);
    endereco_remoto.sin_addr = *reinterpret_cast<struct in_addr*>(he->h_addr);
    memset(endereco_remoto.sin_zero, 0, 8);
    if (connect(socket_local, reinterpret_cast<sockaddr*>(&endereco_remoto), sizeof(struct sockaddr)) == -1)
    {
        connect_error();
    }
    do
    {
        zerar_tabuleiro(tabuleiro);
        minha_vez = 0;
        fim = 0;


        print_menu();
        scanf("%c", &opc);
        fflush(stdin);
        printf("\n");
        if (opc == '1')
        {
            print_setup();
            scanf(" %[^\n]", nome_jogador);
            fflush(stdin);

            // START
            if (send(socket_local, gerar_mensagem(START, nome_jogador, false).c_str(), MAXDATASIZE, 0) == -1)
            {
                send_error();
            }
            // Recebe WELCOME ou FULL_ROOM
            if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
            {
                recv_error();
            }
            buf[num_bytes] = '\0';
            if (get_tipo_mensagem(buf) == WELCOME)
            {
                strcpy(_buf, buf);
                peca = get_valor(_buf)[0];
                printf("\n Olá, %s! Você vai jogar com %c\n\n", nome_jogador, peca);
                printf(" Aguarde a entrada do outro jogador\n");
                if (peca == O)
                {
                    peca_oponente = X;
                }
            }
            else
            {
                printf("\n A sala está cheia, tente novamente mais tarde\n");
                exit(0);
            }
            // Aguarda o jogo estar pronto
            if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
            {
                recv_error();
            }
            buf[num_bytes] = '\0';
            printf("Mensagem >> %s\n", buf);
            printf("Valor >> %s\n", get_valor(buf));
            strcpy(nome_oponente, get_valor(buf));
            // X começa
            if (peca == X)
            {
                minha_vez = 1;
            }
            do
            {
                print_tela_jogo(tabuleiro, nome_jogador, peca, nome_oponente, peca_oponente);
                if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
                {
                    recv_error();
                }
                buf[num_bytes] = '\0';
                if (get_tipo_mensagem(buf) == GAME_OVER)
                {
                    if (strcmp(get_valor(buf), "WIN") == 0)
                    {
                        printf("Você venceu!\n");
                        break;
                    }
                    else if (strcmp(get_valor(buf), "LOSE") == 0)
                    {
                        printf("Você perdeu!\n");
                        break;
                    }
                    else if (strcmp(get_valor(buf), "TIE") == 0)
                    {
                        printf("Deu velha!\n");
                        break;
                    }
                }
                // Minha vez
                if (minha_vez)
                {
                    do
                    {
                        printf(" Digite a coordenada da sua jogada: ");
                        scanf(" %[^\n]", &coordenada);
                    }
                    while (!validar_jogada(tabuleiro, coordenada));
                    sprintf(mensagem, "MOVE %c", coordenada);
                    if (send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
                    {
                        send_error();
                    }
                    // Recebe o VALID_MOVE, inverte o minha_vez
                    if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
                    {
                        recv_error();
                    }
                    buf[num_bytes] = '\0';
                    strcpy(_buf, buf);
                    if (get_tipo_mensagem(buf) == VALID_MOVE)
                    {
                        tabuleiro[(coordenada-48)-1] = peca;
                        minha_vez = 0;
                    }
                }
                else
                {
                    printf(" Aguarde o outro jogador fazer sua jogada.\n");
                    if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
                    {
                        recv_error();
                    }
                    buf[num_bytes] = '\0';
                    strcpy(_buf, buf);
                    if (get_tipo_mensagem(_buf) == OPPONENT_MOVED)
                    {
                        coordenada = static_cast<char>(atoi(get_valor(buf)));
                        tabuleiro[coordenada-1] = peca_oponente;
                        minha_vez = 1;
                    }
                }
            }
            while (fim != 1);
            for (int i = 10; i >= 0; i--)
            {
                std::clog << "\rSaindo da partida em " << i << "s ";
                sleep(1);
            }
            std::clog << std::endl;
            opc = '3';
        }
        else if (opc == '2')
        {
            print_ajuda();
        }
    }
    while (opc != '3');
    close(socket_local);
    return 0;
}
