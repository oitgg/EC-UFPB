#include <stdio.h>
#include <leitura.h>

void ApresentaMenu(void)

{
   inicio:
   printf("\n\n\n\n\t****Opcoes****\n"
          "\n\t[A]dicao\n"
          "\n\t[M]ultiplicacao\n"
          "\n\t[S]ubtracao\n"
          "\n\t[D]ivisao\n"
          "\n\t[E]ncerra o programa\n\n\n");
}

int main(void)
{
   int opcao;
   double x, y;

   while (1)
   {
      ApresentaMenu();
      z:
      printf("\t>>> Escolha sua opcao: ");
      opcao = LeOpcao("A,a,M,m,S,s,D,d,E,e,Y,y,N,n");

      if (opcao == 'E' || opcao == 'e')
      {
         break;
      }

      printf("\n\t Digite o primeiro valor: ");
      x = LeReal();

      printf("\n\t Digite o segundo valor: ");
      y = LeReal();

      switch (opcao)
      {
         case 'A':
         case 'a':
            printf("\n\t %.2f + %.2f = %.2f\n", x, y, x + y);
            break;

         case 'M':
         case 'm':
            printf("\n\t %.2f * %.2f = %.2f\n", x, y, x * y);
            break;

         case 'S':
         case 's':
            printf("\n\t %.2f - %.2f = %.2f\n", x, y, x - y);
            break;

         case 'D':
         case 'd':
            printf("\n\t %.2f / %.2f = %.2f\n", x, y, x / y);
            break;

            if (y)
            {
               printf("\n\t %.2f / %.2f = %.2f\n", x, y, x / y);
            }
            else
            {
               printf("\n\t O divisor nao pode ser zero");
            }
            break;
         default:
            printf("\nEste programa contem um erro!!!");
            break;

            case 'Y':
            case 'y':
               goto z;
               break;

            case 'N':
            case 'n':
               goto u;
               break;
      }


   }
   u:
   printf ("\n\t>>> Obrigado por usar esse programa.\n");

   return 0;
}
