/* main.c */
/* teste do tipo de dados meudouble */
#include <stdio.h>
#include "racional.h"

int main ()
{

/** ------ PARTE ORIGINAL DO PROGRAMA: MEU_Racional ------*/
	Racional_pt num1=NULL, num2=NULL, num3=NULL, num4=NULL;

	/*veja que aqui neste ponto faço chamadas de algumas funções
	 * através dos ponteiros que estão na tabela vtbl (ponteiro "metodo")
	 * da superclasse "Numero". Como as funções desta tabela esperam
	 * receber "ponteiro para Numero_t", preciso converter o ptX1 para
	 * Numero_pt e depois converter o resultado "de volta" para
	 * MeuDouble_pt */

   printf("*********************************************************************************************\n");
   printf("********************DEMONSTRANDO O FUNCIONAMENTO DA BIBLIOTECA RACIONAL.H********************\n");
   printf("*********************************************************************************************\n\n");
   
   num1 = Racional_constroi(num1, 45, 23);
   num2 = Racional_constroi(num2, 57, 55);
   num3 = Racional_constroi(num3, 17, 45);
   printf("Os numeros num1, num2 e num3 foram criados com os valores: num1 = %s,", num1->Metodo->imprime(num1));
   printf(" num2 = %s,", num2->Metodo->imprime(num2));
   printf(" num3 = %s\n", num3->Metodo->imprime(num3));
   //num4 = Racional_constroi(num4, 10, 25);
   num4 = num1->Metodo->copia(num1);
   printf("O num4 foi criado como uma copia do numero 1: num4 = %s\n", num4->Metodo->imprime(num4));

   num4->Metodo->setNum(num4, 10);
   num4->Metodo->setDen(num4, -20);
   num4->Metodo->set(num4, 10, -20);
   printf("O numerador do num4 foi definido como 10 e o denominador como -20: num4 = %s\n", num4->Metodo->imprime(num4));

   printf("O valor do numerador é %ld e do denominador é %ld.\n", num4->Metodo->getNum(num4), num4->Metodo->getDen(num4));
   
   num4 = num2->Metodo->atribui (num2, num4);
   printf("O valor do num2 foi atribuido ao num4: num4 = %s\n", num4->Metodo->imprime(num4));
   long int num , den;
   num4->Metodo->get(num4, &num, &den);
   printf("O valor do numerador é %ld e do denominador é %ld.\n", num, den);

	num3 = num3->Metodo->soma(num1, num2, num3);
   printf("O num3 recebeu o valor da soma do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num3 = num3->Metodo->subt(num1, num2, num3);
   printf("O num3 recebeu o valor da subtracao do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num3 = num3->Metodo->mult(num1, num2, num3);
   printf("O num3 recebeu o valor da multiplicacao do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num3 = num3->Metodo->divd(num1, num2, num3);
   printf("O num3 recebeu o valor da divisao do num1 com o num2: num3 = %s\n", num3->Metodo->imprime(num3));

   num1 = num1->Metodo->ac_soma(num1, num2);
   printf("O num1 foi somado com o num2: num1 = %s\n", num1->Metodo->imprime(num1));

   num1 = num1->Metodo->ac_subt(num1, num2);
   printf("O num2 foi subtraido do num1: num1 = %s\n", num1->Metodo->imprime(num1));

   num1 = num1->Metodo->ac_mult(num1, num2);
   printf("O num1 foi multiplicado pelo num2: num1 = %s\n", num1->Metodo->imprime(num1));

   num1 = num1->Metodo->ac_divd(num1, num2);
   printf("O num1 foi divido pelo num2: num1 = %s\n", num1->Metodo->imprime(num1));

   int resultado = num1->Metodo->compara(num2, num4);
   if (resultado == 0){
      printf("num2 = num4 ");
      printf("(%s = ", num1->Metodo->imprime(num2));
      printf("%s)\n", num2->Metodo->imprime(num4));
   }
   else if (resultado > 0){
      printf("num2 > num4 ");
      printf("(%s > ", num1->Metodo->imprime(num2));
      printf("%s)\n", num2->Metodo->imprime(num4));
   }
   else if (resultado < 0){
      printf("num2 < num4 ");
      printf("(%s < ", num1->Metodo->imprime(num2));
      printf("%s)\n", num2->Metodo->imprime(num4));
   }

   resultado = num1->Metodo->compara(num1, num2);
   if (resultado == 0){
      printf("num1 = num2 ");
      printf("(%s = ", num1->Metodo->imprime(num1));
      printf("%s)\n", num2->Metodo->imprime(num2));
   }
   else if (resultado > 0){
      printf("num1 > num2 ");
      printf("(%s > ", num1->Metodo->imprime(num1));
      printf("%s)\n", num2->Metodo->imprime(num2));
   }
   else if (resultado < 0){
      printf("num1 < num2 ");
      printf("(%s < ", num1->Metodo->imprime(num1));
      printf("%s)\n", num2->Metodo->imprime(num2));
   }
   
	num1->Metodo->destroi(num1);
   num2->Metodo->destroi(num2);
   num3->Metodo->destroi(num3);
   num4->Metodo->destroi(num4);
	return (0);
}








