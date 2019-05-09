input [31:0] x_original, y_original; // Números a serem somados
output [31:0] soma;					 // Resultado da soma

reg somasinal;						 // Bit de sinal do valor 
reg [7:0] somaexpoente; 			 // Expoente do valor
reg [25:0] somamantissa;			 //	Mantissa do valor
assign soma[31:0] = somasinal;		 // Atribui o registrador para o resultado
assign soma[30:23] = somaexpoente;	 // Atribui o registrador para o resultado
assign soma[22:0] = somamantissa;	 // Atribui o registrador para o resultado
	
reg [31:0] x, y;					 // Variáveis de entrada
reg [25:0] xmantissa, ymantissa;	 // Variáveis para as mantissas das entradas
reg [7:0]  xexpoente, yexpoente;	 // Variáveis para os expoentes das entradas
reg xsinal, ysinal;	 				 // Bits de sinal das variáveis de entrada
reg [7:0] diferenca;				 // Diferença entre os expoentes das variáveis de entrada


//A comparação entre os valores de entrada é feito para armazenar os valores nas variáveis.
//Maior valor => Variável x.
//Menor Valor => Variável y.

if (x_original[30:23] < y_original[30:23]) begin
	
	x = y_original;
	y = x_original;

	end
	else
	begin
		
	x = x_original;
	y = y_original;
	end


//Atribui-se o bit de sinal correspondente às variáveis de entrada.

xsinal = x[31];
ysinal = y[31];


//Atribui-se os bits de expoente às variáveis de entrada.

xexpoente = x[30:23];
yexpoente = y[30:23];


//O 0 é atribuído nas posições 24 e 25 para auxiliar no sinal.
//Caso expoente = 0, o 0 vai pra posição 23, caso contrário, ele é atribuído.
//Após isso adiciona-se os bits referentes à mantissa.

xmantissa = (2'b0, xexpoente ? 1'b1 : 1'b0, x[22:0]); 
ymantissa = (2'b0, yexpoente ? 1'b1 : 1'b0, y[22:0]); 


//Normaliza-se o expoente. (Biased)

diferenca = xexpoente - yexpoente;
ymantissa = ymantissa >> diferenca;


//Verifica a soma de x e y.

somasinal = somamantissa[25];

if (somasinal) somamantissa = -somamantissa


//Normaliza a soma

if (somamantissa[24]) begin

// Se a soma ultrapassar a quantidade de bits, acrescenta-se '1' no expoente e desloca-se um bit para a direita.

somaexpoente = xexpoente + 1;
somamantissa >> 1;

end
else
if (somamantissa) begin

// Se a soma for diferente de zero, analisa-se os casos a seguir:

integer posicao, aux, i;

// Encontra o primeiro bit significativo.

pos = 0;
for (i = 23; i >= 0; i = i - 1)
if (!posicao && somamantissa[i]) posicao = i;
aux = 23 - posicao;

if ( xexpoente < aux) begin
	
	// Caso o expoente seja pequeno demais
	somaexpoente = 0;
	somamantissa = 0;
	somasinal 	 = 0;

end
else
begin
	
	// Normaliza a soma
	somaexpoente = xexpoente - aux;
	somamantissa = somamantissa << aux;

end

// A soma é 0

somaexpoente = 0;
somamantissa = 0;





