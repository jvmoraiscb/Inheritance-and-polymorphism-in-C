/*====== definição do TAD racional 
 * fonte: Estruturas de dados usando C
 *        Tenembaum, Langsam, Augestein
 * disponível em https://www.cin.ufpe.br/~garme/public/(ebook)Estruturas%20de%20Dados%20Usando%20C%20(Tenenbaum).pdf 
 * ===========================================================/
 */
#ifndef RACIONAL_H 
#define RACIONAL_H

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif  /* fim do ifndef TRUE */
/*--------------------------------------------------*
 * esta é a "interface" para os números "Racionais" *
 *--------------------------------------------------*/
typedef struct Racional_st * Racional_pt; 

/*--------------------------------------------------*
 * estes são os ponteiros "genéricos" para funções  *
 *--------------------------------------------------*/
typedef Racional_pt (* ptFunc_UmRacional)  (Racional_pt a, 
										 Racional_pt res);
											  
typedef Racional_pt (* ptFunc_DoisRacionais)  (Racional_pt a,
											Racional_pt b,
											Racional_pt res);
											  
typedef Racional_pt (* ptFunc_RacionalInt)  (Racional_pt a,
										  long int b,
										  Racional_pt res);											  
											  
/*------------------------------------------------*
 *            estas são as operações              *
 *------------------------------------------------*/
int 			iguais_racionais 	(Racional_pt rac1, 
									 Racional_pt rac2);
									 
Racional_pt  	constroiRacional 	(long int num, long int den);
Racional_pt		copiaRacional		(Racional_pt origem);
int				destroiRacional		(Racional_pt num);
Racional_pt		atribuiRacional		(Racional_pt origem, 
									 Racional_pt destino);
									 
Racional_pt		nuloRacional		();
Racional_pt		unidadeRacional		();

Racional_pt		adicionaRacionais 	(Racional_pt a, 
									 Racional_pt b, 
									 Racional_pt res );
									 
Racional_pt		multiplicaRacionais (Racional_pt a, 
									 Racional_pt b, 
									 Racional_pt res );
									 
Racional_pt 	subtraiRacionais 	(Racional_pt a, 
									 Racional_pt b, 
									 Racional_pt res );
									 
Racional_pt 	divideRacionais 	(Racional_pt a, 
									 Racional_pt b, 
									 Racional_pt res );


void 			imprimeRacional 			(char * msgPre,
											 Racional_pt a,
											 char * msgPos);
											 
void			imprimeOperacaoUmRacional 	(char * msgPre,
											 ptFunc_UmRacional f,
											 Racional_pt a,
											 Racional_pt res,
											 char * msgPos);

void			imprimeOperacaoDoisRacionais(char * msgPre,
											 ptFunc_DoisRacionais f,
											 Racional_pt a,
											 Racional_pt b,
											 Racional_pt res,
											 char * msgPos);
											 
void 			imprimeOperacaoRacionalInt ( char *msgPre,
										     ptFunc_RacionalInt f,
										     Racional_pt a,
										     long int b,
										     Racional_pt res,
										     char * msgPos);										 
						

#endif /*fim do ifndef RACIONAL_H */
