/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#include "dynamic_list.h"


void createEmptyList(tList *L) {
    /* Objetivo:crear una lista vacía
     * Postcondiciones: la lista queda inicializada y no contiene elementos
     */
    *L = LNULL;
}

//**********************************************
bool isEmptyList(tList L) {
    /* Objetivo:determina si la lista está vacía
     * Precondición: la lista debe estar previamente inicializada
     */
    return L == LNULL; //Iguala la lista a LNULL para comprobar si está vacía
}

//**********************************************
tPosL first(tList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    return L;
}

//**********************************************
tPosL last(tList L) {
    /* Objetivo: devuelve la posición del último elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    tPosL p;
    p = L;
    while (p->next != LNULL) //recorre la lista hasta llegar a la última posición
        p = p->next;
    return p;
}

//**********************************************
tPosL next(tPosL p, tList L) {
    /* Objetivo: devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente)
     * Precondiciones: la posición indicada es una posición válida en la lista
     */
    return p->next;
}

//**********************************************
tPosL previous(tPosL p, tList L) {
    /* Objetivo: devuelve la posición en la lista del elemento anterior al de la posición indicada ( o LNULL si la posición no tiene anterior)
     * Precondiciones:la posición indicada es una posición válida en la lista
     */
    tPosL q;
    if (p == L)
        return LNULL;
    else {
        q = L;
        while (q->next != p)
            q = q->next;
        return q;
    }
}
//**********************************************
bool createNode(tPosL *p) {
    /* Objetivo: Crear nodo
     * Entradas: Posición
     * Salidas: Nodo creado
     * Precondiciones: Tiene que existir la posición
     * Postcondiciones: Las posiciones varían
     */
    *p = malloc(sizeof(**p));
    return *p != LNULL;
}
//**********************************************
tPosL findPosition(tList L, tItemL d){
    /* Objetivo: Encontrar una posición en la lista
     * Entradas: Lista,Item
     * Salidas: Posición
     * Precondiciones: La posición tiene que existir
     */

    tPosL p; //Posición en la lista
    p=L;
    while((p->next!=LNULL)&&(strcmp((p->next->data).nickname,d.nickname) < 0))
        p=p->next;
    return p;
}

//*************************************************************************

bool insertItem(tItemL d, tPosL pos, tList *L) {
    /* Objetivo:inserta un elemento en la lista antes de la posición indicada
     * Salidas: true si el elemento fue insertado; false en caso contrario
     * Precondiciones: la posición indicada es una posición válida en la lista o bien nula
     * Postcondiciones: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado
     */
    tPosL q;
    if (!createNode(&q))  //creamos el nodo y preguntamos si se ha podido o no
        return false;
    else {
        q->data = d;
        q->next = LNULL;
        if (*L == LNULL)   //en el caso de lista vacia insertamos
            *L = q;
        else if (strcmp(d.nickname,(*L)->data.nickname)<0) {   //insertar al principio
            q->next = *L;
            *L = q;
        } else {
            pos = findPosition(*L,d);
            q->next = pos->next;  //asigna nulo si insertamos al final
            pos->next = q;}
        return true;
    }
}
//**********************************************
void deleteAtPosition(tPosL p, tList *L) {
    /* Objetivo: elimina de la lista el elemento que ocupa la posición indicada
    * Precondiciones: la posición indicada es una posición válida en la lista
    * Postcondiciones: las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber cambiado
    */
    tPosL q;
    if (p == *L)
        *L = (*L)->next;
    else if (p->next == LNULL) {
        for (q = *L; q->next != p; q = q->next);
        q->next = LNULL;
    } else {
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

//**********************************************
tItemL getItem(tPosL p, tList L) {
    /* Objetivo: devuelve el contenido del elemento que ocupa la posición indicada
    * Precondiciones: la posición indicada es una posición válida en la lista
    */
    return p->data;
}

//**********************************************
void updateItem(tItemL n, tPosL p, tList *L) {
    /* Objetivo: modifica el contenido del elemento situado en la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     * Postcondiciones: el orden de los elementos de la lista no se ve modificado
     */
    tItemL dato;
    dato = getItem(p, *L);
    dato.numPlay = n.numPlay;
    p->data = dato;
}

//**********************************************
tPosL findItem(tNickname d, tList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado ( o LNULL si no existe tal elemento)
     * Precondición: la lista debe estar previamente inicializada
     */
    tPosL q;
    if (isEmptyList(L))
        q = LNULL;
    else {
        for (q = L; (strcmp(q->data.nickname, d) != 0) && (q->next != LNULL);
             q = q->next) {
        }
        if (strcmp(q->data.nickname, d) != 0)
            q = LNULL;
    }
    return q;
}