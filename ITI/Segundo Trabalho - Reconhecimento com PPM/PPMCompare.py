import pandas as pd
import copy
import matplotlib.pyplot as plt

class comparator:

    def __init__(self):
        
        #carrega os dataframes referentes as imagens concatenadas
        self.dataframe_concatenado = list()
        for i in range(1,41):
            self.dataframe_concatenado.append(pd.read_csv('Tabelas-csv/Tabela-'+str(i)+'.csv', encoding = 'ISO-8859-1'))
        
        #carrega os dataframes referentes as imagens de teste
        self.dataframe_teste = list()
        for i in range(1,41):
            self.dataframe_teste.append(pd.read_csv('Tabela-Teste-csv/TabelaTeste-'+str(i)+'.csv', encoding = 'utf-8'))
        
        #cria uma estrutura que armazena os tamanhos dos arquivos de contexto das concatenadas já divididos por 5, em formato json
        self.concatenadas = dict()
        for i in range(len(self.dataframe_concatenado)):
            self.concatenadas[i+1] = dict()
            for j in range(9):
                tam = self.dataframe_concatenado[i]['Tamanho saída ( )'][j]
                
                self.concatenadas[i+1][j] = tam/5
               
        #cria uma estrutura que armazena os tamanhos dos arquivos de contexto das de teste, em formato json
        self.testes = dict()
        for i in range(len(self.dataframe_teste)):
            self.testes[i+1] = dict()
            for j in range(9):
                self.testes[i+1][j] = self.dataframe_teste[i]['Tamanho saída ( )'][j]
                
    
    def cross(self):
        #cria um json de resultados copiando um já existente pois as keys são iguais
        self.cross_result = copy.deepcopy(self.concatenadas)

        
        #for que itera as pessoas
        for pessoa in self.concatenadas:

            #cria uma nova key para cada pessoa que irá armazenar o melhor contexto
            self.cross_result[pessoa]['best'] = dict()
            self.cross_result[pessoa]['best']['abs'] = 9999
            self.cross_result[pessoa]['best']['contexto'] = -1
            self.cross_result[pessoa]['best']['porcentagem'] = 0
            

            #for que itera entre os contextos
            for contexto in self.concatenadas[pessoa]:
                
                #tira o valor absoluto da diferença entre o contexto em questao da concatenada pela de teste
                abs_result = abs(self.concatenadas[pessoa][contexto] - self.testes[pessoa][contexto])
                self.cross_result[pessoa][contexto] = abs_result
                
                #se o contexto for melhor, atualiza o dicionário de resultado
                if(abs_result < self.cross_result[pessoa]['best']['abs']):
                    self.cross_result[pessoa]['best']['abs'] = abs_result
                    self.cross_result[pessoa]['best']['contexto'] = contexto
                    
                    #verifica qual dos tamanhos dos arquivos é maior para realizar o calculo da porcentagem de acurácia
                    if(self.testes[pessoa][contexto] > self.concatenadas[pessoa][contexto]):
                        self.cross_result[pessoa]['best']['porcentagem'] = (self.concatenadas[pessoa][contexto] * 100)/self.testes[pessoa][contexto]
                    else:
                        self.cross_result[pessoa]['best']['porcentagem'] = (self.testes[pessoa][contexto] * 100)/self.concatenadas[pessoa][contexto]
                        
    def generate_graph_accuracy_context(self):
        
        for pessoa in self.concatenadas:
            
            abs_list = list()
            percent_list = list()
            
            for contexto in self.concatenadas[pessoa]:
                
                abs_list.append(contexto)
                if(self.testes[pessoa][contexto] > self.concatenadas[pessoa][contexto]):
                    percent_list.append((self.concatenadas[pessoa][contexto] * 100)/self.testes[pessoa][contexto])
                else:
                    percent_list.append((self.testes[pessoa][contexto] * 100)/self.concatenadas[pessoa][contexto])
            
            fig = plt.figure()
            plt.plot(abs_list, percent_list)
            plt.suptitle('Pessoa ' + str(pessoa))
            plt.xlabel('CONTEXTO')
            plt.ylabel('ACURÁCIA (%)')
            plt.show()
            fig.savefig('pessoa' + str(pessoa) + '.png')
        
        
    def generate_graph_concat_time_context(self):
        
        for i in range(len(self.dataframe_concatenado)):
            time_list = list()
            context_list = list()
            
            for j in range(9):
                time_list.append(self.dataframe_concatenado[i]['Tempo total ()'][j])
                context_list.append(j)
            
            fig = plt.figure()
            plt.plot(context_list, time_list)
            plt.suptitle('Pessoa ' + str(i+1))
            plt.xlabel('CONTEXTO')
            plt.ylabel('TEMPO (S)')
            plt.show()
            fig.savefig('pessoa' + str(i+1) + '.png')
    
    def generate_graph_test_time_context(self):
        
        for i in range(len(self.dataframe_teste)):
            time_list = list()
            context_list = list()
            
            for j in range(9):
                time_list.append(self.dataframe_teste[i]['Tempo total ()'][j]/1000)
                context_list.append(j)
            
            fig = plt.figure()
            plt.plot(context_list, time_list)
            plt.suptitle('Pessoa ' + str(i+1))
            plt.xlabel('CONTEXTO')
            plt.ylabel('TEMPO (S)')
            plt.show()
            fig.savefig('pessoa' + str(i+1) + '.png')