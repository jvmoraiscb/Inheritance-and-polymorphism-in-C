/*====== definição do TAD racional
 * fonte: Estruturas de dados usando C
 *        Tenembaum, Langsam, Augestein
 * disponível em https://www.cin.ufpe.br/~garme/public/(ebook)Estruturas%20de%20Dados%20Usando%20C%20(Tenenbaum).pdf
 * ===========================================================/
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "racional.h"

#define TRUE 1
#define FALSE 0

/*--------------------------------------------------*
 *         definição de valores                     *
 *--------------------------------------------------*/
/* abstract typedef <integer, integer> RATIONAL;
 *  condition RATIONAL[1] > 0;
 */
struct Racional_st
{
	long int numerador;
	long int denominador;
};
typedef struct Racional_st Racional_t;

/* lembre-se que Racional_pt já está definido lá em racional.h *
 * assim, não é preciso re-defini-lo aqui...                   *
 * ------------------------------------------------------------*
 * typedef struct Racional_st * Racional_pt;                   *
 * *************************************************************/

/* ---------------algoritmo de euclides ------------*
 * note que esta função NÃO está no racional.h      *
 * -------------------------------------------------*/
void reduz_racional_euclides(Racional_pt input, Racional_pt output)
{
	int sinal;
	if ((input->numerador * input->denominador) < 0)
	{
		sinal = -1;
	}
	else
	{
		sinal = +1;
	}

	long int a, b, rem;

	if (input->numerador > input->denominador)
	{
		a = labs(input->numerador);
		b = labs(input->denominador);
	}
	else
	{
		a = labs(input->denominador);
		b = labs(input->numerador);
	}
	while (b > 0)
	{
		rem = b;
		b = a % b;
		a = rem;
	}
	output->numerador = labs(input->numerador) / a * sinal;
	output->denominador = labs(input->denominador) / a;
}

/*----------------------------------------*
 *      COMPARAÇÃO ENTRE DOIS RACIONAIS --*
 * ---------------------------------------*
 *definicao de operador                   *
 * abstract equal(a,b)    written a == b*I
 * RATIONAL a,b;                           *
 * postcondition equal = = (a[0]*b[l ] = = b[0]*a[l]) ;
 */
int iguais_racionais(Racional_pt rac1, Racional_pt rac2)
{
	Racional_t r1, r2;
	reduz_racional_euclides(rac1, &r1);
	reduz_racional_euclides(rac2, &r2);
	if (r1.numerador == r2.numerador &&
		r1.denominador == r2.denominador)
	{
		return (TRUE);
	}
	return FALSE;
}

/*----------------------------------------*
 *      CONSTRUCAO DE UM NUMERO RACIONAL -*
 * ---------------------------------------*
 *definicao de operador                   *
 * abstract RATIONAL makerational(a,b) I* writte n [a,b]
 *  int a,b;
 *  precondition b <> 0;
 *  postcondition makerational[0]*b == a*makerational[1]
 */
Racional_pt constroiRacional(long int num, long int den)
{
	Racional_pt ptNovoRacional;
	Racional_t temp;

	/* garante a pré-condição (pode ser desabilitado se compilado com cc -dNDEBUG...)
	 */
	assert(den != 0);
	/* solução incompleta!! O que faz se não denominador nulo ? *
	 * Mais para frente melhoraremos isso
	 */
	/* se o denominador é negativo, troca sinal de ambos*/
	if (den < 0)
	{
		num = -num;
		den = -den;
	}
	temp.numerador = num;
	temp.denominador = den;
	printf("valores iniciais = %ld %ld", temp.numerador, temp.denominador);

	ptNovoRacional = (Racional_pt)malloc(sizeof(Racional_t));
	if (ptNovoRacional != (Racional_pt)NULL)
	{
		reduz_racional_euclides(&temp, ptNovoRacional);
		printf("valores reduzidos = %ld %ld", ptNovoRacional->numerador, ptNovoRacional->denominador);
		return ptNovoRacional;
	}
	printf("\n Erro! Função constroiRacional: não alocou memória \n");
	/* solução ruim!! Imprime código que o "cliente" vai ler e
	 * não vai entender.... mais para frente melhoraremos isso */
	return (Racional_pt)(NULL);
}

/*----------------------------------------*
 *  COPIA-CONSTRUINDO UM RACIONAL       --*
 * ---------------------------------------*
 *   copia um racional que já existe para um novo racional que
 *   AINDA NÃO existe
 */
Racional_pt copiaRacional(Racional_pt origem)
{
	Racional_pt ptNovoRacional;

	ptNovoRacional = nuloRacional();
	ptNovoRacional->numerador = origem->numerador;
	ptNovoRacional->denominador = origem->denominador;
	return ptNovoRacional;
}

/*----------------------------------------*
 *  LIBERA AREA OCUPADA POR UM RACIONAL --*
 * ---------------------------------------*
 *  libera a área de memória alocada para o número racional
 */
int destroiRacional(Racional_pt num)
{
	if (num == (Racional_pt)NULL)
	{
		return (FALSE);
	}

	free(num);
	return (TRUE);
}

/*------------------------------------------*
 *  ATRIBUI VALORES DE UM RACIONAL EM OUTRO-*
 * -----------------------------------------*
 *   copia um racional que já existe para um novo racional que
 *   JÁ existe
 */
Racional_pt atribuiRacional(Racional_pt origem, Racional_pt destino)
{
	destino->numerador = origem->numerador;
	destino->denominador = origem->denominador;
	return destino;
}

/*----------------------------------------*
 *  CRIA UM RACIONAL NULO               --*
 * ---------------------------------------*/
Racional_pt nuloRacional()
{
	return (constroiRacional(0, 1));
}

/*----------------------------------------*
 *  CRIA UM RACIONAL "UNITARIO"         --*
 * ---------------------------------------*/
Racional_pt unidadeRacional()
{
	return (constroiRacional(1, 1));
}

/*--------------------------------------------------*
 *  ADICIONA DOIS RACIONAIS E ATRIBUI A UM TERCEIRO-*
 * -------------------------------------------------*
 *definicao de operador
 *  abstract RATIONAL add(a,b) I* written a + b*I
 *   RATIONAL a,b;
 *   postcondition add = = (a[0 ] * b[l] + b[0] * a[l]) , a[l]*b[l] ]
 */
Racional_pt adicionaRacionais(Racional_pt a, Racional_pt b, Racional_pt res)
{
	Racional_t temp;
	temp.denominador = a->denominador * b->denominador;
	temp.numerador = (a->numerador * b->denominador + b->numerador * a->denominador);

	reduz_racional_euclides(&temp, res);

	if (res->denominador < 0)
	{
		res->denominador = -res->denominador;
		res->numerador = -res->numerador;
	}
	return (res);
}

/*----------------------------------------------------*
 *  MULTIPLICA DOIS RACIONAIS E ATRIBUI A UM TERCEIRO-*
 * ---------------------------------------------------*
 *definicao de operador
 * abstract RATIONAL mult{a,b)   written a * b *
 *  RATIONAL a,b;
 *  postconditio n mul t = = [a[0 ] * b[0] , a[l ] * b[l ] ]
 */
Racional_pt multiplicaRacionais(Racional_pt a, Racional_pt b, Racional_pt res)
{
	Racional_t temp;

	temp.denominador = a->denominador * b->denominador;
	temp.numerador = a->numerador * b->numerador;
	reduz_racional_euclides(&temp, res);

	if (res->denominador < 0)
	{
		res->denominador = -res->denominador;
		res->numerador = -res->numerador;
	}

	return (res);
}

/*----------------------------------------------------*
 *  DIVIDE DOIS RACIONAIS E ATRIBUI A UM TERCEIRO-    *
 * ---------------------------------------------------*/
Racional_pt divideRacionais(Racional_pt a, Racional_pt b, Racional_pt res)
{
	/* implemente esta operação ....
	 */
	a = NULL;
	b = NULL;
	res = NULL;
	res = a = b;
	return (Racional_pt)res;
}

/*-----------------------------------------------------------------------*
 *  SUBTRAI UM RACIONAL B DE OUTRO A E ATRIBUI O RESULTADO A UM TERCEIRO-*
 * ----------------------------------------------------------------------*/
Racional_pt subtraiRacionais(Racional_pt a, Racional_pt b, Racional_pt res)
{
	/* implemente esta operação ....
	 */
	a = NULL;
	b = NULL;
	res = NULL;
	res = a = b;
	return (Racional_pt)res;
}

/*-----------------------------------------------------------------------*
 *  ELEVA UM RACIONAL A UMA POTÊNCIA INTEIRA (QUE PODE SER NEGATIVA      *
 *   ATRIBUI O RESULTADO A UM TERCEIRO                                   *
 * ----------------------------------------------------------------------*/
Racional_pt potenciaInteiraRacional(Racional_pt a, long int pot,
									Racional_pt res)
{
	/* quanto é "a" elevado-a "pot" ?
	 * implemente esta operação ....
	 */
	a = NULL;
	pot = 0;
	res = NULL;
	res = a + pot;
	return (Racional_pt)res;
}

/*-----------------------------------------------------------------------*
 *  IMPRIME UM NÚMERO RACIONAL, COM UMA MSG ANTES E OUTRA DEPOIS         *
 * ----------------------------------------------------------------------*/
void imprimeRacional(char *msgPre,
					 Racional_pt a,
					 char *msgPos)
{
	printf("%s = (%ld / %ld) %s",
		   msgPre,
		   a->numerador,
		   a->denominador,
		   msgPos);
}

/*-----------------------------------------------------------------------*
 *  IMPRIME O RESULTADO DE UMA FUNÇÃO QUE OPERA SOBRE UM NÚMERO RACIONAL *
 *   COM UMA MSG ANTES E OUTRA DEPOIS                                    *
 * ----------------------------------------------------------------------*/
void imprimeOperacaoUmRacional(char *msgPre,
							   ptFunc_UmRacional f,
							   Racional_pt a,
							   Racional_pt res,
							   char *msgPos)
{
	res = f(a, res);
	printf("%s = (%ld / %ld) %s",
		   msgPre,
		   res->numerador,
		   res->denominador,
		   msgPos);
}

/*-----------------------------------------------------------------------*
 *  IMPRIME O RESULTADO DE UMA FUNÇÃO QUE OPERA SOBRE                    *
 *      DOIS NÚMEROS RACIONAIS                                           *
 *   COM UMA MSG ANTES E OUTRA DEPOIS                                    *
 * ----------------------------------------------------------------------*/
void imprimeOperacaoDoisRacionais(char *msgPre,
								  ptFunc_DoisRacionais f,
								  Racional_pt a,
								  Racional_pt b,
								  Racional_pt res,
								  char *msgPos)
{
	res = f(a, b, res);
	printf("%s = (%ld / %ld) %s",
		   msgPre,
		   res->numerador,
		   res->denominador,
		   msgPos);
}

/*-----------------------------------------------------------------------*
 *  IMPRIME O RESULTADO DE UMA FUNÇÃO QUE OPERA SOBRE                    *
 *      UM NÚMERO RACIONAL E UM INTEIRO                                  *
 *   COM UMA MSG ANTES E OUTRA DEPOIS                                    *
 * ----------------------------------------------------------------------*/
void imprimeOperacaoRacionalInt(char *msgPre,
								ptFunc_RacionalInt f,
								Racional_pt a,
								long int b,
								Racional_pt res,
								char *msgPos)
{
	res = f(a, b, res);
	printf("%s = (%ld / %ld) %s",
		   msgPre,
		   res->numerador,
		   res->denominador,
		   msgPos);
}
