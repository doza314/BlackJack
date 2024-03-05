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
extern int functionNumber;

extern std::vector<SDL_Surface*> surfaceQ;
extern std::vector<SDL_Texture*> textureQ;
extern std::vector<SDL_Rect> rectQ;
//CLASSES

    //Deck variables
    class deckClass 
    {
        public:

        int values[52];
        std::vector<std::string> names;

        std::vector<SDL_Texture*> textures;
        std::vector<SDL_Surface*> surfaces;
        std::vector<SDL_Rect> rects;
    };

    //Players' card variables
    class playerClass 
    {
        public:
        //Graphial Variables
        SDL_Texture* firstCardTexture;
        std::vector<SDL_Texture*> textures;
        std::vector<SDL_Surface*> surfaces;
        std::vector<SDL_Rect> rects;

        //Variables
        std::vector<int> values;
        std::vector<std::string> names;

        //Variables
        int total;
        int newCards;
    };

    //Game variables
    class gameClass 
    {
        public:
        SDL_Color white = {255,255,255,255};
        SDL_Color red = {255,0,0,255};
        std::string selectorString = ">";
        int selectorPos = 0;
        std::string inputString = "";
        //Graphical Variables
        //Title Screen
        SDL_Texture* titleTexture = nullptr;
        SDL_Texture* pressEnterTexture = nullptr;
        SDL_Texture* blankTexture = nullptr;
        
        SDL_Rect titleRect;
        SDL_Rect pressEnterRect;

        //Bet Prompt Screen
        SDL_Texture* balanceTexture = nullptr; //Also used in Game Screen
        SDL_Texture* betPromptTexture = nullptr;
        SDL_Texture* invalidTexture = nullptr;
        SDL_Texture* underscoreTexture = nullptr;
        SDL_Texture* inputTexture = nullptr;
        
        SDL_Rect balanceRect;
        SDL_Rect betPromptRect;
        SDL_Rect invalidRect;
        SDL_Rect underscoreRect;
        SDL_Rect inputRect;

        //Game Screen
        SDL_Texture* selectorTexture = nullptr;
        SDL_Texture* betTexture = nullptr;
        SDL_Texture* youTexture = nullptr;
        SDL_Texture* dealerTexture = nullptr;

        SDL_Texture* hiddenCardTexture = nullptr;
        SDL_Surface* hiddenCardSurface = nullptr;

        SDL_Texture* firstDealerCardTexture = nullptr;
        SDL_Surface* firstDealerCardSurface = nullptr;
        
        SDL_Rect youRect;
        SDL_Rect dealerRect;
        SDL_Rect selectorRect;
        SDL_Rect betRect;
        SDL_Rect hiddenCardRect;
        SDL_Rect firstDealerCardRect = hiddenCardRect;

        //Variables
        bool isQuit = false;
        bool isGameOver = false;
        bool notPlaying = false;
    
        bool hitbool = false;
        bool standbool = false;
        bool doublebool = false;
        bool surrenderbool = false;
        bool splitbool = false;

        int numOptions = 0;
        int turn = 0;
        int newCards = 0;
        Uint32 lastToggle = 0;

        double balance = 1000.00;
        double bet = 0.00;
    };

    //Split variables
    class splitClass 
    {
        public:
        //Graphical Variables
        std::vector<SDL_Texture*> topTextures;
        std::vector<SDL_Surface*> topSurfaces;
        std::vector<SDL_Rect> topRects;

        std::vector<SDL_Texture*> bottomTextures;
        std::vector<SDL_Surface*> bottomSurfaces;
        std::vector<SDL_Rect> bottomRects;

        //Variables
        std::vector<int> topValues;
        std::vector<std::string> topNames;

        std::vector<int> bottomValues;
        std::vector<std::string> bottomNames;

        int topTotal;
        int bottomTotal;
    };

    class optionsClass 
    {
        public:
        //Textures
        SDL_Texture* hitTexture = nullptr;
        SDL_Texture* standTexture = nullptr;
        SDL_Texture* doubleDTexture = nullptr;
        SDL_Texture* surrenderTexture = nullptr;
        SDL_Texture* splitTexture = nullptr;

        SDL_Rect hitRect;
        SDL_Rect standRect;
        SDL_Rect doubleDRect;
        SDL_Rect surrenderRect;
        SDL_Rect splitRect;
    };

    extern deckClass deck;
    extern playerClass player;
    extern playerClass dealer;
    extern gameClass gameObject;
    extern splitClass split;
    extern optionsClass options;


//SECONDARY FUNCTIONALITY TEXTURES
    int calculateTextWidth(std::string text);
    bool isConvertibleToDouble(std::string str);
    std::string toStringWithPrecision(const double value, const int n);
    SDL_Surface* cardSurface(std::string cardName);
    SDL_Texture* cardTexture(SDL_Renderer* renderer, SDL_Surface* cardSurface);
    SDL_Texture* renderText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);

void createTextures(SDL_Renderer* renderer, gameClass& gameObject, optionsClass& options);
void updateQueue(SDL_Renderer* renderer);
void presentQueue(SDL_Renderer* renderer, std::vector<SDL_Texture*>& textureQ, std::vector<SDL_Rect*>& rectQ);
void toggleText(SDL_Renderer* renderer, SDL_Texture* &flashingText, gameClass& gameObject, Uint32 &lastToggle, int &functionNumber);

void showStartMenu(SDL_Renderer* renderer); 
void promptForBet(SDL_Renderer* renderer);  
void game(SDL_Renderer* renderer);

//GAME LOGIC FUNCTIONS
    template<size_t N>
    void random_array(int (&randoms)[N], int int_limit);

    void print_deck();
    void initial_assignment(SDL_Renderer* renderer, deckClass& deck);
    void shuffle();
    void initial_deal(deckClass);
    void hit(playerClass& player_dealer);
