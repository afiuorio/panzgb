SOURCES = panzgb.c
OBJECTS=$(SOURCES:.c=.o)
COMPILER_FLAGS = -c -O2 -std=c99 -Wall -Wextra -pedantic -flto -march=native
EXECUTABLE = panzgb

CC = gcc
INCLUDE_PATHS = -Ilibpanzgb/include
LIBRARY_PATHS = -Llibpanzgb/lib
LINKER_FLAGS = -lSDL2 -lpanzgb

all: libpgb $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $@
.c.o:
	$(CC) $(INCLUDE_PATHS) $(COMPILER_FLAGS) $< -o $@

libpgb:
	git submodule update --remote libpanzgb
	cd libpanzgb && $(MAKE) && cd .. && cp libpanzgb/lib/libpanzgb.so libpanzgb.so

clean:
	@rm *.o

clobber:
	@rm *.o
	@rm panzgb
	@rm libpanzgb.so
	@rm -rf libpanzgb/
