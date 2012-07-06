#ifndef GRIDCOLLISIONMANAGER_H
#define GRIDCOLLISIONMANAGER_H

#include <list>
#include <set>
#include "../util/Pair.h"
#include "../control/Collidable.h"


#ifdef DEBUG_DRAW
#define GRIDCOLLISION_DEBUG_DRAW
#endif

namespace manager
{
        class GridCollisionManager
        {
                typedef std::list<control::Collidable*> CollidableContainer; //Prioridade: inserção e remoção. Segunda prioridade: iteração
                typedef util::Pair<control::Collidable*, control::Collidable*> CollidableAssociation;
                typedef std::set<CollidableAssociation, CollidableAssociation::LessComparator> CollidableAssociationContainer; //Utilizando o comparator

                public:
                        GridCollisionManager(const sf::Vector2i& tileGridSize, const sf::Vector2i& boardSize);
                        virtual ~GridCollisionManager();
                        void execute();
                        void addCollidable(control::Collidable* collidable);
                        void clear();
                        unsigned int gridMaxSize() const;
                        #ifdef GRIDCOLLISION_DEBUG_DRAW
                        void draw() const;
                        #endif
                protected:
                        void checkCollision(control::Collidable* firstCollidable, control::Collidable* lastCollidable);
                private:
                        sf::Vector2i tileGridSize;
                        short numLinhas;
                        short numColunas;
                        CollidableContainer** grid;
                        sf::FloatRect** gridRect;
                        CollidableAssociationContainer collidableAssociationContainer; //Lista dos objetos que já colidiram nessa iteração

        };

}
#endif // GRIDCOLLISIONMANAGER_H

