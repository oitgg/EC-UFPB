#include "main.h"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    int socket_listener;
    int socket_local;
    struct sockaddr_in endereco_local;
    struct sockaddr_in endereco_remoto;
    socklen_t tamanho = sizeof(struct sockaddr_in);
    char *buf;
    char *_buf;
    char *mensagem;
    ssize_t num_bytes;
    char tabuleiro[10];
    char peca = X;
    char peca_oponente = O;
    int my_turn = 0;
    char* nome_jogador;
    char* nome_oponente;
    buf = static_cast<char*>(calloc (MAXDATASIZE, sizeof(char)));
    _buf = static_cast<char*>(calloc (MAXDATASIZE, sizeof(char)));
    mensagem = static_cast<char*>(calloc (MAXDATASIZE, sizeof(char)));
    nome_jogador = static_cast<char*>(calloc (MAXNAMESIZE, sizeof(char)));
    nome_oponente = static_cast<char*>(calloc (MAXNAMESIZE, sizeof(char)));
    system("clear");
    printf("Servidor iniciado\n");
    // Inicia o socket
    socket_listener = socket(AF_INET, SOCK_STREAM, 0);
    int enable = 1;
    if (setsockopt(socket_listener, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        reuse_address_error();
    }
    // Configura o endereco_local
    endereco_local.sin_family = AF_INET;
    endereco_local.sin_port = htons(PORTA);
    endereco_local.sin_addr.s_addr = INADDR_ANY; // Automático
    memset(endereco_local.sin_zero,0,8);
    // bind
    if (bind(socket_listener, reinterpret_cast<sockaddr*>(&endereco_local), sizeof(struct sockaddr)) == -1)
    {
        bind_error();
    }
    // listen
    if (listen(socket_listener, BACKLOG) < 0)
    {
        listen_error();
    }
    while(1)
    {
        // accept
        socket_local = accept(socket_listener, reinterpret_cast<sockaddr*>(&endereco_remoto), &tamanho);
        if (socket_local < 0)
        {
            perror("accept");
            //caso a conexão não seja aceita (dispara erro), o programa volta ao inicio da repetição
            continue;
        }
        // para verificação
        printf("Conectado a %s\n", inet_ntoa(endereco_remoto.sin_addr));
        if (!fork())
        {
            iniciar_jogadores();
            iniciar_tabuleiro();
            zerar_tabuleiro(tabuleiro);
            if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
            {
                recv_error();
            }
            buf[num_bytes] = '\0';
            printf("Mensagem recebida: %s\n", buf);
            strcpy(_buf, buf);
            strcpy(nome_jogador, get_valor(_buf));
            if (inserir_jogador(nome_jogador) == 0)
            {
                if (get_num_jogadores() == 1)
                {
                    peca = X;
                    peca_oponente = O;
                    my_turn = 1;
                    strcpy(mensagem, gerar_mensagem(WELCOME, XX, true).c_str());
                }
                else if (get_num_jogadores() == 2)
                {
                    peca = O;
                    peca_oponente = X;
                    strcpy(mensagem, gerar_mensagem(WELCOME, OO, true).c_str());
                }
            }
            else
            {
                strcpy(mensagem, "FULL_ROOM");
            }
            printf("%s entrou\n", nome_jogador);
            if (send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
            {
                send_error();
            }
            // Aqui ele avisa aos clientes que está pronto para o jogo
            do
            {
                usleep(100000);
            }
            while (get_num_jogadores() != 2);
            get_nome_oponente(nome_jogador, nome_oponente);
            printf("Oponente do %s é o %s\n", nome_jogador, nome_oponente);
            if (send(socket_local, gerar_mensagem(READY, nome_oponente, true).c_str(), MAXDATASIZE, 0) == -1)
            {
                send_error();
            }
            printf("Mandei a mensagem de READY para %s\n", nome_jogador);
            // lógica do jogo...
            do
            {
                // Após cada movimento, checar o status
                if (verificar_fim(tabuleiro, peca, peca_oponente) == 0)
                {
                    if (send(socket_local, "CONTINUE", MAXDATASIZE, 0) == -1)
                    {
                        send_error();
                    }
                    printf("CONTINUE\n");
                }
                else if (verificar_fim(tabuleiro, peca, peca_oponente) == 1)
                {
                    if (send(socket_local, gerar_mensagem(GAME_OVER, "TIE", true).c_str(), MAXDATASIZE, 0) == -1)
                    {
                        send_error();
                    }
                    printf("EMPATE\n");
                    break;
                }
                else if (verificar_fim(tabuleiro, peca, peca_oponente) == 2)
                {
                    if (send(socket_local, gerar_mensagem(GAME_OVER, "WIN", true).c_str(), MAXDATASIZE, 0) == -1)
                    {
                        send_error();
                    }
                    printf("VITORIA\n");
                    break;
                }
                else if (verificar_fim(tabuleiro, peca, peca_oponente) == 3)
                {
                    if (send(socket_local, gerar_mensagem(GAME_OVER, "LOSE", true).c_str(), MAXDATASIZE, 0) == -1)
                    {
                        send_error();
                    }
                    printf("DERROTA\n");
                    break;
                }
                // Vez do jogador
                if (my_turn)
                {
                    // Recupero a mensagem
                    if ((num_bytes = recv(socket_local, buf, MAXDATASIZE, 0)) == -1)
                    {
                        recv_error();
                    }
                    buf[num_bytes] = '\0';
                    printf("Mensagem recebida: %s\n", buf);
                    int coordenada = atoi(get_valor(buf));
                    jogada(coordenada);
                    tabuleiro[coordenada-1] = peca;
                    if (send(socket_local, gerar_mensagem(VALID_MOVE, "", true).c_str(), MAXDATASIZE, 0) == -1)
                    {
                        send_error();
                    }
                    my_turn = 0;
                }
                else
                {
                    // Aqui ele lê o arquivo, esperando uma atualização
                    int posicao_anterior = get_posicao();
                    int posicao_atual = get_posicao();
                    do
                    {
                        posicao_atual = get_posicao();
                        usleep(1000);
                    }
                    while (posicao_anterior == posicao_atual || posicao_atual == -1);
                    tabuleiro[posicao_atual-1] = peca_oponente;
                    sprintf(mensagem, "OPPONENT_MOVED %d", posicao_atual);
                    if (send(socket_local, mensagem, MAXDATASIZE, 0) == -1)
                    {
                        send_error();
                    }
                    printf("Mensagem enviada: %s\n", mensagem);
                    my_turn = 1;
                }
            }
            while(1);
        }
    }
}
