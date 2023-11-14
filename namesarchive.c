#include "namesarchive.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int numberOfNames = 0;
static char archive[MAX_NAMES][MAX_NAME_LEN] = {0};

// Fügt einen Namen hinzu. Im Fehlerfall (Archiv ist voll) soll 0, ansonsten 1 zurückgegeben werden.
// Ist der angegebene Name länger als die zulässige Namenslänge, wird der Name abgeschnitten hinzugefügt. Rückgabe ist dann 1.
int addName(const char *name)
{

}


// Wie addName. Fügt Namen aber direkt sortiert hinzu. Voraussetzung ist ein bereits sortiertes Archiv.
int addNameSorted(const char *name)
{

}

// Entfernt den angegebenen Namen. Gibt bei Erfolg 1 zurück, ansonsten 0 (Name konnte nicht gefunden werden).
int removeName(const char *name)
{

}


// Sortiert die Namen im Archiv aufsteigend.
void sortNames()
{

}


// Gibt die Namen zeilenweise aus.
void printNames()
{

}