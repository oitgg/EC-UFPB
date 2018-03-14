/****
*
* Aluno: Thiago Gonzaga Gomes
* Matricula: 11504760
*
* Data de Criação:  23/03/2016
* Última alteração: 25/03/2016
*
* Descrição Geral:  1ª Questão da Lista de Exercícios de LP1
*
****/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>

#define BASE_DECIMAL 10

using namespace std;

class Data
{
   int dia,mes,ano;
   Data& setDia(int dia);
   Data& setMes(int mes);
   Data& setAno(int ano);
   int getDia();
   int getMes();
   int getAno();
public:
   static bool ValidaData(int dia, int mes, int ano);
   Data(int dia = 0, int mes = 0, int ano= 0);
   Data& setData(int dia,int mes, int ano);
   string getData();
};

Data& Data::setDia(int dia)
{
   this->dia = dia;
   return *this;
}

Data& Data::setMes(int mes)
{
   this->mes = mes;
   return *this;
}

Data& Data::setAno(int ano)
{
   this->ano = ano;
   return *this;
}

int Data::getDia()
{
   return dia;
}

int Data::getMes()
{
   return mes;
}

int Data::getAno()
{
   return ano;
}

Data::Data(int dia, int mes, int ano)
{
   setDia(dia);
   setMes(mes);
   setAno(ano);
}


bool Data::ValidaData(int dia, int mes, int ano)
{
   //Dia Invalido
   if(dia < 1 || dia > 31){
      return false;
   }

   //Mes Invalido
   if(mes < 1 || mes > 12){
      return false;
   }

   // Ano Invalido
      if(ano < 1){
      return false;
   }


   // Meses de 30 ou 28 dias
   if((mes == 2 || mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia == 31){
      return false;
   }

   // Tratamento especifico de fevereiro
   if(mes == 2) {

      if((ano%400 == 0 || (ano%4 == 0 && (!(ano%100 == 0 && ano%400 != 400 )))) && (mes == 2) && (dia == 29)){
         return true;
      } else if(dia > 28) {
         return false;
      }
   }

   return true;
}

Data& Data::setData(int dia,int mes, int ano)
{
   if((ValidaData(dia,mes,ano))){
      setDia(dia);
      setMes(mes);
      setAno(ano);
   }
   return *this;
}

string Data::getData()
{
   char str1[3],str2[3],str3[10];
   itoa(getDia(),str1,BASE_DECIMAL);
   itoa(getMes(),str2,BASE_DECIMAL);
   itoa(getAno(),str3,BASE_DECIMAL);
   return (string(str1) + "/" + string(str2) + "/" + string(str3));
}

class Funcionario
{
   string nome;
   double salario;
   Data dataDeAdmissao;

public:
   Funcionario& setNome(string nome);
   string getNome();
   Funcionario& setSalario(double salario);
   string getSalario();
   Funcionario& setDatadeAdmissao(int dia, int mes, int ano);
   string getDatadeAdmissao();
   double Aumento();
};

Funcionario& Funcionario::setNome(string nome)
{
   this->nome = new char[nome.length()];
   this->nome = nome;

   return *this;
}

string Funcionario::getNome()
{
   return this->nome;
}

Funcionario& Funcionario::setSalario(double salario)
{
   while(salario < 0){
      cout << "Salario invalido, digite novamente: " << endl;
      cin >> salario;
   }

   this->salario = salario;

   return *this;
}

string Funcionario::getSalario()
{
   ostringstream ss;
   string str;
   ss << salario;
   str = ss.str();
   return "R$" + str;
}

Funcionario& Funcionario::setDatadeAdmissao(int dia, int mes, int ano)
{
   this->dataDeAdmissao.setData(dia,mes,ano);

   return *this;
}

string Funcionario::getDatadeAdmissao()
{
   return this->dataDeAdmissao.getData();
}

double Funcionario::Aumento()
{
   salario = salario + (salario/10);

   return salario;
}

class CNPJ
{
   string cnpj;

public:
   CNPJ(string cnpj = "00000000000000");
   static bool ValidaCNPJ(string cnpj);
   CNPJ& setCNPJ(string cnpj);
   string getCNPJ();
};

CNPJ::CNPJ(string cnpj)
{
   setCNPJ(cnpj);
}

CNPJ& CNPJ::setCNPJ(string cnpj)
{
   if(ValidaCNPJ(cnpj)){
      this->cnpj = new char[cnpj.length()];
      this->cnpj = cnpj;
   }
   return *this;
}

string CNPJ::getCNPJ()
{
   return this->cnpj;
}

bool CNPJ::ValidaCNPJ(string cnpj)
{
   // Se o CNPJ não tiver 14 digitos
   if(cnpj.length() != 14){
      return false;
   }

   // Se os 3 primeiros numeros da segunda porção do CNPJ não forem 0
   if(!(cnpj[8] == '0' && cnpj[9] == '0' && cnpj[10] == '0')){
      return false;
   }

   return true;
}


class Empresa
{
   string nome;
   CNPJ cnpjEmpresa;

public:
   Empresa& setNome(string nome);
   string getNome();
   Empresa& setCNPJEmpresa(string cnpj);
   string getCNPJEmpresa();

};

Empresa& Empresa::setNome(string nome)
{
   this->nome = new char[nome.length()];
   this->nome = nome;

   return *this;
}

string Empresa::getNome()
{
   return this->nome;
}

Empresa& Empresa::setCNPJEmpresa(string cnpj)
{
   this->cnpjEmpresa.setCNPJ(cnpj);

   return *this;
}

string Empresa::getCNPJEmpresa()
{
   return this->cnpjEmpresa.getCNPJ();
}


//Alusões de Métodos de Main
extern Empresa PovoarEmpresa(Empresa emp1);
extern Funcionario PovoarFuncionarios(Funcionario f, int i);
extern void MostraSituacaoEmpresa(Empresa emp1);
extern void MostraSituacaoFunc(Funcionario f, int i);

int main()
{
   Empresa emp1;
   int i,num;
   char sair,aumento;
   Funcionario func[50];

   while(1){
      emp1 = PovoarEmpresa(emp1);

      cout << "*******************************************" << endl;
      cout << "         Empresa: " << emp1.getNome() << endl;
      cout << "*******************************************" << endl;
      cout << "Quantos funcionarios deseja adicionar? [MAX = 50]";
      cin >> num;

      for(i=0 ; i<num ; i++){
         func[i] = PovoarFuncionarios(func[i],i + 1);
      }

      aposaumento:
         system("cls");
         for(i=0 ; i<num ; i++){
            if(i == 0){
               MostraSituacaoEmpresa(emp1);
               MostraSituacaoFunc(func[i],i + 1);
            }else{
               MostraSituacaoFunc(func[i],i + 1);
            }
         }

         cout << endl <<"Deseja dar aumento de 10% aos funcionarios[S/N]?";
         cin >> aumento;

         if(aumento == 'S' || aumento == 's'){
            for(i=0; i<num; i++){
               func[i].Aumento();
            }
            goto aposaumento;
         }


         cout << endl << "Digite \"S\" para sair: ";
         cin >> sair;

         if(sair == 's' || sair == 'S'){
            cout << endl <<"Obrigado por usar meu programa." << endl;
            break;
         }
   }

   return 0;
}

Empresa PovoarEmpresa(Empresa emp1)
{
   string n,cnpj;

   cout << "Digite o nome da empresa: ";
   cin >> n;
   emp1.setNome(n);

   cout << "Digite o CNPJ: ";
   cin >> cnpj;
   while(CNPJ::ValidaCNPJ(cnpj) == false){
      cout << "CNPJ Invalido. Digite novamente: ";
      cin >> cnpj;
   }
   emp1.setCNPJEmpresa(cnpj);

   return emp1;

}

Funcionario PovoarFuncionarios(Funcionario f, int i)
{
   double salario;
   int dia,mes,ano;
   string nome;

   cout << "Digite o nome do(a) funcionario(a) " << i << ": ";
   cin >> nome;
   f.setNome(nome);

   cout << "Digite o salario do(a) funcionario(a) " << i << ": ";
   cin >> salario;

   f.setSalario(salario);

   perguntasdata:
      cout << "Digite o dia de admissao do(a) funcionario(a) " << i << ": ";
      cin >> dia;
      cout << "Digite o mes de admissao do(a) funcionario(a) " << i << ": ";
      cin >> mes;
      cout << "Digite o ano de admissao do(a) funcionario(a) " << i << ": ";
      cin >> ano;

      while(Data::ValidaData(dia,mes,ano) == false){
         cout << "Data invalida. Digite novamente: " << endl;
         goto perguntasdata;
      }

      f.setDatadeAdmissao(dia,mes,ano);

      return f;

}

void MostraSituacaoEmpresa(Empresa emp1)
{
   system("cls");

   cout << "*******************************************" << endl;
   cout << "      Empresa: " << emp1.getNome() << endl;
   cout << "      CNPJ: " << emp1.getCNPJEmpresa() << endl;
   cout << "*******************************************" << endl;

   return;
}

void MostraSituacaoFunc(Funcionario f, int i)
{
   if(i == 1){
      cout << "     Nome: " << "---" << " Salario " << "---" << " Data de Admissao " << endl;
   }
   cout << "- >| " << f.getNome() << " --- " << f.getSalario() << " --- " << f.getDatadeAdmissao() << " |" << endl;

   return;
}
