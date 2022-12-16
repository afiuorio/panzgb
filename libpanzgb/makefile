SOURCES = $(wildcard src/*.c)
OBJECTS=$(SOURCES:.c=.o)
COMPILER_FLAGS = -c -O2 -std=c99 -Wall -Wextra -pedantic -flto -march=native -fpic
EXECUTABLE = libpanzgb.so

CC = gcc
INCLUDE_PATHS =
LIBRARY_PATHS =
LINKER_FLAGS = -shared

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@
	mkdir -p include
	mkdir -p lib
	cp src/panzgb.h include/panzgb.h
	mv $(EXECUTABLE) lib/$(EXECUTABLE)
.c.o:
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) $< -o $@

clean:
	@rm src/*.o

clobber:
	@rm src/*.o
	@rm -rf lib/
	@rm -rf include/
