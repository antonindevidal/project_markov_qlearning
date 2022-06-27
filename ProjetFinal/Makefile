SRC=main.c fonctionsSDL.c score.c ./ball/ball.c menus.c renforcement.c
OBJ=main.o fonctionsSDL.o score.o ./ball/ball.o menus.o renforcement.o
DEP=main.d fonctionsSDL.d score.d ./ball/ball.d menus.d renforcement.d
EXE=main.out

CC=gcc
CFLAGS:=-Wall -Wextra -MMD -g $(sdl2-config --cflags)
#CFLAGS:=-Wall -Wextra -MMD -O2 $(sdl2-config --cflags)  # pour la version release
LDFLAGS:=-lSDL2_image -lSDL2_ttf -lSDL2_gfx -lm -lSDL2

all: $(OBJ) 
	echo OBJ
	$(CC) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.o

-include $(DEP)