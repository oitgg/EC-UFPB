;=========================================================================
;=    PROJETO FINAL - ARQUITETURA DE COMPUTADORES                        =
;=    ALUNO: THIAGO GONZAGA GOMES (11504760)                             =
;=========================================================================





PILHA SEGMENT STACK     ;SEGMENTO PILHA
        DB 128 DUP(?)   ;TAMANHO DA PILHA USADA PELO PROGRAMA
PILHA ENDS              ;ENCERRA SEGMENTO PILHA


VARIAVEIS SEGMENT       ;SEGMENTO DE DECLARACAO DE VARIAVEIS
    MENS_ENTRADA DB 'DIGITE UMA NOTA (COM 3 DIGITOS): #' 
    MENS_ERRO DB 'DIGITE ALGO VALIDO!#'
    MENS_APROVADO DB 'APROVADO. MEDIA = #'
    MENS_REPROVADO DB 'REPROVADO. MEDIA = #'
    MENS_FINAL DB 'FINAL. MEDIA = #'
    MENS_FINAL2 DB 'PRECISA TIRAR = #'
    NOTA1 DB 1 DUP(?)     ;DECLARA NOTA 1 COM 1 BYTE NAO INICIALIZADO
    NOTA2 DB 1 DUP(?)     ;DECLARA NOTA 2 COM 1 BYTE NAO INICIALIZADO
    NOTA3 DB 1 DUP(?)     ;DECLARA NOTA 3 COM 1 BYTE NAO INICIALIZADO
    NOTAFINAL DB 1 DUP(?)     ;DECLARA NOTAFINAL COM 1 BYTE NAO INICIALIZADO
    VALOR1 DB 3 DUP(?)        ;DECLARA VALOR1 COM 3 BYTES
    VALOR2 DB 3 DUP(?)        ;DECLARA VALOR2 COM 3 BYTES
    VALOR3 DB 3 DUP(?)        ;DECLARA VALOR3 COM 3 BYTES
    ASCII DB 3 DUP(?)         ;DECLARA ASCII COM 3 BYTES PRA SALVAR A NOTA EM DECIMAL
    MEDIA DB 1 DUP(?)         ;DECLARA MEDIA COM 1 BYTE


VARIAVEIS ENDS          ;ENCERRA SEGMENTO DE DECLARACAO DE VARIAVEIS    


PROGRAMA SEGMENT
    ASSUME SS:PILHA, CS: PROGRAMA, DS: VARIAVEIS, ES:VARIAVEIS
    
CALCULO PROC FAR
    PUSH DS
    XOR AX, AX
    PUSH AX
    MOV AX, VARIAVEIS
    MOV DS, AX
    MOV ES, AX    ;DS E ES = SEGMENTOS DE DADOS
    CALL LIMPA
    MOV DX, 0  
    CALL POS
    MOV CH, 0D
    LEA SI, VALOR1    
    
    
    
GNOTA:
    LEA BX, MENS_ENTRADA    ;BX RECEBE ENDERECO DE MENS_ENTRADA  
    MOV CL, 3D  ;ARMAZENA 3 EM CL (CONTADOR PARA O VETOR)
    
    


;==========================================
;EXIBE A MENS_ENTRADA PARA O USUARIO      =
;==========================================    
BOLA2:
    MOV AL, [BX]    ;ARMAZENA O VALOR DA POSICAO APONTADA POR BX EM AL
    CMP AL,'#'  ;COMPARA PRA VER SE AL=#
    JZ BOLA1    ;SE A COMPARACAO FOR VERDADEIRA VAI PRA BOLA1
    CALL VIDEO  ;EXIBE A MENS_ENTRADA CARACTERE POR CARACTERE
    INC BX  ;INCREMENTA BX
    JMP BOLA2   ;VAI PRA BOLA 2 (RECURSAO)



;==========================================
;BOLA1 VERIFICA SE O VALOR EH VALIDO      =
;==========================================
BOLA1:
    CALL TECLADO    ;CHAMA ROTINA DO TECLADO
    CMP AL, 31H     ;VERIFICA SE AL=1
    JZ NOTA10       ;SE AL=1, VAI PRA NOTA10
    JG BOLA3        ;SE AL>1, VAI PRA BOLA3
    CMP AL, 30H     ;VERIFICA SE AL=0
    JZ MENOR10      ;SE AL=0, VAI PRA MENOR10
    JL BOLA3        ;SE AL<0, VAI PRA BOLA3
    
    
    
    
;===============================================
;NOTA10 DEFINE NOTA COMO 100 QUANDO SE DIGITA 1=
;===============================================
NOTA10:
    CALL VIDEO  ;EXIBE CARACTERE INSERIDO
    MOV [SI], AL    ;ARMAZENA VALOR DE AL NA POSICAO DE SI
    INC SI  ;INCREMENTA SI
    DEC CL  ;DECREMENTA CL
    MOV AL, 30H ;ARMAZENA 0 EM AL
    CMP CL, 0D  ;VERIFICA SE CL=0
    JZ PROXIMANOTA  ;SE A COMPARACAO FOR VERDADEIRA VAI PRA PROXIMANOTA
    JNZ NOTA10  ;SE NAO FOI VERDADEIRA VAI PRA NOTA10 (RECURSAO)
    
    
    
;===============================================================
;MENOR10 COLOCA 0 NO PRIMEIRO ESPACO DO ARRAY E VAI PARA RESDIG=
;===============================================================
MENOR10:
    CALL VIDEO  ;EXIBE CARACTERE INSERIDO
    MOV [SI], AL    ;ARMAZENA AL EM SI
    INC SI      ;INCREMENTA SI
    DEC CL      ;DECREMENTA CL
    CMP CL, 0D    ;VERIFICA CL=0
    JZ PROXIMANOTA     ;SE SIM, VAI PRA PROXIMANOTA
    
    
    
;==============================================
;RESDIG RECEBE OS ULTIMOS DOIS DIGITOS DA NOTA=
;==============================================
RESDIG:
    CALL TECLADO    ;ROTINA DO TECLADO
    CMP AL, 30H     ;VERIFICA SE AL=0
    JL BOLA3        ;SE AL<0, VAI PRA BOLA3
    CMP AL, 39H     ;VERIFICA SE AL=9
    JG BOLA3        ;SE AL>9, VAI PRA BOLA3
    JMP MENOR10     ;VAI PRA MENOR10       
    
    
    
;==========================================
;BOLA3 = MENSAGEM DE ERRO                 =
;==========================================
BOLA3:
    LEA DI, MENS_ERRO   ;RECEBE ENDERECO DE MENS2
    MOV AL, 0DH
    CALL VIDEO      ;EXIBE O QUE TEM EM AL
    MOV AL, 0AH
    CALL VIDEO      ;EXIBE O QUE TEM EM AL
    
    
    
BOLA4:
    MOV AL, [DI]    ;ARMAZENA O VALOR QUE DI APONTA EM AL
    CMP AL, '#'     ;VERIFICA SE AL = #
    JZ BOLA5        ;SE COMPARACAO FOR VERDADEIRA, VAI PRA BOLA5
    CALL VIDEO      ;EXIBE O QUE TEM EM AL
    INC DI          ;INCREMENTA DI
    JMP BOLA4       ;RECURSAO
    
    
    
BOLA5: 
    MOV AL, 0DH
    CALL VIDEO  ;EXIBE O QUE TEM EM AL
    MOV AL, 0AH
    CALL VIDEO  ;EXIBE O QUE TME EM AL
    JMP BOLA1   ;VAI PRA BOLA1
    
    
    
;====================================================
;PROXIMANOTA VERIFICA A NOTA QUE ESTA SENDO INSERIDA=
;====================================================
PROXIMANOTA:
    INC CH      ;INCREMENTA CH
    CMP CH, 1D  ;VERIFICA SE CH=1
    JZ PROXIMANOTA1     ;SE COMPARACAO FOR VERDADEIRA, VAI PRA PROXIMANOTA1
    CMP CH, 2D  ;VERIFICA SE CH=2
    JZ PROXIMANOTA2     ;SE COMPARACAO FOR VERDADEIRA, VAI PRA PROXIMANOTA2
    CMP CH, 3D      ;VERIFICA SE CH=3
    JZ PROXIMANOTA3     ;SE COMPARACAO FOR VERDADEIRA, VAI PRA PROXIMANOTA3
    
    
    
    
;==========================================
;PROXIMANOTA1 CONVERTE E ARMAZENA A 1 NOTA=
;==========================================
PROXIMANOTA1:
    LEA SI, VALOR1  ;SI APONTA PARA 1 POSICAO DE VALOR1
    LEA DI, NOTA1   ;DI APONTA PARA NOTA 1
    CALL CONVERTER  ;CONVERTE NOTA EM BINARIO
    MOV [DI], CL    ;ARMAZENA NOTA CONVERTIDA
    LEA SI, VALOR2  ;FAZ SI APONTAR PRA VALOR2
    CALL LINHA      ;REPOSICIONA O CURSOR
    JMP GNOTA   ;VAI PRA GNOTA
    
    
    
;==========================================
;PROXIMANOTA2 CONVERTE E ARMAZENA A 2 NOTA=
;==========================================
PROXIMANOTA2:
		LEA SI, VALOR2	;SI APONTA PRA 1 POSICAO DE VALOR2
		LEA DI, NOTA2	;DI APONTA PRA NOTA 2
		CALL CONVERTER	;CONVERTE EM BINARIO
		MOV [DI], CL	;ARMAZENA A NOTA CONVERTIDA	
		LEA SI, VALOR3	;FAZ SI APONTAR PRA VALOR3
		CALL LINHA		;CURSOR NA PROXIMA LINHA
		JMP GNOTA		;VAI PRA GNOTA



;==========================================
;PROXIMANOTA3 CONVERTE E ARMAZENA A 3 NOTA=
;==========================================
PROXIMANOTA3:
        LEA SI, VALOR3  ;SO APONTA PRA 1 POSICAO DE VALOR 3
        LEA DI, NOTA3   ;DI APONTA PRA NOTA3
        CALL CONVERTER  ;CONVERTE EM BINARIO
        MOV [DI], CL    ;ARMZENA NOTA EM BINARIO
        CALL LINHA
        
        
        
;============================================
;CALCULAMEDIA CALCULA E ARMAZENA O RESULTADO=
;============================================
CALCULAMEDIA:
        XOR AX, AX
        XOR BX, BX      ;LIMPA VARIAVEIS
        LEA DI, MEDIA   ;DI APONTA PRA MEDIA
        
        LEA SI, NOTA1
        MOV BL, [SI]
        ADD AX, BX
        
        LEA SI, NOTA2
        MOV BL, [SI]
        ADD AX, BX
        
        LEA SI, NOTA3
        MOV BL, [SI]
        ADD AX, BX 
        
        MOV BL, 3D
        DIV BL
        MOV [DI], AL    ;DI APONTA PRA AL
        
        
;==========================================
;AVALIACAO                                =
;==========================================
AVALIACAO:
    CMP MEDIA, 70D  ;DE MEDIA=70
    JAE APROVADO
    CMP MEDIA, 40D  ;DE MEDIA=40
    JL REPROVADO    ;SE <40
    JMP FINAL       ;>40 VAI PRA FINAL  
    
    
  
;==========================================
;APROVADO                                 =
;==========================================
APROVADO:
    LEA BX, MENS_APROVADO    ;RECEBE ENDERECO DE MENSAGEM DE APROVADO
    CALL EXIBE
    LEA SI, ASCII
    LEA DI, MEDIA
    CALL CONVD
    JMP FIM
    
    
    
;==========================================
;REPROVADO                                =
;==========================================
REPROVADO:
    LEA BX, MENS_REPROVADO
    CALL EXIBE
    LEA SI, ASCII
    LEA DI, MEDIA
    CALL CONVD
    JMP FIM
    
    
    
;==========================================
;FINAL                                    =
;==========================================
FINAL: 
    XOR AX, AX
    XOR CX, CX
    LEA SI, ASCII
    LEA DI, MEDIA
    MOV AL, [DI]
    MOV BL, 6D  ;ARMAZENA 6 PARA MULTIPLICAR
    MUL BL      ;MULTIPLICA AL POR BL
    MOV CX, AX
    MOV AX, 500D    ;ARMAZENA 500 EM AX
    SUB AX, CX
    MOV BL, 4D      ;ARMAZENA 4 EM BL
    DIV BL      ;DIVIDE AL POR BL
    LEA DI, NOTAFINAL      
    MOV [DI], AL
    LEA BX, MENS_FINAL
    CALL EXIBE    
    LEA DI, MEDIA
    CALL CONVD
    LEA BX, MENS_FINAL2
    CALL EXIBE
    LEA DI, NOTAFINAL
    CALL CONVD  
    
    
    
FIM: RET
CALCULO ENDP     


;===============================================
;EXIBE = USADA NO PROGRAMA PRINCIPAL (FAR)=
;===============================================
EXIBE PROC NEAR
MENS:
    MOV AL, [BX]
    CMP AL,'#'
    JZ FIN
    CALL VIDEO  ;EXIBE A MENSAGEM POR CARACTERE
    INC BX
    JMP MENS
FIN: RET
EXIBE ENDP   


;======================================================
;CONVERTER = CONVERTE O VALOR DE ENTRADA PARA BINARIO =
;======================================================
CONVERTER PROC NEAR
    PUSH SI
    PUSH AX
    MOV AL, [SI]  ;AL APONTA PRA SI
    SUB AL, 30H   ;SUBTRAI 30H DE AL
    MOV BL, 100D  ;ARMAZENA 100 EM BL
    MUL BL        ;MULTIPLICA AL POR BL
    MOV CL, AL    ;ARMAZENA AL EM CL
    INC SI        ;INCREMENTA SI
    MOV AL, [SI]  ;ARMAZENA O VALOR DE SI EM AL
    SUB AL, 30H   ;SUBTRAI 30H DE AL
    MOV BL, 10D   ;ARMAZENA 10 EM BL
    MUL BL        ;MULTIPLICA AL POR BL
    ADD CL, AL    ;ADICIONA AL EM CL
    INC SI        ;INCREMENTA SI
    MOV AL, [SI]  ;ARMAZENA SI EM AL
    SUB AL, 30H   ;SUBTRAI 30H DE AL
    ADD CL, AL    ;ADICIONA O VALOR DE AL EM CL
    POP AX
    POP SI
    RET
CONVERTER ENDP



;LEA SI, ASCII
;LEA DI, MEDIA
;CHAMAR TODA VEZ QUE CONVD FOR CHAMADA
;=========================================
;CONVD CONVERTE E EXIBE EM HEXADECIMAL   =
;=========================================
CONVD PROC NEAR
    PUSH AX
    PUSH BX
    PUSH CX
    XOR AX, AX
    MOV AL, [DI]
    MOV BL, 10D
    MOV CL, 30H
    DIV BL
    ADD AH, CL
    MOV [SI], AH
    MOV AH, 0D
    INC SI
    DIV BL
    ADD AH, CL
    MOV [SI], AH
    MOV AH, 0D
    INC SI
    ADD AL, CL
    MOV [SI], AL
    MOV AL, [SI]  
    CALL VIDEO
    DEC SI
    MOV AL, [SI]
    CALL VIDEO
    DEC SI
    MOV AL, [SI]
    CALL VIDEO
    POP CX
    POP BX
    RET
CONVD ENDP


;================================
;VIDEO = EXIBE TUDO             =
;================================
VIDEO PROC NEAR
    PUSH SI
    PUSH BX
    PUSH DI
    PUSH CX
    MOV BX, 0
    MOV AH, 14
    INT 10H
    POP CX
    POP DI
    POP BX
    POP SI
    RET
VIDEO ENDP



;=================================
;POS = POSICIONA CURSOR          =
;=================================
POS PROC NEAR
    PUSH AX
    PUSH BX
    PUSH CX
    XOR BX, BX
    MOV AH, 2
    INT 10H
    POP CX
    POP BX
    POP AX
    RET
POS ENDP




;=================================
;LINHA=PULA LINHA                =
;=================================
LINHA PROC NEAR
    PUSH SI
    PUSH BX
    PUSH DI
    PUSH CX
    MOV AL, 0DH
    MOV BX, 0
    MOV AH, 14
    INT 10H
    MOV AL, 0AH
    MOV BX, 0
    MOV AH, 14
    INT 10H
    POP CX
    POP DI
    POP BX
    POP SI
    RET
LINHA ENDP



;=============================
;TECLADO = ROTINA DO TECLADO =
;=============================
TECLADO PROC NEAR
       PUSH DI
       PUSH BX
       PUSH SI
       PUSH CX
       MOV AH, 0
       INT 16H
       POP CX
       POP SI
       POP BX
       POP DI
       RET
TECLADO ENDP




;==============================
;LIMPA = LIMPA A TELA         =
;==============================
LIMPA PROC NEAR
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    XOR AL, AL
    XOR CX, CX
    MOV DH, 24
    MOV DL, 79
    MOV BH, 07H
    MOV AH, 06
    INT 10H
    POP DX
    POP CX
    POP BX
    POP AX
    RET
LIMPA ENDP
PROGRAMA ENDS
    END CALCULO


