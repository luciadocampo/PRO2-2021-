/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */



#include "user_list.h"

void createEmptyList(tUserList *L) {
    /* Objetivo:crear una lista vacía
     * Postcondiciones: la lista queda inicializada y no contiene elementos
     */
    *L = NULL_USER;
}

//**********************************************
bool isEmptyList(tUserList L) {
    /* Objetivo:determina si la lista está vacía
     * Precondición: la lista debe estar previamente inicializada
     */
    return L == NULL_USER; //Iguala la lista a LNULL para comprobar si está vacía
}

//**********************************************
tUserPos first(tUserList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    return L;
}

//**********************************************
tUserPos last(tUserList L) {
    /* Objetivo: devuelve la posición del último elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    tUserPos p;
    p = L;
    while (p->next != NULL_USER) //recorre la lista hasta llegar a la última posición
        p = p->next;
    return p;
}

//**********************************************
tUserPos next(tUserPos p, tUserList L) {
    /* Objetivo: devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente)
     * Precondiciones: la posición indicada es una posición válida en la lista
     */
    return p->next;
}

//**********************************************
tUserPos previous(tUserPos p, tUserList L) {
    /* Objetivo: devuelve la posición en la lista del elemento anterior al de la posición indicada ( o LNULL si la posición no tiene anterior)
     * Precondiciones:la posición indicada es una posición válida en la lista
     */
    tUserPos q;
    if (p == L)
        return NULL_USER;
    else {
        q = L;
        while (q->next != p)
            q = q->next;
        return q;
    }
}
//**********************************************
bool createNode(tUserPos *p) {
    /* Objetivo: Crear nodo
     * Entradas: Posición
     * Salidas: Nodo creado
     * Precondiciones: Tiene que existir la posición
     * Postcondiciones: Las posiciones varían
     */
    *p = malloc(sizeof(**p));
    return *p != NULL_USER;
}
//**********************************************
tUserPos findPosition(tUserList L, tUserItem d){
    /* Objetivo: Encontrar una posición en la lista
     * Entradas: Lista,Item
     * Salidas: Posición
     * Precondiciones: La posición tiene que existir
     */
    tUserPos p;
    p=L;
    while((p->next!=NULL_USER)&&(strcmp((p->next->data).nickname, d.nickname) < 0))
        p=p->next;
    return p;
}
//**********************************************
tUserPos findItem(tNickname d, tUserList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado ( o LNULL si no existe tal elemento)
     * Precondición: la lista debe estar previamente inicializada
     */
    tUserPos q;
        for (q = L; (q != NULL_USER) && (strcmp(q->data.nickname, d) < 0); q = q->next);
        if (q != NULL_USER && (strcmp(q->data.nickname, d) == 0))
            return q;
        else
            return NULL_USER;
}
//*************************************************************************

bool insertItem(tUserItem d, tUserList *L) {
    /* Objetivo:inserta un elemento en la lista antes de la posición indicada
     * Salidas: true si el elemento fue insertado; false en caso contrario
     * Precondiciones: la posición indicada es una posición válida en la lista o bien nula
     * Postcondiciones: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado
     */
    tUserPos pos, q;
        if (!createNode(&q)) { //creamos el nodo y preguntamos si se ha podido o no
            return false;
        } else {
            q->data = d;
            q->next = NULL_USER;
            if (*L == NULL_USER) {  //en el caso de lista vacia insertamos
                *L = q;
            }
            else if (strcmp(d.nickname, (*L)->data.nickname) < 0){    //insertar al principio
                    q->next = *L;
                    *L = q;
            }
            else {
                    pos = findPosition(*L,d);
                    q->next = pos->next;  //asigna nulo si insertamos al final
                    pos->next = q;
                }
            }
            return true;
        }


//**********************************************

void deleteAtPosition(tUserPos p, tUserList *L) {
    /* Objetivo: elimina de la lista el elemento que ocupa la posición indicada
    * Precondiciones: la posición indicada es una posición válida en la lista
    * Postcondiciones: las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber cambiado
    */
    tUserPos q;
    if (p == *L)
        *L = (*L)->next;
    else if (p->next == NULL_USER) {
        for (q = *L; q->next != p; q = q->next);
        q->next = NULL_USER;
    } else {
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

//**********************************************
tUserItem getItem (tUserPos p, tUserList L) {
    /* Objetivo: devuelve el contenido del elemento que ocupa la posición indicada
    * Precondiciones: la posición indicada es una posición válida en la lista
    */
    return p->data;
}

//**********************************************
void updateItem (tUserItem n, tUserPos p, tUserList *L){
    /* Objetivo: modifica el contenido del elemento situado en la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     * Postcondiciones: el orden de los elementos de la lista no se ve modificado
     */
    p->data = n;
}


