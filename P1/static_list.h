/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "stdio.h"
#include <stdbool.h>
#include "types.h"

#define LNULL -1

#define MAX 25


typedef int tPosL;
typedef struct  {
    tItemL data[25];
    tPosL LastPos;
} tList;

void createEmptyList (tList*);
bool insertItem(tItemL, tPosL, tList*);
bool copyList(tList, tList*);
void updateItem(tItemL, tPosL, tList*);
void deleteAtPosition(tPosL, tList*);
//void deleteList(tList*);
tPosL findItem(tNickname, tList);
bool isEmptyList(tList);
tItemL getItem(tPosL, tList);
tPosL first(tList);
tPosL last(tList);
tPosL previous(tPosL, tList);
tPosL next(tPosL, tList);

#endif
