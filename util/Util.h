#ifndef UTIL_H
#define UTIL_H

#include <SFML/Graphics.hpp>
#include <list>
#include <math.h>
#include "Circle.h"

namespace util
{
        struct Util
        {
                template <typename T> static float Distance(const sf::Vector2<T>& p1, const sf::Vector2<T>& p2)
                {
                        return sqrt(  (float)((p1.x - p2.x)*(p1.x - p2.x) +
                                             (p1.y - p2.y)*(p1.y - p2.y))   );

                }
                template <typename T> static bool ListHas(const std::list<T>& list, const T& node)
                {
                        typename std::list<T>::const_iterator it = list.begin();
                        for (; it != list.end(); it++)
                                if ( node.equals(*it) )
                                        return true;
                        return false;
                }
                template <typename T> static bool Remove(std::list<T>& list, const T& node)
                {
                        typename std::list<T>::iterator it = list.begin();
                        for (; it != list.end(); it++)
                                if ( node.equals(*it) )
                                {
                                        list.erase(it);
                                        return true;
                                }
                        return false;
                }
                template <typename T> static float Module(const sf::Vector2<T> & vec)
                {
                        sf::Vector2<T> zero(0,0);
                        return Distance(vec, zero);
                }
                template <typename T> static void Normalize(sf::Vector2<T> & vec)
                {
                        Modulize(vec, 1.f);
                }
                template <typename T> static void Modulize(sf::Vector2<T> & vec, float newModule)
                {
                        sf::Vector2<T> zero(0,0);
                        float module = Distance(vec, zero);
                        float newFactor = newModule/module;
                        vec.x*= newFactor;
                        vec.y*= newFactor;
                }

                template <typename T> static const T& Minimal(const T& x, const T& y)
                {
                        return x<y?x:y;
                }
                template <typename T> static bool Absolute(const T& x)
                {
                        return x>0?x:-x;
                }
                template <typename T> static sf::Vector2<T> Center(const sf::Rect<T> & rect)
                {
                        sf::Vector2<T> retorno (rect.left, rect.top);
                        retorno.x += rect.width/2;
                        retorno.y += rect.height/2;
                        return retorno;
                }
                static bool IntersectsCircleRect(const Circle& circle, const sf::FloatRect& rect)
                {
                        const sf::Vector2f& circleCenter = circle.getCenter();
                        float circleRay = circle.getRay();
                        sf::Vector2f rectCenter = Center(rect);
                        float centersDistance = Distance(circleCenter, rectCenter);
                        float halfDiagonal = Distance(rectCenter, sf::Vector2f(rect.left, rect.top));

                        //Se a distância dos centros for maior do que o raio
                        if (centersDistance > circleRay + halfDiagonal)
                                return false;

                        //Se o círculo colide com o retângulo pela esquerda do retângulo
                        if (circleCenter.x + circleRay < rectCenter.x - rect.width/2)
                                return false;
                        if (circleCenter.x - circleRay > rectCenter.x + rect.width/2)
                                return false;
                        if (circleCenter.y + circleRay < rectCenter.y - rect.height/2)
                                return false;
                        if (circleCenter.y - circleRay > rectCenter.y + rect.height/2)
                                return false;


                        return true;
                }

        };
}
#endif // UTIL_H
