/**********************************************************************
* Baseado no código disponibilizado em
*  Application Note: "Object-Oriented Programming in C"
* https://www.state-machine.com/doc/AN_OOP_in_C.pdf
*
* Aqui se implementa o número do tipo "racional"
*
* numero.h definiu a interface do "número_t virtual"
* que é usada aqui
* ********************************************************************/
#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "meu_racional.h"

/*------------------------------------------------------------------*
 *  IMPLEMENTACAO DAS FUNCOES VIRTUAIS DE "RACIONAL"                *
 * Uma função virtual é uma função que é declarada (mas não         *
 * implementada em uma classe base (NO CASO, NUMERO) e redefinida   *
 * pela classe derivada (NO CASO, RACIONAL).                        *
 * Para declarar uma função como sendo virtual, é preciso associá-la*
 * com uma entrada da tabela vtbl da classe base.                   *
 * A redefinição da função na classe derivada sobrepõe a definição  *
 * da função na classe base.                                        *
 *                                                                  *
 * No fundo, a declaração da função virtual na classe base age      *
 * como uma espécie de indicador que especifica uma linha geral de  *
 * ação e estabelece uma interface de acesso.                       *
 *                                                                  *
 * A redefinição da função virtual pela classe derivada especifica  *
 * verdadeiramente IMPLEMENTA as operações realmente executadas     *
 * por cada método da tabela.                                       *
 *                                                                  *
 * Quando acessadas normalmente, funções virtuais se comportam como *
 * qualquer outro tipo de função membro da classe. Entretanto, o que*
 * torna funções virtuais importantes e capazes de suportar         *
 * polimorfismo em tempode execução é o seu modo de comportamento   *
 * quando acessado através de um apontador.                         *
 *                                                                  *
 * Lembre-se que um apontador para a classe base pode ser usado     *
 * para apontar para qualquer classe derivada daquela classe base,  *
 * desde que corretamente convertido ("cast").                      *
 *                                                                  *
 * Quando um apontador base aponta para um objeto derivado que      *
 * contém uma função virtual, o programa irá determina qual versão  *
 * daquela função chamar baseada no tipo do objeto apontado pelo    *
 * apontador.                                                       *
 *                                                                  *
 * Assim, quando objetos diferentes são apontados, versões          *
 * diferentes da função virtual são executadas.                     *
 * -----------------------------------------------------------------*/

/*------------------------------------------------------------------*
 * PROTOTIPOS DA IMPLEMENTACAO DAS FUNCOES VIRTUAIS                 *
 * note o "_" (underline) no final dos nomes das funções            *
 * Trata-se de uma convenção que usamos para nos lembrar que estas  *
 * funções são "static". Isto é: são declaradas e definidas pelo    *
 * compilador de tal forma que são reconhecidas apenas aqui dentro  *
 * deste arquivo  ____.c --> _______.o                              *
 * Estas funções não podem ser chamadas PELO NOME para serem        *
 * executadas por outros trechos de código em outros arquivos .c    *
 * Todavia, podem ser chamadas para serem executadas através de seus*
 * ENDEREÇOS. E são os endereços destas funções que são atribuídos  *
 * às respectivas posições da tabela vtbl que é apontada pelo campo *
 * super. O campo super a que se refere aqui é o PRIMEIRO campo da  *
 *                                                                  *
 * -----------------------------------------------------------------*/
static  Numero_pt copia_ (Numero_t const * const  me);

static  Numero_pt atribui_ (Numero_t const * const  me,
							         Numero_t       * const  outro) ;

static  Numero_pt soma_  (Numero_t const * const  me,
								   Numero_t const * const  outro,
							       Numero_t       * const  res);

static  Numero_pt subt_  (	Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt mult_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt divd_  ( Numero_t const * const  me,
									Numero_t const * const  outro,
									Numero_t       * const  res);

static  Numero_pt ac_soma_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_subt_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_mult_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  Numero_pt ac_divd_ (Numero_t       * const  me,
									 Numero_t const * const  outro);

static  int	compara_ 	(Numero_t const * const  me,
							 Numero_t const * const  outro);

static  char * imprime_  (Numero_t const * const  me);

static  void destroi_ (Numero_t   *   me);



/*---------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de Meulong int*
 * -------------------------------------------------------------------*/
static  MeuRacional_pt Copia_ (MeuRacional_t const * const  me);

static  MeuRacional_pt Atribui_ (MeuRacional_t const * const  me,
							     MeuRacional_t       * const  outro) ;

static  MeuRacional_pt Soma_  (MeuRacional_t const * const  me,
							   MeuRacional_t const * const  outro,
							   MeuRacional_t       * const  res);

static  MeuRacional_pt Subt_  (MeuRacional_t const * const  me,
							   MeuRacional_t const * const  outro,
							   MeuRacional_t       * const  res);

static  MeuRacional_pt Mult_  ( MeuRacional_t const * const  me,
								MeuRacional_t const * const  outro,
								MeuRacional_t       * const  res);

static  MeuRacional_pt Divd_  ( MeuRacional_t const * const  me,
								MeuRacional_t const * const  outro,
								MeuRacional_t       * const  res);

static  MeuRacional_pt Ac_Soma_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Subt_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Mult_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  MeuRacional_pt Ac_Divd_ (MeuRacional_t       * const  me,
								 MeuRacional_t const * const  outro);

static  int	Compara_ 	    (MeuRacional_t const * const  me,
							 MeuRacional_t const * const  outro);

static  char *      Imprime_  (MeuRacional_t const * const  me);

static  void        Destroi_ (MeuRacional_t  *   me);

/* ------------------------------------------------------- *
 * funções que são típicas do numero Racional, mas não são *
 * funcoes da classe virtual básica número                 *
 * protótipos das funçoes get e set, por exemplo           *
 *---------------------------------------------------------*/
static 	void     Get_ (MeuRacional_t  const * const me,
					 long int * valorNum,
					 long int * valorDen);

static 	void     Set_ (MeuRacional_t   * const me,
					 long int valorNum,
					 long int valorDen);

static 	long int   GetReal_ (MeuRacional_t  const * const me);

static 	void     SetReal_ (MeuRacional_t   * const me,
					     long int valorNum);

static 	long int   GetImag_ (MeuRacional_t  const * const me);

static 	void     SetImag_ (MeuRacional_t   * const me,
					       long int valorDen);

static
MeuRacional_pt  Conjugado_ (MeuRacional_t   const * const me,
	                        MeuRacional_t         * const conj);

static
long int  Modulo_ (MeuRacional_t   const * const me);

static
long int Argumento_ (MeuRacional_t   const * const me);

 /*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
MeuRacional_pt Racional_constroi (MeuRacional_pt  me,
							      long int valorNum,
							      long int valorDen)
{
	/* tabela de funções virtuais da classe Numero_t *
	 * Esta tabela estática será compartilhada por todos os números *
	 * da classe MeuRacional_t                                        */

    static struct NumeroVtbl const vtbl = {
        &copia_,
        &atribui_,
        &soma_,
        &subt_,
        &mult_,
        &divd_,
        &ac_soma_,
        &ac_subt_,
        &ac_mult_,
        &ac_divd_,
        &compara_,
        &imprime_,
        &destroi_
     };

         me = (MeuRacional_pt) Num_constroi ((Numero_pt) me);
                        /*constroi o Numero_t  */
                        /* no início de MeuRacional_t  */

         me->super.metodo = &vtbl;
            /* metodo aponta para vtbl de MeuRacional_t */
            /* as operações do "numero", a partir de agora,     */
            /* são as operações sobre long int                    */

     /* Agora, mais uma tabela estática a ser compartilhada pelos     *
      * "MeuRacional_t": a tabela de interface                          *
      * note que a estrutura Interface incorpora os métodos Get e Set */
     static struct MeuRacional_Interface_st const interface = {
        &Copia_,
        &Atribui_,
        &Soma_,
        &Subt_,
        &Mult_,
        &Divd_,
        &Ac_Soma_,
        &Ac_Subt_,
        &Ac_Mult_,
        &Ac_Divd_,
        &Compara_,
        &Imprime_,
        &Destroi_,
        &Get_,
        &Set_,
        &GetReal_,
        &SetReal_,
        &GetImag_,
        &SetImag_,
        &Conjugado_,
        &Modulo_,
        &Argumento_
     };

     me->Metodo = &interface;
            /* metodo aponta para vtbl de MeuRacional_t */
            /* as operações do "numero", a partir de agora,     */
            /* são as operações sobre long int                    */

    /* aloca dinamicamente uma area de memoria para um long int  */
    /* e atribui o endereço de memória alocada para o ponteiro */
    /* valor que está dentro da estrutura MeuRacional_st         */
	me->valor = (long int *) malloc (2*sizeof(long int));
	if (me->valor == NULL)
	{	/*erro!!! não conseguiu alocar */
	    printf ("Erro na alocação de memória em Num_Constroi");
	    printf ("Nao alocou o valor long int");
	    exit (1);
	}

	/* copia o long int passado como parâmetro */
    /* no endereco de memoria recém alocado  */
     me->valor[0] = valorNum;
     me->valor[1] = valorDen;

     return (me);

	/* ------------------------------------------------------------
	 * quando implementarmos o "meu_float", valor apontará para float
     * quando implementarmos o racional,   valor apontará para
     * um vetor com dois "long int"
     * quando implementarmos o Racional,   valor apontará para
     * um vetor com dois "long int"
     * quando implementarmos o quaternion, valor apontará para
     * um vetor com quatro "long int"
     * Por isso, cada tipo específico de número terminará de implementar
     * o seu construtor....
     *---------------------------------------------------------------*/
}


 /*---------------------------------------------*
 * implementação do set e get                   *
 * ---------------------------------------------*/
 static inline
void Get_ (MeuRacional_t  const * const me,
			long int              	* ptNum,
	        long int 				* ptDen)

{
	 *ptNum = (me->valor[0]);
	 *ptDen = (me->valor[1]);

}


static inline
void Set_ (MeuRacional_t       * const me,
			long int                valorNum,
	        long int 				valorDen)
{
	me->valor[0] = valorNum;
	me->valor[1] = valorDen;

}

static inline
long int GetReal_ (MeuRacional_t  const * const me)
{
	 return ( (me->valor[0]));

}


static inline
void SetReal_ (MeuRacional_t     * const me,
			long int                valorNum)
{
	me->valor[0] = valorNum;

}

static inline
long int  GetImag_ (MeuRacional_t  const * const me)
{
	 return (me->valor[1]);
}


static inline
void SetImag_ (MeuRacional_t       * const me,
	           long int 				  valorDen)
{
	me->valor[1] = valorDen;
}

static
MeuRacional_pt  (Conjugado_)  (MeuRacional_t   const * const me,
	                      MeuRacional_t         * const conj)
{
	conj->valor[0] =   me->valor[0];
	conj->valor[1] = - (me->valor[1]);
	return (conj);
}

static
long int  Modulo_ (MeuRacional_t   const * const me)
{
   return( sqrt(GetReal_(me)*(GetReal_(me)) + (GetImag_(me)*(GetImag_(me))  )));
}

static
long int Argumento_ (MeuRacional_t   const * const me)
{
    return (atan (GetImag_(me) / GetReal_(me) ));
}
/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline
MeuRacional_pt Copia_ (MeuRacional_t const * const  me)
{
	return ( (MeuRacional_pt)
	          copia_ ((Numero_pt) me));
}

 static
 Numero_pt copia_ (Numero_t const * const  me)
{
	assert (me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt) Racional_constroi
							((MeuRacional_pt) outro,
							  GetReal_((MeuRacional_pt) me),
							  GetImag_((MeuRacional_pt) me));
	return outro;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Atribui_(MeuRacional_t const * const me,
					  MeuRacional_t       * const  outro )
{
	return ( (MeuRacional_pt)
	          atribui_ ((Numero_pt) me,
								 (Numero_pt) outro));
}

static
 Numero_pt atribui_ (Numero_t const * const  me,
						  Numero_t       * const  outro)
 {
	 Set_( (MeuRacional_pt) outro,
	       GetReal_((MeuRacional_pt) me),
	       GetImag_ ( (MeuRacional_pt) me) );

	 return (Numero_pt) outro;
 }
/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Soma_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          soma_ ((Numero_pt) me,
					 (Numero_pt) outro,
					 (Numero_pt) res));
}

static  Numero_pt soma_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	Set_((MeuRacional_pt) res,
				GetReal_((MeuRacional_pt) me) +
				GetReal_((MeuRacional_pt) outro),
				GetImag_((MeuRacional_pt) me) +
				GetImag_((MeuRacional_pt) outro) );

	return (Numero_pt) res;
}


/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Subt_  (      MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          subt_ ((Numero_pt) me,
							  (Numero_pt) outro,
							  (Numero_pt) res));
}
static  Numero_pt subt_  (	Numero_t const * const  me,
								    Numero_t const * const  outro,
								    Numero_t       * const  res)
{
		Set_((MeuRacional_pt) res,
				GetReal_((MeuRacional_pt) me) -
				GetReal_((MeuRacional_pt) outro),
				GetImag_((MeuRacional_pt) me) -
				GetImag_((MeuRacional_pt) outro) );
		return (Numero_pt) res;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Mult_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          mult_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}

static  Numero_pt mult_  ( Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
     MeuRacional_pt  temp = NULL;
     temp = Racional_constroi(temp, 0.0,0.0);

	 SetReal_(temp,
				(GetReal_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) -
				(GetImag_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) )  );

	 SetImag_ (temp,
				(GetReal_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) +
				(GetImag_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) );

     SetReal_ ((MeuRacional_pt)res, GetReal_(temp));
     SetImag_ ((MeuRacional_pt)res, GetImag_(temp));
	 Destroi_(temp);

	 return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Divd_  ( MeuRacional_t const * const  me,
						   MeuRacional_t const * const  outro,
						   MeuRacional_t       * const  res)
{
	return ( (MeuRacional_pt)
	          divd_ ((Numero_pt) me,
                     (Numero_pt) outro,
                     (Numero_pt) res));
}

static  Numero_pt divd_  (	Numero_t const * const  me,
								Numero_t const * const  outro,
								Numero_t       * const  res)
{
	long int quociente;
	quociente = GetReal_((MeuRacional_pt) outro) *
	            GetReal_((MeuRacional_pt) outro)    +
	            GetImag_((MeuRacional_pt) outro) *
	            GetImag_((MeuRacional_pt) outro) ;

	MeuRacional_pt  temp = NULL;
	temp = Racional_constroi(temp, 0.0,0.0);

	 SetReal_(temp,
				((GetReal_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) -
				(GetImag_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) )/quociente );

	 SetImag_ (temp,
               ((GetReal_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) +
				(GetImag_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) )/quociente );

     SetReal_ ((MeuRacional_pt)res, GetReal_(temp));
     SetImag_ ((MeuRacional_pt)res, GetImag_(temp));	 Destroi_(temp);
	 return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Soma_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	return ( (MeuRacional_pt)
	          ac_soma_ ((Numero_pt) me,
                        (Numero_pt) outro));
}

static  Numero_pt ac_soma_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
	Set_((MeuRacional_pt)  me,
				GetReal_((MeuRacional_pt) me) +
				GetReal_((MeuRacional_pt) outro),
				GetImag_((MeuRacional_pt) me) +
				GetImag_((MeuRacional_pt) outro) );

	return ((Numero_pt) me);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Subt_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	Set_((MeuRacional_pt)  me,
				GetReal_((MeuRacional_pt) me) -
				GetReal_((MeuRacional_pt) outro),
				GetImag_((MeuRacional_pt) me) -
				GetImag_((MeuRacional_pt) outro) );

	return ( me);
}


static  Numero_pt ac_subt_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
	Set_((MeuRacional_pt)  me,
				GetReal_((MeuRacional_pt) me) -
				GetReal_((MeuRacional_pt) outro),
				GetImag_((MeuRacional_pt) me) -
				GetImag_((MeuRacional_pt) outro) );
	return (Numero_pt) me;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Mult_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	return ( (MeuRacional_pt)
	          ac_mult_ ((Numero_pt) me,
                        (Numero_pt) outro));
}


static  Numero_pt ac_mult_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
	MeuRacional_pt  temp = NULL;
	temp = Racional_constroi(temp, 0.0,0.0);

	 SetReal_(temp,
				(GetReal_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) -
				(GetImag_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) )  );

	 SetImag_ ( temp,
				(GetReal_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) +
				(GetImag_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) );

     SetReal_ ((MeuRacional_pt)me, GetReal_(temp));
     SetImag_ ((MeuRacional_pt)me, GetImag_(temp));
     Destroi_(temp);
	 return ( (Numero_pt) me);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Divd_  ( MeuRacional_t  * const  me,
						 MeuRacional_t const * const  outro)
{
	return ( (MeuRacional_pt)
	          ac_divd_ ((Numero_pt) me,
									     (Numero_pt) outro));
}


static  Numero_pt ac_divd_  (Numero_t       * const  me,
								  Numero_t const * const  outro)
{
	long int quociente;
	quociente = GetReal_((MeuRacional_pt) outro) *
	            GetReal_((MeuRacional_pt) outro)    +
	            GetImag_((MeuRacional_pt) outro) *
	            GetImag_((MeuRacional_pt) outro) ;

    MeuRacional_pt  temp = NULL;
    temp = Racional_constroi(temp, 0.0,0.0);

	 SetReal_( temp,
				((GetReal_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) -
				(GetImag_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) )/quociente );

	 SetImag_ ( temp,
               ((GetReal_((MeuRacional_pt) me) *
				 GetImag_((MeuRacional_pt) outro) ) +
				(GetImag_((MeuRacional_pt) me) *
				 GetReal_((MeuRacional_pt) outro) ) )/quociente );

     SetReal_ ((MeuRacional_pt)me, GetReal_(temp));
     SetImag_ ((MeuRacional_pt)me, GetImag_(temp));
     Destroi_(temp);
	 return ( (Numero_pt) me);}

/*-----------------------------------------------------------------*/
static inline
int Compara_  ( MeuRacional_t const * const  me,
				MeuRacional_t const * const  outro)
{
	return ( compara_ ((Numero_pt) me,
                       (Numero_pt) outro));
}

static  int	compara_ 	(Numero_t const * const  me,
                         Numero_t const * const  outro)
{
   long int diff_real, diff_imag;
   diff_real = abs(GetReal_((MeuRacional_pt)me) - GetReal_((MeuRacional_pt)outro));
   diff_imag = abs(GetImag_((MeuRacional_pt)me) - GetImag_((MeuRacional_pt)outro));

    if (   (    diff_real < (DBL_TRUE_MIN * 256.0))
        && (    diff_imag < (DBL_TRUE_MIN * 256.0)))
    {return (0);}

	if( Modulo_((MeuRacional_pt)me) > Modulo_((MeuRacional_pt)outro) )
	{ return (1);}
	else if( Modulo_((MeuRacional_pt)me) < Modulo_((MeuRacional_pt)outro) )
	{  return (-1);};

	return(0);
}

/*-----------------------------------------------------------------*/
static inline
char * Imprime_  ( MeuRacional_t const * const  me)
{
	return ( imprime_ ((Numero_pt) me));
}
static  char * imprime_  (Numero_t const * const  me)
{
    static char buffer[50];
    if (GetImag_((MeuRacional_pt) me) > 0.0)
	{   sprintf(buffer, "%f + %f i",GetReal_((MeuRacional_pt) me),fabs(GetImag_((MeuRacional_pt) me)) );
	}
	else
	{   sprintf(buffer, "%f - %f i",GetReal_((MeuRacional_pt) me),fabs(GetImag_((MeuRacional_pt) me)) );
	}
	return buffer;
}


 /*---------------------------------------------*
 * implementação do destrutor                   *
 * ---------------------------------------------*/
 /*-----------------------------------------------------------------*/
static inline
void Destroi_  ( MeuRacional_t  *   me)
{
	  destroi_ ((Numero_t *)  me);
}
static void destroi_ (Numero_t *  me)
{
	/* primeiro destroi o valor long int */
	free (((MeuRacional_pt) me)->valor);
	/*... e só agora destroi-se o número virtual da classe base */
	free ((Numero_t *) me);
}
