#ifndef GAMEMACHINE_H
#define GAMEMACHINE_H

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "../manager/TextureResourceManager.h"
#include <stack>

namespace machine
{

        class GameMachine
        {
                typedef std::stack<GameState*> GameStateStack;
                private: //Singleton properties
                        GameMachine();
                        GameMachine(const GameMachine&);
                        GameMachine& operator=(const GameMachine&);
                        static GameMachine* instance;
                public:
                        virtual ~GameMachine();
                        static GameMachine* GetInstance();
                        static void Draw(const sf::Drawable& drawable);
                        void addState(GameState* gameState);
                        void popState();
                        void run();
                        static manager::TextureResourceManager& TextureResourceManager();
                private: //Instance members
                        void init();
                        void load();
                        void gameLoop();
                        void unload();
                        void handleEvents();

                        GameStateStack gameStateStack;
                        sf::RenderWindow renderWindow;
                        manager::TextureResourceManager textureResourceManager;
        };

}

#endif // GAMEMACHINE_H
