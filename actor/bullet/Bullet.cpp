/** ********************/
//***************
//  - Lopidio
#include "Bullet.h"

namespace actor
{
        namespace bullet
        {
                Bullet::Bullet(const sf::Vector2f &position, Unit* target, const BulletDefinition& def)
                        :
                        eBulletAnimation(EBulletAnimationDefault),
                        unitTarget(target),
                        damage(def.damage),
                        speed(def.speed),
                        range(def.range)
                {
                        collisionCircle.setCenter(position);
                        collisionCircle.setRay(3);

                        collidableType = ECollidableTypeTerresterBullet | ECollidableTypeAirBullet; //Valores default
                        collidersMask = ECollidableTypeTerresterUnit | ECollidableTypeFlyerUnit; //Valores default
                }

                Bullet::~Bullet()
                {

                }

                void Bullet::init()
                {

                }
                void Bullet::load()
                {

                }
                void Bullet::unload()
                {

                }

        }

}
