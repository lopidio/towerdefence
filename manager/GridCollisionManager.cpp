/** ********************/
//***************
//  - Lopidio
#include "GridCollisionManager.h"
#include "../machine/GameMachine.h"
#include "../machine/MainGameState.h"
#include "../util/Util.h"
#include "../util/Circle.h"
#include <cmath>
#include <stdio.h>

namespace manager
{

        GridCollisionManager::GridCollisionManager(const sf::Vector2i& tileGridSize_, const sf::Vector2i& boardSize)
                :
                tileGridSize(tileGridSize_),
                numLinhas(ceil((float)boardSize.y/(float)tileGridSize.y)),
                numColunas(ceil((float)boardSize.x/(float)tileGridSize.x)),
                grid(NULL),
                gridRect(NULL),
                collidableAssociationContainer()
        {
                grid = new CollidableContainer*[numLinhas];
                for (char i = 0; i < numLinhas; ++i)
                        grid[i] = new CollidableContainer[numColunas];

                gridRect = new sf::FloatRect*[numLinhas];
                for (char i = 0; i < numLinhas; ++i)
                        gridRect[i] = new FloatRect[numColunas];

                for (char linha = 0; linha < numLinhas; ++linha)
                        for (char coluna = 0; coluna < numColunas; ++coluna)
                        {
                                gridRect[linha][coluna] = sf::FloatRect(coluna*tileGridSize.x, linha*tileGridSize.y, tileGridSize.x, tileGridSize.y);
                        }
        }


        GridCollisionManager::~GridCollisionManager()
        {
                clear();
                //Deleto os ponteiros
                for (char i = 0; i < numLinhas; ++i)
                {
                        delete[] grid[i];
                }

                delete[] grid;
                //Aponto para nulo
                grid = 0;


                //Deleto os ponteiros
                for (char i = 0; i < numLinhas; ++i)
                        delete[] gridRect[i];

                delete[] gridRect;
                //Aponto para nulo
                gridRect = 0;

        }
        void GridCollisionManager::clear()
        {
                for (char linha = 0; linha < numLinhas; ++linha)
                        for (char coluna = 0; coluna < numColunas; ++coluna)
                        {
                                grid[linha][coluna].clear();
                        }

                collidableAssociationContainer.clear();
        }

        void GridCollisionManager::addCollidable(control::Collidable* collidable) //Só invoco esses métodos caso o ator tenha se movido
        {
                const util::Circle& circle = collidable->getCollisionCircle();
                //posição do colidível no tile dos grids (e arredores)
                sf::Vector2i gridPosition(circle.getCenter().x/gridRect[0][0].width, circle.getCenter().y/gridRect[0][0].height);
                sf::Vector2i desloc(ceil(circle.getRay()/gridRect[0][0].width), ceil(circle.getRay()/gridRect[0][0].height));

                //Insere em todos os girds cujo o círculo intersect
                for (short linha = gridPosition.y - desloc.y; linha < numLinhas && linha <= gridPosition.y + desloc.y; ++linha)
                        for (short coluna = gridPosition.x - desloc.x; coluna < numColunas && coluna <= gridPosition.x + desloc.x; ++coluna)
                        {
                                if (linha < 0 || coluna < 0)
                                        continue;
                                const util::Circle& circle = collidable->getCollisionCircle();
                                if (util::Util::IntersectsCircleRect(circle, gridRect[linha][coluna]))
                                {
                                        //std::cout << "Insercao em (" << (int)linha << ", " << (int)coluna << "\n";
                                        grid[linha][coluna].push_back(collidable);
                                }
                        }
        }
        void GridCollisionManager::execute()
        {
                for (char i = 0; i < numLinhas; ++i)
                        for (char j = 0; j < numColunas; ++j) //Todos os grids
                        {
                                if (grid[i][j].size() > 1)
                                {
                                        CollidableContainer& currentList = grid[i][j];
                                        CollidableContainer::iterator itFirst = currentList.begin();
                                        for (; itFirst != currentList.end(); ++itFirst)
                                        {
                                                CollidableContainer::reverse_iterator itLast = currentList.rbegin(); //Começa do fim
                                                for (; *itLast != *itFirst; itLast++)//Todos os elementos dos grids
                                                {
                                                        checkCollision(*itFirst, *itLast);
                                                }
                                        }
                                }
                        }
        }
                void GridCollisionManager::checkCollision(control::Collidable* firstCollidable, control::Collidable* lastCollidable)
                {

                        //Se o primeiro se colide com o segundo
                        CollidableAssociation association1to2(firstCollidable, lastCollidable); //Crio o par
                        if ( firstCollidable->checkCollision( *lastCollidable ) && //Se se colidiram
                        collidableAssociationContainer.find(association1to2) == collidableAssociationContainer.end()) //Se ainda não foram tratados
                        {
                                //Insiro na lista de pares já verificados
                                collidableAssociationContainer.insert(association1to2);
                                firstCollidable->handleCollision(*lastCollidable);
                        }
                        //Se o primeiro se colide com o segundo
                        CollidableAssociation association2to1(lastCollidable, firstCollidable); //Crio o par

                        //Se o segundo se colide com o primeiro
                        if ( lastCollidable->checkCollision( *firstCollidable ) && //Se se colidiram
                        collidableAssociationContainer.find(association2to1) == collidableAssociationContainer.end()) //Se ainda não foram tratados
                        {
                                //Insiro na lista de pares já verificados
                                collidableAssociationContainer.insert(association2to1);
                                lastCollidable->handleCollision(*firstCollidable);
                        }

                }
#ifdef GRIDCOLLISION_DEBUG_DRAW
                void GridCollisionManager::draw() const
                {
                        int heightFactor = 100/numLinhas;
                        int widthFactor = 100/numColunas;
                        int crowdFactor = 50;
                        for (char i = 0; i < numLinhas; ++i)
                                for (char j = 0; j < numColunas; ++j) //Todos os grids
                                {
                                        sf::FloatRect& rect = gridRect[i][j];
                                        sf::RectangleShape rs(sf::Vector2f(rect.width, rect.height));
                                        rs.setPosition(rect.left, rect.top);
                                        rs.setFillColor(sf::Color(crowdFactor*grid[i][j].size(), heightFactor*i + j*widthFactor, 0));
                                        machine::GameMachine::Draw(rs);
                                }

                }
#endif
                unsigned int GridCollisionManager::gridMaxSize() const
                {
                        int maior = 0;
                        for (char i = 0; i < numLinhas; ++i)
                                for (char j = 0; j < numColunas; ++j) //Todos os grids
                                {
                                        int gridSize = grid[i][j].size();
                                        if (gridSize > maior)
                                                maior = gridSize;
                                }
                        return maior;
                }

} //end of namespace control


