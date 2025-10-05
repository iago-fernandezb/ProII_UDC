/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Iago Fernández Blanco LOGIN 1: iago.fernandez.blanco@udc.es
 * AUTHOR 2: Xoán Suárez Mayta LOGIN 2: xoan.suarez@udc.es
 * GROUP: 4.2
 * DATE: 26 / 04 / 24
 */

#include <stdio.h>
#include <string.h>
#include "stdlib.h"

#include "types.h"
#include "user_list.h"

#define MAX_BUFFER 255

void corrects(int max, tPosS L){
    struct tNode i;
    for(i=L,)
}

char* NumToCategory(char *u,tListU *L) {
    //Objetivo: Busca el usuario y retorna su categoria
    //Entrada: El usuario y la lista donde esta contenido
    //Salida: La categotia del usuario
    //PreCD: Lista inicializada, usuario valido
    tPosU p;
    tItemU item;
    static char category[10];
    p = findItemU(u, *L);
    item = getItemU(p, *L);
    if (item.userCategory == basic) {
        strcpy(category, "basic");
    } else {
        strcpy(category, "pro");
    }
    return category;
}

void print_listS(tListS list) {
    //Objetivo: Imprime la lista de canciones de un usuario
    //Entrada: Una lista de canciones
    //Salida: Imprime las canciones con sus atributos
    //PreCD: Lista inicializada
    tPosS pos;
    tItemS item;

    if (!isEmptyListS(list)) {
        pos = firstS(list);
        while (pos != NULLS) {
            item = getItemS(pos, list);
            printf("Song %s playtime %d\n", item.songTitle, item.playTime);
            pos = nextS(pos, list);
        }
        printf("\n");
    }
    else {
        printf("No songs\n\n");
    }
}

void print_list(tListU list) {
    //Objetivo: Muestra la lista de usuarios con sus canciones
    //Entrada: Una lista de usuarios
    //Salida: Muestra por pantalla los usarios de la lista y sus atributos
    //PreCD: Lista inicializada
    tPosU pos;
    tItemU item;
    char category[6];

    if (!isEmptyListU(list)) {
        pos = firstU(list);
        while (pos != NULLU) {
            item = getItemU(pos, list);
            if(item.userCategory==0) {
                strcpy(category, "basic");
            }
            else{
                strcpy(category, "pro");
            }
            printf("User %s category %s totalplaytime %d\n", item.userName, category, item.totalPlayTime);
            print_listS(item.songListS);
            pos = nextU(pos, list);
        }
    }
}

bool new(char *u,  char *c, tListU *L) {
    //Objetivo: Se incorporará el usuario a la lista de usuarios con la categoría indicada y su contador de tiempo de reproducción (totalPlayTime) inicializado a 0.
    //Entrada: El nombre del usuario, su categoria y la lista
    //Salida: True o False si fue posible insertarlo en la lista
    //PreCD: Lista inicializada
    tItemU d;
    strcpy(d.userName, u);
    if (strcmp(c, "basic") == 0) { //Comprueba la categoria que queremos asignarle
        d.userCategory = basic;
    } else {
        d.userCategory = pro;
    }
    d.totalPlayTime = 0;
    createEmptyListS(&d.songListS);
    if (findItemU(u, *L) == NULLU) { //Comprueba si el usuario ya esta en la lista
        if (insertItemU(d, L)) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Add(char *u,  char *c, tListU *L) {
    //Objetivo:  se buscará el usuario y, si no hay ninguna canción con ese título (songTitle) en su lista de reproducción, la canción se añadirá al final de ésta. El valor inicial de su campo playTime será 0.
    //Entrada: El nombre del usuario, el nombre de la cancion y una Lista de usuarios
    //Salida: True o False si fue posible insertarlo en la lista
    //PreCD: Lista inicializada
    tPosU p= findItemU(u, *L);
    if(isEmptyListU(*L)) return false; //Comprueba si la lista esta vacia
    if(p!=NULLU){
        tItemU item= getItemU(p, *L);
        tPosS q=findItemS(c, item.songListS);
        if(q==NULLS){ //Comprueba si el usuario ya esta en la lista
            tItemS song;
            strcpy(song.songTitle, c);
            song.playTime=0;
            insertItemS(song, lastS(item.songListS)+1, &(item.songListS));
            updateItemU(item,p,L);
            return true;
        }
        else return false;
    }
    else return false;
}

void stats(char *commandNumber, char command, tListU *L){
    //Muestra los elementos de la lista y una serie de valores con respecto a esta
    //Entrada: EL numero de peticion, el tipo de peticion y una lista
    //Salida: El contenido entero de la lista y una serie de valores con respecto a esta
    //PreCD: Lista inicializada
    tPosU pos;
    int count_basic=0,count_pro=0;
    int count_basic_plays=0,count_pro_plays=0;
    printf("********************\n");
    printf("%s %c:\n", commandNumber, command);
    print_list(*L);

    if(isEmptyListU(*L)){
        printf("+ Error: Stats not possible\n");
    }
    else {
        printf("Category  Users  TimePlay  Average\n");
        for (pos = firstU(*L); pos != NULLU; pos = nextU(pos, *L)) { //Bucle para contar el numero de usuarios y sus reproducciones segun su categoria
            tItemU item;
            item = getItemU(pos, *L);
            if (item.userCategory == basic) {
                count_basic = count_basic + 1;
                count_basic_plays = count_basic_plays + item.totalPlayTime;
            } else {
                count_pro = count_pro + 1;
                count_pro_plays = count_pro_plays + item.totalPlayTime;
            }
        }
        float media_a, media_b;
        media_a = (float) count_basic_plays / (float) count_basic;
        media_b = (float) count_pro_plays / (float) count_pro;
        if (count_basic == 0) {
            media_a = 0;
        }
        printf("Basic     %5d %9d %8.2f\n", count_basic, count_basic_plays, media_a);
        if (count_pro == 0) {
            media_b = 0;
        }
        printf("Pro       %5d %9d %8.2f\n", count_pro, count_pro_plays, media_b);
    }
}

void upgrade(tUserName u,tListU *L){

    //Objetivo: Cambia la categoria de un elemento de basic a pro
    //Entrada: El nombre del usuario y la lista donde esta contenido
    //Salida: True o False dependiendo de si se ha podido realizar la funcion
    //PreCD: Lista inicializada

    tPosU p;
    tItemU item;

    if(!isEmptyListU(*L)){
        p= findItemU(u,*L);
        if(p!=NULLU){
            item=getItemU(p, *L);
            if(item.userCategory==basic) {
                item.userCategory=pro;
                updateItemU(item, p, L);
                printf("* Upgrade: user %s category %s\n", u, NumToCategory(u, L));

            }
            else {
                printf("+ Error: Upgrade not possible\n");
            }
        }
        else{
            printf("+ Error: Upgrade not possible\n");
        }
    }
    else{
        printf("+ Error: Upgrade not possible\n");
    }
}

bool play(char *u, char *c, char *m, tListU *L){
    //Objetivo: Añade la duracion de una cancion a la lista de canciones del usuario
    //Entrada: El nombre del usuario, el nombre de la cancion, la duracion de la cancion y la lista donde estan contenidas
    //Salida: True o False dependiendo de si se ha podido realizar la funcion
    //PreCD: Lista inicializada
    tPosU p= findItemU(u, *L);
    if(isEmptyListU(*L)) return false;
    if(p!=NULLU){
        tItemU itemU = getItemU(p, *L);
        tPosS q=findItemS(c, itemU.songListS);
        if(q!=NULLS){
            int a ;
            a= atoi(m);
            tItemS items = getItemS(q, itemU.songListS);
            items.playTime =items.playTime+a;
            itemU.totalPlayTime = itemU.totalPlayTime+ a;
            updateItemS(items, q, &(itemU.songListS)); //Actualizamos la lista de canciones auxiliar
            updateItemU(itemU, p, L); //Actualizamos el usuario con todos los campos nuevos ya cubiertos
            printf("* Play: user %s plays song %s playtime %d totalplaytime %d\n", u, c, items.playTime, itemU.totalPlayTime);

            return true;
        }
        else return false;
    }
    else return false;
}

bool delete(char *u, tListU *L){
    //Objetivo: Elimina a un usuario de la lista
    //Entrada: El nombre del usuario a eliminar y la lista donde esta contenido
    //Salida: True o False dependiendo de si se ha podido realizar la funcion
    //PreCD: Lista inicializada
    if(isEmptyListU(*L)){
        return false;
    }
    else{
        tPosU p = findItemU(u, *L);
        if(p!=NULLU) {
            tItemU item= getItemU(p, *L);
            if (!isEmptyListS((item.songListS))) {
                //Bucle para eliminar todas las canciones de un usuario en caso de que halla alguna
                for (tPosS m= firstS(item.songListS); firstS(item.songListS)==NULLS; m=nextS(m, item.songListS)) {
                    deleteAtPositionS(m, &item.songListS);
                }
                updateItemU(item, p, L);
            }
            printf("* Delete: user %s category %s totalplaytime %d\n",u, NumToCategory(u, L), item.totalPlayTime);
            deleteAtPositionU(p, L); //Eliminamos el usuario una vez ya no tenga canciones en su lista de reproduccion
            return true;
        }
        else{
            return false;
        }
    }
}

void deleteaux(char *u, tListU *L){
    //Objetivo: Elimina a un usuario de la lista
    //Entrada: El nombre del usuario a eliminar y la lista donde esta contenido
    //Salida: True o False dependiendo de si se ha podido realizar la funcion
    //PreCD: Lista inicializada

    tPosU p = findItemU(u, *L);
    if(p!=NULLU) {
        tItemU item= getItemU(p, *L);
        if (!isEmptyListS((item.songListS))) {
            item.songListS.LastPos = NULLS;
            updateItemU(item, p, L);
        }
        deleteAtPositionU(p, L);
    }
    else{
    }
}

bool Remove(char *u, tListU *L) {
    //Objetivo: Elimina a todos los usuarios con un tiempo de reproduccion mayor al permitido pertenecientes a la categoria basic
    //Entrada: El nombre del usuario a eliminar y la lista donde esta contenido
    //Salida: True o False dependiendo de si se ha podido realizar la funcion
    //PreCD: Lista inicializada
    tPosU pos = firstU(*L);
    tPosU prev = NULLU;
    bool removed = false;
    int limit = atoi(u);
    if (isEmptyListU(*L)) {
        return false;
    }
    if (limit <= 0) {
        return false;
    }
    while (pos != NULLU) { //Bucle que va comprobando los usuarios uno a uno hasta llegar al final de la lista utilizando 2 punteros auxiliares para al borrar elementos guardar la posicion anterior y no tener que recorrer la lista desde el principio
        tItemU item = getItemU(pos, *L);
        if (item.userCategory == basic && item.totalPlayTime > limit) {
            printf("Removing user %s total playtime %d\n", item.userName, item.totalPlayTime);
            tPosU nextPos = nextU(pos, *L);
            deleteaux((char *) pos, L);
            if (prev == NULLU) {
                pos = nextPos;
            } else {
                prev->next = nextPos;
                pos = nextPos;
            }
            removed = true;
        } else {
            prev = pos;
            pos = nextU(pos, *L);
        }
    }
    return removed;
}


void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListU *L) {

    switch (command) {
        case 'N':
            printf("********************\n");
            printf("%s %c: user %s category %s\n", commandNumber, command, param1, param2);

            if(new(param1,param2,  L)!=false) {
                printf("* New: user %s category %s\n",param1, param2);
            }

            else{
                printf("+ Error: New not possible\n");
            }
            break;
        case 'D':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);
            if(delete(param1, L)!=true){
                printf("+ Error: Delete not possible\n");
            }
            break;
        case 'A':
            printf("********************\n");
            printf("%s %c: user %s song %s\n", commandNumber, command, param1, param2);

            if(Add(param1,param2, L)!=false) {
                printf("* Add: user %s adds song %s\n",param1, param2);
            }

            else{
                printf("+ Error: Add not possible\n");
            }
            break;
        case 'U':
            printf("********************\n");
            printf("%s %c: user %s\n", commandNumber, command, param1);
            upgrade(param1, L);
            break;
        case 'P':
            printf("********************\n");
            printf("%s %c: user %s song %s minutes %s\n", commandNumber, command, param1, param2, param3);

            if(play(param1, param2, param3, L)!=true){
                printf("+ Error: Play not possible\n");
            }
            break;
        case 'S':
            stats(commandNumber, command, L);
            break;
        case 'R':
            printf("********************\n");
            printf("%s %c: maxtime %s\n", commandNumber, command, param1);

            if(Remove(param1, L)!=true){
                printf("+ Error: Remove not possible\n");
            }
            break;
        default:
            break;
    }
}

void readTasks(char *filename, tListU *L) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {


    tListU L;
    createEmptyListU(&L);

    char *file_name = "upgrade.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &L);

    return 0;
}
