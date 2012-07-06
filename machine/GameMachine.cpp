/** ********************/
//***************
//  - Lopidio
#include "GameMachine.h"
#include "MainGameState.h"

#include <iostream>

namespace machine
{
        GameMachine* GameMachine::instance = NULL;

        GameMachine::GameMachine()
                :
                gameStateStack(),
                renderWindow(sf::VideoMode(800, 600), "SFML works!"),
                textureResourceManager()
        {
                //ctor
        }

        GameMachine::~GameMachine()
        {
                //dtor
        }

        /** @brief unload
          *
          * @todo: document this function
          */
        void GameMachine::unload()
        {
                if (gameStateStack.size() > 0)
                        gameStateStack.top()->unload();
        }

        /** @brief gameLoop
          *
          * @todo: document this function
          */
        void GameMachine::gameLoop()
        {
            while (renderWindow.isOpen())
            {
                handleEvents();
                renderWindow.clear();
                if (gameStateStack.size() > 0)
                {
//                        std::cout << "gameloop\n";
                        gameStateStack.top()->update();
                        gameStateStack.top()->draw();
                }
                renderWindow.display();
            }
        }

        /** @brief handleEvents
          *
          * @todo: document this function
          */
        void GameMachine::handleEvents()
        {
                sf::Event event;
                while (renderWindow.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        renderWindow.close();
                }

        }


        /** @brief load
          *
          * @todo: document this function
          */
        void GameMachine::load()
        {
        }

        /** @brief run
          *
          * @todo: document this function
          */
        void GameMachine::run()
        {
                //add default state
                init();
                load();
                gameLoop();
                unload();
        }

        /** @brief popState
          *
          * @todo: document this function
          */
        void GameMachine::popState()
        {
                if (gameStateStack.size() > 0)
                {
                        gameStateStack.top()->unload();
                        gameStateStack.pop();
                }
        }

        /** @brief addState
          *
          * @todo: document this function
          */
        void GameMachine::addState(GameState* gameState)
        {
                if (gameState)
                {
                        gameState->init();
                        gameState->load();
                        gameStateStack.push(gameState);
                }
        }

        /** @brief getInstance
          *
          * @todo: document this function
          */
        GameMachine* GameMachine::GetInstance()
        {
                if (!instance)
                        instance = new GameMachine();
                return instance;
        }


        /** @brief init
          *
          * @todo: document this function
          */
        void GameMachine::init()
        {
                addState(new MainGameState());
        }


        /** @brief draw
          *
          * @todo: document this function
          */
        void GameMachine::Draw(const sf::Drawable& drawable)
        {
                GetInstance()->renderWindow.draw(drawable);
        }

        /** @brief getTextureResourceManager
          *
          * @todo: document this function
          */
        manager::TextureResourceManager& GameMachine::TextureResourceManager()
        {
                return GetInstance()->textureResourceManager;
        }

        const sf::RenderWindow& GameMachine::Window()
        {
                return GetInstance()->renderWindow;
        }
}
