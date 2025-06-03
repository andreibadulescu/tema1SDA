/* BADULESCU Andrei-Marcel - 314CC */

typedef struct Browser {
	tab *current;
	tabList list;
} browser;

void initialiseBrowser(browser *session, page *pageList);

int newTab(browser *session, page *pageList, int tabCount);

int closeTab(browser *session);

int openTab(browser *session, int givenId);

void nextTab(browser *session);

void prevTab(browser *session);

void printTabs(browser session, FILE *writeFile);

int printHistory(browser session, int givenId, FILE *writeFile);
