/* BADULESCU Andrei-Marcel - 314CC */

#ifndef libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab.h"
#include "browser.h"
#include "functions.h"
#endif

void initialiseBrowser(browser *session, page *pageList) {
	// Initializarea santinelei
	session->list.previousTab = &session->list;
	session->list.nextTab = &session->list;
	session->list.value.forwardStack = NULL;
	session->list.value.backwardStack = NULL;
	session->list.value.currentPage = NULL;
	session->list.value.id = -1;

	// Adaugarea tab-ului default
	newTab(session, pageList, 0);
}

int newTab(browser *session, page *pageList, int tabCount) {
	tabList *ptr = (tabList *) malloc(sizeof(tabList));
	if (!ptr)
		return 1;

	// Configurarea pointerilor
	ptr->nextTab = &session->list;
	ptr->previousTab = session->list.previousTab;
	(session->list.previousTab)->nextTab = ptr;
	session->list.previousTab = ptr;

	// Configurarea noului tab
	ptr->value.id = tabCount;
	ptr->value.currentPage = pageList;
	ptr->value.backwardStack = NULL;
	ptr->value.forwardStack = NULL;

	// Schimbarea tab-ului curent la cel creat
	session->current = &ptr->value;
	return 0;
}

int closeTab(browser *session) {
	// Tab-ul default nu poate fi inchis
	if (session->current->id == session->list.nextTab->value.id) {
		return 0;
	}

	/* Initializarea unor pointeri pentru tab-urile
	din stanga si din dreapta celui curent */
	tabList *ptr = &session->list;
	while (ptr->value.id != session->current->id) {
		ptr = ptr->nextTab;
	}

	tabList *lhsPtr = ptr->previousTab;
	tabList *rhsPtr = ptr->nextTab;

	/* Curatarea memoriei folosite de stack-urile
	istoricului de navigare */
	emptyStack(&session->current->backwardStack);
	emptyStack(&session->current->forwardStack);

	/* Reconfigurarea pointerilor din lista
	si dealocarea memoriei folosite */
	lhsPtr->nextTab = rhsPtr;
	rhsPtr->previousTab = lhsPtr;
	free(ptr);

	// Tab-ul curent devine cel din stanga
	session->current = &lhsPtr->value;
	return 1;
}

int openTab(browser *session, int givenId) {
	tabList *ptr = session->list.nextTab;

	// Cautarea tab-ului care are ID-ul dat
	while (ptr->value.id != session->list.value.id && ptr->value.id != givenId) {
		ptr = ptr->nextTab;
	}

	/* Daca tab-ul nu exista,
	mesajul de eroare 403 va fi printat */
	if (ptr->value.id == session->list.value.id) {
		return 0;
	}

	/* Schimbarea tab-ului curent daca
	acesta este gasit */
	session->current = &ptr->value;
	return 1;
}

void nextTab(browser *session) {
	tabList *ptr = &session->list;
	while (ptr->value.id != session->current->id) {
		ptr = ptr->nextTab;
	}

	ptr = ptr->nextTab;

	// Sarim peste santinela din lista de tab-uri
	if (ptr->value.id == session->list.value.id) {
		ptr = ptr->nextTab;
	}

	session->current = &ptr->value;
}

void prevTab(browser *session) {
	tabList *ptr = &session->list;
	while (ptr->value.id != session->current->id) {
		ptr = ptr->nextTab;
	}

	ptr = ptr->previousTab;

	// Sarim peste santinela din lista de tab-uri
	if (ptr->value.id == session->list.value.id) {
		ptr = ptr->previousTab;
	}

	session->current = &ptr->value;
}

void printTabs(browser session, FILE *writeFile) {
	tabList *ptr = &session.list;
	while (ptr->value.id != session.current->id) {
		ptr = ptr->nextTab;
	}

	// Parcurgerea intregii liste de tab-uri
	do {
		// Santinela din lista de tab-uri este sarita
		if (ptr->value.id != -1) {
			fprintf(writeFile, "%d ", ptr->value.id);
		}

		ptr = ptr->nextTab;
	} while (ptr->value.id != session.current->id);

	// Printarea descrierii tab-ului curent
	//fprintf(writeFile, "\n%s\n", session.current->currentPage->description);
	fprintf(writeFile, "\n%s", session.current->currentPage->description);
}

int printHistory(browser session, int givenId, FILE *writeFile) {
	tabList *ptr = session.list.nextTab;

	// Cautarea tab-ului care are ID-ul dat
	while (ptr->value.id != -1 && ptr->value.id != givenId) {
		ptr = ptr->nextTab;
	}

	/* Daca tab-ul nu exista,
	mesajul de eroare 403 va fi printat */
	if (ptr->value.id == -1) {
		return 0;
	}

	// Afisarea istoricului de navigare complet pentru tab-ul cautat
	reversePrintStack(ptr->value.forwardStack, writeFile);
	fprintf(writeFile, "%s\n", ptr->value.currentPage->url);
	fflush(writeFile);
	printStack(ptr->value.backwardStack, writeFile);
	return 1;
}
