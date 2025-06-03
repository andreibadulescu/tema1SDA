/* BADULESCU Andrei-Marcel - 314CC */

typedef struct Page {
	int id;
	char url[50];
	char *description;
} page;

typedef struct Stack {
	page *value;
	struct Stack *under;
} stack;

typedef struct Tab {
	int id;
	page *currentPage;
	stack *backwardStack;
	stack *forwardStack;
} tab;

typedef struct TabList {
	struct TabList *nextTab;
	struct TabList *previousTab;
	tab value;
} tabList;

int openPage(tab *currentTab, page *pageList, int pageCount, int givenId);

int backwardPage(tab *currentTab);

int forwardPage(tab *currentTab);

int pushOnStack(stack **head, page *newValue);

void popFromStack(stack **head);

void emptyStack(stack **head);

void printStack(stack *head, FILE *writeFile);

void reversePrintStack(stack *head, FILE *writeFile);
