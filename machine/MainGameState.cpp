/** ********************/
//***************
//  - Lopidio
#include "MainGameState.h"
#include "../actor/Unit.h"
#include "../actor/Artefact.h"

namespace machine
{
        //Global access
        MainGameState* MainGameState::globalInstance = NULL;

        MainGameState::MainGameState()
                :
                gameActorList(),
                collisionManager(sf::Vector2i(128,128), sf::Vector2i(640,420)), //Tamanho de (2x2) grid, e tamanho do tabuleiro
                timeMaster(),
                pathFinder(),
                tileSize(32),
                board(16,20), //Linhas, colunas
                artefactFactory()
        {
        }

        MainGameState::~MainGameState()
        {
                //Deletar o ponteiro
                //Remover do gerenciador de colisões
                gameActorList.clear();

                if (globalInstance == this)
                        globalInstance = NULL;
        }

        /** @brief draw
          *
          * @todo: document this function
          */
        void MainGameState::draw() const
        {
#ifdef DEBUG_DRAW
                collisionManager.draw();
#endif

                //Percorre de trás para frente (por conta da ordenação contrária)
                for (GameActorList::const_iterator it = gameActorList.begin(); it != gameActorList.end(); ++it)
                        (*it)->draw();

#ifdef DEBUG_DRAW
                artefactFactory.draw();
#endif

                //desenhar a GUI
        }

        /** @brief update
          *
          * @todo: document this function
          */
        void MainGameState::update()
        {
                collisionManager.clear();
                float deltaTime = timeMaster.getEllapsedTimeInSeconds();
                timeMaster.restart();
                if (deltaTime >= 0.2)//Dar valores máximos
                        deltaTime = 0.2;

                artefactFactory.update();
                for (GameActorList::iterator it = gameActorList.begin(); it != gameActorList.end(); ++it)
                {
                        (*it)->update(deltaTime);
                }

                removeDeadGameActor();

                //std::cout << "Update time: " << deltaTime <<"\n";
                //verificar se o alive == true

                //Atualizar o gerenciador de colisão
                collisionManager.execute();

                //Ordeno a lista para a renderização ficar correta
                gameActorList.sort(actor::GameActor::ZIndexComparator);
        }

        void MainGameState::removeDeadGameActor()
        {
                for (GameActorList::iterator it = gameActorList.begin(); it != gameActorList.end();)
                {
                        if(!(*it)->isAlive())
                                it = gameActorList.erase(it);
                        else
                                ++it;
                }
        }


        /** @brief getTileSize
          *
          * @todo: document this function
          */
        int MainGameState::TileSize()
        {
                return globalInstance->tileSize;
        }

        /** @brief init
          *
          * @todo: document this function
          */
        void MainGameState::init()
        {
                globalInstance = this;
                //Percorre de trás para frente (por conta da ordenação contrária)
                for (GameActorList::const_iterator it = gameActorList.begin(); it != gameActorList.end(); ++it)
                        (*it)->init();

                control::Path caminho;
                caminho.push_back(sf::Vector2f(0,0));
                caminho.push_back(sf::Vector2f(1,0));
                caminho.push_back(sf::Vector2f(1,1));
                caminho.push_back(sf::Vector2f(2,1));
                caminho.push_back(sf::Vector2f(2,0));
                caminho.push_back(sf::Vector2f(3,0));
                caminho.push_back(sf::Vector2f(3,1));
                caminho.push_back(sf::Vector2f(3,2));
                caminho.push_back(sf::Vector2f(3,3));
                caminho.push_back(sf::Vector2f(4,3));
                caminho.push_back(sf::Vector2f(4,2));
                caminho.push_back(sf::Vector2f(4,1));
                caminho.push_back(sf::Vector2f(4,0));
                caminho.push_back(sf::Vector2f(5,0));
                caminho.push_back(sf::Vector2f(4,0));
                caminho.push_back(sf::Vector2f(3,0));
                caminho.push_back(sf::Vector2f(2,0));
                caminho.push_back(sf::Vector2f(2,1));
                caminho.push_back(sf::Vector2f(2,2));
                caminho.push_back(sf::Vector2f(2,3));
                caminho.push_back(sf::Vector2f(3,3));
                caminho.push_back(sf::Vector2f(3,2));
                caminho.push_back(sf::Vector2f(3,1));
                caminho.push_back(sf::Vector2f(4,1));
                caminho.push_back(sf::Vector2f(5,1));

                control::Path c2;

                c2.push_back(sf::Vector2f(2,5));
                c2.push_back(sf::Vector2f(3,5));
                c2.push_back(sf::Vector2f(3,4));
                c2.push_back(sf::Vector2f(3,3));
                c2.push_back(sf::Vector2f(4,3));
                c2.push_back(sf::Vector2f(5,3));
                c2.push_back(sf::Vector2f(6,3));
                c2.push_back(sf::Vector2f(6,4));
                c2.push_back(sf::Vector2f(6,5));
                c2.push_back(sf::Vector2f(6,6));
                c2.push_back(sf::Vector2f(7,6));

                actor::Unit* unit;
                actor::GameActor* ga;

                unit  = new actor::Unit();
                ga = unit;
                ga->init();
                unit->setPath(caminho);
                gameActorList.push_back(unit);

                unit  = new actor::Unit();
                ga = unit;
                ga->init();
                unit->setPath(c2);
                gameActorList.push_back(unit);

                pathFinder.setBoard(&board);
                pathFinder.setGoal(sf::Vector2f(5,2));

                /*sf::Vector2i pos(2,6);
                actor::Artefact::ArtefactDefinition def;
                def.ray = 80;
                def.position = pos;
                actor::Artefact* arte;
                arte = new actor::Artefact(def);
                ga = arte;
                ga->init();
                gameActorList.push_back(ga);
                board.setCell(ga->getBoardPosition().y, ga->getBoardPosition().x, true);

                def.position = sf::Vector2i(4,2);
                arte = new actor::Artefact(def);
                ga = arte;
                ga->init();
                gameActorList.push_back(ga);
                board.setCell(ga->getBoardPosition().y, ga->getBoardPosition().x, true);*/

                artefactFactory.select(0); //ID do artefato selecionado
        }

        /** @brief GetGlobalAccess
          *
          * @todo: document this function
          */
        MainGameState * MainGameState::GetGlobalAccess()
        {
                return globalInstance;
        }

        void MainGameState::load()
        {
                for (GameActorList::iterator it = gameActorList.begin(); it != gameActorList.end(); ++it)
                        (*it)->load();
        }
        void MainGameState::unload()
        {
                for (GameActorList::iterator it = gameActorList.begin(); it != gameActorList.end(); ++it)
                        (*it)->unload();
        }
        sf::Vector2i MainGameState::TransformToTilePosition(const sf::Vector2f& position)
        {
                //retorno
                sf::Vector2i tilePosition = sf::Vector2i(position);
                //Calcula a posição em tiles
                tilePosition.x /= globalInstance->tileSize;
                tilePosition.y /= globalInstance->tileSize;
                return tilePosition;
        }
        sf::Vector2i MainGameState::TransformTileToBoardPosition(const sf::Vector2f& position)
        {
                sf::Vector2i tilePosition = sf::Vector2i(position);
                tilePosition *= globalInstance->tileSize;

                //Centraliza a unidade no centro da tile
                tilePosition.x += globalInstance->tileSize/2;
                tilePosition.y += globalInstance->tileSize/2;

                return tilePosition;
        }
        manager::GridCollisionManager& MainGameState::GridCollisionManager()
        {
                return GetGlobalAccess()->collisionManager;
        }
        void MainGameState::AddGameActor(actor::GameActor* gameActor)
        {
                globalInstance->gameActorList.push_back(gameActor);
        }

        /** @brief GetBoard
        *
        * @todo: document this function
        */
        control::Board & MainGameState::GetBoard()
        {
                return globalInstance->board;
        }

}
