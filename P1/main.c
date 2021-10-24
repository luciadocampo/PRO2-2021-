/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: Lucía Docampo Rodríguez LOGIN 1: lucia.docampo
 * AUTHOR 2: Pablo Torrado García LOGIN 2: p.torrado
 * GROUP: 1.1
 * DATE: 09 / 04 / 21
 */

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef STATIC_LIST
#include "static_list.h"
#endif
#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef TEST_LIST
#include "list/list.h"
#endif

void New(tList *list, tNickname name, tUserCategory category){   //
    /* Objetivo: alta de un usuario de categoría standard o premium
     * Entradas: la lista, un nombre de usuario y la categoría elegida
     * Salidas: lista modificada
     * Precondiciones: la posición es nula (no existe el usuario)
     * Postcondiciones: las posiciones posteriores del nuevo elemento varían
     */
    tItemL item; //Datos del usuario
    tPosL pos; //Posición en la lista
    pos = findItem(name, *list); //Devuelve el elemento de la lista en el que el nickname coincide con el indicado
    if (pos == LNULL){ //Crea el nuevo usuario si la posición es nula (cuado es la última de la lista)
        strcpy(item.nickname, name); //Copia la cadena apuntada por item.nickname en el destino name
        item.userCategory = category; //Categoría del nuevo usurio (standard o premium)
        item.numPlay = 0; //Numero de reproducciones = 0 (nuevo usuario)
        if (insertItem(item, LNULL, list)){ //Inserta el nuevo elemento en la lista cuando la función devuelve true
            if (item.userCategory == 0){//Devuelve el nuevo usuario con la categoría standard cuando el enum == 0
                printf("* New: nick %s category standard \n", name);
            }
            else{ //Devuelve el nuevo usuario con la categoría premium cuando el enum == 1
                printf("* New: nick %s category premium \n", name);
            }
        }
        else{ //Devuelve error si no se puede insertar elemento en la lista
            printf("+ Error: New not possible\n");
        }
    }
    else { //Devuelve error si la posición no es nula (cuado no es la última de la lista)
        printf("+ Error: New not possible\n");
    }
}

void Delete(tList *list, tNickname name){
    /* Objetivo: baja de usuario
     * Entradas: la lista y el nombre de usuario
     * Salidas: lista modificada
     * Precondiciones: la posición no es nula (existe el usuario)
     * Postcondiciones: las posiciones posteriores del elemento eliminado varían
     */
    tPosL pos; //Posición en la lista
    tItemL item; //Datos del usuario
    pos = findItem(name, *list); //Devuelve el elemento de la lista en el que el nickname coincide con el indicado
    if (pos != LNULL) { //Si la posición no es nula obtiene los datos del struct tItemL
        item = getItem(pos, *list); //Devuelve el contenido del struct tItemL
        if (item.userCategory == 0){ //Devuelve los datos del usuario con la categoría Standard cuando el enum == 0
            printf("* Delete: nick %s category standard numplays %d\n", name, item.numPlay);
        }
        else{ //Devuelve los datos del usuario con la categoría Premium cuando el enum == 1
            printf("* Delete: nick %s category premium numplays %d\n", name, item.numPlay);
        }
        deleteAtPosition (pos, list); //Elimina de la lista el elemento que ocupa la posición
    }
    else{ //Devuelve error cuanddo la posición es nula
        printf("+ Error: Delete not possible\n");
    }
}

void Play(tList *list, tNickname name, tTitleVideo video){
    /* Objetivo: reproducción de un vídeo por parte de un usuario
     * Entradas: la lista, el nombre de usuario y el video reproducido
     * Salidas: lista modificada
     * Precondiciones: La posición no es nula (existe el usuario)
     * Postcondiciones: Varían las reproducciones del usuario
     */
    tPosL pos; //Posición en la lista
    tItemL item; //Datos del usuario
    pos = findItem(name, *list); //Devuelve el elemento de la lista en el que el nickname coincide con el indicado
    if (pos != LNULL) { //Comprueba si la posición no es nula
        item = getItem(pos, *list); //Devuelve el contenido del struct tItemL
        item.numPlay++; //Incrementa el numero de reproducciones
        updateItem(item, pos, list); //Modifica el contenido de la posición (en este caso, el número de reproducciones)
        printf("* Play: nick %s plays video %s numplays %d\n", name, video, item.numPlay); //Devuelve nombre de usuario y video e incrementa el número de reproducciones
    }
    else{ //Devuelve error si la posición es nula
        printf("+ Error: Play not possible\n");
    }
}

void Stats(tList *list){
    /* Objetivo: listado de los usuarios actuales y sus datos
     * Entradas: la lista
     * Salidas: no tiene salida
     * Precondiciones: la lista no puede estar vacía
     * Postcondiciones: no tiene
     */
    tPosL pos;
    tItemL Item;
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
        while(pos != LNULL){ //Mientras la posiciónm no sea nula (la última) devuelve el usuario de la posición junto con sus datos
            Item = getItem (pos, *list); //Devuelve el contenido del struct tItemL
            if (Item.userCategory == 0){ //Devuelve los datos de cada uno de los usuarios en la categoría Standard cuando el enum == 0
                printf("Nick %s category standard numplays %d\n", Item.nickname, Item.numPlay);
            }
            else{ //Devuelve los datos de cada uno de los usuarios en la categoría Premium cuando el enum == 1
                printf("Nick %s category premium numplays %d\n", Item.nickname, Item.numPlay);
            }

            if(Item.userCategory == premium){ //Cálculo de la media para la categoría Premium
                numNicksPremium++; //Incrementa en 1 el valor del número de usuarios de la categoría Premium
                numPlaysPremium = numPlaysPremium + Item.numPlay; //Sumatorio del número de reproducciones de los usuarios Premium
                average2 = (float) (numPlaysPremium / numNicksPremium); //Realiza la división entre el numero de reproducciones y el de usuarios (Premium)
            }
            else{ //Cálculo de la media para la categoría Standard
                numNicksStandard++; //Incrementa en 1 el valor del número de usuarios de la categoría Standard
                numPlaysStandard = numPlaysStandard + Item.numPlay; //Sumatorio del número de reproducciones de los usuarios Standard
                average1 = (float) (numPlaysStandard / numNicksStandard); //Realiza la división entre el numero de reproducciones y el de usuarios (Standard)
                }
            pos = next(pos, *list); //Devuelve la posición en la lista del elemento siguiente al de la posición indicada

            }
        }
    printf("Category  Users  Plays  Average\n"); //Cabecera de los datos generales según la categoría
    printf("Standard    %d     %d     %.2f\n", numNicksStandard, numPlaysStandard, average1); //Muestra los datos generales de la propia categoria Standard
    printf("Premium     %d     %d     %.2f\n", numNicksPremium, numPlaysPremium, average2); //Muestra los datos generales de la propia categoria Premium
    }

void processCommand(char *commandNumber, char command, tList *list, char *param1, char *param2) {
    /* Objetivo:  procesar las peticiones de los usuarios
     * Entradas: commandNumber, command, lista, param1 y param2
     * Salidas: commandNumber, lista, param1 y param2
     */
    tUserCategory param3;

    switch(command) {
        case 'N': {
            if (strcmp(param2,"standard")==0){
                param3 = standard;
            } if (strcmp(param2, "premium")==0){
                param3 = premium;
            }
            printf("********************\n");
            printf("%s %c: nick %s category %s\n", commandNumber, command, param1, param2);
            New(list, param1, param3);
            break;
        }
        case 'P':{
            printf("********************\n");
            printf("%s %c: nick %s video %s\n", commandNumber, command, param1, param2);
            Play(list, param1, param2);
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
        }
        default: {
            break;
        }
    }
}


void readTasks(char *filename) {
    /* Objetivo: Leer las Tareas
     * Entradas: filename
     * Salidas: no tiene
     * Precondiciones: el archivo tiene que existir
     * Postcondiciones: no tiene
     */
    FILE *df;
    char *commandNumber, *command, *param1, *param2;

    tList list;
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
            processCommand(commandNumber, command[0], &list, param1, param2);
        }
        fclose(df);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

int main(int nargs, char **args) {

    char *file_name = "new.txt";

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






