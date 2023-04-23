#include "listacir.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

listacir *ListaVacia_lc() {
  listacir *l = (listacir *)malloc(sizeof(listacir));
  l->head = l->tail = NULL;
  l->len = 0;
  return l;
}

bool EsVacia_lc(listacir *l) { return (l->head == NULL && l->tail == NULL); }

listacir *Agregar_lc(listacir *l, int e, int p) {
  nodo *newNode = crear_nodo(e);
  if (p < 0 || p > l->len) {
    printf("La posición no es válida\n");
    return l;
  }
  // si la lista está vacía
  if (l->head == NULL) {
    l->head = newNode;
    l->tail = newNode;
    newNode->sig = newNode;
  } /*si se agrega en la posición 0*/ else if (p == 0) {
    newNode->sig = l->head;
    l->tail->sig = newNode;
    l->head = newNode;
  } /*si se agrega al final*/ else if (p == l->len) {
    l->tail->sig = newNode;
    newNode->sig = l->head;
    l->tail = newNode; // esta cambia
    /*es lo mismo que agregar en cero. solo cambia la lina 3*/
  } /*agregar en cualquier otro lado*/ else {
    nodo *tmp = l->head;
    for (int i = 0; i < p - 1; i++)
      tmp = tmp->sig;
    newNode->sig = tmp->sig;
    tmp->sig = newNode;
  }
  l->len++;
  return l;
}

listacir *Eliminar_lc(listacir *l, int p) {
  if (p < 0 || p >= l->len) {
    printf("Posición %d inválida\n", p);
    return l;
  }
  nodo *tmp = l->head;
  if (p == 0) {
    if (l->len == 1) {
      free(tmp);
      l->head = l->tail = NULL;
    } else {
      l->head = tmp->sig;
      l->tail->sig = l->head;
      free(tmp);
    }
  } else {
    for (int i = 0; i < p - 1; i++)
      tmp = tmp->sig;
    nodo *tmp2 = tmp->sig; // tmp2 será el nodo que eliminaremos
    tmp->sig = tmp2->sig;
    free(tmp2);
    if (p == l->len - 1)
      l->tail = tmp;
  }
  l->len--;
  return l;
}

int Localizar_lc(listacir *l, int p) {
  if (EsVacia_lc(l) || p >= l->len || p < 0) {
    printf("\nN0 se puede localizar el elemento\n");
    return -1;
  }
  nodo *tmp = l->head;
  for (int i = 0; i < p; i++)
    tmp = tmp->sig;
  return tmp->dato;
}

int Buscar_lc(listacir *l, int e) {
  nodo *tmp = l->head;
  int position = 0;
  do {
    if (tmp->dato == e)
      return position;
    tmp = tmp->sig;
    position++;
  } while (tmp != l->head);
  printf(RED "\nNo se encontró el elemento\n" RESET);
  return -1;
}

void imprimir_lista_lc(listacir *l) {
  nodo *tmp = l->head;
  if (!EsVacia(l)) {
    printf("[ ");
    for (; tmp != NULL; tmp = tmp->sig)
      printf("%d ", tmp->dato);
    printf("... %d ]\n", l->head->dato);
  } else {
    printf("[ ]\n");
  }
}

void menu_listacir() {
  int op, valor, e, p;
  listacir *l;
  l = ListaVacia();

  do {
    printf("\033[1;32m\t\t###MENU LISTA CIRCULAR###\033[0m \n");
    printf("1. " MAGENTA "Agregar elemento\n" RESET);
    printf("2. " MAGENTA "Eliminar elemento\n" RESET);
    printf("3. " MAGENTA "Localizar elemento\n" RESET);
    printf("4. " MAGENTA "Buscar elemento\n" RESET);
    printf("5. " MAGENTA "Mostrar Lista\n" RESET);
    printf("6. " MAGENTA "Salir\n" RESET);
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
      imprimir_lista_lc(l);
      break;
    case 2:
      printf(RED "\tELIMINAR ELEMENTO\n" RESET);
      printf("Ingrese la posición en donde quiere eliminar el elemento: \n");
      scanf("%i", &p);
      Eliminar_lc(l, p);
      imprimir_lista_lc(l);
      break;
    case 3:
      printf(RED "\tLOCALIZAR ELEMENTO\n" RESET);
      printf("Ingrese la posición del elemento que quiere obtener: \n");
      scanf("%i", &p);
      printf("El valor de la posición %i es %i\n", p, Localizar_lc(l, p));
      break;
    case 4:
      printf(RED "\tBUSCAR ELEMENTO\n" RESET);
      printf("Ingrese el elemento para saber su posición:\n");
      scanf("%i", &e);
      printf("La posición del elemento %i es %i\n", e, Buscar(l, e));
      break;
    case 5:
      printf(RED "\tMOSTRAR LISTA CIRCULAR\n" RESET);
      imprimir_lista_lc(l);
      break;
    case 6:
      printf(CYAN "Saliendo del menu de la lista circular...\n" RESET);
      break;
    default:
      printf(RED "Opcion invalida, intente de nuevo\n" RESET);
      break;
    }
  } while (op != 6);
}
