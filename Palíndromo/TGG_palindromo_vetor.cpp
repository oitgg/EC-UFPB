#include <iostream>
#include <stdio.h>
#include <typeinfo>
#include <cstdlib>
#include <vector>
#include <locale.h>

using namespace std;

void ShowMenu()
{
   cout << "---------------------------" << endl;
   cout << "           MENU            " << endl;
   cout << "---------------------------" << endl;
   cout << "[1] Vetor de Numeros Reais " << endl;
   cout << "[2] Vetor de Caracteres " << endl;
   cout << "[3] Vetor de Inteiros " << endl;
   cout << "[4] Vetor de Strings " << endl;
   cout << "[5] Sair " << endl;
   cout << "___________________________" << endl;
}

void palindromo (bool resultado)
{
     if (resultado)
     {
         cout << "\nO vetor e' um palindromo" << endl << endl;
     }
     else
     {
         cout << "\nO vetor nao e' um palindromo" << endl << endl;
     }
     system("pause");
}

template <typename Tmplt>
vector<Tmplt> fillvector(vector<Tmplt> v)
{
   unsigned int i = 1;
   char op;
   Tmplt input;
   string tmp;

   while(1)
   {
       cout << "\nDigite o elemento " << i << " do vetor: ";

       if (typeid(Tmplt) == typeid(int))
       {
            while(!(cin >> input))
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "\nDigite um valor valido" << endl;
                cout << "\n ";
            }
       }

       else if (typeid(Tmplt) == typeid(double))
       {
            while(!(cin >> input))
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "\nDigite um valor valido." << endl;
                cout << "\nDigite o elemento " << i << " do vetor: ";
            }
       }

       else
       {
          cin >> input;
       }

       v.push_back(input);

       cout << "\nDeseja inserir outro elemento? [S/N]: ";
       cin >> op;

       while (op != 'S' && op != 's' && op != 'N' && op != 'n')
       {
           cout << "\nDigite uma opcao valida" << endl;
           cout << "\nDeseja inserir outro elemento? [S/N]: ";
           cin >> op;
       }

      if(op == 'N' || op == 'n')
      {
         break;
      }

      i++;
    }

   cout << "\nVetor: ";
   cout << "(";
   for(i = 0; i < v.size(); i++)
   {
       if (i == v.size() - 1)
       {
           cout << v[i] << ")" << endl;
           continue;
       }
      cout << v[i] << ", ";
   }

   return v;
}

template <typename Tmplt>
bool checkpal(vector<Tmplt> v)
{
    int i = 0;
    int f = v.size() - 1;

    for (;(v[i]) == (v[f]); i++, f--)
    {
        if (f + 1 % 2 != 0)
        {
             if (i == f) // Condição pra quantidade ímpar
             {
                return true;
             }
        }

        if (f - i == 1) // Condição pra quantidade par
        {
            return true;
        }

    }

    return false; // Nenhuma condição == não é palíndromo
}



int main()
{
    setlocale(LC_ALL, "Portuguese");

    bool checkresult;
    char op;
    vector<double> vdouble;
    vector<char> vchar;
    vector<int> vint;
    vector<string> vstring;

    do
    {
        system("cls");
        ShowMenu();
        cout << "Escolha uma opcao: ";
        cin >> op;

        switch(op)
        {
            case '1':
                checkresult = checkpal(fillvector(vdouble));
                palindromo(checkresult);
                break;
            case '2':
                checkresult = checkpal(fillvector(vchar));
                palindromo(checkresult);
                break;
            case '3':
                checkresult = checkpal(fillvector(vint));
                palindromo(checkresult);
                break;
            case '4':
                checkresult = checkpal(fillvector(vstring));
                palindromo(checkresult);
            case '5':

                break;
           default:
                cout << "\nOpcao invalida" << endl << endl;
                system("pause");
        }

   }
   while(op != '5');

   return 0;
}
