#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct nodo
{
    struct nodo *nodo_anterior;
    int valor;
} nodo_t;

nodo_t *new_nodo(int valor)
{
    nodo_t *n = (nodo_t *)malloc(sizeof(nodo_t));

    n->nodo_anterior = NULL;
    n->valor = valor;

    return n;
}

typedef struct
{
    nodo_t *inicio;
    nodo_t *fim;
    int qtd_elementos;
} fila_t;

fila_t *new_fila() 
{
    fila_t *f = (fila_t *)malloc(sizeof(fila_t));

    f->inicio = NULL;
    f->fim = NULL;
    f->qtd_elementos = 0;

    return f;
}

bool vazia_esta_a(fila_t *fila)
{
    if (fila == NULL)
    {
        perror("A fila não foi alocada");
        return false;
    }

    return fila->qtd_elementos == 0;
}

bool enfileirar(fila_t *fila, nodo_t *nodo)
{
    bool status = false;

    if (fila == NULL)
    {
        perror("Não é possível enfileira porque a fila não foi alocada");
        status = false;
    }
    else if (vazia_esta_a(fila))
    {
        fila->fim = nodo;
        fila->inicio = fila->fim;

        fila->qtd_elementos++;
        status = true;
    }
    else
    {
        fila->fim->nodo_anterior = nodo;
        fila->fim = nodo;

        fila->qtd_elementos++;
        status = true;
    }

    return status;
}

void enfileirar_test()
{
    fila_t *fila_sem_new = NULL;
    fila_t *fila = new_fila();

    nodo_t *nodo_1 = new_nodo(1);
    nodo_t *nodo_2 = new_nodo(2);
    nodo_t *nodo_3 = new_nodo(3);

    assert(enfileirar(fila_sem_new, nodo_1) == false);
    assert(fila->qtd_elementos == 0);
    assert(fila->inicio == NULL);
    assert(fila->fim == NULL);

    assert(enfileirar(fila, nodo_1));
    assert(fila->qtd_elementos == 1);
    assert(fila->inicio == nodo_1);
    assert(fila->fim == nodo_1);

    assert(enfileirar(fila, nodo_2));
    assert(fila->qtd_elementos == 2);
    assert(fila->inicio == nodo_1);
    assert(fila->fim == nodo_2);

    assert(enfileirar(fila, nodo_3));
    assert(fila->qtd_elementos == 3);
    assert(fila->inicio == nodo_1);
    assert(fila->fim == nodo_3);

    free(nodo_1);
    free(nodo_2);
    free(nodo_3);

    free(fila);
}

void retornar_tamanho_test()
{
// fila->qtd_elementos;
}

void retornar_inicio_test()
{
// inicio_da(fila);
}

bool desenfileirar(fila_t *fila);

void desenfileirar_test()
{
//  INCIALIZANDO E CONFIGURANDO A FILA PREIMEIRO

    fila_t *fila_sem_new = NULL;
    fila_t *fila = new_fila();

    nodo_t *nodo_1 = new_nodo(1);
    nodo_t *nodo_2 = new_nodo(2);
    nodo_t *nodo_3 = new_nodo(3);

    assert(enfileirar(fila_sem_new, nodo_1) == false);
    assert(fila->qtd_elementos == 0);
    assert(fila->inicio == NULL);
    assert(fila->fim == NULL);

    assert(enfileirar(fila, nodo_1));
    assert(fila->qtd_elementos == 1);
    assert(fila->inicio == nodo_1);
    assert(fila->fim == nodo_1);

    assert(enfileirar(fila, nodo_2));
    assert(fila->qtd_elementos == 2);
    assert(fila->inicio == nodo_1);
    assert(fila->fim == nodo_2);

    assert(enfileirar(fila, nodo_3));
    assert(fila->qtd_elementos == 3);
    assert(fila->inicio == nodo_1);
    assert(fila->fim == nodo_3);

//  AGORA SIM PODEMOS DESENFILEIRAR

    assert(desenfileirar(fila_sem_new) == false);

    assert(desenfileirar(fila));
    assert(fila->qtd_elementos == 2);
    assert(fila->inicio == nodo_2);
    assert(fila->fim == nodo_3);

    assert(desenfileirar(fila));
    assert(fila->qtd_elementos == 1);
    assert(fila->inicio == nodo_3);
    assert(fila->fim == nodo_3);

    assert(desenfileirar(fila));
    assert(fila->qtd_elementos == 0);
    assert(fila->inicio == NULL);
    assert(fila->fim == NULL);

    assert(desenfileirar(fila) == false);
    assert(fila->qtd_elementos == 0);
    assert(fila->inicio == NULL);
    assert(fila->fim == NULL);

    free(fila);
}

bool desenfileirar(fila_t *fila)
{
    bool status = false;

    if (fila == NULL)
    {
        perror("Não é possível desenfileira porque a fila não foi alocada");
        status = false;
    }
    else if (vazia_esta_a(fila))
    {
        perror("Não é possível desenfileira porque a fila está vazia");
        status = false;
    }
    else if (fila->inicio == fila->fim)
    {
        free(fila->inicio);
        fila->inicio = NULL;
        fila->fim = NULL;
        fila->qtd_elementos--;
        status = true;
    }
    else
    {
        nodo_t *nodo_desenfileirando = fila->inicio;
        fila->inicio = fila->inicio->nodo_anterior;

        free(nodo_desenfileirando);
        fila->qtd_elementos--;
        status = true;
    }

    return status;
}

int main()
{
   enfileirar_test();
   desenfileirar_test();
}