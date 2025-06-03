CC=gcc
CFLAGS=-Wall -Wextra -Werror
TARGET=tema1
ALLFILES=main.c functions.c tab.c browser.c

.PHONY: all

all: $(TARGET)

$(TARGET): $(ALLFILES)
	$(CC) $(CFLAGS) $^ -o ../$@