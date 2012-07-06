#ifndef BULLETFACTORY_H
#define BULLETFACTORY_H

#include <map>
#include "../actor/bullet/Bullet.h"

namespace factory
{
        class BulletFactory
        {
                private: //static attributes
                        typedef std::map<unsigned char, actor::bullet::Bullet::BulletDefinition> BulletDefinitionMap;
                public: //static methods
                        static const actor::bullet::Bullet::BulletDefinition& getBulletDefinnition(unsigned char);
                        static void loadBulletDefinitions(); //L� a partir do XML
                        static void unloadBulletDefinitions(); //Limpa o mapa
                        static actor::bullet::Bullet* Factory(unsigned char bulletId, actor::Unit* target, const sf::Vector2f& position);
                private:
                        static BulletDefinitionMap bulletDefinitionMap;
        };

}
#endif // BULLETFACTORY_H
