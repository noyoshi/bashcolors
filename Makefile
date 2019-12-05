EXE_NAME = colorize
CC = gcc

all: colorize

colorize: colorize.c
	$(CC) $^ -o $(EXE_NAME)

clean:
	@rm -f $(EXE_NAME)