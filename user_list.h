/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Iago Fernández Blanco LOGIN 1: iago.fernandez.blanco@udc.es
 * AUTHOR 2: Xoán Suárez Mayta LOGIN 2: xoan.suarez@udc.es
 * GROUP: 4.2
 * DATE: 26 / 04 / 24
 */

#ifndef USER_LIST_H
#define USER_LIST_H
#define NULLU NULL

#include "types.h"
#include "song_list.h"

/* Write your code here... */
typedef struct tNode* tPosU;

typedef struct tItemU {
    tUserName userName;
    tPlayTime totalPlayTime;
    tUserCategory userCategory;
    tListS songListS;
} tItemU;

struct tNode{
    tItemU data;
    tPosU next;
};
typedef tPosU tListU;


void createEmptyListU(tListU *L);
bool isEmptyListU(tListU L);
tPosU firstU(tListU L);
tPosU lastU(tListU L);
tPosU nextU(tPosU p, tListU L);
tPosU previousU(tPosU p,tListU L );
bool insertItemU(tItemU m, tListU *L);
void deleteAtPositionU(tPosU p, tListU *L);
tItemU getItemU(tPosU p, tListU L);
void updateItemU(tItemU d,tPosU p ,tListU *L );
tPosU findItemU(tUserName d, tListU L);


#endif
