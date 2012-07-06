#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>

namespace util
{
        class Circle
        {
                public:
                        Circle(const sf::Vector2f& center, float ray);
                        virtual ~Circle();

                        bool isPointInside(const sf::Vector2f&) const;
                        bool intersectsWithCircle(const Circle& circle) const;
                        void setRay(float newRay);
                        void setCenter(const sf::Vector2f& newCenter);
                        float getRay() const;
                        const sf::Vector2f& getCenter() const;
                protected:
                private:
                        sf::Vector2f center;
                        float ray;
        };
}

#endif // CIRCLE_H
