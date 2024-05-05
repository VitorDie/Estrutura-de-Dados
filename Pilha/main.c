#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct nodo
{
    struct nodo *nodo_abaixo;
    int valor;
} nodo_t;

typedef struct 
{
    nodo_t *topo;
    int qtd_nodos;
} pilha_t;

nodo_t *new_nodo(int valor)
{
    nodo_t *n = (nodo_t *)malloc(sizeof(nodo_t));
    n->nodo_abaixo = NULL; 
    n->valor = valor;

    return n;
}

pilha_t *new_pilha(void)
{
    pilha_t *p = (pilha_t *)malloc(sizeof(pilha_t));
    p->topo = NULL;
    p->qtd_nodos = 0;

    return p;
}

bool esta_vazia(pilha_t *pilha)
{
    return pilha->qtd_nodos == 0;
}

bool empilhar(pilha_t *pilha, nodo_t *nodo)
{
    bool status = false;

    if (pilha == NULL)
    {
        status = false;
    }
    else if (esta_vazia(pilha))
    {
        pilha->topo = nodo;

        pilha->qtd_nodos++;
        status = true;
    }
    else
    {
        nodo->nodo_abaixo = pilha->topo;
        pilha->topo = nodo;

        pilha->qtd_nodos++;
        status = true;
    }

    return status;
}


void empilhar_test(void)
{
    pilha_t *pilha_sem_new = NULL;

    nodo_t *nodo_1 = new_nodo(1);
    nodo_t *nodo_2 = new_nodo(2);
    nodo_t *nodo_3 = new_nodo(3);

    assert(false == empilhar(pilha_sem_new, nodo_1));

    pilha_t *pilha = new_pilha();
    assert(pilha->qtd_nodos == 0);
    assert(pilha->topo == NULL);


    assert(empilhar(pilha, nodo_1));
    assert(pilha->topo->valor == 1);
    assert(pilha->qtd_nodos == 1);

    assert(empilhar(pilha, nodo_2));
    assert(pilha->topo->valor == 2);
    assert(pilha->qtd_nodos == 2);

    assert(empilhar(pilha, nodo_3));
    assert(pilha->topo->valor == 3);
    assert(pilha->qtd_nodos == 3);

    free(nodo_1);
    free(nodo_2);
    free(nodo_3);
    free(pilha);
}

bool desempilhar(pilha_t *pilha)
{
    bool status = false;

    if (NULL == pilha)
    {
        status = false;
    }
    else if(esta_vazia(pilha))
    {
        status = false;
    }
    else if (1 == pilha->qtd_nodos)
    {
        nodo_t *nodo_removendo = pilha->topo;
        pilha->topo = pilha->topo->nodo_abaixo;

        pilha->topo = NULL;
        free(nodo_removendo);
        pilha->qtd_nodos--;
        status = true;
    }
    else
    {
        nodo_t *nodo_removendo = pilha->topo;
        pilha->topo = pilha->topo->nodo_abaixo;

        free(nodo_removendo);
        pilha->qtd_nodos--;
        status = true;
    }

    return status;
}

void desempilhar_test(void)
{
    // Setup da pilha

    pilha_t *pilha_sem_new = NULL;

    nodo_t *nodo_1 = new_nodo(1);
    nodo_t *nodo_2 = new_nodo(2);
    nodo_t *nodo_3 = new_nodo(3);

    assert(false == empilhar(pilha_sem_new, nodo_1));

    pilha_t *pilha = new_pilha();
    assert(pilha->qtd_nodos == 0);
    assert(pilha->topo == NULL);


    assert(empilhar(pilha, nodo_1));
    assert(pilha->topo->valor == 1);
    assert(pilha->qtd_nodos == 1);

    assert(empilhar(pilha, nodo_2));
    assert(pilha->topo->valor == 2);
    assert(pilha->qtd_nodos == 2);

    assert(empilhar(pilha, nodo_3));
    assert(pilha->topo->valor == 3);
    assert(pilha->qtd_nodos == 3);

    // Teste de Desempilhar

    assert(desempilhar(pilha));
    assert(pilha->topo->valor == 2);
    assert(pilha->qtd_nodos == 2);

    assert(desempilhar(pilha));
    assert(pilha->topo->valor == 1);
    assert(pilha->qtd_nodos == 1);

    assert(desempilhar(pilha));
    assert(pilha->topo == NULL);
    assert(pilha->qtd_nodos == 0);
    
    assert(desempilhar(pilha) == false);
    assert(pilha->topo == NULL);
    assert(pilha->qtd_nodos == 0);

    free(pilha);
}

int main(void)
{
    empilhar_test();
    desempilhar_test();

    return 0;
}