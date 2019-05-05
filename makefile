SOURCES = $(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
COMPILER_FLAGS = -c -g -std=c99 -Wall -Wextra -pedantic -flto -march=native
EXECUTABLE = panzgb

CC = gcc
INCLUDE_PATHS =
LIBRARY_PATHS =
LINKER_FLAGS = -lSDL2

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@
.c.o:
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) $< -o $@
clean:
	@rm src/*.o
clobber:
	@rm src/*.o
	@rm panzgb
