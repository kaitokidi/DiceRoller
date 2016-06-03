//GRAVITY
#include <time.h>       /* time */
#include <string>       /*strings*/
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "button.h"
#include "Portada.hpp"
#include "TextScreen.hpp"
#include "MenuSelection.hpp"


int main(int argc, const char* argv[]){
      
    srand (time(NULL));
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Dice Roller");
    sf::Vector2f screenSize = sf::Vector2f(window.getSize().x,window.getSize().y);    
    float deltatime = 0;
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    Portada portada;
    
    //Cover
    portada.notAnimation();
    portada.display(&window, "res/pics/portada.png");
    //Credits
//     portada.animation();
     portada.display(&window, "res/pics/credits.png");
        
    //GAME
    
    int kind = 0;
    MenuSelection kindSelector;
    std::vector<std::string> kinds;
    //same order as enum.
    int diceQtty = 9;
    int dices[diceQtty] = {2,3,4,6,8,10,12,20,100};
    
    int qttyCrit = 6;
    std::string criticals[qttyCrit] = { "CRITICAL!!!", "MAX DMG!", "TOO MUCH!", "INSTAKILL!", "KABOOOM!!!", "PENTAKILL!!!"}; 
    
    int qttyFail = 6;
    std::string pifies[qttyFail] = { "PIFIA!!!", "Ridiculous amount!", "Null", "... nothing", "NaN", "fail..."}; 
    
//     std::cout << "penguin" << std::endl;
    for(int i = 0; i < diceQtty; ++i){
        kinds.push_back(" "+std::to_string(dices[i])+" ");
    }
    kinds.push_back(" Crit ");
    kinds.push_back(" Fail ");

    kind = kindSelector.select(&window, kinds);
    
    Button button;
    button.setTexture("res/pics/buttons/buttonReleassed.png");
    button.setPressedTexture("res/pics/buttons/buttonPressed.png");
    button.setOrigin(sf::Vector2f(button.getSize().x/2,button.getSize().y/2));
    button.setPosition(window.getSize().x/2,window.getSize().y/2);
    button.setSize(window.getSize().y/3,window.getSize().y/3);
    TextScreen textScreen;

    Button back_button;
    sf::Font font;
    if(!font.loadFromFile("res/fonts/font.otf")){ std::cerr << "Can't find the font file" << std::endl; }
    back_button.setFont(font);    
    back_button.setTexture("res/pics/buttons/back_buttonReleassed.png");
    back_button.setPressedTexture("res/pics/buttons/back_buttonPressed.png");
    back_button.setPosition(0,0);
    back_button.setSize(window.getSize().x/10,window.getSize().x/20);
    back_button.setText("   back   ");
    
    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)) {
            button.handleEvent(event);
            back_button.handleEvent(event);
            
            if (event.type == sf::Event::Closed) { window.close(); exit(0); } 
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { window.close(); exit(0); }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); exit(0); }
        
        if(!button.isClicked() && button.hasBeenClicked()){
            std::string frase = "You Rolled ";

            if(kind == diceQtty){
                frase += criticals[rand()%qttyCrit];
            }
            else if(kind == diceQtty +1){
                frase += pifies[rand()%qttyFail];
            }
            else frase+= std::to_string((rand()%dices[kind]) +1);

            textScreen.displayText(&window, frase, sf::Color::Black); 
        }
        if(!back_button.isClicked() && back_button.hasBeenClicked()){
            kind = kindSelector.select(&window, kinds);
        }        
        window.clear();
        button.draw(window);
        back_button.draw(window);
        window.display();
    }
}
