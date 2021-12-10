/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#ifndef P2_USER_LIST_H
#define P2_USER_LIST_H

#include <stdbool.h>

#define NULL_USER NULL

#include "types.h"
#include "string.h"
#include "video_list.h"
#include "stdlib.h"

typedef struct tNode *tUserList;
typedef struct tNode *tUserPos;
typedef struct tUserItem *tNode;

typedef struct tUserItem {
    tNickname nickname;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tVideoList videoList;
} tUserItem;

struct tNode {
    tUserItem data;
    struct tNode *next;
};

void createEmptyList(tUserList *);
bool isEmptyList(tUserList);
tUserPos first(tUserList);
tUserPos last(tUserList);
tUserPos next(tUserPos, tUserList);
tUserPos previous(tUserPos, tUserList);
bool insertItem(tUserItem, tUserList *);
void deleteAtPosition(tUserPos, tUserList *);
tUserItem getItem(tUserPos, tUserList);
void updateItem(tUserItem, tUserPos, tUserList *);
tUserPos findItem(tNickname, tUserList);
tUserPos findPosition(tUserList, tUserItem);

#endif