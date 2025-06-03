/* BADULESCU Andrei-Marcel - 314CC */

void errorHandler(int errorId, FILE *logFile);

int parseInstruction(char instruction[]);

int readPages(int pageCount, page *pageList, FILE *readFile);

int executeInstructions(browser *currentSession, int pageCount, page *pageList, FILE *readFile, FILE *writeFile);
