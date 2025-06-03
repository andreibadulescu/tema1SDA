/* BADULESCU Andrei-Marcel - 314CC */

#ifndef libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tab.h"
#include "browser.h"
#include "functions.h"
#endif

int openPage(tab *currentTab, page *pageList, int pageCount, int givenId) {
	// Parcurgerea intregii liste de pagini
	for (int i = 0; i < pageCount; i++) {
		if (pageList[i].id == givenId) {
			/* Adaugarea paginii curente in istoric si actualizarea
			paginii curente si stivei Forward */
			if (pushOnStack(&currentTab->backwardStack, currentTab->currentPage))
				return 2;
			currentTab->currentPage = (pageList + i);
			emptyStack(&currentTab->forwardStack);
			break;
		}
	}

	/* Afisarea erorii 403 daca niciuna dintre pagini
	nu are un ID care sa se potriveasca celui cautat */
	if (currentTab->currentPage->id != givenId) {
		return 0;
	} else {
		return 1;
	}
}

int backwardPage(tab *currentTab) {
	// Afisarea erorii 403 daca stiva Backward este vida
	if (!currentTab->backwardStack) {
		return 0;
	}

	/* Plasarea paginii curente in stiva Forward si
	schimbarea acesteia in elementul din varful stivei Backward */
	if (pushOnStack(&currentTab->forwardStack, currentTab->currentPage))
		return 2;
	currentTab->currentPage = currentTab->backwardStack->value;
	popFromStack(&currentTab->backwardStack);
	return 1;
}

int forwardPage(tab *currentTab) {
	// Afisarea erorii 403 daca stiva Forward este vida
	if (!currentTab->forwardStack) {
		return 0;
	}

	/* Plasarea paginii curente in stiva Backward si
	schimbarea acesteia in elementul din varful stivei FOrward */
	if (pushOnStack(&currentTab->backwardStack, currentTab->currentPage))
		return 2;
	currentTab->currentPage = currentTab->forwardStack->value;
	popFromStack(&currentTab->forwardStack);
	return 1;
}

int pushOnStack(stack **head, page *newValue) {
	// Alocarea memoriei si setarea unei valori date
	stack *newElement = (stack *)malloc(sizeof(stack));
	if (!newElement)
		return 1;
	newElement->value = newValue;

	// Rearanjarea elementelor pe stack
	if (!*head) {
		newElement->under = NULL;
		*head = newElement;
	} else {
		newElement->under = *head;
		*head = newElement;
	}

	return 0;
}

void popFromStack(stack **head) {
	if (!*head) {
		return;
	}

	// Dealocarea memoriei
	stack *ptr = *head;
	*head = (*head)->under;
	free(ptr);
}

void emptyStack(stack **head) {
	// Elementele sunt eliminate pana stiva este vida
	while (*head) {
		popFromStack(head);
	}
}

void printStack(stack *head, FILE *writeFile) {
	stack *ptr = head;

	// Printarea link-urilor de pe stiva
	while (ptr) {
		fprintf(writeFile, "%s\n", ptr->value->url);
		ptr = ptr->under;
	}
}

void reversePrintStack(stack *head, FILE *writeFile) {
	if (!head) {
		return;
	}

	/* Printarea link-urilor recursiv de pe
	stiva in ordine inversa */
	reversePrintStack(head->under, writeFile);
	fprintf(writeFile, "%s\n", head->value->url);
}
