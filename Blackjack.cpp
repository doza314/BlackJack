#include "Blackjack.hpp"
#include <string>

//Variable Initialization 
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

bool isQuit = false;
bool isGameOver = false;
bool notPlaying = false;
int functionNumber = 0;

//Render Queue
std::vector<SDL_Surface*> surfaceQ;
std::vector<SDL_Texture*> textureQ;
std::vector<SDL_Rect> rectQ;


gameClass gameObject;  //Responsible for the game states and textures

deckClass deck; //Responsible for the deck

playerClass player;  //Responsible for player's cards

playerClass dealer;  //Responsible for dealer's cards

optionsClass options; //Responsible for the options textures

splitClass split; //Responsible for the split cards

int main() {
    srand(time(NULL));
    
   
        //Start up SDL and create window

            //Initializing SDL
            if (SDL_Init(SDL_INIT_VIDEO) < 0) 
            {
                std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
                return 1;
            }
            //Initializing SDL_ttf
            if (TTF_Init() == -1) 
            {
                std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
                return 1;
            }
            //Creating the window
            window = SDL_CreateWindow("Blackjack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
            if (window == nullptr) 
            {
                std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                return 1;
            }

            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) {
                std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
                return 1;
            }

   //initial_assignment(renderer, deck);
   //shuffle();
   //initial_deal();

    //Initital texture creation
    createTextures(renderer, gameObject, options);
        
    //Main loop
    while (!isQuit) {
    //Start menu
    showStartMenu(renderer);
    
        while (!notPlaying) 
        {
        // Bet Prompt
        promptForBet(renderer); 

        initial_assignment(renderer, deck);
        shuffle();

        //Game Initialization
        initial_deal(deck);
    
    
        //Main game screen
        game(renderer);

        //Results
        playAgain(renderer);
        }
    }

    return 0;
}