/** ********************/
//***************
//  - Lopidio
#include "GameActor.h"
#include "../machine/GameMachine.h"
#include "../machine/MainGameState.h"

namespace actor
{
        GameActor::GameActor()
                :
                currentAnimationIndex(0),
                animationVector(),
                animationsFileName(),
                alive(true)
        {
                //ctor
        }

        GameActor::~GameActor()
        {
                animationsFileName.clear();
                animationVector.clear();
        }

        /** @brief childUpdate
          *
          * @todo: document this function
          */
        void GameActor::childUpdate(float deltaTime)
        {
                //Hook ;) Template Method - Design Pattern
        }

#ifdef GAMEACTOR_DEBUG_DRAW
        sf::CircleShape printCircle(const sf::Vector2f& ci, float ray)
        {
                sf::CircleShape c(ray);
                c.setPosition(ci.x - ray, ci.y - ray);
                c.setFillColor(sf::Color::Red);
                return c;
        }
#endif
        void GameActor::draw() const
        {
#ifdef GAMEACTOR_DEBUG_DRAW
                machine::GameMachine::Draw(printCircle(collisionCircle.getCenter(), collisionCircle.getRay()));
#endif
                //Atualiza a posição do sprite (APENAS PARA A RENDERIZAÇÃO!!!! )
                if (animationVector.size() > 0) //Só imprime caso haja algo para imprimir...
                {
                        sf::Sprite& sprite = animationVector[currentAnimationIndex]->getSprite();
                        const sf::IntRect& frameRect = animationVector[currentAnimationIndex]->getFrameRect();

                        sf::Vector2f prevPosition = sprite.getPosition();
                        sprite.setPosition(sf::Vector2f(collisionCircle.getCenter().x - frameRect.width/2,
                                                        collisionCircle.getCenter().y - frameRect.height/2));

                        machine::GameMachine::Draw(sprite);

                        sprite.setPosition(prevPosition);
                }
        }

        /** @brief update
          *
          * @todo: document this function
          */
        void GameActor::update(float deltaTime)
        {
                childUpdate(deltaTime);//Permito que o filho se altere
                //
                if (animationVector.size() > 0) //Só atualiza caso haja algo para atualizar...
                        animationVector[currentAnimationIndex]->update(deltaTime);
        }

        /** @brief unload
          *
          * @todo: document this function
          */
        void GameActor::unload()
        {
                //Opcionalmente sobrecarregados
        }

        /** @brief load
          *
          * @todo: document this function
          */
        void GameActor::load()
        {
                //Opcionalmente sobrecarregados
        }

        /** @brief init
          *
          * @todo: document this function
          */
        void GameActor::init()
        {

        }

        /** @brief getPosition
          *
          * @todo: document this function
          */
        const sf::Vector2f & GameActor::getPosition() const
        {
                return collisionCircle.getCenter();
        }

        //Retorna < 0 caso eu seja menor, 0 caso seja igual, >0 caso seja maior
        int GameActor::getZIndex(const GameActor& other) const
        {
                return getPosition().y - other.getPosition().y;
        }

        bool GameActor::ZIndexComparator(const GameActor* lhs, const GameActor* rhs)
        {
                return lhs->getZIndex(*rhs) < 0;
        }

        bool GameActor::isAlive() const
        {
                return alive;
        }
}
