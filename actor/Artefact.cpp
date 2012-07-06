/** ********************/
//***************
//  - Lopidio
#include "Artefact.h"
#include "../machine/MainGameState.h"
#include "../factory/BulletFactory.h"
#include <stdio.h>

namespace actor
{

        Artefact::Artefact(const ArtefactDefinition& def)
                :
                coast(50),
                sellCoast(25),
                upgradeCoast(100),
                reloadTime(0.5), //in seconds
                buildTime(3),//in seconds
                bulletId(0),
                buildTimePassed(0),//in seconds
                reloadTimePassed(0),//in seconds
                building(true),
                reloading(false),
                shooting(false)
        {
                int tileSize = machine::MainGameState::TileSize();
                collisionCircle.setCenter(sf::Vector2f(def.position.x*tileSize + tileSize/2, def.position.y*tileSize + tileSize/2));

                //boto na quina da tile
                collisionCircle.setRay(def.ray);
                animationVector.reserve(EArtefactAnimationCount);
                animationsFileName.reserve(EArtefactAnimationCount);

                collidableType = ECollidableTypeArtefact;
                collidersMask = ECollidableTypeTerresterUnit | ECollidableTypeFlyerUnit;
        }

        Artefact::~Artefact()
        {
                //Carrega todas as texturas das anima��es
                for (char i = 0; i < EArtefactAnimationCount; ++i)
                {
                        machine::GameMachine::TextureResourceManager().destroyResource(animationsFileName[i]);
                }
        }

        void Artefact::load()
        {
                //Carrega todas as texturas das anima��es
                for (char i = 0; i < EArtefactAnimationCount; ++i)
                {
                        animationVector.push_back(new util::Animation(machine::GameMachine::TextureResourceManager().loadResource(animationsFileName[i]), 1));
                        if (i == EArtefactAnimationShooting)
                                animationVector[i]->setLooping(false);
                }
        }
        void Artefact::unload()
        {

        }
        void Artefact::handleCollision(control::Collidable& target)
        {
                if (!building && !reloading) //Se est� pronto para atirar
                {
                        if (!shooting)
                        {
                                Unit* unit = static_cast<Unit*>(&target);
                                bullet::Bullet* newbullet = factory::BulletFactory::Factory(bulletId, unit, collisionCircle.getCenter());
                                newbullet->init();
                                newbullet->load();
                                machine::MainGameState::AddGameActor(newbullet);

                                shooting = true;
                                currentAnimationIndex = EArtefactAnimationShooting;
                        }
                }
        }

        void Artefact::childUpdate(float deltaTime)
        {
                machine::MainGameState::GridCollisionManager().addCollidable(this); //Se adiciona ao gerenciador de colis�es
                currentAnimationIndex = EArtefactAnimationAiming;//Por default � essa
                //Verifica se j� construiu
                if (building)
                {
                        if (buildTimePassed >= buildTime)
                                building = false;
                        else
                        {
                                buildTimePassed += deltaTime;
                                currentAnimationIndex = EArtefactAnimationBuilding;
                                return;
                        }
                }
                if (shooting) //Se acabou de atirar, verifica o fim da anima��o
                {
                        if (animationVector[EArtefactAnimationShooting]->isanimationFinalized())
                        {
                                shooting = false;
                                reloading = true;
                                reloadTimePassed = 0;
                        }
                        else
                        {
                                currentAnimationIndex = EArtefactAnimationShooting;
                                return;
                        }
                }
                if (reloading)                 //verifica se j� carregou
                {
                        if (reloadTimePassed >= reloadTime)
                                reloading = false;
                        else
                        {
                                reloadTimePassed += deltaTime;
                                currentAnimationIndex = EArtefactAnimationReloading;
                                return;
                        }
                }
                toAim();

        }
        void Artefact::toAim()
        {
                //Se n�o � nenhuma outra anima��o, � essa
                currentAnimationIndex = EArtefactAnimationAiming;

                //@todo
                //Calcular o �ngulo da unidade mais pr�xima
                //E fazer algo semelhante a currentAnimationIndex = EEArtefactAnimationAiming + (int)anguloIndex
        }
        void Artefact::init()
        {
                //Chama o init da superclasse
                GameActor::init();

                animationsFileName[EArtefactAnimationAiming] = "resources/textures/artefacts/bomb.png";
                animationsFileName[EArtefactAnimationBuilding] = "resources/textures/artefacts/bomb.png";
                animationsFileName[EArtefactAnimationReloading] = "resources/textures/artefacts/bomb.png";
                animationsFileName[EArtefactAnimationShooting] = "resources/textures/artefacts/bomb.png";
        }

        void Artefact::upgrade()
        {

        }
} //namespace actor
