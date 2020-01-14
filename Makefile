EXEC=game
SOURCES=$(wildcard src/*.cc)
OBJECTS=$(SOURCES:.cc=.o)
CCFLAGS=-Wall `sdl-config --cflags` -std=c++11
CC=g++
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) `pkg-config --cflags --libs sdl2` -lSDL2_image -lSDL2_ttf -lsfml-audio -o $(EXEC)
%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXEC)
