/* BADULESCU Andrei-Marcel - 314CC */

#ifndef libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab.h"
#include "browser.h"
#include "functions.h"
#endif

/* Functie care afiseaza codul de eroare intors de functiile
din cadrul browser-ului */

void errorHandler(int errorId, FILE *logFile) {
	switch (errorId) {
	case 403:
		fprintf(logFile, "403 Forbidden\n");
		break;
	}
}

/* Functie care citeste instructiunile linie cu linie si apeleaza
functiile asociate */

int executeInstructions(browser *currentSession, int pageCount, page *pageList, FILE *readFile, FILE *writeFile) {
	int instructionCount = 0;
	if (fscanf(readFile, "%d", &instructionCount) == EOF)
		return 1;

	int tabCount = 1;
	for (int i = 0; i < instructionCount; i++) {
		char instruction[100];
		if (fscanf(readFile, "%s", instruction) == EOF)
			return 1;

		int instructionType = parseInstruction(instruction);
		int returnValue;
		int givenId;

		switch (instructionType) {
		case 1:
			if (newTab(currentSession, pageList, tabCount++))
				return 1;
			break;
		case 2:
			returnValue = closeTab(currentSession);
			if (!returnValue)
				errorHandler(403, writeFile);
			break;
		case 3:
			if (fscanf(readFile, "%d", &givenId) == EOF)
				return 1;
			returnValue = openTab(currentSession, givenId);
			if (!returnValue)
				errorHandler(403, writeFile);
			break;
		case 4:
			nextTab(currentSession);
			break;
		case 5:
			prevTab(currentSession);
			break;
		case 6:
			if (fscanf(readFile, "%d", &givenId) == EOF)
				return 1;
			returnValue = openPage(currentSession->current, pageList, pageCount, givenId);
			if (!returnValue)
				errorHandler(403, writeFile);
			if (returnValue == 2)
				return 1;
			break;
		case 7:
			returnValue = backwardPage(currentSession->current);
			if (!returnValue)
				errorHandler(403, writeFile);
			if (returnValue == 2)
				return 1;
			break;
		case 8:
			returnValue = forwardPage(currentSession->current);
			if (!returnValue)
				errorHandler(403, writeFile);
			if (returnValue == 2)
				return 1;
			break;
		case 9:
			printTabs(*currentSession, writeFile);
			break;
		case 10:
			if (fscanf(readFile, "%d", &givenId) == EOF)
				return 1;
			returnValue = printHistory(*currentSession, givenId, writeFile);
			if (!returnValue)
				errorHandler(403, writeFile);
			break;
		default:
			break;
		}
	}

	return 0;
}

/* Functie care citeste paginile introduse in fisierul de input
si le salveaza in vectorul alocat dinamic transmis prin referinta */

int readPages(int pageCount, page *pageList, FILE *readFile) {
	for (int i = 1; i < pageCount; i++) {
		if (fscanf(readFile, "%d", &pageList[i].id) == EOF)
			return 1;
		if (fscanf(readFile, "%s", pageList[i].url) == EOF)
			return 1;

		char description[100];

		// Sarim peste \n de dupa link
		if (!fgets(description, 5, readFile))
			return 1;
		if (!fgets(description, 100, readFile))
			return 1;

		// Lasam loc si pentru \0
		pageList[i].description = calloc(strlen(description) + 1, sizeof(char));
		strcpy(pageList[i].description, description);
	}

	return 0;
}

/* Functie care parseaza cuvantul-cheie al instructiunii si
returneaza codul specific pentru acel cuvant-cheie:
	1 := NEW_TAB
	2 := CLOSE
	3 := OPEN <ID>
	4 := NEXT
	5 := PREV
	6 := PAGE <ID>
	7 := BACKWARD
	8 := FORWARD
	9 := PRINT
	10 := PRINT_HISTORY <ID>
*/

int parseInstruction(char instruction[]) {
	if (!strcmp("NEW_TAB", instruction)) {
		return 1;
	}

	if (!strcmp("CLOSE", instruction)) {
		return 2;
	}

	if (!strcmp("OPEN", instruction)) {
		return 3;
	}

	if (!strcmp("NEXT", instruction)) {
		return 4;
	}

	if (!strcmp("PREV", instruction)) {
		return 5;
	}

	if (!strcmp("PAGE", instruction)) {
		return 6;
	}

	if (!strcmp("BACKWARD", instruction)) {
		return 7;
	}

	if (!strcmp("FORWARD", instruction)) {
		return 8;
	}

	if (!strcmp("PRINT", instruction)) {
		return 9;
	}

	if (!strcmp("PRINT_HISTORY", instruction)) {
		return 10;
	}

	return 0;
}
