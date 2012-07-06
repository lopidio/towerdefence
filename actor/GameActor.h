#ifndef GAMEACTOR_H
#define GAMEACTOR_H

#include <SFML/Graphics.hpp>
#include "../util/Animation.h"
#include "../util/Circle.h"
#include "../control/Collidable.h"
#include <iostream>

#ifdef DEBUG_DRAW
#define GAMEACTOR_DEBUG_DRAW
#endif

namespace actor
{
        class GameActor: public control::Collidable
        {
                typedef std::vector<util::Animation*> AnimationVector;
                typedef std::vector<const char*> AnimationsFileName;

                public:
                        GameActor();
                        virtual ~GameActor();
                        virtual void init();
                        void update(float deltaTime);
                        virtual void draw() const;
                        virtual void load();
                        virtual void unload();
                        virtual int getZIndex(const GameActor& other) const;
                        static bool ZIndexComparator(const GameActor* lhs, const GameActor* rhs);
                        bool isAlive() const;
                        const sf::Vector2f & getPosition() const;
                protected:
                        virtual void childUpdate(float deltaTime);
                protected:
                        unsigned char currentAnimationIndex;
                        AnimationVector animationVector;
                        AnimationsFileName animationsFileName;
                        bool alive;
                private:
        };

}
#endif // GAMEACTOR_H
