/** ********************/
//***************
//  - Lopidio
#include "ArtefactBuilder.h"
#include <SFML/Graphics.hpp>
#include "../control/Board.h"
#include "../machine/MainGameState.h"
#include <stdio.h>

using namespace sf;
using namespace actor;

namespace factory
{

        ArtefactBuilder::ArtefactBuilder():artefactDefinitionSelected(NULL)
        {
                //ctor
        }

        ArtefactBuilder::~ArtefactBuilder()
        {
                //dtor
        }

        void ArtefactBuilder::update()
        {
                if (artefactDefinitionSelected)
                {
                        if (Mouse::isButtonPressed(Mouse::Left))
                        {
                                Vector2i mousePosition = Mouse::getPosition(machine::GameMachine::Window());
                                Vector2i mouseTilePosition(mousePosition.x-mousePosition.x%32 + 16, mousePosition.y-mousePosition.y%32 + 16);

                                if (!machine::MainGameState::GetBoard().getCell(mouseTilePosition.y, mouseTilePosition.x))//Verifica se o tabuleiro está livre
                                {
                                        //Construo um novo artefato
                                        //O adiciono à lista de gameObjects
                                        artefactDefinitionSelected = NULL;
                                }
                        }
                }
        }
#ifdef DEBUG_DRAW
        void ArtefactBuilder::draw() const
        {
                if (artefactDefinitionSelected )
                {
                        int ray = artefactDefinitionSelected->ray;
                        int tileSize = machine::MainGameState::TileSize();
                        Vector2i mousePosition = Mouse::getPosition(machine::GameMachine::Window());
                        Vector2i mouseBoardPosition = machine::MainGameState::TransformToTilePosition(Vector2f(mousePosition));
                        Vector2i mouseTilePosition(mousePosition.x-mousePosition.x%tileSize + tileSize/2, mousePosition.y-mousePosition.y%tileSize + tileSize/2);

                        printf("mouseBoardPosition: %d, %d\n", mouseBoardPosition.x, mouseBoardPosition.y);
                        if (!machine::MainGameState::GetBoard().getCell(mouseBoardPosition.y, mouseBoardPosition.x))//Verifica se o tabuleiro está livre
                        {
                                sf::CircleShape c(ray);
                                c.setPosition(mouseTilePosition.x - ray, mouseTilePosition.y - ray);
                                c.setFillColor(sf::Color::White);

                                machine::GameMachine::Draw(c);

                                RectangleShape r(sf::Vector2f(machine::MainGameState::TileSize(), machine::MainGameState::TileSize()));
                                r.setPosition(mouseTilePosition.x - 16, mouseTilePosition.y- 16);
                                r.setFillColor(sf::Color::Yellow);
                                machine::GameMachine::Draw(r);
                        }
                }
        }
#endif
        void ArtefactBuilder::setArtefactDefinition(actor::Artefact::ArtefactDefinition* newOne)
        {
                artefactDefinitionSelected = newOne;
        }
}
