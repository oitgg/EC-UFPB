#ifndef ERROR_H
#define ERROR_H

#include <stdlib.h>
#include <stdio.h>

// Erro ao criar um socket
__attribute__((noreturn)) void socket_error();

// Erro ao solicitar uma conexão
__attribute__((noreturn)) void connect_error();

// Erro ao receber uma mensagem
__attribute__((noreturn)) void recv_error();

// Erro ao enviar uma mensagem
__attribute__((noreturn)) void send_error();

// Erro ao associar uma porta ao socket
__attribute__((noreturn)) void bind_error();

// Erro ao iniciar uma escuta
__attribute__((noreturn)) void listen_error();

// Erro no gethostbyname
__attribute__((noreturn)) void gethostbyname_error();

// Erro no reuse address
__attribute__((noreturn)) void reuse_address_error();

#endif // ERROR_H
