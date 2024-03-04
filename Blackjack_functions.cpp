#include "Blackjack.hpp"



//SECONDARY FUNCTIONALITY TEXTURES

    //Function to calculate text width
    int calculateTextWidth(std::string text) 
    {
    int textWidth = 0;
    textWidth = text.length()*18;
    return textWidth;
    }

    //Function to check if string can be converted to double
    bool isConvertibleToDouble(std::string str) 
    {
    std::istringstream iss(str);
    double val;
    iss >> val;
    // Check if entire string was consumed and if only whitespace remains.
    return iss.eof() && !iss.fail(); 
    }

    //Function to convert double to string
    std::string toStringWithPrecision(const double value, const int n = 2) 
    {
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << value;
    return out.str();
    }

    //Create texture from string
    SDL_Texture* renderText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer) 
    {
        // Open the font
        TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
        if (font == nullptr) 
        {
            std::cerr << "Failed to load font: " << TTF_GetError() <<std::endl;
            return nullptr;
        }

        // Render the message to an SDL_Surface
        SDL_Surface* surf = TTF_RenderText_Solid(font, message.c_str(), color);
        if (surf == nullptr) 
        {
            TTF_CloseFont(font);
            std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
            return nullptr;
        }

        // Convert the surface to a texture
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
        if (texture == nullptr) 
        {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        }

        // Clean up the surface and font
        SDL_FreeSurface(surf);
        TTF_CloseFont(font);

        return texture;
    }

    //Creates a card surface
    SDL_Surface* cardSurface(std::string cardName) 
    {
        std::string path = "cards/" + cardName + ".png";
        SDL_Surface* surface = IMG_Load(path.c_str());
        return surface;
    }

    //Creates a card texture
    SDL_Texture* cardTexture(SDL_Renderer* renderer, SDL_Surface* cardSurface) 
    {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, cardSurface);
        return texture;
    }

//Creates all textures
void createTextures(SDL_Renderer* renderer, gameClass& gameObject, optionsClass& options) 
{
    //Game Textures
    //Main Menu Textures
    gameObject.titleTexture = renderText("Blackjack !", "C:/Windows/Fonts/arial.ttf", gameObject.white, 48, renderer);
    gameObject.pressEnterTexture = renderText("Press Enter", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.blankTexture = renderText(" ", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);

        //Main Menu Rectangles
        gameObject.titleRect = {1280 / 2 - 200, 720 / 2 - 70, 400, 100};
        gameObject.pressEnterRect = {1280 / 2 - 100, 720 / 2 + 25, 200, 50};
    

    //Bet Prompt Textures
    gameObject.betPromptTexture  = renderText("Enter your bet: ", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.underscoreTexture = renderText("_", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.invalidTexture = renderText("Invalid input! Bet must be a number less than or equal to your balance!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 24, renderer);

        //Bet Prompt Rectangles
        gameObject.betPromptRect = {1280 / 2 - 200, 720 / 2 + 25, 225, 50};
        gameObject.underscoreRect = {1280 / 2 + 20, 720 / 2 + 25, 20, 50};
        gameObject.invalidRect = {1280/2 - 500, 720 / 2 + 100, 1000, 50};

    
    //Other game textures
    gameObject.balanceTexture = renderText("Balance : $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.betTexture = renderText("Bet : $" + toStringWithPrecision(gameObject.bet), "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.selectorTexture = renderText(">", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.youTexture = renderText("You: ", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.dealerTexture = renderText("Dealer: ", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);

        //Other game Rectangles
        gameObject.balanceRect = {20, 20, 400, 50};
        gameObject.betRect = {20, 70, 250, 50};
        gameObject.selectorRect = {20, 120, 20, 50};
        gameObject.youRect = {390, 550, 100, 50};
        gameObject.dealerRect = {390, 275, 100, 50};
    

    //Options Textures
    options.hitTexture = renderText("Hit", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.standTexture = renderText("Stand", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.doubleDTexture = renderText("Double Down", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.surrenderTexture = renderText("Surrender", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.splitTexture = renderText("Split", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);

        //Options Rectangles
        options.hitRect = {100, 300, 42, 50};
        options.standRect = {100, 350, 70, 50};
        options.doubleDRect = {100, 400, 154, 50};
        options.surrenderRect = {100, 500, 70, 50};
        options.splitRect = {100, 450, 126, 50};

    //Deck Textures
    gameObject.hiddenCardSurface = cardSurface("hidden");
    gameObject.hiddenCardTexture = cardTexture(renderer, gameObject.hiddenCardSurface);

    
    //Assign textures to each card in deck
    SDL_Surface* surface;
    SDL_Texture* texture;
    for (int i = 0; i < 52; i++) 
    {  
        surface = cardSurface(deck.names[i]);
        texture = cardTexture(renderer, surface);

      deck.surfaces.push_back(surface);
      deck.textures.push_back(texture);
    }
    
    
}

/**Function numbers

1 - showStartMenu
2 - promptForBet
3 - Game
4 - Hit
5 - Stand
6 - Double
7 - Surrender
8 - Split

**/

//Updates render qeueue
void updateQueue(SDL_Renderer* renderer) 
{
    switch (functionNumber) 
    {
        case 1: //Start Menu
            textureQ.push_back(gameObject.titleTexture);
            rectQ.push_back(gameObject.titleRect);
            textureQ.push_back(gameObject.pressEnterTexture);
            rectQ.push_back(gameObject.pressEnterRect);
        break;
        case 2: //Prompt for bet
            textureQ.push_back(gameObject.underscoreTexture); //Underscore in position 0
            rectQ.push_back(gameObject.underscoreRect);

            textureQ.push_back(gameObject.inputTexture); //Input in position 1
            rectQ.push_back(gameObject.inputRect);

            textureQ.push_back(gameObject.balanceTexture); 
            rectQ.push_back(gameObject.balanceRect);

            textureQ.push_back(gameObject.betPromptTexture);
            rectQ.push_back(gameObject.betPromptRect);
            
            //Invalid texture in position 4

        break;
        case 3: //Game

            textureQ.push_back(gameObject.selectorTexture); //Selector in position 0
            rectQ.push_back(gameObject.selectorRect);

            textureQ.push_back(gameObject.balanceTexture); //Balance in position 1
            rectQ.push_back(gameObject.balanceRect);

            textureQ.push_back(gameObject.betTexture); //Bet in position 2
            rectQ.push_back(gameObject.betRect);

            textureQ.push_back(gameObject.dealerTexture); //"Dealer: " in position 3
            rectQ.push_back(gameObject.dealerRect);

            textureQ.push_back(gameObject.youTexture); //"You: " in position 4
            rectQ.push_back(gameObject.youRect);

            textureQ.push_back(options.hitTexture); //"Hit" in position 5
            rectQ.push_back(options.hitRect);

            textureQ.push_back(options.standTexture); //"Stand" in position 6
            rectQ.push_back(options.standRect);

            textureQ.push_back(options.doubleDTexture); //"Double Down" in position 7    
            rectQ.push_back(options.doubleDRect);

            textureQ.push_back(options.surrenderTexture); //"Surrender" in position 8
            rectQ.push_back(options.surrenderRect);

            textureQ.push_back(options.splitTexture); //"Split" in position 9
            rectQ.push_back(options.splitRect);
        
        
        
        for (int i = 0; i < player.textures.size(); i++) {
                std::cout << "Player:" << std::endl;
                std::cout << player.rects[i].x << " " << player.rects[i].y << std::endl;
                textureQ.push_back(player.textures[i]);
                rectQ.push_back(player.rects[i]);
            }   
            for (int i = 0; i < dealer.textures.size(); i++) {

                std::cout << "Dealer:" << std::endl;
                std::cout << dealer.rects[i].x << " " << dealer.rects[i].y << std::endl;
                textureQ.push_back(dealer.textures[i]);
                rectQ.push_back(dealer.rects[i]);
            }
            std::cout<< "textureQ size: " << textureQ.size() << std::endl;
            std::cout<< "rectQ size: " << rectQ.size() << std::endl;
            
        break;
        case 4: //Hit
        break;
        case 5: //Stand

        break;
        case 6: //Double

        break;
        case 7: //Surrender

        break;
        case 8: //Split

        break; 
    }
}
//Adds textures to queue
void addToQueue() 
{

}
//Presents the queue
void presentQueue(SDL_Renderer* renderer, std::vector<SDL_Texture*>& textureQ, std::vector<SDL_Rect>& rectQ) 
{
    for (int i = 0; i < textureQ.size(); i++) 
    {
        SDL_RenderCopy(renderer, textureQ[i], NULL, &rectQ[i]);
    }

        SDL_RenderPresent(renderer);
}

void toggleText(SDL_Renderer* renderer, SDL_Texture* &flashingText, gameClass& gameObject, Uint32 &lastToggle, int &functionNumber) 
{   
    //Time variables
    Uint32 currentTime = SDL_GetTicks();
    const Uint32 toggleInterval = 250;
    static bool showText = true; // Static to maintain the state between calls

    // Check if it's time to toggle the text visibility
    if (currentTime - lastToggle > toggleInterval) {
        showText = !showText; // Toggle visibility
        lastToggle = currentTime; // Reset the last toggle time
    }

    // Render the text if it's set to be shown
    if (showText) {
        if (functionNumber == 1) {
            flashingText = gameObject.pressEnterTexture;
        }
        else if (functionNumber == 2) {
            flashingText = gameObject.underscoreTexture;
        }
        else if (functionNumber == 3) {
            flashingText = gameObject.selectorTexture;
        }
    }
    else {
        flashingText = gameObject.blankTexture;
    }
}




/////////////////////////////////////////////////////////////////////////////////FUCKED UP CODE BE CAREFUL/////////////////////////////////////////////////////////////////////////////////

//Start Menu
void showStartMenu(SDL_Renderer* renderer) 
{
    functionNumber = 1;

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    bool startGame = false;
    SDL_Event event;

    updateQueue(renderer);
    presentQueue(renderer, textureQ, rectQ);

    while (!startGame) 
    {
        while (SDL_PollEvent(&event) != 0) 
        {
            if (event.type == SDL_QUIT) 
            {
                isQuit = true;
                startGame = true;
            } 
            else if (event.type == SDL_KEYDOWN) 
            {
                if (event.key.keysym.sym == SDLK_RETURN) 
                {
                    startGame = true;
                }
            }
        }
        SDL_RenderClear(renderer);
        toggleText(renderer, textureQ[1], gameObject, gameObject.lastToggle, functionNumber);// Update the screen
        presentQueue(renderer, textureQ, rectQ);
    }
    textureQ.clear();
    rectQ.clear();
    SDL_DestroyTexture(gameObject.titleTexture);
    SDL_DestroyTexture(gameObject.pressEnterTexture);
}

//Prompt for bet
void promptForBet(SDL_Renderer* renderer) 
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    functionNumber = 2;
    bool done = false;
    bool printError = false;
    int inputStringWidth = 0;
    int underscoreIndex;
    SDL_Event event;

    updateQueue(renderer);
    presentQueue(renderer, textureQ, rectQ);
    
    while (!done) 
    {
        while (SDL_PollEvent(&event) != 0) 
        {
             switch (event.type)
             {
                case SDL_QUIT:
                    isQuit = true;
                    done = true;
                break;

                case SDL_TEXTINPUT:  //Key presses

                    gameObject.inputString += event.text.text;
                    inputStringWidth = calculateTextWidth(gameObject.inputString);

                    gameObject.underscoreRect = {1280 / 2 + 20 + inputStringWidth, 720 / 2 + 25, 20, 50};
                    gameObject.inputRect = {1280 / 2 + 20, 720/2 + 25, inputStringWidth, 50};
                    gameObject.inputTexture = renderText(gameObject.inputString, "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                
                    rectQ[0] = gameObject.underscoreRect;

                    textureQ[1] = gameObject.inputTexture;
                    rectQ[1] = gameObject.inputRect;

                    SDL_RenderClear(renderer);
                    presentQueue(renderer, textureQ, rectQ);
                break;

                case SDL_KEYDOWN: 
                    if (event.key.keysym.sym == SDLK_BACKSPACE && !gameObject.inputString.empty()) 
                    {
                        // Remove the last character
                        gameObject.inputString.pop_back();                    
                        SDL_RenderClear(renderer);

                        inputStringWidth = calculateTextWidth(gameObject.inputString);

                        gameObject.underscoreRect = {1280 / 2 + 20 + inputStringWidth, 720 / 2 + 25, 20, 50};
                        gameObject.inputRect = {1280 / 2 + 20, 720/2 + 25, inputStringWidth, 50};

                        gameObject.inputTexture = renderText(gameObject.inputString, "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);

                        rectQ[0] = gameObject.underscoreRect;
    
                        textureQ[1] = gameObject.inputTexture;
                        rectQ[1] = gameObject.inputRect;


                        // Render bet prompt and balance

                        SDL_RenderClear(renderer);
                        presentQueue(renderer, textureQ, rectQ);
                    }

                    else if (event.key.keysym.sym == SDLK_RETURN) //User pressed Enter, submit the bet
                    {
                        if (isConvertibleToDouble(gameObject.inputString) && std::stod(gameObject.inputString) <= gameObject.balance) 
                        {
                            done = true;
                            gameObject.balance -= std::stod(gameObject.inputString);
                            gameObject.bet = std::stod(gameObject.inputString);

                            gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                            gameObject.betTexture = renderText("Bet: $" + toStringWithPrecision(gameObject.bet), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                        }
                        else 
                        {
                            textureQ.push_back(gameObject.invalidTexture);
                            rectQ.push_back(gameObject.invalidRect);

                            SDL_RenderClear(renderer);
                            presentQueue(renderer, textureQ, rectQ);
                        }
                    }
                break;
            
            }
        }

        SDL_RenderClear(renderer);
        toggleText(renderer, textureQ[0], gameObject, gameObject.lastToggle, functionNumber);// Update the screen
        presentQueue(renderer, textureQ, rectQ);
    }
    textureQ.clear();
    rectQ.clear();
    SDL_DestroyTexture(gameObject.underscoreTexture);
    SDL_DestroyTexture(gameObject.inputTexture);
    SDL_DestroyTexture(gameObject.betPromptTexture);
    SDL_DestroyTexture(gameObject.invalidTexture);
}

void game(SDL_Renderer* renderer)
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    functionNumber = 3;
    if (player.values[0] == player.values[1]) 
    {
        gameObject.numOptions = 5;
    }
    else
    {
        gameObject.numOptions = 4;
    }

    gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

    updateQueue(renderer);
    presentQueue(renderer, textureQ, rectQ);

    SDL_Event event;
    while (!isGameOver) 
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    isQuit = true;
                    isGameOver = true;
                break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_UP && gameObject.selectorPos > 0)
                    {
                        gameObject.selectorPos --;
                        gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                        SDL_RenderClear(renderer);
                        rectQ[0] = gameObject.selectorRect;
                        presentQueue(renderer, textureQ, rectQ);
                    }
                    if (event.key.keysym.sym == SDLK_DOWN && gameObject.selectorPos <= gameObject.numOptions - 1)
                    {
                        gameObject.selectorPos ++;
                        gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                        SDL_RenderClear(renderer);
                        rectQ[0] = gameObject.selectorRect;
                        presentQueue(renderer, textureQ, rectQ);
                    }
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        switch (gameObject.selectorPos)
                        {
                            case 0: //HIT

                            break;
                            case 1: //STAND

                            break;
                            case 2: //DOUBLE

                            break;
                            case 3: //SURRENDER

                            break;
                            case 4: //SPLIT

                            break;
                        }
                    }
            }                
        }
        SDL_RenderClear(renderer);
        toggleText(renderer, textureQ[0], gameObject, gameObject.lastToggle, functionNumber);// Update the screen
        presentQueue(renderer, textureQ, rectQ);
    }
}
/////////////////////////////////////////////////////////////////////////////////FUCKED UP CODE BE CAREFUL/////////////////////////////////////////////////////////////////////////////////

//Displays results and asks player if they want to go again
void playAgainScreen()
{

}


//GAME LOGIC FUNCTIONS
    //Function assigning unique random values to input array
    /*Takes an integer array of size N along with an integer as input arguments.
    The function assignes each element of the array with a unique integer ranging from zero to (int_limit - 1)
    */
    //NO ADJUSTMENT NEEDED
    template<size_t N>
    void random_array(int (&randoms)[N], int int_limit) 
    {
        bool works;
        bool check;
        int rand_index;
        int j;

        if (int_limit < N) 
        {
            std::cerr << "Error: int_limit must be at least as large as N to ensure uniqueness." << std::endl;
            return; 
        }

        for (int i = 0; i < N; i++) 
        {
            works = false;  

            while (works == false)
            {
                check = false;
                rand_index = rand() % int_limit;
                randoms[i] = rand_index;
                j = 0;

                //Checks to see if the random integer works
                while (j <= N-1) 
                {
                    if (i == j) 
                    {
                        j +=1;
                    }
                    else if (randoms[i] != randoms[j]) 
                    {
                        check = true;
                        j += 1;
                    }
                    else if (i != j && randoms[i] == randoms[j]) 
                    {
                        check = false; 
                        j = N;
                    }
                    else if (check == true && j == N-1) 
                    {
                        j += 1;
                    }
                }

                if (check == true) 
                {
                    works = true;
                }
            }
        }
    }

    //ADJUSTED
    void print_deck() 
    {
        for (int i = 0; i < 52; i++) 
        {
            std::cout << deck.names[i] << " has value " << deck.values[i] << std::endl;
        }
    }

    //ADJUSTED
    void initial_assignment(deckClass& deck) 
    {
        std::cout << "initial assignment started" << std::endl;
        //Number assignment
        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 13; j++)
            {
                if (j + 1 <= 10) 
                {
                    std::cout << "loop 1" << i << " " << j << "" << std::endl;
                    deck.values[(i * 13) + j] = j + 1; 
                }
                else if (j + 1 > 10) 
                {
                    std::cout << "loop 1" << i << " " << j << "" << std::endl;
                    deck.values[(i*13) + j] = 10;
                }
            }
        }
        //Name assignment
        std::string suits[4] = {"H", "C", "D", "S"};
        std::string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
        
        deck.names.resize(52);

        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 13; j++) 
            {
                std::cout << "loop 2 " << i << " " << j << "" << std::endl;
                deck.names[(i * 13) + j] = ranks[j] + suits[i];
                std::cout << deck.names[(i * 13) + j] << std::endl;
            }
        }
    }

    //ADJUSTED
    void shuffle() 
    {
        int randoms[52];
        int previous_values[52];
        std::string previous_names[52];
        std::vector<SDL_Texture*> previous_textures;
        previous_textures.resize(52);
        deck.textures.resize(52);

        for (int i = 0; i < 52; i ++) 
        {
            std::cout << "loop 3 ran" << std::endl;
            previous_values[i] = deck.values[i];
            previous_names[i] = deck.names[i];
            previous_textures.push_back(deck.textures[i]);
        }

        //Unique random number array generation
        random_array(randoms, 52);

        for (int i = 0; i < 52; i++) 
        {
            std::cout << "loop 4 ran" << std::endl;
            deck.values[randoms[i]] = previous_values[i];
            deck.names[randoms[i]] = previous_names[i];
            deck.textures[randoms[i]] = previous_textures[i];
        }
    }

    //ADJUSTED
    void initial_deal() 
    {
        for (int i = 0; i < 4; i++)
        {
            //Player
            if (i == 0 || i == 2) 
            {
                player.values.push_back(deck.values[51 - i]);
                player.names.push_back(deck.names[51 - i]);
                player.textures.push_back(deck.textures[51 - i]);

                player.rects.push_back({500 + (i/2 * 150), 380, 145, 250}); //PLAYER.RECTS ASSIGNMENT
                std::cout << "player rects have been updated" << std::endl;
                player.total += deck.values[51 - i];
                deck.values[51 - i] = 0;
                deck.names[51 - i] = "EMPTY";
            }
            //Dealer
            else if (i == 1 || i == 3) 
            {
                dealer.values.push_back(deck.values[51 - i]);
                dealer.names.push_back(deck.names[51 - i]);
                if (i == 1) 
                {
                    gameObject.firstDealerCardSurface= deck.surfaces[51 - i];
                    gameObject.firstDealerCardTexture = deck.textures[51 - i];
                    dealer.textures.push_back(gameObject.hiddenCardTexture);
                }
                else 
                {
                    dealer.textures.push_back(deck.textures[51 - i]);
                }   
                dealer.rects.push_back({500 + ((i-1)/2 * 150), 100, 145, 250}); 
                std::cout << "dealer rects have been updated" << std::endl;
                dealer.total += deck.values[51 - i];
                deck.values[51 - i] = 0;
                deck.names[51 - i] = "EMPTY";
            }
        }
    }

    //ADJUSTED
    void hit(playerClass& player_dealer)    
    {
        int index = 51;
        bool condition = false;

        while (condition == false) 
        {
            if (deck.values[index] != 0) 
            {
                condition = true;
            }
            else 
            {
                index -= 1;
            }
        }

        player_dealer.total += deck.values[index];
        gameObject.newCards += 1;
        player_dealer.values.push_back(deck.values[index]);
        player_dealer.names.push_back(deck.names[index]);
        player_dealer.textures.push_back(deck.textures[index]);

        std::cout << "card from hit: " << deck.names[index] << std::endl;
        deck.values[index] = 0;
        deck.names[index] = "EMPTY";
        deck.textures[index] = nullptr;
    }