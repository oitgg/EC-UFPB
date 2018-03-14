#include <sys/types.h>

// Seta o arquivo para ser aberto
void set_input(char*);

// Retorna o nome do arquivo de entrada
char* get_input();

// Retorna o tamanho (em bytes) do arquivo de entrada
off_t get_input_size();

// Retorna a progressão do cabeçalho (em bytes) do arquivo de entrada
off_t get_input_current();

// Cria o leitor antes de ler
int create_reader();

// Deleta o leitor depois de ler
int delete_reader();

// Retorna o próximo byte lido do arquivo
int read_byte();

// Retorna o próximo bit lido do arquivo
int read_bit();


// Seta o arquivo para ser aberto
void set_output(char*);

// Retorna o nome do arquivo de saída
char* get_output();

// Retorna a progressão do cabeçalho (em bytes) do arquivo de saída
off_t get_output_current();

// Cria o escritor antes de escrever
int create_writer();

// Cria o escritor deopis de escrever
int delete_writer();

// Adiciona o byte ao arquivo
int write_byte(int);

// Adiciona o bit ao arquivo
int write_bit(int);
