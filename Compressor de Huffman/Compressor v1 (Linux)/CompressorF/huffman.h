#include <sys/types.h>

// Comprime o arquivo
void compress();

// Descomprime o arquivo e retorna o original
void uncompress();

// Update
void nothing();

// Seta a função update no final de cada iteração
void set_update(void(*)());
