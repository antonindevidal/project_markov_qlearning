SRC=main.c
EXE=prog

CC=gcc
CFLAGS:=-Wall -Wextra -MMD -Og -g $(sdl2-config --cflags)
LDFLAGS:=-lSDL2_image -lSDL2_ttf -lSDL2_gfx -lm -lSDL2

OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

all: $(OBJ) 
	$(CC) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.o

-include $(DEP)