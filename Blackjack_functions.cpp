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
    
    //Results Textures
    gameObject.playerWinsTexture = renderText("You win!", "C:/Windows/Fonts/arial.ttf", gameObject.yellow, 24, renderer);
    gameObject.dealerWinsTexture = renderText("You lose!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 24, renderer);
    gameObject.blackjackTexture = renderText("Blackjack!", "C:/Windows/Fonts/arial.ttf", gameObject.yellow, 24, renderer);
    gameObject.pushTexture = renderText("Push!", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.bustTexture = renderText("Bust!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 24, renderer);

        //Results Rectangles
        gameObject.playerWinsRect = {20, 170, 250, 50};
        gameObject.dealerWinsRect = {20, 170, 250, 50};
        gameObject.blackjackRect = {20, 170, 250, 50};
        gameObject.pushRect = {20, 170, 250, 100};
        gameObject.bustRect = {20, 170, 250, 100};

    //Options Textures
    options.hitTexture = renderText("Hit", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.standTexture = renderText("Stand", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.doubleDTexture = renderText("Double Down", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.surrenderTexture = renderText("Surrender", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.splitTexture = renderText("Split", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    options.continueTexture = renderText("Continue", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);

        //Options Rectangles
        options.hitRect = {100, 300, 42, 50};
        options.standRect = {100, 350, 70, 50};
        options.doubleDRect = {100, 400, 154, 50};
        options.surrenderRect = {100, 450, 126, 50};
        options.splitRect = {100, 500, 70, 50};
        options.continueRect = {100, 550, 120, 50};

    //Split Textures
    split.selectorTexture = renderText(">", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);


    //Deck Textures
    gameObject.hiddenCardSurface = cardSurface("hidden");
    gameObject.hiddenCardTexture = cardTexture(renderer, gameObject.hiddenCardSurface);

    //Play Again Functions
    gameObject.playAgainTexture = renderText("Play Again?", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.yesTexture = renderText("Yes", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);
    gameObject.noTexture = renderText("No", "C:/Windows/Fonts/arial.ttf", gameObject.white, 24, renderer);

        //Play Again Rectangles
        gameObject.playAgainRect = {500, 280, 250, 60};
        gameObject.yesRect = {570, 360, 75, 50};
        gameObject.noRect = {570, 410, 75, 50};
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

            textureQ.push_back(gameObject.dealerTexture); //Dealer in position 3
            rectQ.push_back(gameObject.dealerRect);

            //textureQ.push_back(dealer.totalTexture); 
            //rectQ.push_back(dealer.totalRect);

            textureQ.push_back(gameObject.youTexture); //"You: " in position 4
            rectQ.push_back(gameObject.youRect);

            textureQ.push_back(player.totalTexture); //You total in position 5
            rectQ.push_back(player.totalRect);

            if (player.total != 21)
            {
            textureQ.push_back(options.hitTexture); //"Hit" in position 6
            rectQ.push_back(options.hitRect);

            textureQ.push_back(options.doubleDTexture); //"Double Down" in position 7
            rectQ.push_back(options.doubleDRect);

            textureQ.push_back(options.surrenderTexture); //"Surrender" in position 8
            rectQ.push_back(options.surrenderRect);
            }

            textureQ.push_back(options.standTexture); //"Stand" in position 9
            rectQ.push_back(options.standRect);

            

            if (gameObject.numOptions == 5) 
            {
                textureQ.push_back(options.splitTexture); //"Split" in position 10
                rectQ.push_back(options.splitRect);
            }
            
            for (int i = 0; i < player.textures.size(); i++)
            {
                textureQ.push_back(player.textures[i]);
                rectQ.push_back(player.rects[i]);
            }   
            for (int i = 0; i < dealer.textures.size(); i++) 
            {
                textureQ.push_back(dealer.textures[i]);
                rectQ.push_back(dealer.rects[i]);
            }
            
            break;
        case 4: //Hit
            
            textureQ.push_back(gameObject.selectorTexture); //Selector in position 0
            rectQ.push_back(gameObject.selectorRect);

            textureQ.push_back(gameObject.balanceTexture); //Balance in position 1
            rectQ.push_back(gameObject.balanceRect);

            textureQ.push_back(gameObject.betTexture); //Bet in position 2
            rectQ.push_back(gameObject.betRect);

            textureQ.push_back(gameObject.dealerTexture); //Dealer in position 3
            rectQ.push_back(gameObject.dealerRect);

            //textureQ.push_back(dealer.totalTexture); 
            //rectQ.push_back(dealer.totalRect);

            textureQ.push_back(gameObject.youTexture); //"You: " in position 4
            rectQ.push_back(gameObject.youRect);

            textureQ.push_back(player.totalTexture); //You total in position 5
            rectQ.push_back(player.totalRect);

            textureQ.push_back(options.hitTexture); //"Hit" in position 6
            rectQ.push_back(options.hitRect);

            textureQ.push_back(options.standTexture); //"Stand" in position 7
            rectQ.push_back(options.standRect);

            for (int i = 0; i < player.textures.size(); i++)
            {
                textureQ.push_back(player.textures[i]);
                rectQ.push_back(player.rects[i]);
            }   
            for (int i = 0; i < dealer.textures.size(); i++) 
            {
                textureQ.push_back(dealer.textures[i]);
                rectQ.push_back(dealer.rects[i]);
            }
        break;
        case 5: //END OF TURN
        case 6: 
        case 7:
            
            textureQ.push_back(gameObject.selectorTexture); //Selector in position 0
            rectQ.push_back(gameObject.selectorRect);

            textureQ.push_back(gameObject.dealerTexture); //"Dealer: " in position 1
            rectQ.push_back(gameObject.dealerRect);

            textureQ.push_back(dealer.totalTexture); //Dealer total in position 2
            rectQ.push_back(dealer.totalRect);

            textureQ.push_back(gameObject.youTexture); //"You: " in position 3
            rectQ.push_back(gameObject.youRect);

            textureQ.push_back(options.continueTexture); //"Continue" in position 4
            rectQ.push_back(options.continueRect);

            //Outcome conditionals
            if (!gameObject.splitbool)  //NON-SPLIT RESULTS
            {
            
                textureQ.push_back(player.totalTexture); //You total in position 5
                rectQ.push_back(player.totalRect);

                for (int i = 0; i < player.textures.size(); i++)
                {
                    textureQ.push_back(player.textures[i]);
                    rectQ.push_back(player.rects[i]);
                }   
                for (int i = 0; i < dealer.textures.size(); i++) 
                {
                    textureQ.push_back(dealer.textures[i]);
                    rectQ.push_back(dealer.rects[i]);
                }

                if(player.total > 21 && !gameObject.surrenderbool) //Player busts
                {
                    textureQ.push_back(gameObject.bustTexture);
                    rectQ.push_back(gameObject.bustRect);
                    gameObject.bet = 0;
                }
                else if (player.total <= 21 && dealer.total <= 21 && player.total == dealer.total && !gameObject.surrenderbool) //Push
                {
                    textureQ.push_back(gameObject.pushTexture);
                    rectQ.push_back(gameObject.pushRect);
                    gameObject.balance += gameObject.bet;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                    gameObject.bet = 0;
                }
                else if ((player.total < 21 && dealer.total < 21 && player.total > dealer.total) && !gameObject.surrenderbool || (player.total < 21 && dealer.total > 21) && !gameObject.surrenderbool) //Player wins
                {
                    textureQ.push_back(gameObject.playerWinsTexture);
                    rectQ.push_back(gameObject.playerWinsRect);
                    gameObject.balance += 2*gameObject.bet;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                    gameObject.bet = 0;
                }
                else if ((player.total < 21 && dealer.total < 21 && player.total < dealer.total) && !gameObject.surrenderbool || (player.total < 21 & dealer.total == 21) && !gameObject.surrenderbool) //Dealer wins
                {
                    textureQ.push_back(gameObject.dealerWinsTexture);
                    rectQ.push_back(gameObject.dealerWinsRect);
                    gameObject.bet = 0;
                }
                else if (dealer.total != 21 && player.total == 21 && !gameObject.surrenderbool) //Blackjack
                {
                    textureQ.push_back(gameObject.blackjackTexture);
                    rectQ.push_back(gameObject.blackjackRect);
                    gameObject.balance += 2*gameObject.bet;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                    gameObject.bet = 0;
                }
                else if (gameObject.surrenderbool == true) //Surrender
                {
                    textureQ.push_back(gameObject.dealerWinsTexture);
                    rectQ.push_back(gameObject.dealerWinsRect);
                    gameObject.bet = 0;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                    gameObject.surrenderbool = false;
                }
            }


            if (gameObject.splitbool && split.bottomResult) //SPLIT RESULTS
            {
                textureQ.push_back(split.topTotalTexture);
                rectQ.push_back(split.topTotalRect);

                textureQ.push_back(split.bottomTotalTexture);
                rectQ.push_back(split.bottomTotalRect);

                for (int i = 0; i < split.topValues.size(); i++) //Split top cards
                {
                    textureQ.push_back(split.topTextures[i]);
                    rectQ.push_back(split.topRects[i]);
                }
                for (int i = 0; i < split.bottomValues.size(); i++) //Split bottom cards
                {
                    textureQ.push_back(split.bottomTextures[i]);
                    rectQ.push_back(split.bottomRects[i]);

                }
                for (int i = 0; i < dealer.textures.size(); i++) //Dealer cards
                {
                    textureQ.push_back(dealer.textures[i]);
                    rectQ.push_back(dealer.rects[i]);
                }

                //SPLIT RESULTS BALANCE CALCULATION
               
            if (!split.topBust) //TOP HAND
            {
                //std::cout << "Top total: " << split.topTotal << std::endl;
                //std::cout << "Bottom total: " << split.bottomTotal << std::endl;
                //std::cout << "Dealer total: " << dealer.total << std::endl;
                if (split.topTotal <= 21 && dealer.total <= 21 && split.topTotal == dealer.total) //Push
                {
                    split.topResultTexture = renderText("PUSH!", "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                    split.topResultRect = {static_cast<int>(650 + (split.topValues.size()) * 75), 400, 180, 50};

                    textureQ.push_back(split.topResultTexture);
                    rectQ.push_back(split.topResultRect);

                    gameObject.balance += split.topBet;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                }
                if (split.topTotal < 21 && dealer.total < 21 && split.topTotal > dealer.total || (split.topTotal < 21 && dealer.total > 21)) //Player wins
                {
                    split.topResultTexture = renderText("YOU WIN!", "C:/Windows/Fonts/arial.ttf", gameObject.yellow, 14, renderer);
                    split.topResultRect = {static_cast<int>(650 + (split.topValues.size()) * 75), 400, 180, 50};

                    textureQ.push_back(split.topResultTexture);
                    rectQ.push_back(split.topResultRect);

                    gameObject.balance += split.topBet * 2;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                }
                if (split.topTotal == 21 && (dealer.total != 21)) //Blackjack
                {
                    split.topResultTexture = renderText("BLACKJACK!", "C:/Windows/Fonts/arial.ttf", gameObject.yellow, 14, renderer);  
                    split.topResultRect = {static_cast<int>(650 + (split.topValues.size()) * 75), 400, 180, 50};

                    textureQ.push_back(split.topResultTexture);
                    rectQ.push_back(split.topResultRect);

                    gameObject.balance += split.topBet * 2;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                }
                if (split.topTotal < 21 && dealer.total < 21 && split.topTotal < dealer.total) //Dealer wins
                {
                    split.topResultTexture = renderText("YOU LOSE!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 14, renderer);
                    split.topResultRect = {static_cast<int>(650 + (split.topValues.size()) * 75), 400, 180, 50};

                    textureQ.push_back(split.topResultTexture);
                    rectQ.push_back(split.topResultRect);
                }   
            }
            if (!split.bottomBust) //BOTTOM HAND
            {
                if (split.bottomTotal <= 21 && dealer.total <= 21 && split.bottomTotal == dealer.total) //Push
                {
                    split.bottomResultTexture = renderText("PUSH!", "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);  
                    split.bottomResultRect = {static_cast<int>(650 + (split.bottomValues.size()) * 75), 530, 180, 50};

                    textureQ.push_back(split.bottomResultTexture);
                    rectQ.push_back(split.bottomResultRect);

                    gameObject.balance += split.bottomBet;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                }
                if ((split.bottomTotal < 21 && dealer.total < 21 && split.bottomTotal > dealer.total) || (split.bottomTotal < 21 && dealer.total > 21)) //Player wins
                {
                    split.bottomResultTexture = renderText("YOU WIN!", "C:/Windows/Fonts/arial.ttf", gameObject.yellow, 14, renderer);  
                    split.bottomResultRect = {static_cast<int>(650 + (split.bottomValues.size()) * 75), 530, 180, 50};

                    textureQ.push_back(split.bottomResultTexture);
                    rectQ.push_back(split.bottomResultRect);

                    gameObject.balance += split.bottomBet * 2;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                }
                if (split.bottomTotal == 21 && (dealer.total != 21)) //Blackjack
                {
                    split.bottomResultTexture = renderText("BLACKJACK!", "C:/Windows/Fonts/arial.ttf", gameObject.yellow, 14, renderer);  
                    split.bottomResultRect = {static_cast<int>(650 + (split.bottomValues.size()) * 75), 530, 180, 50};

                    textureQ.push_back(split.bottomResultTexture);
                    rectQ.push_back(split.bottomResultRect);

                    gameObject.balance += split.bottomBet * 2;
                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                }
                if ((split.bottomTotal < 21 && dealer.total < 21 && split.bottomTotal < dealer.total)) //Dealer wins
                {
                    split.bottomResultTexture = renderText("YOU LOSE!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 14, renderer);  
                    split.bottomResultRect = {static_cast<int>(650 + (split.bottomValues.size()) * 75), 530, 180, 50};

                    textureQ.push_back(split.bottomResultTexture);
                    rectQ.push_back(split.bottomResultRect);
                }
                else 
                {
                    textureQ.push_back(split.topResultTexture);
                    rectQ.push_back(split.topResultRect);

                    textureQ.push_back(split.bottomResultTexture);
                    rectQ.push_back(split.bottomResultRect);
                }
            }
            }
            gameObject.bet = 0;
            textureQ.push_back(gameObject.balanceTexture); //Balance in position 1
            rectQ.push_back(gameObject.balanceRect);

        break;
        case 8: //Split
            textureQ.push_back(gameObject.selectorTexture);//Selector in position 0
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

            if (gameObject.numOptions == 3) 
            {
            textureQ.push_back(options.doubleDTexture); //"Double" in position 7
            rectQ.push_back(options.doubleDRect);
            }

            textureQ.push_back(split.selectorTexture); //Split selector in position 8
            rectQ.push_back(split.selectorRect);

            textureQ.push_back(split.topTotalTexture); //Split top total in position 9
            rectQ.push_back(split.topTotalRect);

            textureQ.push_back(split.bottomTotalTexture); //Split bottom total in position 10
            rectQ.push_back(split.bottomTotalRect);

            if (split.topResult) //Split top result
            {
                textureQ.push_back(split.topResultTexture);
                rectQ.push_back(split.topResultRect);
                
            }
            

            for (int i = 0; i < split.topValues.size(); i++) //Split top cards
            {
                textureQ.push_back(split.topTextures[i]);
                rectQ.push_back(split.topRects[i]);
            }
            for (int i = 0; i < split.bottomValues.size(); i++) //Split bottom cards
            {
                textureQ.push_back(split.bottomTextures[i]);
                rectQ.push_back(split.bottomRects[i]);

            }
            for (int i = 0; i < dealer.textures.size(); i++) //Split dealer cards
            {
                textureQ.push_back(dealer.textures[i]);
                rectQ.push_back(dealer.rects[i]);
            }


        break; 
        case 9: //End menu
            textureQ.push_back(gameObject.selectorTexture); //Selector in position 0
            rectQ.push_back(gameObject.selectorRect);

            textureQ.push_back(gameObject.balanceTexture); //Balance in position 1
            rectQ.push_back(gameObject.balanceRect);

            textureQ.push_back(gameObject.playAgainTexture); //"Yes" in position 2
            rectQ.push_back(gameObject.playAgainRect);

            textureQ.push_back(gameObject.yesTexture); //"Yes" in position 3
            rectQ.push_back(gameObject.yesRect);

            textureQ.push_back(gameObject.noTexture); //"No" in position 4
            rectQ.push_back(gameObject.noRect);
        
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
        else if (functionNumber == 3 || functionNumber == 4 || functionNumber == 5 || functionNumber == 6 || functionNumber == 7 || functionNumber == 8 || functionNumber == 9) {
            flashingText = gameObject.selectorTexture;
            if (functionNumber == 8) {
                flashingText = split.selectorTexture;
            }
        }

    }
    else {
        flashingText = gameObject.blankTexture;
    }
}




/////////////////////////////////////////////////////////////////////////////////MAIN LOOOP/////////////////////////////////////////////////////////////////////////////////

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
                    Mix_PlayChannel(-1, sound, 0);
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
                        Mix_PlayChannel(-1, sound, 0);
                        if (isConvertibleToDouble(gameObject.inputString) && std::stod(gameObject.inputString) <= gameObject.balance && std::stod(gameObject.inputString) > 0) 
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
}

void game(SDL_Renderer* renderer)
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);
    
    player.totalTexture = renderText("Total: " + toStringWithPrecision(player.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
    player.totalRect = {390, 600, 100, 50};
    
    dealer.totalTexture = renderText("Total: " + toStringWithPrecision(dealer.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
    dealer.totalRect = {390, 325, 100, 50};

    gameObject.playerTurn = true;
    gameObject.surrenderbool = false;
    gameObject.splitbool = false;

    isGameOver = false;
    gameObject.selectorPos = 0;
    functionNumber = 3;

    if (player.values[0] == player.values[1] || (player.values[0] == 11 && player.values[1] == 1)) 
    {
        gameObject.numOptions = 5;
    }
    else if (player.values[0] != player.values[1] && player.total != 21)
    {
        gameObject.numOptions = 4;
    }
    else if (player.total == 21)
    {
        gameObject.numOptions = 1;
        gameObject.selectorPos = 1;
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
                    if (event.key.keysym.sym == SDLK_UP && gameObject.selectorPos > 0 && gameObject.selectorPos != 5 && gameObject.numOptions != 1)
                    {
                        gameObject.selectorPos --;
                        gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                        SDL_RenderClear(renderer);
                        rectQ[0] = gameObject.selectorRect;
                        presentQueue(renderer, textureQ, rectQ);
                    }
                    if (event.key.keysym.sym == SDLK_DOWN && gameObject.selectorPos < gameObject.numOptions - 1)
                    {
                        gameObject.selectorPos ++;
                        gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                        SDL_RenderClear(renderer);
                        rectQ[0] = gameObject.selectorRect;
                        presentQueue(renderer, textureQ, rectQ);
                    }
                    if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        Mix_PlayChannel(-1, sound, 0);
                        switch (gameObject.selectorPos)
                        {
                            case 0: //HIT
                                SDL_RenderClear(renderer);
                                textureQ.clear();
                                rectQ.clear();
                                
                                    if (gameObject.splitbool) //SPLIT HITITNG
                                    {
                                        functionNumber = 8;
                                        gameObject.numOptions = 2;
                                        gameObject.selectorPos = 0;
                                        gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                    switch (split.selectorPos)
                                    {
                                        case 0:
                                        if (split.topTotal <= 21)
                                        {
                                            hit(player);
                                            SDL_DestroyTexture(split.topTotalTexture);
                                            split.topTotalTexture = renderText("Total: " + toStringWithPrecision(split.topTotal, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                        }
                                        if (split.topTotal > 21)
                                        {   
                                            gameObject.numOptions = 3;
                                            split.topResult = true;
                                            split.topResultTexture = renderText("BUST!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 14, renderer);
                                            split.topResultRect = {static_cast<int>(650 + (split.topValues.size()) * 75), 400, 100, 50};
                                            split.selectorPos = 1;
                                            split.selectorRect = {625, 410 + (split.selectorPos * 130), 20, 50};
                                            functionNumber = 8;
                                        }
                                        break;
                                        case 1: 
                                        if (split.bottomTotal < 21)
                                        {
                                            hit(player);
                                            SDL_DestroyTexture(split.bottomTotalTexture);
                                            split.bottomTotalTexture = renderText("Total: " + toStringWithPrecision(split.bottomTotal, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                        }
                                        if (split.bottomTotal == 21)
                                        {
                                            split.bottomResult = true;
                                            split.bottomResultTexture = renderText("BLACKJACK!", "C:/Windows/Fonts/arial.ttf", gameObject.yellow, 14, renderer);
                                            //std::cout << split.bottomResultTexture << std::endl;
                                            split.bottomResultRect = {static_cast<int>(650 + (split.bottomValues.size()) * 75), 530, 180, 50};
                                            gameObject.numOptions = 1;
                                            gameObject.selectorPos = 5;
                                            gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                            functionNumber = 6;
                                        }
                                        if (split.bottomTotal > 21)
                                        {   
                                            split.bottomResult = true;
                                            split.bottomResultTexture = renderText("BUST!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 14, renderer);
                                            split.bottomResultRect = {static_cast<int>(650 + (split.bottomValues.size()) * 75), 530, 100, 50};
                                            gameObject.numOptions = 1;
                                            gameObject.selectorPos = 5;
                                            gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                            functionNumber = 6;
                                        }

                                        break;
                                    }
                                    }
                                
                                else if (!gameObject.splitbool) //REGULAR HITTING
                                {
                                    functionNumber = 4;
                                    gameObject.numOptions = 2;
                                    SDL_DestroyTexture(player.totalTexture);
                               

                                    if (player.total < 21)
                                    {
                                        hit(player);  
                                    }
                                    if (player.total > 21)
                                    {
                                        functionNumber = 6;
                                        dealer.textures[0] = dealer.firstCardTexture;
                                        gameObject.numOptions = 1;
                                        gameObject.selectorPos = 5;
                                        gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                    } 
                                    if (player.total == 21)
                                    {   
                                        functionNumber = 3;
                                        gameObject.numOptions = 1;
                                        gameObject.selectorPos = 1;
                                        gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                    }
                                    player.totalTexture = renderText("Total: " + toStringWithPrecision(player.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                }

                                updateQueue(renderer);
                                presentQueue(renderer, textureQ, rectQ);
                                
                            break;
                            case 1: //STAND
                                SDL_RenderClear(renderer);
                                textureQ.clear();
                                rectQ.clear();
                                        
                                    if (gameObject.splitbool)  //SPLIT STANDING
                                    {
                                        switch (split.selectorPos)
                                        {
                                            case 0:
                                                gameObject.numOptions = 3;
                                                split.selectorPos = 1;
                                                split.selectorRect = {625, 410 + (split.selectorPos * 130), 20, 50};
                                            break;
                                            case 1:
                                                functionNumber = 5;
                                                dealer.textures[0] = dealer.firstCardTexture;
                                                gameObject.numOptions = 1;
                                                gameObject.selectorPos = 5;
                                                gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                                                gameObject.playerTurn = false;
                                                split.splitstand = true;
                                                split.bottomResult = true;
                                                while (dealer.total < 17)
                                                {
                                                    hit(dealer);
                                                    SDL_DestroyTexture(dealer.totalTexture);
                                                    dealer.totalTexture = renderText("Total: " + toStringWithPrecision(dealer.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                                }
                                            break;
                                        }
                                    }
                                
                                else if (!gameObject.splitbool)
                                {
                                functionNumber = 5;
                                dealer.textures[0] = dealer.firstCardTexture;
                                gameObject.numOptions = 1;      
                                gameObject.selectorPos = 5;
                                gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                                gameObject.playerTurn = false;
                                while (dealer.total < 17)
                                {
                                    hit(dealer);
                                    SDL_DestroyTexture(dealer.totalTexture);
                                    dealer.totalTexture = renderText("Total: " + toStringWithPrecision(dealer.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                }
                                }
                                updateQueue(renderer);  
                                presentQueue(renderer, textureQ, rectQ);
                            break;
                            case 2: //DOUBLE DOWN
                                SDL_RenderClear(renderer);
                                textureQ.clear();
                                rectQ.clear();

                                    if (gameObject.splitbool)  //SPLIT DOUBLE DOWN
                                    {
                                        switch (split.selectorPos)
                                        {
                                            case 0:
                                                gameObject.numOptions = 3;
                                                gameObject.balance -= split.topBet;
                                                gameObject.balanceTexture = renderText("Balance: " + toStringWithPrecision(gameObject.balance, 2), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                                gameObject.bet += split.topBet;
                                                split.topBet *= 2;
                                                gameObject.betTexture = renderText("Bet: " + toStringWithPrecision(gameObject.bet, 2), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                                functionNumber = 8;
                                                hit(player);
                                                SDL_DestroyTexture(split.topTotalTexture);
                                                split.topTotalTexture = renderText("Total: " + toStringWithPrecision(split.topTotal, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);

                                                if (split.topTotal > 21)
                                                {
                                                    split.topResult = true;
                                                    split.topResultTexture = renderText("BUST!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 14, renderer);
                                                    split.topResultRect = {static_cast<int>(650 + (split.topValues.size()) * 75), 400, 100, 50};
                                                }
                                                split.selectorPos = 1;
                                                split.selectorRect = {625, 410 + (split.selectorPos * 130), 20, 50};
                                            break;
                                            case 1:
                                                gameObject.balance -= (split.bottomBet);
                                                gameObject.balanceTexture = renderText("Balance: " + toStringWithPrecision(gameObject.balance, 2), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                                gameObject.bet += (split.bottomBet);
                                                split.bottomBet *= 2;
                                                gameObject.betTexture = renderText("Bet: " + toStringWithPrecision(gameObject.bet, 2), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                                functionNumber = 6;
                                                gameObject.numOptions = 1;
                                                split.bottomResult = true;
                                                hit(player);
                                                SDL_DestroyTexture(split.bottomTotalTexture);
                                                split.bottomTotalTexture = renderText("Total: " + toStringWithPrecision(split.bottomTotal, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                                dealer.textures[0] = dealer.firstCardTexture;
                                                gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                                                if (split.bottomTotal > 21)
                                                {
                                                    split.bottomResult = true;
                                                    split.bottomResultTexture = renderText("BUST!", "C:/Windows/Fonts/arial.ttf", gameObject.red, 14, renderer);
                                                    split.bottomResultRect = {static_cast<int>(650 + (split.bottomValues.size()) * 75), 550, 100, 50};

                                                }
                                                gameObject.selectorPos = 5;
                                                gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                                split.splitstand = true;
                                                gameObject.playerTurn = false;

                                                while(dealer.total < 17)
                                                {
                                                   hit(dealer);
                                                   SDL_DestroyTexture(dealer.totalTexture);
                                                   dealer.totalTexture = renderText("Total: " + toStringWithPrecision(dealer.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                                }
                                            break;
                                        }
                                    }
                                    else if (!gameObject.splitbool) //REGULAR DOUBLE DOWN
                                    {
                                    gameObject.bet *= 2;
                                    gameObject.balance -= gameObject.bet/2;
                                    functionNumber = 6;
                                    gameObject.numOptions = 1;
                                    gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                    gameObject.betTexture = renderText("Bet: $" + toStringWithPrecision(gameObject.bet), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                    dealer.textures[0] = dealer.firstCardTexture;
                                    gameObject.selectorPos = 5;
                                    gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                    SDL_DestroyTexture(player.totalTexture);

                                    hit(player);
                                    player.totalTexture = renderText("Total: " + toStringWithPrecision(player.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                    gameObject.playerTurn = false;

                                    while(dealer.total < 17)
                                    {
                                        hit(dealer);
                                        SDL_DestroyTexture(dealer.totalTexture);
                                        dealer.totalTexture = renderText("Total: " + toStringWithPrecision(dealer.total, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                    }
                                    }
                                updateQueue(renderer);
                                presentQueue(renderer, textureQ, rectQ);
                            break;
                            case 3: //SURRENDER
                                gameObject.surrenderbool = true;
                                gameObject.playerTurn = false;
                                gameObject.balance += gameObject.bet/2;
                                dealer.textures[0] = dealer.firstCardTexture;
                                functionNumber = 6;
                                gameObject.numOptions = 1;
                                gameObject.selectorPos = 5;
                                gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};

                                SDL_RenderClear(renderer);
                                textureQ.clear();
                                rectQ.clear();

                                
                                updateQueue(renderer);
                                presentQueue(renderer, textureQ, rectQ);

                            break;
                            case 4: //SPLIT
                                SDL_RenderClear(renderer);
                                textureQ.clear();
                                rectQ.clear();

                                split.topBet = gameObject.bet;
                                split.bottomBet = gameObject.bet;
                                functionNumber = 8;
                                gameObject.balance -= gameObject.bet;
                                gameObject.bet *= 2;
                                gameObject.betTexture = renderText("Bet: $" + toStringWithPrecision(gameObject.bet), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                gameObject.balanceTexture = renderText("Balance: $" + toStringWithPrecision(gameObject.balance), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);

                                gameObject.splitbool = true;
                                gameObject.numOptions = 3;
                                gameObject.selectorPos = 0;
                                gameObject.selectorRect = {75, 300 + (gameObject.selectorPos * 50), 20, 50};
                                split.selectorPos = 0;
                                split.selectorRect = {625, 410 + (split.selectorPos * 130), 20, 50}; // {x, y, w, h) }
                                player.rects[0] = {650, 380, 73, 125};
                                player.rects[1] = {650, 510, 73, 125};
                                
                                split.topTotal = player.values[0];
                                split.topTotalTexture = renderText("Total: " + toStringWithPrecision(split.topTotal, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                split.topValues.push_back(player.values[0]);
                                split.topTextures.push_back(player.textures[0]);
                                split.topRects.push_back(player.rects[0]);
                                
                                split.bottomTotal = player.values[1];
                                split.bottomTotalTexture = renderText("Total: " + toStringWithPrecision(split.bottomTotal, 0), "C:/Windows/Fonts/arial.ttf", gameObject.white, 14, renderer);
                                if (player.values[1] == 11 || player.values[1] == 1)
                                {
                                     split.bottomValues.push_back(11);
                                }
                                else
                                {
                                    split.bottomValues.push_back(player.values[1]);
                                }
                               
                                split.bottomTextures.push_back(player.textures[1]);
                                split.bottomRects.push_back(player.rects[1]);

                                SDL_RenderClear(renderer);
                                textureQ.clear();
                                rectQ.clear();

                                updateQueue(renderer);      
                                presentQueue(renderer, textureQ, rectQ);


                            break;
                            case 5: //CONTINUE TO END MENU
                                isGameOver = true;
                            break;
                        }
                    }
            }                
        }
        SDL_RenderClear(renderer);
        toggleText(renderer, textureQ[0], gameObject, gameObject.lastToggle, functionNumber);// Update the screen
        if (gameObject.splitbool && functionNumber == 8 && gameObject.numOptions == 3)
        {
            toggleText(renderer, textureQ[8], gameObject, gameObject.lastToggle, functionNumber);
        }
        else if (gameObject.splitbool && functionNumber == 8 && gameObject.numOptions == 2)
        {
            toggleText(renderer, textureQ[7], gameObject, gameObject.lastToggle, functionNumber);
        }
        presentQueue(renderer, textureQ, rectQ);
    }
    gameObject.splitbool = false;
    split.selectorPos = 0;
    split.splitstand = false;
    player.total = 0;
    player.textures.clear();
    player.values.clear();
    player.names.clear();
    player.rects.clear();  

    split.topTotal = 0;
    split.topBust = false;
    split.topBlackjack = false;
    split.topResult = false;
    SDL_DestroyTexture(split.topTotalTexture);
    split.topTextures.clear();
    split.topValues.clear();
    split.topRects.clear();

    split.bottomTotal = 0;
    split.bottomBust = false;
    split.bottomBlackjack = false;
    split.bottomResult = false;
    SDL_DestroyTexture(split.bottomTotalTexture);
    split.bottomTextures.clear();
    split.bottomValues.clear();
    split.bottomRects.clear();

    for (int i = 0; i < 52; i++)
    {
        SDL_DestroyTexture(deck.textures[i]);
        SDL_FreeSurface(deck.surfaces[i]);
    }

    dealer.total = 0;
    dealer.textures.clear();
    dealer.values.clear();
    dealer.names.clear();
    dealer.rects.clear();

    deck.names.clear();
    deck.textures.clear();
    deck.surfaces.clear();

    textureQ.clear();
    rectQ.clear();
}

void playAgain(SDL_Renderer* renderer)
{
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255);
    SDL_RenderClear(renderer);
    functionNumber = 9;
    gameObject.numOptions = 2;
    gameObject.selectorPos = 0;
    gameObject.selectorRect = {540, 360 + (gameObject.selectorPos *  50), 20, 50};

    
    bool menu = true;
    SDL_Event event;
    updateQueue(renderer);
    presentQueue(renderer, textureQ, rectQ);

    while (menu)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    isQuit = true;
                    notPlaying = true;
                    menu = false;
                break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_DOWN && gameObject.selectorPos < gameObject.numOptions - 1)
                    {
                        gameObject.selectorPos += 1;
                        gameObject.selectorRect = {540, 360 + (gameObject.selectorPos *  50), 20, 50};

                        SDL_RenderClear(renderer);
                        rectQ[0] = gameObject.selectorRect;
                        presentQueue(renderer, textureQ, rectQ);
                    }
                    else if (event.key.keysym.sym == SDLK_UP && gameObject.selectorPos > 0) 
                    {
                        gameObject.selectorPos -= 1;
                        gameObject.selectorRect = {540, 360 + (gameObject.selectorPos *  50), 20, 50};

                        SDL_RenderClear(renderer);
                        rectQ[0] = gameObject.selectorRect;
                        presentQueue(renderer, textureQ, rectQ);
                    }
                    else if (event.key.keysym.sym == SDLK_RETURN)
                    {
                        Mix_PlayChannel(-1, sound, 0);
                        switch(gameObject.selectorPos) 
                        {
                            case 0: //YES PLAY AGAIN
                                menu = false;
                            break;
                            case 1: //NO DON'T PLAY AGAIN.
                                isQuit = true;
                                notPlaying = true;
                                menu = false;
                            break;
                        }
                    }
            }

        }
        SDL_RenderClear(renderer);
        toggleText(renderer, textureQ[0], gameObject, gameObject.lastToggle, functionNumber);// Update the screen
        presentQueue(renderer, textureQ, rectQ);
    }
    textureQ.clear();
    rectQ.clear();
}   
/////////////////////////////////////////////////////////////////////////////////END OF MAIN LOOP/////////////////////////////////////////////////////////////////////////////////




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
            //std::cout << deck.names[i] << " has value " << deck.values[i] << std::endl;
        }
    }

    //ADJUSTED
    void initial_assignment(SDL_Renderer* renderer, deckClass& deck) 
    {
        //std::cout << "initial assignment started" << std::endl;
        //Number assignment
        for (int i = 0; i < 4; i++) 
        {
            for (int j = 0; j < 13; j++)
            {
                if (j + 1 <= 10) 
                {
                    deck.values[(i * 13) + j] = j + 1; 
                }
                else if (j + 1 > 10) 
                {
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
                deck.names[(i * 13) + j] = ranks[j] + suits[i];
            }
        }

        for (int i = 0; i < 52; i++) 
        {
            //std::cout << "card " << (i) << ": " << deck.names[i] << std::endl;
        }

        SDL_Surface* surface;
        SDL_Texture* texture;
        for (int i = 0; i < 52; i++) 
        {
            surface = cardSurface(deck.names[i]);
            texture = cardTexture(renderer, surface);
            deck.surfaces.push_back(surface);
            deck.textures.push_back(texture);
            //std::cout << "texture " << (i) << ": " << deck.textures[i] << std::endl;
        }
    }

    //ADJUSTED
    void shuffle() 
    {
        int randoms[52];
        int previous_values[52];
        std::string previous_names[52];
        std::vector<SDL_Texture*> previous_textures;

        for (int i = 0; i < 52; i ++) 
        {
            ////std::cout << "loop 3 ran" << std::endl;
            previous_values[i] = deck.values[i];
            previous_names[i] = deck.names[i];
            previous_textures.push_back(deck.textures[i]);
            ////std::cout << "Previous texture:" << previous_textures[i] << std::endl;
        }

        //Unique random number array generation
        random_array(randoms, 52);
        for (int i = 0; i < 52; i++)
        {
            //std::cout << randoms[i] << std::endl;
        }
        for (int i = 0; i < 52; i++) 
        {
            deck.values[randoms[i]] = previous_values[i];
            deck.names[randoms[i]] = previous_names[i];
            deck.textures[randoms[i]] = previous_textures[i];
        }
    }

    //ADJUSTED
    void initial_deal(deckClass deck) 
    {
        player.total = 0;
        dealer.total = 0;
        for (int i = 0; i < 4; i++)
        {
            //Player
            if (i == 0 || i == 2) 
            {
                //std::cout << "texture to be assigned to player: " << deck.textures[51 - i] << std::endl;
                player.values.push_back(deck.values[51 - i]);
                player.names.push_back(deck.names[51 - i]);
                player.textures.push_back(deck.textures[51 - i]);
                player.rects.push_back({500 + (i/2 * 150), 380, 145, 250}); //PLAYER.RECTS ASSIGNMENT
                ////std::cout << "player name: " << player.names[player.names.size() - 1] << std::endl;
                //std::cout << "texture in player vector: " << player.textures[player.textures.size() - 1] << std::endl;
                //std::cout << "Player value: " << player.values[player.values.size() - 1] << std::endl;
                player.total += deck.values[51 - i];
                deck.textures[51 - i] = nullptr;
                deck.values[51 - i] = 0;
                deck.names[51 - i] = "EMPTY";
            }
            //Dealer
            else if (i == 1 || i == 3) 
            {
                //std::cout << "texture to be assigned to dealer: " << deck.textures[51 - i] << std::endl;
                dealer.values.push_back(deck.values[51 - i]);
                dealer.names.push_back(deck.names[51 - i]);
                dealer.rects.push_back({500 + ((i-1)/2 * 150), 80, 145, 250});
                //std::cout << "dealer name: " << dealer.names[dealer.names.size() - 1] << std::endl;
                //std::cout << "dealer rects have been updated" << std::endl;
                if (i == 1) 
                {
                    gameObject.firstDealerCardSurface= deck.surfaces[51 - i];
                    gameObject.firstDealerCardTexture = deck.textures[51 - i];
                    dealer.firstCardTexture = gameObject.firstDealerCardTexture;
                    dealer.textures.push_back(gameObject.hiddenCardTexture);
                }
                else 
                {
                    dealer.textures.push_back(deck.textures[51 - i]);
                }   
                //std::cout << "texture in dealer vector: " << dealer.textures[dealer.textures.size() - 1] << std::endl;
                dealer.total += deck.values[51 - i];
                deck.textures[51 - i] = nullptr;
                deck.values[51 - i] = 0;
                deck.names[51 - i] = "EMPTY";
            }
        }

        /*
        for (int i = 0; i < 52; i++) 
        {
            //std::cout << "card " << i << ": " << deck.names[i] << " has value " << deck.values[i] << std::endl;
        }
       */
       

       //Player draws an ace or multiple aces
        if (player.values[0] == player.values[1]  && player.values[0] == 1)  
        {
            player.values[0] = 11;
            player.total = player.values[0] + player.values[1];
        }
        else if (player.values[0] == 1 && (11 + player.values[1]) <= 21)
        {
            player.values[0] = 11;
            player.total = player.values[0] + player.values[1];
        }
        else if (player.values[1] == 1 && (11 + player.values[0]) <= 21)
        {
            player.values[1] = 11;
            player.total = player.values[0] + player.values[1];
        }

        //Dealer draws an ace or multiple aces
        if (dealer.values[0] == dealer.values[1]  && dealer.values[0] == 1)
        {
            dealer.values[0] = 11;
            dealer.total = dealer.values[0] + dealer.values[1];
        }
        else if (dealer.values[0] == 1 && (11 + dealer.values[1]) <= 21)
        {
            dealer.values[0] = 11;
            dealer.total = dealer.values[0] + dealer.values[1];
        }
        else if (dealer.values[1] == 1 && (11 + dealer.values[0]) <= 21)
        {
            dealer.values[1] = 11;
            dealer.total = dealer.values[0] + dealer.values[1];
        }

    }

    //ADJUSTED
    void hit(playerClass& player_dealer)    
    {
        int index = 47;
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

        if (!gameObject.splitbool || split.splitstand) //REGULAR HITTING
        {
            //std::cout << "0" << std::endl;
           
            //std::cout << "player total: " << player_dealer.total << std::endl;
            gameObject.newCards += 1;
            player_dealer.values.push_back(deck.values[index]);
            player_dealer.names.push_back(deck.names[index]);
            player_dealer.textures.push_back(deck.textures[index]);

            if (deck.values[index] == 1 && (11 + player_dealer.total <= 21))
            {
                player_dealer.values[player_dealer.values.size() - 1] = 11;
                deck.values[index] = 11;
            }
            
            player_dealer.total += deck.values[index];

            if (player_dealer.total > 21)   //ACE FIX IF TOTAL > 21 & PLAYER/DEALER HAS AN ACE VALUE OF 11
            {
                for (int i = 0; i < player_dealer.values.size(); i++)
                {
                    if (player_dealer.values[i] == 11)
                    {
                        player_dealer.values[i] = 1;
                        player_dealer.total -= 10;
                    }
                }
            }

            if (gameObject.playerTurn == true && gameObject.splitbool == false)  //PLAYER CARD RECTANGLE MGMT
            {
                //std::cout << "1" << std::endl;
                if (player_dealer.values.size() > 5) 
                {   
                    for (int i = 0; i < 5; i++) 
                    {
                        player_dealer.rects[i] = {500 + (i * 75), 380, 73, 125};
                    }
                    for (int j = 0; j < player_dealer.values.size() - 5; j++)
                    {
                        player_dealer.rects[j + 5] = {500 + (j * 75), 510, 73, 125};
                    }
                }
                else
                {
                    player_dealer.rects.push_back({static_cast<int>(500 + ((player_dealer.values.size() - 1) * 150)), 380, 145, 250});
                }
            }
            else if (gameObject.playerTurn == false)  //DEALER CARD RECTANGLE MGMT
            {
                //std::cout << "2" << std::endl;
                if (player_dealer.values.size() > 5) 
                {   
                    for (int i = 0; i < 5; i++) 
                    {
                        player_dealer.rects[i] = {500 + (i * 75), 80, 73, 125};
                    }

                    for (int j = 0; j < player_dealer.values.size() - 5; j++)
                    {
                        player_dealer.rects[j + 5] = {500 + (j * 75), 210, 73 , 125};
                    }
                }
                else 
                { 
                    player_dealer.rects.push_back({static_cast<int>(500 + ((player_dealer.values.size() - 1) * 150)), 80, 145, 250});
                }
            
            }
        }



        else if (gameObject.playerTurn == true && gameObject.splitbool == true)  //SPLIT HITTING
        {
            switch (split.selectorPos)
            {
                case 0:
                    gameObject.newCards += 1;
                    
                    split.topValues.push_back(deck.values[index]);
                    
                    if (deck.values[index] == 1 && (11 + split.topTotal <= 21))
                    {
                        split.topValues[split.topValues.size() - 1] = 11;
                        deck.values[index] = 11;
                    }
                    split.topTotal += deck.values[index];
                    split.topNames.push_back(deck.names[index]);
                    split.topTextures.push_back(deck.textures[index]);
                    split.topRects.push_back({static_cast<int>(650 + (split.topValues.size() - 1) * 75), 380, 73, 125});

                    if (split.topTotal > 21) 
                    {
                        for (int i = 0; i < split.topValues.size(); i++) 
                        {
                            if (split.topValues[i] == 11) 
                            {
                                split.topValues[i] = 1;
                                split.topTotal -= 10;
                            }
                        }
                    }
                    
                break;
                case 1:
                    gameObject.newCards += 1;
                    
                    split.bottomValues.push_back(deck.values[index]);

                    if (deck.values[index] == 1 && (11 + split.bottomTotal <= 21)) 
                    {
                        split.bottomValues[split.bottomValues.size() - 1] = 11;
                        deck.values[index] = 11;
                    }

                    split.bottomTotal += deck.values[index];
                    split.bottomNames.push_back(deck.names[index]);
                    split.bottomTextures.push_back(deck.textures[index]);
                    split.bottomRects.push_back({static_cast<int>(650 + (split.bottomValues.size() - 1) * 75), 510, 73, 125});

                    if (split.bottomTotal > 21)
                    {
                        for (int i = 0; i < split.bottomValues.size(); i++) 
                        {
                            if (split.bottomValues[i] == 11) 
                            {
                                split.bottomValues[i] = 1;
                                split.bottomTotal -= 10;
                            }
                        }
                    }
                break;
            }
        }
        //std::cout << "card from hit: " << deck.names[index] << std::endl;
        deck.values[index] = 0;
        deck.names[index] = "EMPTY";
        deck.textures[index] = nullptr;
    }