SRC=main.c fonctionsSDL.c score.c ball/ball.c menus.c renforcement/renforcement.c player/player.c terrain/terrain.c player/ordinateur.c screens/endScreen.c
EXE=main.out



CC=gcc
CFLAGS:=-Wall -Wextra -MMD -g $(sdl2-config --cflags)
#CFLAGS:=-Wall -Wextra -MMD -O2 $(sdl2-config --cflags)  # pour la version release
LDFLAGS:=-lSDL2_image -lSDL2_ttf -lSDL2_gfx -lm -lSDL2 -lSDL2_mixer
OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))
all: $(OBJ) 
	$(CC) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	@mkdir -p build/ball
	@mkdir -p build/renforcement
	@mkdir -p build/player
	@mkdir -p build/terrain
	@mkdir -p build/screens
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.o

-include $(DEP)