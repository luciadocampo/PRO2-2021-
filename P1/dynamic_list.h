/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include <stdbool.h>

#define LNULL NULL

#include <stdio.h>
#include "types.h"
#include "string.h"
#include "stdlib.h"

typedef struct tNode *tList;
typedef struct tNode *tPosL;
typedef struct tItemL *tNode;

struct tNode {
    tItemL data;
    struct tNode *next;
};

void createEmptyList(tList *);

bool isEmptyList(tList);

tPosL first(tList);

tPosL last(tList);

tPosL next(tPosL, tList);

tPosL previous(tPosL, tList);

bool insertItem(tItemL,tPosL pos, tList *);

void deleteAtPosition(tPosL, tList *);

tItemL getItem(tPosL, tList);

void updateItem(tItemL, tPosL, tList *);

tPosL findItem(tNickname, tList);



#endif