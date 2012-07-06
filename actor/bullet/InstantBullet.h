#ifndef INSTANTBULLET_H
#define INSTANTBULLET_H

#include "Bullet.h"

namespace actor
{
        namespace bullet
        {

                class InstantBullet: public Bullet
                {
                        public:
                                InstantBullet(const sf::Vector2f& position, actor::Unit* unitTarget, const Bullet::BulletDefinition& bulletDef);
                                virtual ~InstantBullet();
                        protected:
                                virtual void handleCollision(control::Collidable& collidable);
                                void childUpdate(float deltaTime);
                        private:
                                bool hitUnit;
                };

        }
}
#endif // INSTANTBULLET_H
