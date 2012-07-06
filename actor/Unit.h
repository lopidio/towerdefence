#ifndef UNIT_H
#define UNIT_H

#include "GameActor.h"
#include "../control/PathFinder.h"
#include <SFML/Graphics.hpp>
#include <list>
#include <vector>

//Forward declaration
namespace control
{
        class PathFinder;
}

namespace actor
{
        class Unit: public GameActor
        {
                typedef std::list<sf::Vector2f> Path;
                public:
                        enum EUnitAnimations
                        {
                                EUnitOrientationWalkingUp,
                                EUnitOrientationWalkingDown,
                                EUnitOrientationWalkingLeft,
                                EUnitOrientationWalkingRight,
                                EUnitOrientationDying,
                                EUnitOrientationCount
                        };

                public:
                        Unit();
                        virtual ~Unit();
                        bool isFlyer() const;
                        void buildPath(control::PathFinder& pathFinder);
                        void setPath(const Path& caminho);
                        void putDamage(int damage);
                protected:
                        virtual void childUpdate(float deltaTime);
                        virtual void init();
                        virtual void load();
                private:
                        void followPath();
                        void move(float deltaTime);
                        bool dying; //Começa a animação da morte
                        bool victory; //Chegou ao final
                        int life;
                        EUnitAnimations unitAnimation; //Indica a animação atual do boneco
                        float slowMotionFactor;
                        float speed; //pixelPerSecond
                        float armor;
                        const bool flies;
                        Path path;
                        sf::Vector2f direction;
        };

}

#endif // UNIT_H
