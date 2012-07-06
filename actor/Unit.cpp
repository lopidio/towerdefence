/** ********************/
//***************
//  - Lopidio
#include "Unit.h"
#include <iostream>
#include <stdio.h>
#include "../machine/MainGameState.h"
#include "../util/Util.h"

namespace actor
{
        Unit::Unit()
                :
                dying(false),
                victory(false),
                life(1000),
                unitAnimation(EUnitOrientationWalkingRight),
                slowMotionFactor(1),
                speed(20.0f),
                armor(0.9f), //Absorve 10% dq chibata
                flies(false),
                path(),
                direction(1,0)//default
        {
                collisionCircle.setRay(20);
                animationVector.reserve(EUnitOrientationCount);
                animationsFileName.reserve(EUnitOrientationCount);
                collidableType = ECollidableTypeTerresterUnit;
        }

        Unit::~Unit()
        {
                //Destrói todas as texturas das animações
                for (char i = 0; i < EUnitOrientationCount; ++i)
                {
                        machine::GameMachine::TextureResourceManager().destroyResource(animationsFileName[i]);
                }
        }

        bool Unit::isFlyer() const
        {
                return flies;
        }

        /** @brief buildPath
          *
          * @todo: document this function
          */
        void Unit::buildPath(control::PathFinder& pathFinder)
        {
                //setPath(pathFinder.getPathFromUnit(*this));
        }
        void Unit::setPath(const control::Path& caminho)
        {
                int tileSize = machine::MainGameState::TileSize();
                for ( Path::const_iterator it = caminho.begin() ;it != caminho.end(); ++it)
                {
                        sf::Vector2f itValue = *it;
                        const sf::Vector2i& boardPosition = sf::Vector2i(itValue.x*tileSize + tileSize/2, itValue.y*tileSize + tileSize/2);
                        path.push_back(sf::Vector2f(boardPosition));
                }
                collisionCircle.setCenter(path.front());
        }
        void Unit::childUpdate(float deltaTime)
        {
                if (dying)
                {
                        //do something usefull
                        //muda a animação
                        //se a animação acabar alive = false;
                        alive = false;

                }
                else
                {
                        machine::MainGameState::GridCollisionManager().addCollidable(this); //Se adiciona ao gerenciador de colisões
                        followPath();
                        move(deltaTime);
                }
        }
        void Unit::init()
        {
                //Chama o init da superclasse
                GameActor::init();

                printf("Unit address:%p\n", this);

                animationsFileName[EUnitOrientationWalkingRight] = "resources/textures/units/RightBomberUnit.png";
                animationsFileName[EUnitOrientationWalkingLeft] = "resources/textures/units/LeftBomberUnit.png";
                animationsFileName[EUnitOrientationWalkingUp] = "resources/textures/units/UpBomberUnit.png";
                animationsFileName[EUnitOrientationWalkingDown] = "resources/textures/units/DownBomberUnit.png";
                animationsFileName[EUnitOrientationDying] = "resources/textures/units/DyingBomberUnit.png";
        }
        void Unit::load()
        {
                //Carrega todas as texturas das animações
                for (char i = 0; i < EUnitOrientationCount; ++i)
                {
                        animationVector.push_back(new util::Animation(machine::GameMachine::TextureResourceManager().loadResource(animationsFileName[i]), 5));
                        animationVector[i]->setFramePerSecond(6);
                        animationVector[i]->setPingpong(true);
                }
        }
        void Unit::followPath()
        {
                if (path.size() == 0)
                {
                        victory = true;
                        alive = false;
                        return;
                }

                sf::Vector2f worldPosition = path.front();//Onde eu deveria estar
                float distance = util::Util::Distance(worldPosition, collisionCircle.getCenter());
                if (distance <= 0) //Tolerância na conversão
                {
                        //removo o primeiro
                        path.erase(path.begin());

                        const sf::Vector2f& targetPosition = path.front();

                        collisionCircle.setCenter(worldPosition);

                        direction = targetPosition - collisionCircle.getCenter();
                        util::Util::Modulize(direction, util::Util::Minimal(1.f, util::Util::Module(direction)));


                        if (targetPosition.x > collisionCircle.getCenter().x)//Direita
                        {
                                currentAnimationIndex = EUnitOrientationWalkingRight;
                        }
                        else if (targetPosition.x < collisionCircle.getCenter().x) //Esq
                        {
                                currentAnimationIndex = EUnitOrientationWalkingLeft;
                        }
                        else if (targetPosition.y > collisionCircle.getCenter().y)//Baixo
                        {
                                currentAnimationIndex = EUnitOrientationWalkingDown;
                        }
                        else if (targetPosition.y < collisionCircle.getCenter().y) //Cima
                        {
                                currentAnimationIndex = EUnitOrientationWalkingUp;
                        }

                }
        }
        void Unit::move(float deltaTime)
        {
                float movementFactor = speed*deltaTime*slowMotionFactor;

                sf::Vector2f position = collisionCircle.getCenter();
                float prevDistance = util::Util::Distance(path.front(), position);
                sf::Vector2f newPosition(direction.x*movementFactor + position.x,
                                            direction.y*movementFactor + position.y);
                float currDistance = util::Util::Distance(path.front(), newPosition);
                //Se a distância está diminuindo
                if (prevDistance > currDistance)
                        collisionCircle.setCenter(newPosition);
                else//Se a distância aumentou, então já passou do ponto
                        collisionCircle.setCenter(path.front());
        }

        /** @brief putDamage
          *
          * @todo: document this function
          */
        void Unit::putDamage(int damage)
        {
                printf("Ouch! Actor damage:%d and life:%d\n", damage, life);
                life -= damage*armor;
                if (life <= 0)
                {
                        dying = true;
                        currentAnimationIndex = EUnitOrientationDying;
                }
        }

}
