#include "tree.h"
#include "model.h"
#include "memory_buffer.h"
#include "file_buffer.h"
#include "arithmetic_compressor.h"
#include <iostream>
#include <chrono>
#include <string>

int main(int argc, char* argv[]){

	std::cerr << "\n";
	if( argc < 3 ){
		std::cerr << "Poucos argumentos...\n\n";
		return 0;
	}

	uint in_size, out_size;
	float RC;
	uchar k;
	uchar header[5] = {0xAB, 0x58, 0x44, 0x47, 0xBB};
	double entropy;
	std::chrono::high_resolution_clock::time_point start_time, end_time;

	std::string compress = std::string{argv[1]};
	std::string input_file_name = std::string{argv[2]};
	std::string output_file_name;

	if(compress == "-c"){

		// Checa a existência do nome do output
		output_file_name = input_file_name + ".ppm";
		if( std::ifstream{output_file_name} ){
			std::cerr << "Arquivo de saida ja existe.\n\n";
			exit(0);
		}

		// Pega o valor de 'k'
		if( argc < 4 ) k = 2;
		else k = std::stoi(std::string{argv[3]});

		uint tree_mode = 0;
		if( argc > 4 && std::string{argv[4]} == "-map") tree_mode = 1;
		else if( argc > 4 && std::string{argv[4]} == "-list") tree_mode = 2;

		// Inicializa os objetos
		FileSymbolBuffer input{input_file_name};
		FileBitBuffer output{output_file_name};
		ArithmeticCompressor comp{k, tree_mode};

		// Escreve as informações no cabeçalho
		in_size = input.size();
		for(uint i = 0; i < 5; i++)
			output.writeBlock(header[i]);
		output.writeBlock(k);
		output.writeBlock(in_size/8);

		// Comprime
		start_time = std::chrono::high_resolution_clock::now();
		comp.encode(input, output, entropy);
		end_time = std::chrono::high_resolution_clock::now();
		
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		out_size = output.size();
		RC = (float)in_size / out_size;

		// Printa as estatísticas de compressão
		std::cerr << std::setprecision(3);
		std::cerr << "\n\nTempo total: " << elapsed.count()/1000.0f << " s" << std::endl;
		std::cerr << "\nInfo do input:" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Tamanho: " << in_size/1024 << " kb" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Comprimento medio: " << 8.0f << " bits/simbolo" << std::endl;
		std::cerr << "\nInfo do output:" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Tamanho: " << out_size/1024 << " kb" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Comprimento medio: " << (float)out_size/(in_size/8) << " bits/simbolo" << std::endl;
		std::cerr << "\nInfo da codificacao:" << std::endl;
		std::cerr << std::setw(15) << std::left << "  Entropia: " << entropy << " bits/simbolo" << std::endl;
		std::cerr << std::setw(15) << std::left << "  RC: " << RC << " : 1" << std::endl;
	}
	else if(compress == "-d"){

		uint num_symbols;
		uchar header_check;

		// Checa o do nome do input
		uint s = input_file_name.size();
		if(s > 4 && input_file_name.substr( s-4 ) == ".ppm" )
			output_file_name = input_file_name.substr(0, s-4);
		else{
			std::cerr << "Formato de arquivo inválido. Por favor, insira um arquivo PPM.\n\n";
			exit(0);
		}
		
		// Checa o nome do output
		if( argc > 3 ) output_file_name = std::string{argv[3]};
		if( std::ifstream{output_file_name} ){
			std::cerr << "Arquivo de saida ja existe.\n\n";
			exit(0);
		}

		uint tree_mode = 0;
		if( argc > 4 && std::string{argv[4]} == "-map") tree_mode = 1;
		else if( argc > 4 && std::string{argv[4]} == "-list") tree_mode = 2;

		// Cria os objetos
		FileBitBuffer input{input_file_name};
		FileSymbolBuffer output{output_file_name};

		// Extrai a informação do cabeçalho
		for(uint i = 0; i < 5; i++){
			input.readBlock(header_check);
			if(header_check != header[i]){
				std::cerr << "Formato de arquivo inválido. Por favor, insira um arquivo PPM.\n\n";
				exit(0);
			}
		}
		input.readBlock(k);
		input.readBlock(num_symbols);

		ArithmeticCompressor comp{k, tree_mode};

		// Descomprime
		start_time = std::chrono::high_resolution_clock::now();
		comp.decode(input, output, num_symbols);
		end_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

		// Printa a informação da descompressão
		std::cerr << std::setprecision(3);
		std::cerr << "\n\nTempo total: " << elapsed.count()/1000.0f << " s" << std::endl;
	}
	std::cerr << "\n";

	return 0;
}