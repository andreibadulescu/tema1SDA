/* BADULESCU Andrei-Marcel - 314CC */

#define libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab.h"
#include "browser.h"
#include "functions.h"

int main(void) {
	// Deschiderea fisierele de date
	FILE *writeFile = fopen("tema1.out", "w");
	FILE *readFile = fopen("tema1.in", "r");

	// Initializarea variabilelor
	browser currentSession;
	currentSession.current = NULL;

	int pageCount = 0;
	if (fscanf(readFile, "%d", &pageCount) == EOF)
		return 1;
	pageCount++;

	page *pageList;
	pageList = (page *)malloc(pageCount * sizeof(page));
	if (!pageList)
		return 1;

	// Adaugarea paginii default
	pageList[0].id = 0;
	strcpy(pageList[0].url, "https://acs.pub.ro/");
	pageList[0].description = calloc(18, sizeof(char));

	if (!pageList[0].description)
		return 1;

	strcpy(pageList[0].description, "Computer Science\n");
	initialiseBrowser(&currentSession, pageList);

	// Citirea paginilor oferite la citire
	if (readPages(pageCount, pageList, readFile))
		return 1;

	// Parsam instructiunile
	executeInstructions(&currentSession, pageCount, pageList, readFile, writeFile);

	// Inchidem fisierele de date
	fclose(readFile);
	fclose(writeFile);

	// Curatam memoria
	for (int i = 0; i < pageCount; i++) {
		free(pageList[i].description);
	}

	currentSession.current = &currentSession.list.previousTab->value;

	// Inchidem tab-urile din browser
	while (closeTab(&currentSession));
	emptyStack(&currentSession.current->backwardStack);
	emptyStack(&currentSession.current->forwardStack);

	// Inchidem tab-ul care nu poate fi inchis de user
	free(currentSession.list.nextTab);

	currentSession.list.nextTab = &currentSession.list;
	currentSession.list.previousTab = &currentSession.list;

	free(pageList);
	return 0;
}
