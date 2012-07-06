/** ********************/
//***************
//  - Lopidio
#include "InstantBullet.h"
#include "../../machine/MainGameState.h"
#include <stdio.h>

namespace actor
{
        namespace bullet
        {

                InstantBullet::InstantBullet(const sf::Vector2f& position, actor::Unit* unitTarget, const Bullet::BulletDefinition& bulletDef)
                        :
                        Bullet(unitTarget->getPosition(), unitTarget, bulletDef),
                        hitUnit(false)
                {
                        //ctor
                        collisionCircle.setRay(1);//S� tem 1 m�sero alvo
                }

                InstantBullet::~InstantBullet()
                {
                        //dtor
                }

                void InstantBullet::handleCollision(control::Collidable& collidable)
                {
                        //Tipo mais simples de bala
                        if (&collidable == unitTarget && !hitUnit)
                        {
                                currentAnimationIndex = EBulletAnimationExploding;
                                unitTarget->putDamage(damage);//J� fiz o que eu tinha pra fazer
                                hitUnit = true;
                        }
                }
                void InstantBullet::childUpdate(float deltaTime)
                {
                        if (!unitTarget->isAlive())
                                alive = false;
                        if (alive && !hitUnit) //Se o alvo que eu estava perseguindo j� foi assassinado, eu morro
                                machine::MainGameState::GridCollisionManager().addCollidable(this); //Se adiciona ao gerenciador de colis�es
                        else
                        {
                                //Espera a anima��o da explos�o acabar
                                //if (animationVector[EBulletAnimationExploding].isEnd())
                                        alive = false;
                        }
                }
        }
}
