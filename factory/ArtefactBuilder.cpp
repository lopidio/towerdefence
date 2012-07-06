/** ********************/
//***************
//  - Lopidio
#include "ArtefactBuilder.h"
#include <SFML/Graphics.hpp>
#include "../control/Board.h"
#include "../machine/MainGameState.h"

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
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                        if (artefactDefinitionSelected)
                        {
                                Vector2i mouseTilePosition = machine::MainGameState::TransformToTilePosition(sf::Vector2f(Mouse::getPosition()));
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
        void ArtefactBuilder::draw()
        {
                if (artefactDefinitionSelected)
                {
                        sf::CircleShape c(artefactDefinitionSelected->ray);
                        Vector2i mouseTilePosition = machine::MainGameState::TransformToTilePosition(sf::Vector2f(Mouse::getPosition()));
                        c.setPosition(mouseTilePosition.x - artefactDefinitionSelected->ray, mouseTilePosition.y - artefactDefinitionSelected->ray);
                        c.setFillColor(sf::Color::White);

                        machine::GameMachine::Draw(c);

                        RectangleShape r(sf::Vector2f(machine::MainGameState::TileSize(), machine::MainGameState::TileSize()));
                        r.setPosition(mouseTilePosition.x, mouseTilePosition.y);
                        r.setFillColor(sf::Color::Yellow);
                        machine::GameMachine::Draw(r);
                }
        }
#endif

}
