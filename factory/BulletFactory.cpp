/** ********************/
//***************
//  - Lopidio
#include "BulletFactory.h"
#include "../actor/bullet/InstantBullet.h"

namespace factory
{
        actor::bullet::Bullet* BulletFactory::Factory(unsigned char bulletId, actor::Unit* target, const sf::Vector2f& position)
        {
                actor::bullet::Bullet::BulletDefinition bulletDef;
                bulletDef.damage = 5;
                bulletDef.range = 10;
                bulletDef.speed = 10;
                return new actor::bullet::InstantBullet(position, target, bulletDef);
        }

}
