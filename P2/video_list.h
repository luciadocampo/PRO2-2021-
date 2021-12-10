/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#ifndef P2_VIDEO_LIST_H
#define P2_VIDEO_LIST_H

#include <stdbool.h>

#define NULL_VIDEO -1

#define MAX 25

#include "types.h"
#include "string.h"
#include "stdlib.h"

typedef int tVideoPos;
typedef struct tVideo tVideoItem;

typedef struct {
    tVideoItem data[25];
    tVideoPos LastPos;
}tVideoList;

void createEmptyListV (tVideoList*);
bool isEmptyListV (tVideoList);
tVideoPos firstV (tVideoList);
tVideoPos lastV (tVideoList);
tVideoPos nextV (tVideoPos, tVideoList);
tVideoPos previousV (tVideoPos, tVideoList);
bool insertItemV (tVideoItem, tVideoPos, tVideoList*);
void deleteAtPositionV(tVideoPos, tVideoList*);
tVideoItem getItemV (tVideoPos, tVideoList);
void updateItemV (tVideoItem, tVideoPos, tVideoList*);
tVideoPos findItemV(tTitleVideo, tVideoList);

#endif //P2_VIDEO_LIST_H

