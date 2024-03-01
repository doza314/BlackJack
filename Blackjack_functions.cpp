#include "Blackjack.hpp"

int calculateTextWidth(std::string text) {
    int textWidth = 0;
    textWidth = text.length()*18;
    return textWidth;
}


bool isConvertibleToDouble(std::string str) {
    std::istringstream iss(str);
    double val;
    iss >> val;
    // Check if entire string was consumed and if only whitespace remains.
    return iss.eof() && !iss.fail(); 
}

std::string toStringWithPrecision(const double value, const int n = 2) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << value;
    return out.str();
}

//renderText function
SDL_Texture* renderText(const std::string& message, const std::string& fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer) {
  
    // Open the font
    TTF_Font* font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() <<std::endl;
        return nullptr;
    }

    // Render the message to an SDL_Surface
    SDL_Surface* surf = TTF_RenderText_Solid(font, message.c_str(), color);
    if (surf == nullptr) {
        TTF_CloseFont(font);
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        return nullptr;
    }

    // Convert the surface to a texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
    if (texture == nullptr) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    }

    // Clean up the surface and font
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);

    return texture;
}

//Creates a card surface
SDL_Surface* cardSurface(std::string cardName) {
    std::string path = "cards/" + cardName + ".png";
    SDL_Surface* surface = IMG_Load(path.c_str());
    return surface;
}

//Creates a card texture
SDL_Texture* cardTexture(SDL_Renderer* renderer, SDL_Surface* cardSurface) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, cardSurface);
    return texture;
}

//Start Menu
void showStartMenu(SDL_Renderer* renderer) {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    // Set the text for the start menu
    std::string message = "Blackjack !";
    std::string enter = "Press Enter";

    // Set the color of the text
    SDL_Color white = {255, 255, 255, 255};

    // Variables for flashing text
    SDL_Texture* enterTexture = nullptr;
    SDL_Rect enterRect = {1280 / 2 - 100, 720 / 2 + 25, 200, 50};
    bool showEnterText = true;
    Uint32 lastToggle = SDL_GetTicks();
    const Uint32 toggleInterval = 250; // Time in milliseconds

    // Render the text
    SDL_Texture* messageTexture = renderText(message, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect messageRect = {1280 / 2 - 200, 720 / 2 - 70, 400, 100}; // Adjust these values as needed
    //SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);

    // Update the screen
    //SDL_RenderPresent(renderer);

    // Wait for the user to press Enter
    SDL_Event event;
    bool startGame = false;
    while (!startGame) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isQuit = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RETURN) {
                    startGame = true;
                }
            }
        }

        // Toggle "Press Enter" visibility
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastToggle > toggleInterval) {
            showEnterText = !showEnterText;
            lastToggle = currentTime;
        }

        //Clear screen
        SDL_RenderClear(renderer);

        // Render main message
        SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);

        // Conditionally render "Press Enter" text
        if (showEnterText) {
            if (!enterTexture) { // Lazy load the texture
                enterTexture = renderText(enter, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
            }
            SDL_RenderCopy(renderer, enterTexture, NULL, &enterRect);
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(messageTexture);
    SDL_DestroyTexture(enterTexture);
}

//Betting function
void promptForBet(SDL_Renderer* renderer, double& balance, double& bet) {

    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);

    // White text
    SDL_Color white = {255, 255, 255, 255};

    //Bank account text
    std::string balance_string = "Balance : $" + toStringWithPrecision(balance);
    //Balance texture
    SDL_Texture* balanceTexture = renderText(balance_string, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect balanceRect = {20, 20, 400, 50}; // Adjust these values as needed
    SDL_RenderCopy(renderer, balanceTexture, NULL, &balanceRect);
    SDL_RenderPresent(renderer);

    // Bet Prompt text
    std::string betPrompt = "Enter your bet : ";
    // Render the bet prompt text
    SDL_Texture* betPromptTexture = renderText(betPrompt, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect betPromptRect = {1280 / 2 - 200, 720 / 2 + 25, 225, 50};
    SDL_RenderCopy(renderer, betPromptTexture, NULL, &betPromptRect);
    SDL_RenderPresent(renderer);

    //Invalid input error texture
    SDL_Color red = {255, 0, 0, 255};
    std::string invalidBet = "Invalid Input! Bet must be a number less than or equal to your balance!";
    SDL_Rect invalidRect = {1280/2 - 500, 720 / 2 + 100, 1000, 50};
    SDL_Texture* invalidTexture =  renderText(invalidBet, "C:/Windows/Fonts/arial.ttf", red, 14, renderer);


     // Variables for flashing underscore
    Uint32 lastToggle = SDL_GetTicks();
    bool showUnderscoreText = true;
    const Uint32 toggleInterval = 250; // Time in milliseconds
    std::string underscore = "_";
    SDL_Texture* underscoreTexture = nullptr;
    SDL_Rect underscoreRect = {1280 / 2 + 20, 720 / 2 + 25, 20, 50};

    SDL_StartTextInput(); // Start accepting text input
    SDL_Color color = {255, 255, 255, 255}; // White color for text

    std::string inputText = ""; // String to hold the user's text input
    int inputTextWidth = calculateTextWidth(inputText);
    SDL_Rect inputRect = {1280 / 2 + 20, 720/2 + 25, inputTextWidth, 50};
    SDL_Texture* inputTexture = renderText(inputText, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);

    SDL_Event e;
    bool done = false;

    bool print_error = false;
    //User enters an double that is less than their bank.
    while (!done) {
        while (SDL_PollEvent(&e) != 0) {
             switch (e.type) {
                case SDL_QUIT:
                // Handle quit requests (like closing the window)
                isQuit = true;
                done = true;
                break;
                case SDL_TEXTINPUT: 
                // Handle key presses
                inputText += e.text.text;

                inputTextWidth = calculateTextWidth(inputText);

                underscoreRect = {1280 / 2 + 20 + inputTextWidth, 720 / 2 + 25, 20, 50};

                inputRect = {1280 / 2 + 20, 720/2 + 25, inputTextWidth, 50};
                inputTexture = renderText(inputText, "C:/Windows/Fonts/arial.ttf", white, 14, renderer);

                SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);
                SDL_RenderPresent(renderer);
                break;
                case SDL_KEYDOWN: 
                    if (e.key.keysym.sym == SDLK_BACKSPACE && !inputText.empty()) {
                    // Remove the last character
                        inputText.pop_back();                    
                        SDL_RenderClear(renderer);
                        inputTextWidth = calculateTextWidth(inputText);
                        underscoreRect = {1280 / 2 + 20 + inputTextWidth, 720 / 2 + 25, 20, 50};
                        inputRect = {1280 / 2 + 20, 720/2 + 25, inputTextWidth, 50};
                        inputTexture = renderText(inputText, "C:/Windows/Fonts/arial.ttf", white, 14, renderer);

                        // Render bet prompt and balance
                        SDL_RenderCopy(renderer, betPromptTexture, NULL, &betPromptRect);
                        SDL_RenderCopy(renderer, balanceTexture, NULL, &balanceRect);
                        SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);
                        SDL_RenderPresent(renderer);
                     }
                    else if (e.key.keysym.sym == SDLK_RETURN) {
                    // User pressed Enter, submit the bet
                    
                    //!!! IMPLEMENT LOGIC THAT MAKES SURE INPUT IS A DOUBLE !!!!
                    if (isConvertibleToDouble(inputText) && stod(inputText) <= balance) {
                        done = true;
                        balance -= stod(inputText);
                        bet = stod(inputText);
                    }
                    else {
                        //Invalid input 

                        //SDL_RenderClear(renderer);
                        //SDL_RenderCopy(renderer, betPromptTexture, NULL, &betPromptRect);
                        //SDL_RenderCopy(renderer, balanceTexture, NULL, &balanceRect);
                        //SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);
                        SDL_RenderCopy(renderer, invalidTexture, NULL, &invalidRect);
                        SDL_RenderPresent(renderer);

                        print_error = true;
                    }
                }
        break;
        // and so on for other event types...
    }
        }
        
        // Toggle underscore visibility
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastToggle > toggleInterval) {
            showUnderscoreText = !showUnderscoreText;
            lastToggle = currentTime;
        }
        //Clear screen
        SDL_RenderClear(renderer);

        // Render bet prompt and balance
        SDL_RenderCopy(renderer, betPromptTexture, NULL, &betPromptRect);
        SDL_RenderCopy(renderer, balanceTexture, NULL, &balanceRect);
        SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);

        if (print_error) {
            SDL_RenderCopy(renderer, invalidTexture, NULL, &invalidRect);
        }
        

        // Conditionally render underscore text
        if (showUnderscoreText) {
            if (!underscoreTexture) { // Lazy load the texture
                underscoreTexture = renderText(underscore, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
            }
            SDL_RenderCopy(renderer, underscoreTexture, NULL, &underscoreRect);
        }
        // Update the screen
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(inputTexture);
    SDL_DestroyTexture(underscoreTexture);
    SDL_DestroyTexture(betPromptTexture);
    SDL_DestroyTexture(balanceTexture);
    SDL_DestroyTexture(invalidTexture);
}

//Showing cards to screen 
void showCards(SDL_Renderer* renderer, std::vector<std::string> player_names, std::vector<std::string> dealer_names, SDL_Texture* &hiddenCard, SDL_Texture* &firstDealerCard, std::vector<SDL_Texture*>& playerCardTextures, std::vector<SDL_Surface*>& playerCardSurfaces, std::vector<SDL_Rect>& playerCardRects,
 std::vector<SDL_Texture*>& dealerCardTextures, std::vector<SDL_Surface*>& dealerCardSurfaces, std::vector<SDL_Rect>& dealerCardRects, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects) {

    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect cardRect;

    //Player cards
    for (int i = 0; i < player_names.size(); i++) {
        surface = cardSurface(player_names[i]);
        texture = cardTexture(renderer, surface);

        playerCardSurfaces.push_back(surface);
        playerCardTextures.push_back(texture);
        playerCardRects.push_back({500 + (i * 150), 380, 145, 250});
        allTextures.push_back(texture);
        allRects.push_back({500 + (i * 150), 380, 145, 250});
    }

    //Dealer cards
    for (int i = 0; i < dealer_names.size(); i++) {
        if (i == 0) {
            surface = cardSurface("hidden");
            hiddenCard = cardTexture(renderer, surface);
            dealerCardSurfaces.push_back(surface);

            surface = cardSurface(dealer_names[i]);
            firstDealerCard = cardTexture(renderer, surface);

            
            dealerCardTextures.push_back(hiddenCard);
            dealerCardRects.push_back({500 + (i * 150), 100, 145, 250});
            allTextures.push_back(hiddenCard);
            allRects.push_back({500 + (i * 150), 100, 145, 250});
        }
        else {
            surface = cardSurface(dealer_names[i]);
            texture = cardTexture(renderer, surface);
            allTextures.push_back(texture);
            dealerCardSurfaces.push_back(surface);
            dealerCardTextures.push_back(texture);
            dealerCardRects.push_back({500 + (i * 150), 100, 145, 250});
            allRects.push_back({500 + (i * 150), 100, 145, 250});
        }
    }
}

//Render text to screen
void gameText(SDL_Renderer* renderer, double balance, SDL_Texture* &betTexture, SDL_Texture* &balanceTexture, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects) {

    SDL_Color white = {255,255,255,255};

    //Bank account texture      
    std::string balance_string = "Balance : $" + toStringWithPrecision(balance);
    balanceTexture = renderText(balance_string, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect balanceRect = {20, 20, 400, 50}; // Adjust these values as needed
    allTextures.push_back(balanceTexture);
    allRects.push_back(balanceRect);

    //Bet texture
    std::string bet_string = "Bet: $" + toStringWithPrecision(bet);
    betTexture = renderText(bet_string, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect betRect = {20, 70, 250, 50}; // Adjust these values as needed
    allTextures.push_back(betTexture);
    allRects.push_back(betRect);

    //"Dealer: " texture 
    std::string dealerString = "Dealer: ";
    SDL_Texture* dealerTexture = renderText(dealerString, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect dealerRect = {390, 275, 100, 50};
    allTextures.push_back(dealerTexture);
    allRects.push_back({390, 275, 100, 50});

    //"You: " texture
    std::string youString = "You: ";
    SDL_Texture* youTexture = renderText(youString, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect youRect = {390, 550, 100, 50};
    allTextures.push_back(youTexture); 
    allRects.push_back({390, 550, 100, 50});
}

//Show player option prompt
void showPrompt(SDL_Renderer* renderer, SDL_Texture* &hitTexture, SDL_Texture* &standTexture, SDL_Texture* &doubleDTexture, SDL_Texture* &surrenderTexture, SDL_Texture* &splitTexture, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects, std::vector<int> player_vals, int& numOptions) {

    SDL_Color white = {255,255,255,255};

    //Hit
    std::string hitString = "Hit";
    hitTexture = renderText(hitString, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect hitRect = {100, 300, 42, 50};
    
    //Stand
    std::string standString = "Stand";
    standTexture = renderText(standString, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect standRect = {100, 350, 70, 50};
    
    //Double Down
    std::string doubleDString = "Double Down";
    doubleDTexture = renderText(doubleDString, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect doubleDRect = {100, 400, 154, 50};
   
    //Split
    std::string splitString = "Split";
    splitTexture = renderText(splitString, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect splitRect = {100, 500, 70, 50};

    //Surrender
    std::string surrenderString = "Surrender";
    surrenderTexture = renderText(surrenderString, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect surrenderRect = {100, 450, 126, 50};
    
    //All options for player if split is possible
    if (player_vals[0] == player_vals[1]) {
        numOptions = 5;
        allTextures.push_back(hitTexture);
        allRects.push_back(hitRect);

        allTextures.push_back(standTexture);
        allRects.push_back(standRect);

        allTextures.push_back(doubleDTexture);
        allRects.push_back(doubleDRect);

        allTextures.push_back(surrenderTexture);
        allRects.push_back(surrenderRect);

        allTextures.push_back(splitTexture);
        allRects.push_back(splitRect);
        
        
    }
    //All options except split
    else if (player_vals[0] != player_vals[1]) {
        numOptions = 4;
        allTextures.push_back(hitTexture);
        allRects.push_back(hitRect);

        allTextures.push_back(standTexture);
        allRects.push_back(standRect);

        allTextures.push_back(doubleDTexture);
        allRects.push_back(doubleDRect);
        
        allTextures.push_back(surrenderTexture);
        allRects.push_back(surrenderRect);
    }
}

void gameTexturesCopy(SDL_Renderer* renderer, std::vector<SDL_Texture*> allTextures, std::vector<SDL_Surface*> allSurfaces, std::vector<SDL_Rect> allRects) {
    for (int i = 0; i < allTextures.size(); i++) {
        SDL_RenderCopy(renderer, allTextures[i], NULL, &allRects[i]);
    }
}

void cleanUp(SDL_Renderer* renderer, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects) {
    
    //Clean up textures
    for (int i = 0; i < allTextures.size(); i++) {
        SDL_DestroyTexture(allTextures[i]);
    }
    for (int i = 0; i < allSurfaces.size(); i++) {
        SDL_FreeSurface(allSurfaces[i]);
    }
    allTextures.clear();
    allSurfaces.clear();
    allRects.clear();
}

void addCardTexture(SDL_Renderer* renderer, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects, std::vector<std::string> names, bool isPlayer, bool split, int newCards) {
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Rect cardRect;

    for (int i = 0; i < newCards; i++) { 
     surface = cardSurface(names[names.size() - (newCards - i)]);
     texture = cardTexture(renderer, surface);
     allTextures.push_back(texture);
        if (isPlayer && !split) {
            allRects.push_back({static_cast<int>(500 + ((names.size() - (newCards - i)) * 150)), 380, 145, 250});
        }
        else if (isPlayer && split) {
            
        }
        else if (!isPlayer) {
            allRects.push_back({static_cast<int>(500 + ((names.size() - (newCards - i)) * 150)), 100, 145, 250});
        }
    }
    

}

void updateBetTexture(SDL_Renderer* renderer, SDL_Texture* &betTexture, SDL_Texture* &balanceTexture, double bet, double balance) {
    for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == betTexture) {
                allTextures.erase(allTextures.begin() + i);
                allRects.erase(allRects.begin() + i);
            }
        }
    
    for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == balanceTexture) {
                allTextures.erase(allTextures.begin() + i);
                allRects.erase(allRects.begin() + i);
            }
        }

        //Bet texture
    std::string bet_string = "Bet: $" + toStringWithPrecision(bet);
    betTexture = renderText(bet_string, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect betRect = {20, 70, 250, 50}; // Adjust these values as needed
    allTextures.push_back(betTexture);
    allRects.push_back(betRect);

    //Balance texture
    std::string balance_string = "Balance : $" + toStringWithPrecision(balance);
    balanceTexture = renderText(balance_string, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
    SDL_Rect balanceRect = {20, 20, 400, 50}; // Adjust these values as needed
    allTextures.push_back(balanceTexture);
    allRects.push_back(balanceRect);
}

void splitFunction(SDL_Renderer* renderer, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces, std::vector<SDL_Rect>& allRects,
std::vector<SDL_Texture*>& playerCardTextures, std::vector<SDL_Surface*>& playerCardSurfaces, std::vector<SDL_Rect>& playerCardRects,
std::vector<int> &player_vals, std::vector<std::string> &player_names, 
std::vector<int> &split_vals1, std::vector<std::string> &split_names1, std::vector<int> &split_vals2, std::vector<std::string> &split_names2, std::vector<SDL_Rect> &split_rects1, std::vector<SDL_Rect> &split_rects2) {

    //Fill split vectors
for (int i = 0; i < playerCardTextures.size(); i++) {
    if (i == 0 || i % 2 == 0) {
        split_vals1.push_back(player_vals[i]);
        split_names1.push_back(player_names[i]);
        split_rects1.push_back({530 + (i/2 * 150), 380, 70, 120});
    }
    if (i == 1 || i % 2 == 1) {
        split_vals2.push_back(player_vals[i]);
        split_names2.push_back(player_names[i]);
        split_rects2.push_back({530 + ((i-1)/2 * 150), 520, 70, 120});
    }
}

    //Remove preexisting player card textures
    for(int j = 0; j < playerCardTextures.size(); j++) {
    for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == playerCardTextures[j]) {
                allTextures.erase(allTextures.begin() + i);
                allRects.erase(allRects.begin() + i);
            }
        }
    }

}

//Function that renders the player's cards, dealer's cards, balance, and prompts the user to make a selection
void game(SDL_Renderer* renderer, double& balance, double& bet, int& playerTotal, int& dealerTotal, std::vector<SDL_Texture*>& allTextures, std::vector<SDL_Surface*>& allSurfaces,
 std::vector<SDL_Rect>& allRects, bool& notPlaying, bool &hitbool, bool &standbool, bool &doubleDownbool, bool &splitbool, bool &surrenderbool) {

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Color white  = {255, 255, 255, 255};

    // Variables for flashing selector
    std::string selector = ">";
    int selectorPosition = 0;
    int option = 0;
    int newCards = 0;
    int n = 0;
    bool playerTurn = true;
    bool hasSplit = false;
    SDL_Texture* selectorTexture = nullptr;
    SDL_Rect selectorRect = {75, 300 + (selectorPosition * 50), 20, 50};
    Uint32 lastToggle = SDL_GetTicks();
    bool showSelector = true;
    const Uint32 toggleInterval = 250; // Time in milliseconds

   //Render textures and present renderer
    showCards(renderer, player_names, dealer_names, hiddenCard, firstDealerCard, playerCardTextures, playerCardSurfaces, playerCardRects, dealerCardTextures, dealerCardSurfaces, dealerCardRects, allTextures, allSurfaces, allRects);
    gameText(renderer, balance, betTexture, balanceTexture, allTextures, allSurfaces, allRects);
    showPrompt(renderer, hitTexture, standTexture, doubleDTexture, surrenderTexture, splitTexture, allTextures, allSurfaces, allRects, player_vals, numOptions);
    gameTexturesCopy(renderer, allTextures, allSurfaces, allRects);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while(!isGameOver) {
    while (SDL_PollEvent(&event) != 0) {
        switch (event.type) {
            case SDL_QUIT:
                isQuit = true;
                isGameOver = true;
                notPlaying = true;
            break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isQuit = true;
                    isGameOver = true;
                    notPlaying = true;
                }
                else if (event.key.keysym.sym == SDLK_DOWN && selectorPosition < numOptions - 1) {
                    selectorPosition += 1;
                    selectorRect = {75, 300 + (selectorPosition * 50), 20, 50};
                }
                else if (event.key.keysym.sym == SDLK_UP && selectorPosition > 0 ) {
                    selectorPosition -= 1;
                    selectorRect = {75, 300 + (selectorPosition * 50), 20, 50};
                }
                else if (event.key.keysym.sym == SDLK_RETURN) {
                    switch(selectorPosition) {
                        case 0: // Hit
                            if (playerTotal < 21 && playerTurn) {
                            turn += 1;
                            newCards += 1;
                            hitbool = true;
                            hit(values, names, playerTotal, player_vals, player_names, newCards);
                            std::cout << "Player Total: " << playerTotal << std::endl;
                                if (playerTotal > 21) {
                                    //isGameOver = true;
                                }
                            }
                        break;
                        case 1: // Stand
                            turn += 1;
                            playerTurn = false;
                            standbool = true;
                            if (splitbool) {
                                while (dealerTotal < 17) {
                                 hit(values, names, dealerTotal, dealer_vals, dealer_names, newCards);
                            }
                            }
                        break;
                        case 2: // Double Down
                            if (!doubleDownbool) {
                            turn += 1;
                            doubleDownbool = true;
                            bet *= 2;
                            balance -= bet/2;
                            
                            updateBetTexture(renderer, betTexture, balanceTexture, bet, balance);

                            //player takes a card
                            hit(values, names, playerTotal, player_vals, player_names, newCards);

                            //dealer goes
                            while (dealerTotal < 17) {
                                 hit(values, names, dealerTotal, dealer_vals, dealer_names, newCards);
                            }
                            }
                        break;

                        case 3: // Surrender
                            turn += 1;
                            surrenderbool = true;
                            bet = 0;
                            isGameOver = true;
                        break;

                        case 4: // Split
                            if (!splitbool) {
                            turn += 1;
                            splitbool = true;
                            bool hasSplit = true;
                            newCards += 1;
                            bet *= 2;
                            balance -= bet/2;
                            selectorPosition = 0;
                            selectorRect = {75, 300 + (selectorPosition * 50), 20, 50};
                            splitFunction(renderer, allTextures, allSurfaces, allRects, playerCardTextures, playerCardSurfaces, playerCardRects, player_vals, player_names, split_vals1, split_names1, split_vals2, split_names2, split_rects1, split_rects2);
                            }
                        break;
                    }
                }
            break;
        }
    }

    //Removing options after first selection
    if (turn > 0) {
        if (hitbool && !standbool || splitbool) {
            numOptions = 2;
            for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == doubleDTexture || allTextures[i] == surrenderTexture || allTextures[i] == splitTexture) {
                allTextures.erase(allTextures.begin() + i);
                allRects.erase(allRects.begin() + i);
                --i;
            }
        }
        }
        else if (standbool) {
            numOptions = 1;
            selectorPosition = 0;
            for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == hitTexture || allTextures[i] == doubleDTexture || allTextures[i] == surrenderTexture || allTextures[i] == splitTexture) {
                allTextures.erase(allTextures.begin() + i);
                allRects.erase(allRects.begin() + i);
            }
        }
        }
        else if (doubleDownbool) {
            numOptions = 1;
            selectorPosition = 0;
            for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == hitTexture || allTextures[i] == standTexture ||allTextures[i] == surrenderTexture || allTextures[i] == splitTexture) {
                allTextures.erase(allTextures.begin() + i);
                allRects.erase(allRects.begin() + i);
            }
            }
        }
    }
    
    //Adding card textures based on choice
    if (newCards > 0 && playerTurn && !doubleDownbool && !splitbool) {
        addCardTexture(renderer, allTextures, allSurfaces, allRects, player_names, playerTurn, splitbool, newCards);
        newCards = 0;
    }

    if (doubleDownbool) {
        addCardTexture(renderer, allTextures, allSurfaces, allRects, player_names, playerTurn, splitbool, newCards);
        playerTurn = false;
        for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == hiddenCard) {
                allTextures[i] = firstDealerCard;
            }
        }
        addCardTexture(renderer, allTextures, allSurfaces, allRects, dealer_names, playerTurn, splitbool, newCards);
        newCards = 0;
    }
    
    if (standbool && !playerTurn) {
        for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == hiddenCard) {
                allTextures[i] = firstDealerCard;
            }
        }
        addCardTexture(renderer, allTextures, allSurfaces, allRects, dealer_names, playerTurn, splitbool, newCards);
        newCards = 0;
    }

    if (splitbool) {
        allRects.push_back(split_rects1[split_rects1.size()-1]);
        addCardTexture(renderer, allTextures, allSurfaces, allRects, split_names1, playerTurn, splitbool, newCards);
        allRects.push_back(split_rects2[split_rects2.size()-1]);
        addCardTexture(renderer, allTextures, allSurfaces, allRects, split_names2, playerTurn, splitbool, newCards);
        newCards = 0;
        splitbool = false;
        for (int i = 0; i < allTextures.size(); i++) {
            if (allTextures[i] == selectorTexture) {
                allTextures.erase(allTextures.begin() + i);
                allRects.erase(allRects.begin() + i);
            }
        }
    }
    
    
    SDL_RenderClear(renderer);
    gameTexturesCopy(renderer, allTextures, allSurfaces, allRects);

    // Toggle underscore visibility
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastToggle > toggleInterval) {
            showSelector = !showSelector;
            lastToggle = currentTime;
            for (int i = 0; i < allTextures.size(); i++) {
                if (allTextures[i] == selectorTexture) {
                    allTextures.erase(allTextures.begin() + i);
                    allRects.erase(allRects.begin() + i);
                }
            }
            
    }

    // Conditionally render underscore text
    if (showSelector) {
        if (!selectorTexture) { // Lazy load the texture 
                selectorTexture = renderText(selector, "C:/Windows/Fonts/arial.ttf", white, 12, renderer);
                selectorRect = {75, 300 + (selectorPosition * 50), 20, 50};
                allTextures.push_back(selectorTexture);
                allRects.push_back(selectorRect);
                std::cout << "selector" << n << std::endl;
                n++;
    }
    SDL_RenderCopy(renderer, selectorTexture, NULL, &selectorRect);
    }
    SDL_RenderPresent(renderer);
    }

    //Clean up textures
    cleanUp(renderer,allTextures, allSurfaces, allRects);
}

//Displays results and asks player if they want to go again
void results() {}

//Function assigning unique random values to input array
/*Takes an integer array of size N along with an integer as input arguments.
The function assignes each element of the array with a unique integer ranging from zero to (int_limit - 1)
*/
template<size_t N>
void random_array(int (&randoms)[N], int int_limit) {
    bool works;
    bool check;
    int rand_index;
    int j;

    if (int_limit < N) {
        std::cerr << "Error: int_limit must be at least as large as N to ensure uniqueness." << std::endl;
        return; 
    }

    for (int i = 0; i < N; i++) {
        works = false;  

        while (works == false) {
        check = false;
        rand_index = rand() % int_limit;
        randoms[i] = rand_index;
        j = 0;

        //Checks to see if the random integer works
        while (j <= N-1) {
            if (i == j) {
                j +=1;
            }
            else if (randoms[i] != randoms[j]) {
                check = true;
                j += 1;
            }
            else if (i != j && randoms[i] == randoms[j]) {
                check = false; 
                j = N;
            }
            else if (check == true && j == N-1) {
                j += 1;
            }
        }
            if (check == true) {
                works = true;
            }
    }
}
}

void print_deck(int values[52], std::string names[52]) {
    for (int i = 0; i < 52; i++) {
        std::cout << names[i] << " has value " << values[i] << std::endl;
    }
}

void initial_assignment(int (&values)[52], std::string (&names)[52]) {
    //Number assignment
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            if (j + 1 <= 10) {
                values[(i * 13) + j] = j + 1; 
            }
            else if (j + 1 > 10) {
                values[(i*13) + j] = 10;
            }
        }
    }
    //Name assignment
    std::string suits[4] = {"H", "C", "D", "S"};
    std::string ranks[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            names[(i * 13) + j] = ranks[j] + suits[i];
            // cout << names[(i * 13) + j] << endl;
        }
    }
}

void shuffle(int (&values)[52], std::string (&names)[52]) {
    int randoms[52];
    int previous_values[52];
    std::string previous_names[52];

    for (int i = 0; i < 52; i ++) {
        previous_values[i] = values[i];
        previous_names[i] = names[i];
    }

    //Unique random number array generation
    random_array(randoms, 52);

    for (int i = 0; i < 52; i++) {
        values[randoms[i]] = previous_values[i];
        names[randoms[i]] = previous_names[i];
    }
}

void initial_deal(int (&values)[52], std::string (&names)[52], int& playerTotal, int& dealerTotal, std::vector<int>& player_vals, std::vector<std::string>& player_names, std::vector<int>& dealer_vals, std::vector<std::string>& dealer_names) {
   
    for (int i = 0; i < 4; i++) {
        //Player
        if (i == 0 || i == 2) {
            player_vals.push_back(values[51 - i]);
            player_names.push_back(names[51 - i]);
            playerTotal += values[51 - i];
            values[51 - i] = 0;
            names[51 - i] = "EMPTY";
        }
        //Dealer
        else if (i == 1 || i == 3) {
            dealer_vals.push_back(values[51 - i]);
            dealer_names.push_back(names[51 - i]);
            dealerTotal += values[51 - i];
            values[51 - i] = 0;
            names[51 - i] = "EMPTY";
        }
    }
}

void hit(int (&values)[52], std::string (&names)[52], int& total, std::vector<int>& vals, std::vector<std::string>& nams, int& newCards) {
    int index = 51;
    bool condition = false;

    while (condition == false) {
        if (values[index] != 0) {
            condition = true;
        }
        else {
            index -= 1;
        }
    }

    total += values[index];
    newCards += 1;
    vals.push_back(values[index]);
    nams.push_back(names[index]);

    values[index] = 0;
    names[index] = "EMPTY";
}