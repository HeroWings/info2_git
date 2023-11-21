#include "namesarchive.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static int numberOfNames = 0;
static char **archive;
static int compNames(const void*, const void*);
#define MAX_NAME_LEN 10

// Fügt einen Namen hinzu. Im Fehlerfall (kein Speicher mehr) soll 0, ansonsten 1 zurückgegeben werden.
int addName(const char *name)
{
	//Platz für weiteren Namen hinzufügen
	archive = realloc(archive, numberOfNames+1);
	if(archive == NULL) return 0;
	
	//Platz für den zusätzlichen Namen allocaten
	archive[numberOfNames] = (char*) malloc(strlen(name)+1);
	if(archive[numberOfNames] == NULL) return 0;
	
	//Namen an Listenende einfügen
	strcpy(archive[numberOfNames], name);
	numberOfNames++;
	return 1;
}

// Wie addName. Fügt Namen aber direkt sortiert hinzu. Voraussetzung ist ein bereits sortiertes Archiv.
int addNameSorted(const char *name)
{
    for(int i = 0; i < numberOfNames; i++)
    { // 1. addName(name) -> 2. qsort -> return
        if(strcmp(archive[i], name) > 0)
        {
            for(int j = numberOfNames; j >= i; j--)
                strncpy(archive[j],archive[j-1],MAX_NAME_LEN);

            strncpy(archive[i], name, MAX_NAME_LEN);
            break;
        }

    }
    numberOfNames++;
    return 1;
}

// Entfernt den angegebenen Namen. Gibt bei Erfolg 1 zurück, ansonsten 0 (Name konnte nicht gefunden werden).
int removeName(const char *name)
{
    for(int i = 0; i < numberOfNames; i++) {
        if(strncmp(archive[i], name, MAX_NAME_LEN) == 0) {
            for(int j = i; j < numberOfNames; j++) {
                strcpy(archive[j-1], archive[j]); // Hans [j+1] -> Alexander [j] -> Hans\0nder [j]
            }
            numberOfNames--;
            return 1;
        }
    }
    return 0;
}



// Sortiert die Namen im Archiv aufsteigend.
void sortNames() {
    qsort(archive, numberOfNames, sizeof(archive[0]), compNames);
}
/*
static int compareNames(const void *arg1, const void *arg2)
{
    return compNames(arg1, arg2); //auskommentiert -> trust
}*/

/*
    char * temp =malloc(MAX_NAME_LEN);        //Ersatz String
    char * max = archive[0]; //qsort ? ; tolower nur einzelne chars
    int max_idx = 0;

    for(int i = 0; i < numberOfNames; i++){
        for(int j = 0; j < numberOfNames - i; j++){
            if(strcmp(archive[j], max) > 0){
                strcpy(max, archive[j]);
                max_idx = j;
            }
        }
        strcpy(temp,archive[numberOfNames - i]);
        strcpy(archive[numberOfNames - i],max);
        strcpy(archive[max_idx], temp);
    }
}
*/

// Gibt die Namen zeilenweise aus.
void printNames()
{
    for(int i = 0; i < numberOfNames; i++){
        printf("%s\n", archive[i]);
    }

}

// Leert das Archiv
void clearArchive()
{
    
}

static int compNames(const void* arg1, const void* arg2) { // returns 1 when arg1 > arg2
    char* name1 = (char*) arg1;
    char* name2 = (char*) arg2;
/*
    int i = 0;
    while(name1[i]) {
        name1[i] = tolower(name1[i]);
        i++;
    }

    i = 0;
    while(name2[i]) {
        name2[i] = tolower(name2[i]);
        i++;
    }
*/
    int i;
    for(i = 0; name1[i] != '\0' && name2[i] != '\0'; i++) {
        if(tolower(name1[i]) > tolower(name2[i])) return 1;
        else if(tolower(name1[i]) < tolower(name2[i])) return -1;
    }
    if(name1[i] != '\0') return -1;
    if(name2[i] != '\0') return 1;
    return 0;
}
