#ifndef __NODO_H__
#define __NODO_H__

typedef struct _nodo nodo;
struct _nodo{
    int dato;
    nodo *sig;
};
nodo *crear_nodo(int dato);
nodo* borrar_nodo(nodo *n);

#endif
