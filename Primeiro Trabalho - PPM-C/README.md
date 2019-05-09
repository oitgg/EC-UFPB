# PPM-C

Compressor aritmiético que usa o PPM (Prediction by Partial Matching) como método
para adquirir as probabilidades dos símbolos dado um contexto k.

## Buildando o projeto

Para builtar o projeto, digite no terminal:

`$ make`

Para comprimir algum arquivo, digite:

`$ ./compressor -c arquivo_de_entrada k tree_mode`

O primeiro parâmetro "arquivo_de_entrada" é autoexplicatório. 
"k" define o número máximo do contexto a ser usado no processo de compressão e é opcional (default = 2).
A saída gerada terá o mesmo nome do arquivo de entrada mais a extensão ".ppm".
"tree_mode" indica como a árvore interna será criada. Ela pode ter dois valores: -list, pra forçar a utilização
de listas, ou -map, pra forçar a utilização de maps. Na ausência do parâmetro, a escolha (automática) dependerá do valor de k.

Para descomprimir, digite:

`$ ./compressor -d arquivo_de_entrada arquivo_de_saída`

Os dois parâmetros são autoexplicatórios. O primeiro deve terminar com ".ppm". O segundo é opcional,
por default será o nome do arquivo de entrada menos a extensão ".ppm".
