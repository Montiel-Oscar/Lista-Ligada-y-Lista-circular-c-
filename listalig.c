#include "listalig.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#pragma GCC diagnostic ignored "-Wunused-result"

#define RED "\033[31m"
#define WHITE "\033[1;37m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"
#define NEGRITA "\033[1m"
#define SUB "\033[4m"
#define REV "\033[7m"

listal *ListaVacia() {
  listal *l;
  l = (listal *)malloc(sizeof(listal));
  l->len = 0;
  l->head = l->tail = NULL;
  return l;
}

bool EsVacia(listal *l) { return (l->head == NULL && l->tail == NULL); }

listal *Agregar(listal *l, int e, int p) {
  // comprobar que la posición es valida
  if (p < 0 || p > l->len) {
    printf("Posición inválida\n");
    return l;
  }
  // Si p es correcta, crear el nodo
  nodo *newNode = crear_nodo(e);

  // Agregar e dependiendo de p
  if (p == 0) {
    newNode->sig = l->head;
    l->head = newNode;
    if (l->len == 0)
      l->tail = newNode; // si la lista está vacía, actualiza tail
  } else if (p == l->len) {
    l->tail->sig = newNode;
    l->tail = newNode;
    newNode->sig = NULL;
  } else {
    nodo *tmp = l->head;
    for (int i = 0; i < p - 1; i++)
      tmp = tmp->sig;
    newNode->sig = tmp->sig;
    tmp->sig = newNode;
  }
  // Terminando de insertar el elemento
  l->len++;
  return l;
}

listal *Eliminar(listal *l, int p) {

  if (l == NULL || p > l->len || p < 0) {
    printf("\nNo se puede eliminar\n");
    return l;
  }

  nodo *tmp;
  tmp = l->head;

  if (p == 0) {
    l->head = l->head->sig;
    free(tmp);
  } else if (p == l->len - 1) {
    while (tmp->sig != l->tail) {
      tmp = tmp->sig;
    }
    free(l->tail);
    l->tail = tmp;
    l->tail->sig = NULL;
  } else {
    nodo *tmp2;
    tmp2 = l->head;
    for (int i = 0; i < p - 1; i++)
      tmp2 = tmp2->sig;
    tmp = tmp2->sig;
    tmp2->sig = tmp->sig;
    free(tmp);
  }

  l->len--;
  return l;
}
int Buscar(listal *l, int e) {
  nodo *tmp = l->head;
  int pos = 0;

  while (tmp != NULL) {
    if (tmp->dato == e) {
      return pos;
    }
    tmp = tmp->sig;
    pos++;
  }

  return -1;
}

int Localizar(listal *l, int p) {
  if (EsVacia(l)) {
    printf(RED "La lista está vacía\n" RESET);
    return -1;
  }
  if (p < 0 || p >= l->len) {
    printf(RED "La posición especificada está fuera del rango válido\n" RESET);
    return -1;
  }

  nodo *tmp = l->head;
  int contador = 0;
  printf("Lista actual\n");
  imprimir_lista(l);
  for (; tmp != NULL; tmp = tmp->sig) {
    if (contador == p) {
      return tmp->dato;
    }
    contador++;
  }

  return -1;
}

void imprimir_lista(listal *l) {
  nodo *tmp = l->head;
  if (!EsVacia(l)) {
    printf("[ ");
    for (; tmp != NULL; tmp = tmp->sig) {
      printf("%d ", tmp->dato);
    }
    printf("]\n");
  } else {
    printf("[ ]\n");
  }
}
void Vaciar(listal *l) {
  if (EsVacia(l)) {
    printf("\nLa lista ya es vacia\n");
    return;
  }
  nodo *tmp = l->head;
  while (tmp != NULL) {
    nodo *borrar = tmp;
    tmp = tmp->sig;
    free(borrar);
  }
  l->head = NULL;
  l->tail = NULL;
  l->len = 0;
}

void menu_lista() {
  listal *l;
  int e, p;
  l = ListaVacia();
  int op;
  do {
    printf("\033[1;32m\t\t###MENU LISTA SIMPLE###\033[0m \n");
    printf("1. " MAGENTA "Agregar elemento\n" RESET);
    printf("2. " MAGENTA "Eliminar elemento\n" RESET);
    printf("3. " MAGENTA "Localizar elemento\n" RESET);
    printf("4. " MAGENTA "Buscar elemento\n" RESET);
    printf("5. " MAGENTA "Mostrar Lista\n" RESET);
    printf("6. " MAGENTA "Vaciar\n" RESET);
    printf("7. " MAGENTA "Salir\n" RESET);
    printf("Seleccione una opcion: ");
    scanf("%d", &op);
    switch (op) {
    case 1:
      printf(RED "\tAGREGAR ELEMENTO\n" RESET);
      printf("Ingrese el valor del elemento que quiere introducir: \n");
      scanf("%i", &e);
      printf("Ingrese la posición en donde quiere introducir el elemento "
             "(inicia en 0): \n");
      scanf("%i", &p);
      Agregar(l, e, p);
      imprimir_lista(l);

      break;
    case 2:
      printf(RED "\tELIMINAR ELEMENTO\n" RESET);

      printf("Ingrese la posición en donde quiere eliminar el elemento: \n");
      scanf("%i", &p);

      Eliminar(l, p);

      imprimir_lista(l);
      break;
    case 3:
      printf(RED "\tLOCALIZAR ELEMENTO\n" RESET);
      printf("Ingrese la posiciòn del elemento que quiere obtener: \n");
      scanf("%i", &p);
      printf("El valor de la posición %i es %i\n", p, Localizar(l, p));
      break;
    case 4:
      printf(RED "\tBUSCAR ELEMENTO\n" RESET);
      printf("Ingrese el elemento para saber su posición:\n");
      scanf("%i", &e);
      printf("La posición del elemento %i es %i\n", e, Buscar_lc(l, e));
      break;
    case 5:
      printf(RED "\tMOSTRAR LISTA SIMPLE\n" RESET);
      imprimir_lista(l);
      break;
    case 6:
      printf(RED "\tVACIAR\n" RESET);
      Vaciar(l);
      imprimir_lista(l);
      break;
    case 7:
      printf(CYAN "Saliendo del menu de la lista simple...\n" RESET);
      break;
    default:
      printf(RED "Opcion invalida, intente de nuevo\n" RESET);
      break;
    }
  } while (op != 7);
}
