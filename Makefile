EXEC=game
SOURCES=$(wildcard src/*.cc)
OBJECTS=$(SOURCES:.cc=.o)
CCFLAGS=-Wall `sdl-config --cflags`
CC=g++
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) `pkg-config --cflags --libs sdl2` -lSDL2_image -lSDL2_ttf -o $(EXEC)
%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXEC)
