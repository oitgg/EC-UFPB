#include "mensagem.h"

std::string gerar_mensagem(const int& tipo_mensagem, const std::string& valor, const bool& print_log)
{
    std::string mensagem = "";
    switch(tipo_mensagem)
    {
        // START <username>
        case START: mensagem += "START " + valor; break;
        case WELCOME: mensagem += "WELCOME " + valor; break;
        case FULL_ROOM: mensagem += "FULL_ROOM"; break;
        case READY: mensagem += "READY " + valor; break;
        case MOVE: mensagem += "MOVE " + valor; break;
        case VALID_MOVE: mensagem += "VALID_MOVE"; break;
        case OPPONENT_MOVED: mensagem += "OPPONENT_MOVED " + valor; break;
        case GAME_OVER: mensagem += "GAME_OVER " + valor; break;
        case CONTINUE: mensagem += "CONTINUE"; break;
    }
    if (print_log)
    {
        printf("Mensagem gerada: %s\n", mensagem.c_str());
    }
    return mensagem;
}

enum tipo get_tipo_mensagem(char *mensagem)
{
    char *_mensagem = static_cast<char*>(calloc((strlen(mensagem)), sizeof(char)));
    strcpy(_mensagem, mensagem);
    char *tag;
    tag = strtok(_mensagem, " ");
    if (strcmp(tag, "START") == 0)
    {
        return START;
    }
    if (strcmp(tag, "WELCOME") == 0)
    {
        return WELCOME;
    }
    if (strcmp(tag, "MOVE") == 0)
    {
        return MOVE;
    }
    if (strcmp(tag, "VALID_MOVE") == 0)
    {
        return VALID_MOVE;
    }
    if (strcmp(tag, "OPPONENT_MOVED") == 0)
    {
        return OPPONENT_MOVED;
    }
    if (strcmp(tag, "GAME_OVER") == 0)
    {
        return GAME_OVER;
    }
    if (strcmp(tag, "CONTINUE") == 0)
    {
        return CONTINUE;
    }
    return NONE;
}

char* get_valor(char *mensagem)
{
    char *_mensagem = static_cast<char*>(calloc((strlen(mensagem)), sizeof(char)));
    strcpy(_mensagem, mensagem);
    const char s[2] = " ";
    char *token;
    token = strtok(_mensagem, s);
    token = strtok(nullptr, s);
    return token;
}
