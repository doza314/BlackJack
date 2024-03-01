#include "Blackjack.hpp"
#include <string>
//Variable Initialization 
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

bool isQuit = false;
bool isGameOver = false;
bool notPlaying = false;

SDL_Color white = {255,255,255,255};
double balance = 1000.00;
double bet;
int turn = 0;
int numOptions = 0;
bool hitbool;
bool standbool;
bool doubleDownbool = false;
bool splitbool = false;
bool surrenderbool;
int newCards = 0;
int playerTotal = 0;
int dealerTotal = 0;
int values[52];

SDL_Texture* betTexture = nullptr;
SDL_Texture* balanceTexture = nullptr;
SDL_Texture* hiddenCard = nullptr;
SDL_Texture* firstDealerCard = nullptr;
SDL_Texture* hitTexture = nullptr;
SDL_Texture* standTexture = nullptr;
SDL_Texture* doubleDTexture = nullptr;
SDL_Texture* surrenderTexture = nullptr;
SDL_Texture* splitTexture = nullptr;

std::string names[52];
std::vector<int> player_vals;
std::vector<std::string> player_names;
std::vector<int> dealer_vals;
std::vector<std::string> dealer_names;

std::vector<int> split_vals1;
std::vector<std::string> split_names1;
std::vector<SDL_Rect> split_rects1;

std::vector<int> split_vals2;
std::vector<std::string> split_names2;
std::vector<SDL_Rect> split_rects2;

std::vector<SDL_Texture*> playerCardTextures;
std::vector<SDL_Surface*> playerCardSurfaces;
std::vector<SDL_Rect> playerCardRects;

std::vector<SDL_Texture*> dealerCardTextures;
std::vector<SDL_Surface*> dealerCardSurfaces;
std::vector<SDL_Rect> dealerCardRects;

std::vector<SDL_Texture*> allTextures;
std::vector<SDL_Surface*> allSurfaces;
std::vector<SDL_Rect> allRects;

int main() {
    srand(time(NULL));
    
    //Initializing SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    //Initializing SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        return 1;
    }
    //Creating the window
    window = SDL_CreateWindow("Blackjack", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }
        
    while (!isQuit) {
    //Start menu
    showStartMenu(renderer);
    
    // Bet Prompt
    promptForBet(renderer, balance, bet); 
    initial_assignment(values, names);
    shuffle(values, names);
    initial_deal(values, names, playerTotal, dealerTotal, player_vals,  player_names, dealer_vals, dealer_names);

    std::cout << "cards/" <<  player_names[0] << ".png" << std::endl;
    std::cout << "cards/" <<  player_names[1] << ".png" << std::endl;
    std::cout << "cards/" <<  dealer_names[0] << ".png" << std::endl;
    std::cout << "cards/" <<  dealer_names[1] << ".png" << std::endl;
    
    //Game
    while (!notPlaying) {
        game(renderer, balance, bet, playerTotal, dealerTotal, allTextures, allSurfaces, allRects,
        notPlaying, hitbool, standbool, doubleDownbool, splitbool, surrenderbool);
    }
        
    
    }

    //Initial assignment, shuffling, and dealing
    /*
    initial_assignment(values, names);
    shuffle(values, names);
    initial_deal(values, names, player_vals, player_names, dealer_vals, dealer_names);
    */

    //print_deck(values, names);

    return 0;
}