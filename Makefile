all: 
	g++ src/Blackjack.cpp src/Blackjack_functions.cpp src/resource.o -o bin/BlackJack_v1.0.1.exe -I include/SDL2 -L lib  -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer