/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Iago Fernández Blanco LOGIN 1: iago.fernandez.blanco@udc.es
 * AUTHOR 2: Xoán Suárez Mayta LOGIN 2: xoan.suarez@udc.es
 * GROUP: 4.2
 * DATE: 26 / 04 / 24
 */

#include "user_list.h"
#include "song_list.h"
#include "stdlib.h"
#include "string.h"

/* Write your code here... */



void createEmptyListU(tListU *L){
    //Objetivo: Crea una lista vacia
    //Entrada: Una Lista
    //Salida: LastPos incializado en LNULL
    //PostCD: La lista queda inicializada y no contiene elementos.
    *L=NULLU;
}


bool isEmptyListU(tListU L){
    //Objetivo: Determina si la lista esta vacia
    //Entrada: Una Lista
    //Salida: True o False
    return L==NULLU;
}

tPosU firstU(tListU L){
    //Objetivo: Devuelve la posicion del primer elemento de la lista
    //Entrada: Una Lista
    //Salida: La primera posicion de la lista
    //PreCD: La lista no está vacía.
    return L;
}


tPosU lastU(tListU L){
    //Objetivo: Devuelve la posicion del ultimo elemento de la lista
    //Entrada: Una lista
    //Salida: La ultima posicion de la lista
    //PreCD: La lista no está vacía.
    tPosU p;
    for(p=L; p->next!=NULLU; p=p->next);
    return p;
}

tPosU nextU(tPosU p, tListU L){
    //Objetivo: Devuelve la posicion en la lista del elemento siguiente al de la posicio
    //Entradas: Una posicion de la lista y la lista
    //Salida: El elemento siguiente de la lista
    //PreCD: La posición indicada es una posición válida en la lista.
    return p->next;
}

tPosU previousU(tPosU p, tListU L){
    //Objetivo: Devuelve la posicion en la lista del elemento anterior al de la posicion
    //Entradas: Una posicion de la lista y la lista
    //Salida: La posicion anterior de la lista o NULL
    //PreCD: La posición indicada es una posición válida en la lista.
    tPosU q;
    if(p==L){
        q=NULLU;
    }
    else{
        for (q = L; q->next!=p; q=q->next);
    }
    return q;
}

//Función complementaria para InsertItem
bool createNodeU(tPosU *p){
    *p=malloc(sizeof(struct tNode));
    return *p!=NULLU;
}

tPosU findPosition(tListU L, tItemU d) {
    tPosU p;
    p = L;
    while ((p->next != NULLU) && (strcmp(p->next->data.userName, d.userName)<0)) {
        p = p->next;
    }
    return p;
}


bool insertItemU(tItemU d, tListU *L){
    //Objetivo: Inserta un elemento en la lista antes de la posicion indicada. Si la posicion es LNULL se añade al final
    //Entradas: Un elemento de la lista, una posicion de la lista y una lista
    //Salidas: True o False
    //PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
    //PostCD: Las posiciones de los elementos de la lista posteriores a la del elemento insertado pueden haber variado.
    tPosU q,p;
    if(!createNodeU(&q))
        return false;
    else{
        q->data=d;
        q->next=NULLU;
        if(*L == NULLU) *L=q;
        else if(strcmp((*L)->data.userName, q->data.userName)>0){
            q->next=*L;
            *L=q;
        }
        else{
            p= findPosition(*L,d);
            q->next=p->next;
            p->next=q;

        }
        return true;
    }
}

void deleteAtPositionU(tPosU p, tListU *L){
    //Objetivo: Elimina de la lista el elemento que ocupa la posicion indicada
    //Entradas: Una posicion de la lista y una lista
    //Salidas: La lista sin el elemento situado en la posicion especificada
    //PreCD: La posición indicada es una posición válida en la lista.
    //PostCD: Las posiciones de los elementos de la lista posteriores a la de la posición eliminada pueden haber variado.
    tPosU q;
    if(p==*L){
        *L=p->next;
        if(*L!=NULLU){
            p->next=NULLU;
        }
    }
    else if(p->next!=NULLU) {
        previousU(p, *L)->next = p->next;
    }
    else {
        previousU(p, *L)->next = NULLU;
    }
    free(p);
}

tItemU getItemU(tPosU p, tListU L){
    //Objetivo: Devuelve el contenido del elemento que ocupa la posicion indicada
    //Entradas: Una posicion de la lista y una lista
    //Salidas: El contenido de la posicion especificada
    //PreCD: La posición indicada es una posición válida en la lista.
    return p->data;
}

void updateItemU(tItemU d, tPosU p, tListU *L){
    //Objetivo: Modifica el contido del elemento situado en la posicion
    //Entradas: Un elemento, una posicion de la lista y una lista
    //Salidas: La lista con el elemento actualizado en la posicion especificada
    //PreCD: La posición indicada es una posición válida en la lista.
    //PostCD: El orden de los elementos de la lista no se ve modificado.
    p->data=d;
}

tPosU findItemU(tUserName d, tListU L){
    //Objetivo: Devuelve la posicion del primer elemento de la lista cuya nombre de usuario se corresponda con el indicado(o LNULL si no existe tal elemento)
    //Entradas: Un elemento y una lista
    //Salida: La posicion del elemento deseado
    tPosU p;
    if(isEmptyListU(L)) return p=NULLU;
    else{
        for(p=L;(p!=NULLU)&&(strcmp(p->data.userName, d)); p=p->next);
        return p;
    }
}