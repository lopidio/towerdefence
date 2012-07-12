#ifndef MAINGAMESTATE_H
#define MAINGAMESTATE_H

#include <SFML/Graphics.hpp>
#include <list>
#include "GameState.h"
#include "GameMachine.h"
#include "../actor/GameActor.h"
#include "../manager/GridCollisionManager.h"
#include "../control/TimeMaster.h"
#include "../control/PathFinder.h"
#include "../factory/ArtefactFactory.h"

using namespace sf;

namespace machine
{
        typedef std::list<actor::GameActor*> GameActorList;
        class MainGameState : public GameState
        {
                private://Global access
                        static MainGameState* globalInstance;
                public:
                        MainGameState();
                        virtual ~MainGameState();
                        virtual void init();
                        virtual void update();
                        virtual void load();
                        virtual void unload();
                        virtual void draw() const;
                        static int TileSize();
                        static MainGameState* GetGlobalAccess();
                        static sf::Vector2i TransformToTilePosition(const sf::Vector2f& position);
                        static sf::Vector2i TransformTileToBoardPosition(const sf::Vector2f& position);
                        static manager::GridCollisionManager& GridCollisionManager();
                        static void AddGameActor(actor::GameActor* gameActor);
                        static control::Board& GetBoard();
                        static control::PathFinder& GetPathFinder();
                protected:
                        void removeDeadGameActor();
                private:
                        GameActorList gameActorList;
                        manager::GridCollisionManager collisionManager;
                        control::TimeMaster timeMaster;
                        control::PathFinder pathFinder;
                        int tileSize;
                        control::Board board;
                        factory::ArtefactFactory artefactFactory;
        };

}
#endif // MAINGAMESTATE_H
