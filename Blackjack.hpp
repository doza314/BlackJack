#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>

extern bool isQuit;
extern bool isGameOver;
extern bool notPlaying;
extern double bet;
extern double balance;
extern int turn;
extern int numOptions;
extern int newCards;
extern int playerTotal;
extern int dealerTotal;
extern int values[52];

extern SDL_Texture* betTexture;
extern SDL_Texture* balanceTexture;
extern SDL_Texture* hiddenCard;
extern SDL_Texture* firstDealerCard;
extern SDL_Texture* hitTexture;
extern SDL_Texture* standTexture;
extern SDL_Texture* doubleDTexture;
extern SDL_Texture* surrenderTexture;
extern SDL_Texture* splitTexture;

extern std::vector<int> split_vals1;
extern std::vector<std::string> split_names1;
extern std::vector<SDL_Rect> split_rects1;

extern std::vector<int> split_vals2;
extern std::vector<std::string> split_names2;
extern std::vector<SDL_Rect> split_rects2;

extern std::string names[52];
extern std::vector<int> player_vals;
extern std::vector<std::string> player_names;
extern std::vector<int> dealer_vals;
extern std::vector<std::string> dealer_names;

extern std::vector<SDL_Texture*> playerCardTextures;
extern std::vector<SDL_Surface*> playerCardSurfaces;
extern std::vector<SDL_Rect> playerCardRects;

extern std::vector<SDL_Texture*> dealerCardTextures;
extern std::vector<SDL_Surface*> dealerCardSurfaces;
extern std::vector<SDL_Rect> dealerCardRects;

extern std::vector<SDL_Texture*> allTextures;
extern std::vector<SDL_Surface*> allSurfaces;
extern std::vector<SDL_Rect> allRects;

extern SDL_Color white;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern TTF_Font* font; 

int calculateTextWidth(std::string text);
bool isConvertibleToDouble(std::string str);
std::string toStringWithPrecision(const double value, const int n);

void showStartMenu(SDL_Renderer* renderer);
void promptForBet(SDL_Renderer* renderer, double& balance, double& bet);
SDL_Surface* cardSurface(std::string cardName);
SDL_Texture* cardTexture(SDL_Renderer* renderer, SDL_Surface* cardSurface);
SDL_Texture* renderText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);

void showCards(SDL_Renderer* renderer, std::vector<std::string> player_names, std::vector<std::string> dealer_names, SDL_Texture* &hiddenCard, SDL_Texture* &firstDealerCard,  std::vector<SDL_Texture*>& playerCardTextures, std::vector<SDL_Surface*>& playerCardSurfaces, std::vector<SDL_Rect>& playerCardRects,
 std::vector<SDL_Texture*>& dealerCardTextures, std::vector<SDL_Surface*>& dealerCardSurfaces, std::vector<SDL_Rect>& dealerCardRects, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects);

void gameText(SDL_Renderer* renderer, double balance, SDL_Texture* &betTexture, SDL_Texture* &balanceTexture, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects);
void showPrompt(SDL_Renderer* renderer, SDL_Texture* &hitTexture, SDL_Texture* &standTexture, SDL_Texture* &doubleDTexture, SDL_Texture* &surrenderTexture, SDL_Texture* &splitTexture, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects, std::vector<int> player_vals, int& numOptions, std::vector<int>& dealer_vals);
void gameTexturesCopy(SDL_Renderer* renderer, std::vector<SDL_Texture*> allTextures, std::vector<SDL_Surface*> allSurfaces, std::vector<SDL_Rect> allRects);

void game(SDL_Renderer* renderer, double& balance, double& bet, int& playerTotal, int& dealerTotal, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects, 
bool &notPlaying, bool &hitbool, bool &standbool, bool &doubleDownbool, bool &splitbool, bool &surrenderbool);

template<size_t N>
void random_array(int (&randoms)[N], int int_limit);

void print_deck(int values[52], std::string names[52]);
void initial_assignment(int (&values)[52], std::string (&names)[52]);
void shuffle(int (&values)[52], std::string (&names)[52]);
void initial_deal(int (&values)[52], std::string (&names)[52], int& playerTotal, int& dealerTotal, std::vector<int>& player_vals, std::vector<std::string>& player_names, std::vector<int>& dealer_vals, std::vector<std::string>& dealer_names);
void hit(int (&values)[52], std::string (&names)[52], int& total, std::vector<int>& vals, std::vector<std::string>& nams, int& newCards);
