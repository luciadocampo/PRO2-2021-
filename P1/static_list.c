/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#include "static_list.h"


#include "string.h"
#include <stdbool.h>



void createEmptyList(tList *L) {
    /* Objetivo:crear una lista vacía
     * Postcondiciones: la lista queda inicializada y no contiene elementos
     */
    L->LastPos = LNULL;
}
//**********************************************
bool isEmptyList(tList L) {
    /* Objetivo:determina si la lista está vacía
     * Precondición: la lista debe estar previamente inicializada
     */
    return L.LastPos == LNULL;
}

//**********************************************
tPosL first(tList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    if (isEmptyList(L)) {
        return LNULL;
    } else {
        return 0;
    }
}

//**********************************************
tPosL last(tList L) {
    /* Objetivo: devuelve la posición del último elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    return L.LastPos;
}

//**********************************************
tPosL next(tPosL p, tList L) {
    /* Objetivo: devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente)
     * Precondiciones: la posición indicada es una posición válida en la lista
     */
    if (p == L.LastPos)
        return LNULL;
    else
        return ++p;
}

//**********************************************
tPosL previous(tPosL p, tList L) {
    /* Objetivo: devuelve la posición en la lista del elemento anterior al de la posición indicada ( o LNULL si la posición no tiene anterior)
     * Precondiciones:la posición indicada es una posición válida en la lista
     */
    if (p != first(L)) {
        return --p;
    } else return LNULL;
}
//**********************************************
bool insertItem(tItemL item, tPosL pos, tList *L) {
    /* Objetivo:inserta un elemento en la lista antes de la posición indicada
     * Salidas: true si el elemento fue insertado; false en caso contrario
     * Precondiciones: la posición indicada es una posición válida en la lista o bien nula
     * Postcondiciones: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado
     */

    if (L->LastPos == MAX - 1) {
        return false;

    } else {//insertamos el item

        if (isEmptyList(
                *L)) {//Si la lista está vacía, aumentamos  en 1 y ponemos en la pos  0.
            L->LastPos++;
            L->data[0] = item;
        } else {
            L->LastPos++;//Posicion +1.
            for (pos = L->LastPos - 1; (pos >= 0) && (strcmp(item.nickname, L->data[pos].nickname) <0); pos--) {

                L->data[pos + 1] = L->data[pos];//
            }
            L->data[pos + 1] = item;

        }
        return true;

    }
}

//**********************************************
void deleteAtPosition(tPosL p, tList *L) {
    /* Objetivo: elimina de la lista el elemento que ocupa la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     * Postcondiciones: las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber cambiado
     */
    tPosL i;
    L->LastPos--;
    for (i = p; i <= L->LastPos; i++)
        L->data[i] = L->data[i + 1];
}

//**********************************************
tItemL getItem(tPosL p, tList L) {
    /* Objetivo: devuelve el contenido del elemento que ocupa la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     */
    return L.data[p];
}

//**********************************************
void updateItem(tItemL d, tPosL p, tList *L) {
    /* Objetivo: modifica el contenido del elemento situado en la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     * Postcondiciones: el orden de los elementos de la lista no se ve modificado
     */
    L->data[p].numPlay = d.numPlay;

}

//**********************************************
tPosL findItem(tNickname d, tList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado ( o LNULL si no existe tal elemento)
     * Precondición: la lista debe estar previamente inicializada
     */
    if (isEmptyList(L) == true) {
        return LNULL;
    } else {
        for (tPosL i = first(L); (i <= L.LastPos); i++) {
            if (strcmp(L.data[i].nickname, d) == 0) {
                return i;
            }
        }
        return LNULL;
    }
}