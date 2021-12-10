/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "video_list.h"
#include "user_list.h"

#define MAX_BUFFER 255


void New(tUserList *list, tNickname name, tUserCategory category){

    /* Objetivo: alta de un usuario de categoría standard o premium
     * Entradas: la lista, un nombre de usuario y la categoría elegida
     * Salidas: lista modificada
     * Precondición: la posición es nula (no existe el usuario)
     * Postcondición:
     */


    tUserPos pos;
    tUserItem item;

    pos = findItem(name, *list); //devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado ( o NULL_USER si no existe tal elemento)
    if (pos == NULL_USER){ //Si la posición es nula, entonces se inicia el proceso de inserción del nuevo usuario
        strcpy(item.nickname, name); //Copia el nick del nuevo usuario
        item.userCategory = category;
        createEmptyListV(&item.videoList); //Crea una lista de video vacía
        if (insertItem(item, list)){ //Si el usuario se insertó correctamente, lo muestra por pantalla
            if (item.userCategory == standard){
                printf("* New: nick %s category standard \n", name);
            }
            else{
                printf("* New: nick %s category premium \n", name);
            }
        }
        else{ //Si no se puede insertar muestra error
            printf("+ Error: New not possible\n");
        }
    }
    else { //Si ya hay un usuario con ese nick muestra error
        printf("+ Error: New not possible\n");
    }
}


void Stats(tUserList *list){
    /* Objetivo: listado de los usuarios actuales y sus datos
     * Entradas: la lista
     * Salidas: no tiene salida
     * Precondiciones: la lista no puede estar vacía
     * Postcondiciones:
     */
    tUserPos pos;
    tVideoPos posV;
    tUserItem item;
    tVideoItem itemV;
    int numNicksStandard = 0; //Número de usuarios de la categoría Standard
    int numNicksPremium = 0; //Número de usuarios de la categoría Premium
    int numPlaysStandard = 0; //Número de reproducciones de usuarios Standard
    int numPlaysPremium = 0; //Número de reproducciones de usuarios Premium
    float average1 = 0; //Media de reproducción de usuarios Standard
    float average2 = 0; //Media de reproducción de usuarios Premium

    if (isEmptyList(*list)){ //Devuelve error si la lista está vacía
        printf("+ Error: Stats not possible\n");
    }
    else{
        pos = first(*list); //Sitúa la posición al inicio de la lista
        while(pos != NULL_USER){ //Mientras la posición no sea nula (la última) devuelve el usuario de la posición junto con sus datos
            item = getItem (pos, *list); //Obtiene los datos del item
            if (item.userCategory == standard) { //Devuelve los datos de cada uno de los usuarios en la categoría Standard
                printf("*Nick %s category standard totalplaytime %d\n", item.nickname, item.totalPlayTime);
            }
            else { //Devuelve los datos de cada uno de los usuarios en la categoría Premium
                printf("*Nick %s category premium totalplaytime %d\n", item.nickname, item.totalPlayTime);
            }

            if (isEmptyListV(item.videoList)){ //Si la lista de videos del usuario está vacía muestra "No videos"
                printf("No videos\n");
            }
            else{
                posV = firstV(item.videoList);//Sitúa la posición al inicio de la lista
                while(posV != NULL_VIDEO){ //Mientras la posición no sea nula (la última) devuelve el video y sus datos de reproducción
                    itemV = getItemV(posV, item.videoList); //Obtiene los datos del item de video
                    printf("Video %s playtime %d\n", itemV.titleVideo, itemV.playTime); //Muestra los datos por pantalla
                    posV = nextV(posV,item.videoList); //Devuelve la posición en la lista del elemento siguiente al de la posición indicada
                }
            }
            if(item.userCategory == premium){ //Cálculo de la media para la categoría Premium
                numNicksPremium++; //Incrementa en 1 el valor del número de usuarios de la categoría Premium
                numPlaysPremium = numPlaysPremium + item.totalPlayTime; //Sumatorio del número de reproducciones de los usuarios Premium
                average2 =  numPlaysPremium / (float)numNicksPremium; //Realiza la división entre el numero de reproducciones y el de usuarios (Premium)
            }
            else{ //Cálculo de la media para la categoría Standard
                numNicksStandard++; //Incrementa en 1 el valor del número de usuarios de la categoría Standard
                numPlaysStandard = numPlaysStandard + item.totalPlayTime; //Sumatorio del número de reproducciones de los usuarios Standard
                average1 =  numPlaysStandard / (float)numNicksStandard; //Realiza la división entre el numero de reproducciones y el de usuarios (Standard)
            }
            pos = next(pos, *list); //Devuelve la posición en la lista del elemento siguiente al de la posición indicada

        }
    }
    printf("Category  Users  TimePlay  Average\n"); //Cabecera de los datos generales según la categoría
    printf("Standard    %d     %d     %.2f\n", numNicksStandard, numPlaysStandard, average1); //Muestra los datos generales de la propia categoria Standard
    printf("Premium     %d     %d     %.2f\n", numNicksPremium, numPlaysPremium, average2); //Muestra los datos generales de la propia categoria Premium
}


void Add(tUserList *list, tNickname nickname, tTitleVideo titleVideo){

    /* Objetivo: inserta un vídeo en la lista de vídeos de un usuario
     * Entradas: la lista, un nombre de usuario y el título del vídeo
     * Salidas: lista modificada
     * Precondición: la posición es nula (no existe el vídeo)
     * Postcondición:
     */

    tUserPos pos;
    tVideoPos posV;
    tUserItem item;
    tVideoItem itemV;
    pos = findItem(nickname, *list); //devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado ( o NULL_USER si no existe tal elemento)
    if (pos != NULL_USER) { //Si la posición no es nula obtiene los datos del struct tUserItem
        item = getItem(pos, *list);
        posV = findItemV(nickname, item.videoList); //devuelve la posición del primer elemento de la lista cuyo title video se corresponda con el indicado ( o NULL_VIDEO si no existe tal elemento)
        if (posV == NULL_VIDEO){ //Si no existe el video se añade
            strcpy(itemV.titleVideo, titleVideo); //Copia el titlevideo para el insert
            itemV.playTime = 0; //Al ser nuevo video situa el tiempo de reproducción a 0
            insertItemV(itemV, NULL_VIDEO, &item.videoList); //Inserta el nuevo video
            updateItem(item, pos, list); //Actualiza el contenido de la lista
            printf("* Add: nick %s adds video %s \n", nickname, titleVideo); //Muestra la inserción del nuevo video
        }
        else {
            printf("+ Error: Add not possible\n"); //Muestra error si ya existe el video
        }
}
    else{
        printf("+ Error: Add not possible\n"); //Muestra error si no existe el usuario
    }
}


void Play(tUserList *list, tNickname name, tTitleVideo video, tPlayTime playTime) {

    /* Objetivo: reproducción de minutos por parte de un usuario
     * Entradas: la lista, el nombre de usuario y el video reproducido
     * Salidas: lista modificada
     * Precondiciones: La posición no es nula (existe el usuario)
     * Postcondiciones:
     */

    tUserPos pos;
    tVideoPos posV;
    tUserItem item;
    tVideoItem itemV;

    pos = findItem(name, *list); //devuelve la posición del primer elemento de la lista cuyo nick de usuario se corresponda con el indicado ( o NULL_USER si no existe tal elemento)
    if (pos != NULL_USER) { //Si la posición no es nula obtiene los datos del struct tUserItem
        item = getItem(pos, *list); //Obtiene los datos del item
        posV = findItemV(video, item.videoList); //devuelve la posición del primer elemento de la lista cuyo title video se corresponda con el indicado ( o NULL_VIDEO si no existe tal elemento)
        if (posV != NULL_VIDEO) { //Si el video existe inicia el proceso del play
            itemV = getItemV(posV, item.videoList); //Obtiene los datos del struct de video
            itemV.playTime = itemV.playTime + playTime; //Calcula el playTime
            item.totalPlayTime = item.totalPlayTime + playTime; //Calcula el totalPlayTime
            updateItemV(itemV, posV, &item.videoList); //Actualiza el contenido de la lista
            printf("* Play: nick %s plays video %s playtime %d totalplaytime %d\n", name, video, playTime, item.totalPlayTime); //Muestra el proceso del play
            updateItem(item, pos, list); //Actualiza el contenido de la lista
        }
        else { //Si el video no existe muestra error
            printf("+ Error: Play not possible\n");
        }
    }
    else{ //Si no existe el video
        printf("+ Error: Play not possible\n");
    }
}


void Delete(tUserList *list, tNickname name){

    /* Objetivo: baja de usuario
     * Entradas: la lista y el nombre de usuario
     * Salidas: lista modificada
     * Precondición: la posición no es nula (existe el usuario)
     * Postcondición:
     */

    tUserPos pos; //Posición en la lista
    tUserItem item; //Datos del usuario

    pos = findItem(name, *list); //Devuelve el elemento de la lista en el que el nickname coincide con el indicado
    if (pos != NULL_USER) { //Si la posición no es nula obtiene los datos del struct tUserItem
        item = getItem(pos, *list); //Obtiene el contenido del struct tUserItem
        if (item.userCategory == standard){ //Devuelve los datos del usuario con la categoría Standard
            printf("* Delete: nick %s category standard totalplaytime %d\n", name, item.totalPlayTime);
        }
        if (item.userCategory == premium){ //Devuelve los datos del usuario con la categoría Premium
            printf("* Delete: nick %s category premium totalplaytime %d\n", name, item.totalPlayTime);
        }
        deleteAtPosition (pos, list); //Elimina de la lista el elemento que ocupa la posición
    }
    else{ //Devuelve error cuanddo la posición es nula
        printf("+ Error: Delete not possible\n");
    }
}


void Remove(tUserList *list, int maxTime){

    /* Objetivo: elimina todos los usuarios standard que hayan excedido el maxTime
     * Entradas: la lista y el nombre de usuario
     * Salidas: lista modificada
     * Precondición: existe un usuario de categoría standard que excede el maxTime
     * Postcondición:
     */

    tUserPos pos;
    tUserItem item;
    int counter = 0; //Inicializamos una variable entera para detectar el numero de usuarios borrados

    if (isEmptyList(*list)){ //Devuelve error si la lista está vacía
        printf("+ Error: Remove not possible\n");
    }
    else{
        pos = first(*list); //Sitúa la posición al inicio de la lista
        while(pos != NULL_USER){ //Si la posición no es nula obtiene los datos del struct tUserItem
            item = getItem(pos, *list); //Obtiene el contenido del struct tUserItem
            if(item.userCategory == standard && item.totalPlayTime > maxTime) { //Condiciones para el remove: Categoría Standard y Totalplaytime > maxTime
                if (pos == first(*list)) { //Si las condiciones se cumplen para la primera posición se ejecuta el proceso de borrado
                    deleteAtPosition(first(*list),list); //Borra el usuario
                    counter ++; //Incrementamos el número de usuarios borrados
                    printf("Removing %s totalplaytime %d\n", item.nickname, item.totalPlayTime); //Se muestra por pantalla que se está borrando un usuario
                    if (isEmptyList(*list)){ //Se comprueba si la lista está vacía despues del borrado del usuario
                        pos = NULL_USER; //Si está vacía la posición es nula
                    }
                    else{
                        pos=first(*list);//Si la lista no está vacía la posición continúa siendo la primera
                    }
                }
                else {
                    pos = previous(pos, *list); //Sitúa la posición en el elemento de la lista anterior
                    deleteAtPosition(next(pos, *list), list); //Elimina el elemento siguiente de la lista
                    counter ++; //Incrementamos el número de usuarios borrados
                    pos = next(pos, *list); //Sitúa la posición en el siguiente elemento de la lista
                    printf("Removing %s totalplaytime %d\n", item.nickname, item.totalPlayTime); //Se muestra por pantalla que se está borrando un usuario
                }
            }
            else{
                pos = next(pos,*list); //Sitúa la posición en el siguiente elemento de la lista
            }
        }
        if(counter == 0){
            printf("+ Error: Remove not possible\n"); //Muestra un mensaje de error si no se eliminaron usuarios
        }
    }
}



void processCommand(char *commandNumber, char command, tUserList *list, char *param1, char *param2, char *param3){

    tUserCategory param4;

    switch(command){
        case 'N': {
            if (strcmp(param2,"standard")==0){
                param4 = standard;
            }
            if (strcmp(param2, "premium")==0){
                param4 = premium;
            }
            printf("********************\n");
            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);
            New(list, param1, param4);
            break;
        }
        case 'A': {
            printf("********************\n");
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            Add(list, param1, param2);
            break;
        }
        case 'P': {
            printf("********************\n");
            printf("%s %c: nick %s video %s minutes %s\n", commandNumber, command, param1, param2, param3);
            Play(list, param1, param2, atoi(param3));
            break;
        }
        case 'S':{
            printf("********************\n");
            printf("%s %c\n", commandNumber, command);
            Stats(list);
            break;
        }
        case 'D':{
            printf("********************\n");
            printf("%s %c: nick %s\n", commandNumber, command, param1);
            Delete(list, param1);
            break;
        }
        case 'R':{
            printf("********************\n");
            printf("%s %c: maxtime %s category %s\n", commandNumber, command, param1, param2);
            Remove(list, atoi(param1));
            break;
        }
        default: {
            break;
        }
    }
}


void readTasks(char *filename) {
    FILE *df;
    char *commandNumber, *command, *param1, *param2, *param3;

    tUserList list;
    createEmptyList(&list);

    df = fopen(filename, "rb");
    if (df != NULL) {
        const char delimiters[] = " \n\r";
        char buffer[MAX_BUFFER];
        while (fgets(buffer, MAX_BUFFER, df)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            processCommand(commandNumber, command[0], &list, param1, param2, param3);
        }
        fclose(df);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "play.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}
