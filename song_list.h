/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Iago Fernández Blanco LOGIN 1: iago.fernandez.blanco@udc.es
 * AUTHOR 2: Xoán Suárez Mayta LOGIN 2: xoan.suarez@udc.es
 * GROUP: 4.2
 * DATE: 26 / 04 / 24
 */

#ifndef SONG_LIST_H
#define SONG_LIST_H
#define MAX 25
#define NULLS -1

#include "types.h"

/* Write your code here... */


typedef tSong tItemS;

typedef int tPosS;
typedef struct{
    tItemS data[MAX];
    tPosS LastPos;
}tListS;

void createEmptyListS(tListS *L);
bool isEmptyListS(tListS L);
tPosS firstS(tListS L);
tPosS lastS(tListS L);
tPosS nextS(tPosS p, tListS L);
tPosS previousS(tPosS p,tListS L );
bool insertItemS(tItemS m, tPosS p, tListS *L);
void deleteAtPositionS(tPosS p, tListS *L);
tItemS getItemS(tPosS p, tListS L);
void updateItemS(tItemS d,tPosS p ,tListS *L );
tPosS findItemS(tSongTitle d, tListS L);

#endif
