/** ********************/
//***************
//  - Lopidio
#include "Collidable.h"

namespace control
{
        Collidable::Collidable()
                :
                collisionCircle(sf::Vector2f(0,0), 0),
                collidersMask(0),
                collidableType(ECollidableTypeNothing)
        {
                //ctor
        }

        Collidable::~Collidable()
        {
                //dtor
        }

        /** @brief checkCollision
          *
          * @todo: document this function
          */
        bool Collidable::checkCollision(Collidable& other) const
        {
                bool maskChecking = collidersMask & other.collidableType;
                bool circleIntersects = collisionCircle.intersectsWithCircle(other.collisionCircle);
                return maskChecking && circleIntersects;
        }

        /** @brief handleCollision
          *
          * @todo: document this function
          */
        void Collidable::handleCollision(Collidable& other)
        {
                //do nothing, para ser sobrescrito
        }

        /** @brief getCollisionCircle
          *
          * @todo: document this function
          */
        const util::Circle& Collidable::getCollisionCircle() const
        {
                return collisionCircle;
        }

        void Collidable::setCollidableType(ECollidableType newType)
        {
                collidableType = newType;
        }
        void Collidable::setCollidableMask(unsigned char newMask)
        {
                collidersMask = newMask;
        }


}
