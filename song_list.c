/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Iago Fernández Blanco LOGIN 1: iago.fernandez.blanco@udc.es
 * AUTHOR 2: Xoán Suárez Mayta LOGIN 2: xoan.suarez@udc.es
 * GROUP: 4.2
 * DATE: 26 / 04 / 24
 */

#include "song_list.h"

/* Write your code here... */
#include "string.h"
#define NULLS -1

/* Write your code here... */
void createEmptyListS(tListS *L){
    //Objetivo: Crea una lista vacia
    //Entrada: Una Lista
    //Salida: LastPos incializado en LNULL
    //PostCD: La lista queda inicializada y no contiene elementos.
    L -> LastPos = NULLS;
}

bool isEmptyListS(tListS L){

    //Objetivo: Determina si la lista esta vacia
    //Entrada: Una Lista
    //Salida: True o False

    if(L.LastPos==NULLS) return(true);
    else return false;
}

tPosS firstS(tListS L){
    //Objetivo: Devuelve la posicion del primer elemento de la lista
    //Entrada: Una Lista
    //Salida: La primera posicion de la lista
    //PreCD: La lista no está vacía.
    return 0;
}

tPosS lastS(tListS L){
    //Objetivo: Devuelve la posicion del ultimo elemento de la lista
    //Entrada: Una lista
    //Salida: La ultima posicion de la lista
    //PreCD: La lista no está vacía.
    return L.LastPos;
}

tPosS nextS(tPosS p, tListS L){
    //Objetivo: Devuelve la posicion en la lista del elemento siguiente al de la posicio
    //Entradas: Una posicion de la lista y la lista
    //Salida: El elemento siguiente de la lista
    //PreCD: La posición indicada es una posición válida en la lista.
    if(p==L.LastPos) {
        return NULLS;
    }
    else return ++p;
}

tPosS previousS(tPosS p, tListS L){
    //Objetivo: Devuelve la posicion en la lista del elemento anterior al de la posicion
    //Entradas: Una posicion de la lista y la lista
    //Salida: La posicion anterior de la lista o NULL
    //PreCD: La posición indicada es una posición válida en la lista.

    return --p;
}

bool insertItemS(tItemS m, tPosS p, tListS *L){
    //Objetivo: Inserta un elemento en la lista antes de la posicion indicada. Si la posicion es LNULL se añade al final
    //Entradas: Un elemento de la lista, una posicion de la lista y una lista
    //Salidas: True o False
    //PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
    //PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
    tPosS i;
    if(L -> LastPos == (MAX-1)) return false;
    else{
        L -> LastPos++;
        if(p==NULLS){
            L -> data[L->LastPos] = m;
        }
        else{
            for (i = L->LastPos; i > p ; i--) {
                L->data[i]=L->data[i-1];
            }
            L->data[p]=m;
        }
        return true;
    }
}

void deleteAtPositionS(tPosS p, tListS *L){
    //Objetivo: Elimina de la lista el elemento que ocupa la posicion indicada
    //Entradas: Una posicion de la lista y una lista
    //Salidas: La lista sin el elemento situado en la posicion especificada
    //PreCD: La posición indicada es una posición válida en la lista.
    //PostCD: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
    tPosS i;
    for(i=p; i<L->LastPos; i++){
        L->data[i] = L->data[i+1];
    }
    L->LastPos=L->LastPos-1;
}

tItemS getItemS(tPosS p, tListS L){
    //Objetivo: Devuelve el contenido del elemento que ocupa la posicion indicada
    //Entradas: Una posicion de la lista y una lista
    //Salidas: El contenido de la posicion especificada
    //PreCD: La posición indicada es una posición válida en la lista.
    return L.data[p];
}

void updateItemS(tItemS d,tPosS p , tListS *L){
    //Objetivo: Modifica el contido del elemento situado en la posicion
    //Entradas: Un elemento, una posicion de la lista y una lista
    //Salidas: La lista con el elemento actualizado en la posicion especificada
    //PreCD: La posición indicada es una posición válida en la lista.
    //PostCD: El orden de los elementos de la lista no se ve modificado.
    L->data[p]=d;
}

tPosS findItemS(tSongTitle d, tListS L) {
    //Objetivo: Devuelve la posicion del primer elemento de la lista cuya nombre de usuario se corresponda con el indicado(o LNULL si no existe tal elemento)
    //Entradas: Un elemento y una lista
    //Salida: La posicion del elemento deseado
    tPosS i;
    if (isEmptyListS(L)) {
        return NULLS;
    } else {
        for (i = 0; (strcmp(L.data[i].songTitle, d)) && (i <= L.LastPos); i++);
        if (i <= L.LastPos) return i;
        else return NULLS;
    }
}