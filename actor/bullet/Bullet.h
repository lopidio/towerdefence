#ifndef BULLET_H
#define BULLET_H

#include "../GameActor.h"
#include "../Unit.h"
#include <string>

namespace actor
{
        namespace bullet
        {
                class Bullet: public GameActor
                {
                        public:
                                struct BulletDefinition
                                {
                                        unsigned int damage;
                                        unsigned char id;
                                        float speed;
                                        float range;
                                        //animações
                                };
                                virtual ~Bullet();
                                virtual void init();
                                virtual void load();
                                virtual void unload();
                        protected:
                                enum EBulletAnimation
                                {
                                        EBulletAnimationDefault,
                                        EBulletAnimationExploding,
                                        EBulletAnimationCount
                                };

                                //Construtor
                                Bullet(const sf::Vector2f& position, Unit* target, const BulletDefinition& def);
                        protected: //attributes
                                EBulletAnimation eBulletAnimation;
                                actor::Unit* unitTarget;
                                unsigned int damage;
                                float speed;
                                float range;
                                //nome das animações
                };
        }
}
#endif // BULLET_H
