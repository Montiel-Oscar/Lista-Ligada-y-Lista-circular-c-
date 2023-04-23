#ifndef __LISTACIR_H__
#define __LISTACIR_H__
#include "nodo.h"
#include <stdbool.h>

struct _listacir{
    nodo *head;
    nodo *tail;
    int len;
};
typedef struct _listacir listacir;

//prototipos, lc == lista circular
void menu_listacir();
listacir* ListaVavia_lc();
bool EsVacia_lc(listacir*);
listacir* Agregar_lc(listacir *l, int e, int p);
listacir* Eliminar_lc(listacir *l, int);
int Buscar_lc(listacir*,int);
int Localizar_lc(listacir*,int);

void imprimir_lista_lc(listacir *l);


#endif
