#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include "io.h"

static FILE* input;
static int input_buffer;
static int input_buffer_size;
static char* input_filename = "input.file";
static off_t input_size;
static off_t input_current;

static FILE* output;
static int output_buffer;
static int output_buffer_size;
static char* output_filename = "output.file";
static off_t output_current;

void set_input(char* name) {
	input_filename = name;
}

char* get_input() {
	return input_filename;
}

off_t get_input_size() {
	return input_size;
}

off_t get_input_current() {
	return input_current;
}


int create_reader() {
	// Abre o arquivo
	input = fopen(input_filename, "r");
	input_buffer = 0;
	input_buffer_size = 0;

	// Checa se existem erros
	if (input == NULL) {
		return 1; // Erro enquanto abrindo o arquivo
	}

	// Pega o tamanho
	struct stat st;

    if (stat(input_filename, &st) == 0) {
		input_size = st.st_size;
		input_current = 0; // Zero bytes lidos
	} else {
		return 2; // Erro enquanto lendo o tamanho
	}
	return 0; // Arquivo abertp
}

int delete_reader() {
	// Fecha o arquivo
	int error = fclose(input);
	if (error == EOF) {
		return 1; // Erro
	}
	return 0; // Sucesso
}

int read_byte() {
	int byte = 0;

	// Adiciona o byte para a fila
	byte = fgetc(input);
	input_buffer = input_buffer << 8;
	input_buffer = input_buffer | byte;

	++input_current; // Mais um byte lido

	// Consume um byte
	byte = input_buffer >> input_buffer_size;

	// Mantém apenas o último bit não usado
	input_buffer = input_buffer & ((1 << input_buffer_size) - 1);

	// Retorna o byte
	return byte;
}

int read_bit() {
	// Guarda o bit
	int bit;

	if (input_buffer_size == 0) {
		// Adiciona o próximo byte ao buffer
		input_buffer = fgetc(input);

		if (input_buffer == EOF) {
			return EOF; // Final do arquivo alcanlçado
		}

		++input_current; // Mais um byte lido

		// 8 bits no buffer
		input_buffer_size = 8;
	}

	// Consume um bit do buffer
	--input_buffer_size;
	bit = (input_buffer & (1 << input_buffer_size)) >> input_buffer_size;
	input_buffer = input_buffer & ((1 << input_buffer_size) - 1);

	return bit;
}

void set_output(char* name) {
	output_filename = name;
}

char* get_output() {
	return output_filename;
}

off_t get_output_current() {
	return output_current;
}

int create_writer() {
	// Abre o arquivo
	output = fopen(output_filename, "w");
	output_buffer = 0;
	output_buffer_size = 0;
	output_current = 0; // Zero bytes escritos

	if (output == NULL) {
		return 1; // Erro enquanto abrindo o arquivo
	}
	return 0; // Arquivo está aberto
}

int delete_writer() {
	// Joga os bits restantes no buffer
	if (output_buffer_size > 0) {
		write_byte(0);
	}

	// Fecha o arquivo
	int error = fclose(output);
	if (error == EOF) {
		return 1; // Erro
	}
	return 0; // Sucesso
}

int write_byte(int byte) {
	int character;

	// Adiciona byte ao buffer
	output_buffer = (output_buffer << 8) | byte;

	// Pega o primeiro byte do buffer
	character = output_buffer >> output_buffer_size;

	// Mantém os bits inutilizados
	output_buffer = output_buffer & ((1 << output_buffer_size) - 1);

	// Adiciona os bytes ao arquivo
	int code = fputc(character, output);

	if (code == EOF) {
		return 1; // Erro enquanto escrevendo
	}
	++output_current; // Mais 1 byte escrito
	return 0; // Sucesso
}

int write_bit(int bit) {
	// Adiciona um bit ao buffer
	++output_buffer_size;
	output_buffer = (output_buffer << 1) | bit;

	// O buffer está cheio
	if (output_buffer_size == 8) {
		int code = fputc(output_buffer, output);

		if (code == EOF) {
			return 1; // Erro enquanto escrevendo
		}

		++output_current; // Mais 1 byte escrito

		// Reseta o buffer
		output_buffer = 0;
		output_buffer_size = 0;
	}
	return 0; // Sucesso
}
