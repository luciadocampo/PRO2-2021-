/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */


#include "video_list.h"


void createEmptyListV (tVideoList *L) {
    /* Objetivo:crear una lista vacía
     * Postcondiciones: la lista queda inicializada y no contiene elementos
     */
    L->LastPos = NULL_VIDEO;
}
//**********************************************
bool isEmptyListV (tVideoList L) {
    /* Objetivo:determina si la lista está vacía
     * Precondición: la lista debe estar previamente inicializada
     */
    return L.LastPos == NULL_VIDEO;
}

//**********************************************
tVideoPos firstV (tVideoList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    if (isEmptyListV (L)) {
        return NULL_VIDEO;
    } else {
        return 0;
    }
}

//**********************************************
tVideoPos lastV (tVideoList L) {
    /* Objetivo: devuelve la posición del último elemento de la lista
     * Precondiciones: la lista no está vacía
     */
    return L.LastPos;
}

//**********************************************
tVideoPos nextV (tVideoPos p, tVideoList L) {
    /* Objetivo: devuelve la posición en la lista del elemento siguiente al de la posición indicada (o LNULL si la posición no tiene siguiente)
     * Precondiciones: la posición indicada es una posición válida en la lista
     */
    if (p == L.LastPos)
        return NULL_VIDEO;
    else
        return ++p;
}

//**********************************************
tVideoPos previousV (tVideoPos p, tVideoList L) {
    /* Objetivo: devuelve la posición en la lista del elemento anterior al de la posición indicada ( o LNULL si la posición no tiene anterior)
     * Precondiciones:la posición indicada es una posición válida en la lista
     */
    if (p != firstV(L)) {
        return --p;
    } else return NULL_VIDEO;
}
//**********************************************
bool insertItemV(tVideoItem item, tVideoPos p, tVideoList* L){

    tVideoPos i;
    if (L->LastPos==MAX-1)
        return false;
    else {
        L->LastPos++;
        if (p == NULL_VIDEO) { //Insertar al final
            L->data[L->LastPos] = item;
        } else {
            for (i = L->LastPos; i >=p+1; i--)
                L->data[i] = L->data[i-1];
            L->data[p] = item;
        }
        return true;

    }
}

//**********************************************
void deleteAtPositionV (tVideoPos p, tVideoList *L) {
    /* Objetivo: elimina de la lista el elemento que ocupa la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     * Postcondiciones: las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber cambiado
     */
    tVideoPos i;
    L->LastPos--;
    for (i = p; i <= L->LastPos; i++)
        L->data[i] = L->data[i + 1];
}

//**********************************************
tVideoItem getItemV (tVideoPos p, tVideoList L) {
    /* Objetivo: devuelve el contenido del elemento que ocupa la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     */
    return L.data[p];
}

//**********************************************
void updateItemV (tVideoItem item, tVideoPos p, tVideoList *L) {
    /* Objetivo: modifica el contenido del elemento situado en la posición indicada
     * Precondiciones: la posición indicada es una posición válida en la lista
     * Postcondiciones: el orden de los elementos de la lista no se ve modificado
     */
    L->data[p].playTime = item.playTime;

}
//**********************************************
tVideoPos findItemV (tTitleVideo d, tVideoList L) {
    /* Objetivo: devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado ( o LNULL si no existe tal elemento)
     * Precondición: la lista debe estar previamente inicializada
     */
    if (isEmptyListV(L) == true) {
        return NULL_VIDEO;
    } else {
        for (tVideoPos i = firstV(L); (i <= L.LastPos); i++) {
            if (strcmp(L.data[i].titleVideo, d) == 0) {
                return i;
            }
        }
        return NULL_VIDEO;
    }
}