/**********************************************************************
 * Baseado no código disponibilizado em
 *  Application Note: "Object-Oriented Programming in C"
 * https://www.state-machine.com/doc/AN_OOP_in_C.pdf
 *
 * Aqui se apresenta a interface do número do tipo "matriz"
 *
 * numero.h definiu a interface do "número_t virtual"
 * ********************************************************************/

#ifndef MATRIZ_H
#define MATRIZ_H

#include "numero.h" /*a interface da classe básica */

struct Matriz_Interface_st;

struct Matriz_st
{
    struct Numero_st super;
    /* <== herda a "super-classe Numeros",
     * isto é, a classe superior a Meulong int na
     * hierarquia dos números
     * Com isso, herda as operações da
     * tabela de métodos comuns a todos os Numeros
     * assim como os atributos desta classe base,
     * (caso houvessem)       */

    struct Matriz_Interface_st const *Metodo;
    /* o ponteiro para a tabela de
     * ponteiros para funções
     * que são apenas as chamadas para os métodos
     * da super-classe, porém fazendo as
     * devidas conversões na "entrada" e na
     * saída               */

    unsigned int *tam;

    double **matriz;
};
/* ----------------------------------------------------------*
 * declaro o ponteiro para o número do tipo Matriz_t      *
 * que não estão "dentro" da tabela de funções virtuais      *
 * ----------------------------------------------------------*/
typedef struct Matriz_st *Matriz_pt;
typedef struct Matriz_st Matriz_t;

struct Matriz_Interface_st
{
    Matriz_pt (*copia)(Matriz_t const *const me);

    Matriz_pt (*atribui)(Matriz_t const *const me, Matriz_t *const outro);

    Matriz_pt (*soma)(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

    Matriz_pt (*subt)(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

    Matriz_pt (*mult)(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

    Matriz_pt (*divd)(Matriz_t const *const me, Matriz_t const *const outro, Matriz_t *const res);

    Matriz_pt (*ac_soma)(Matriz_t *const me, Matriz_t const *const outro);

    Matriz_pt (*ac_subt)(Matriz_t *const me, Matriz_t const *const outro);

    Matriz_pt (*ac_mult)(Matriz_t *const me, Matriz_t const *const outro);

    Matriz_pt (*ac_divd)(Matriz_t *const me, Matriz_t const *const outro);

    int (*compara)(Matriz_t const *const me, Matriz_t const *const outro);

    char *(*imprime)(Matriz_t const *const me);

    void (*destroi)(Matriz_t *me);
    /*------------------------------------------------------*/
    void (*set)(Matriz_t *const me, unsigned int i, unsigned int j, double valor);

    double(*get)(Matriz_t const *const me, unsigned int i, unsigned int j);

    int (*compara_tamanho)(Matriz_t const *const me, Matriz_t const *const outro);
    
    Matriz_pt (*resize)(Matriz_t *const me, unsigned int *tam);

    Matriz_pt (*ones)(Matriz_t *const me, unsigned int *tam);

    Matriz_pt (*identidade)(Matriz_t *const me, unsigned int *tam);

    Matriz_pt (*multip_escalar)(Matriz_t *const me, unsigned int valor);

    Matriz_pt (*dot)(Matriz_t *const me, Matriz_t const *const outro);

    Matriz_pt (*transpor)(Matriz_t *const me);

    Matriz_pt (*transpor_diag2)(Matriz_t *const me);

    Matriz_pt (*reverse_horizontal)(Matriz_t *const me);

    Matriz_pt (*reverse_vertical)(Matriz_t *const me);

    Matriz_pt (*acrescenta_linha)(Matriz_t *const me);

    Matriz_pt (*acrescenta_coluna)(Matriz_t *const me);
    /*------------------------------------------------------*/
};

typedef struct Matriz_Interface_st *Matriz_Interface_pt;

/* protótipo do construtor   */
Matriz_pt Matriz_constroi(Matriz_pt me, unsigned int *tam, double *matriz);

#endif /* MATRIZ_H */