#ifndef __LISTALIG_H__
#define __LISTALIG_H__
#include "nodo.h"
#include <stdbool.h>

struct _listaligada{
    nodo *head;
    nodo *tail;
    int len;
};
typedef struct _listaligada listal;

//Prototipos
void menu_lista();
listal *ListaVacia();
bool EsVacia(listal*);
listal *Agregar(listal *l, int e, int p);
listal* Eliminar(listal*,int);
int Buscar(listal*,int);
int Localizar(listal*,int);
void Vaciar(listal*);
void imprimir_lista(listal*);

#endif
