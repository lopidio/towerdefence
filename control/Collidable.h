#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "../util/Circle.h"

namespace control
{

        class Collidable
        {
                public:
                        enum ECollidableType
                        {
                                ECollidableTypeNothing            = 0,
                                ECollidableTypeTerresterUnit      = 1 << 0,
                                ECollidableTypeFlyerUnit          = 1 << 1,
                                ECollidableTypeAirBullet          = 1 << 2,
                                ECollidableTypeTerresterBullet    = 1 << 3,
                                ECollidableTypeArtefact           = 1 << 4,
                        };
                public:
                        Collidable();
                        virtual ~Collidable();
                        const util::Circle& getCollisionCircle() const; //Checa colisões, e insere no grid correto
                        virtual void handleCollision(Collidable&);
                        bool checkCollision(Collidable&) const;
                        void setCollidableType(ECollidableType newType);
                        void setCollidableMask(unsigned char newMask);
                protected:
                        util::Circle collisionCircle;
                        unsigned char collidersMask; //Colido com o que?
                        unsigned char collidableType; //Meu tipo
                private:
        };

}
#endif // COLLIDABLE_H
