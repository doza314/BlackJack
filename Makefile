all: 
	g++ Blackjack.cpp Blackjack_functions.cpp -o BlackJack -I src/include/SDL2 -L src/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer