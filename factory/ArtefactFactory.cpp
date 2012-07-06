/** ********************/
//***************
//  - Lopidio
#include "ArtefactFactory.h"
#include <SFML/Graphics.hpp>
#include "../control/Board.h"
#include "../machine/MainGameState.h"
#include <stdio.h>

using namespace sf;
using namespace actor;

namespace factory
{

        ArtefactFactory::ArtefactFactory():artefactDefinitionSelected(NULL)
        {
                //ctor
        }

        ArtefactFactory::~ArtefactFactory()
        {
                //dtor
        }

        void ArtefactFactory::update()
        {
                //Lembrar de verificar o dinheiro tb, claro.
                if (artefactDefinitionSelected)
                {
                        if (Mouse::isButtonPressed(Mouse::Left))
                        {
                        Vector2i mousePosition = Mouse::getPosition(machine::GameMachine::Window());
                        Vector2i mouseBoardPosition = machine::MainGameState::TransformToTilePosition(Vector2f(mousePosition));
                                if (!machine::MainGameState::GetBoard().getCell(mouseBoardPosition.y, mouseBoardPosition.x))//Verifica se o tabuleiro está livre
                                {
                                        int tileSize = machine::MainGameState::TileSize();
                                        Vector2i ArtefactFactoryPosition(mousePosition.x-mousePosition.x%tileSize + tileSize/2, mousePosition.y-mousePosition.y%tileSize + tileSize/2);
                                        artefactDefinitionSelected->position = mouseBoardPosition;
                                        //Artefact* newArtefact = ArtefactFactory::factory(artefactDefinitionSelected);
                                        //newArtefact->init();
                                        //newArtefact->load();
                                        //machine::MainGameState::addGameActor(newArtefact);

                                        //Construo um novo artefato
                                        //O adiciono à lista de gameObjects
                                        artefactDefinitionSelected = NULL;
                                }
                        }
                }
        }
#ifdef DEBUG_DRAW
        void ArtefactFactory::draw() const
        {
                if (artefactDefinitionSelected )
                {
                        int ray = artefactDefinitionSelected->ray;
                        int tileSize = machine::MainGameState::TileSize();
                        Vector2i mousePosition = Mouse::getPosition(machine::GameMachine::Window());
                        Vector2i mouseBoardPosition = machine::MainGameState::TransformToTilePosition(Vector2f(mousePosition));

                        if (!machine::MainGameState::GetBoard().getCell(mouseBoardPosition.y, mouseBoardPosition.x))//Verifica se o tabuleiro está livre
                        {
                                Vector2i ArtefactFactoryPosition(mousePosition.x-mousePosition.x%tileSize + tileSize/2, mousePosition.y-mousePosition.y%tileSize + tileSize/2);

                                sf::CircleShape c(ray);
                                c.setPosition(ArtefactFactoryPosition.x - ray, ArtefactFactoryPosition.y - ray);
                                c.setFillColor(sf::Color::White);

                                machine::GameMachine::Draw(c);

                                RectangleShape r(sf::Vector2f(machine::MainGameState::TileSize(), machine::MainGameState::TileSize()));
                                r.setPosition(ArtefactFactoryPosition.x - 16, ArtefactFactoryPosition.y- 16);
                                r.setFillColor(sf::Color::Yellow);
                                machine::GameMachine::Draw(r);
                        }
                }
        }
#endif
        void ArtefactFactory::setArtefactDefinition(actor::Artefact::ArtefactDefinition* newOne)
        {
                artefactDefinitionSelected = newOne;
        }

        actor::Artefact* ArtefactFactory::Factory(const actor::Artefact::ArtefactDefinition& def)
        {
                return new Artefact(def);
        }
}
