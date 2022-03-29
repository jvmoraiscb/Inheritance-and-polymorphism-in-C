/* main.c */
/* teste do tipo de dados racional e da matriz */
#include <stdio.h>
#include "racional.h"
#include "matriz.h"

int main ()
{

/** ------ PARTE ORIGINAL DO PROGRAMA: RACIONAL ------*/
	Racional_pt num1=NULL, num2=NULL, num3=NULL, num4=NULL;
   Matriz_pt mat1=NULL, mat2=NULL, mat3=NULL, mat4=NULL;
	/*veja que aqui neste ponto faço chamadas de algumas funções
	 * através dos ponteiros que estão na tabela vtbl (ponteiro "metodo")
	 * da superclasse "Numero". Como as funções desta tabela esperam
	 * receber "ponteiro para Numero_t", preciso converter o ptX1 para
	 * Numero_pt e depois converter o resultado "de volta" para
	 * MeuDouble_pt */

   printf("*********************************************************************************************\n");
   printf("********************DEMONSTRANDO O FUNCIONAMENTO DA BIBLIOTECA MATRIZ.H**********************\n");
   printf("*********************************************************************************************\n");

   unsigned int tam[2], tam1[]={3,3}, tam2[]={4,5}, tam3[]={3,3};
   double matriz1[]={1,2,3,4,5,6,7,8,9}, matriz2[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, matriz3[] = {10,20,30,40,50,60,70,80,90};

   printf("Foram criadas tres matrizes:\n\n");
   printf("Mat1 =");
   mat1 = Matriz_constroi(mat1, tam1, matriz1);
   printf("%s", mat1->Metodo->imprime(mat1));

   printf("Mat2 =");
   mat2 = Matriz_constroi(mat2, tam2, matriz2);
   printf("%s", mat2->Metodo->imprime(mat2));

   printf("Mat3 =");
   mat3 = Matriz_constroi(mat3, tam3, matriz3);
   printf("%s", mat3->Metodo->imprime(mat3));

   printf("Mat4 foi criada como copia de mat1\n\nMat4 =");
   mat4 = mat1->Metodo->copia(mat1);
   printf("%s", mat4->Metodo->imprime(mat4));

   printf("Mat3 foi atribuida a mat4\n\nMat4 =");
   mat4 = mat4->Metodo->atribui(mat3, mat4);
   printf("%s", mat4->Metodo->imprime(mat4));

   mat4->Metodo->set(mat4, 1, 1, 365);
   printf("Mat4[1][1] foi alterado para %.2f\n\nMat4 =", mat4->Metodo->get(mat4, 1, 1));
   printf("%s", mat4->Metodo->imprime(mat4));

   tam[0] = 5;
   tam[1] = 5;
   mat4 = mat4->Metodo->resize(mat4, tam);
   printf("Mat4 teve o seu tamanho reajustado para 5x5\n\nMat4 =");
   printf("%s",mat4->Metodo->imprime(mat4));

   printf("*********************************************************************************************\n");
   printf("********************DEMONSTRANDO O FUNCIONAMENTO DA BIBLIOTECA RACIONAL.H********************\n");
   printf("*********************************************************************************************\n");
   
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








