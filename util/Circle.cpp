/** ********************/
//***************
//  - Lopidio
#include "Circle.h"
#include "Util.h"

namespace util
{

        /** @brief Circle
          *
          * @todo: document this function
          */
        Circle::Circle(const sf::Vector2f& center_, float ray_):center(center_), ray(ray_)
        {

        }

        Circle::~Circle()
        {
                //dtor
        }

        /** @brief setCenter
          *
          * @todo: document this function
          */
        void Circle::setCenter(const sf::Vector2f& newCenter)
        {
                center = newCenter;
        }

        /** @brief setRay
          *
          * @todo: document this function
          */
        void Circle::setRay(float newRay)
        {
                ray = newRay;
        }

        /** @brief intersectsWithCircle
          *
          * @todo: document this function
          */
        bool Circle::intersectsWithCircle(const Circle& circle) const
        {
                return Util::Distance(center, circle.center) <= ray+circle.ray;
        }

        /** @brief isPointInside
          *
          * @todo: document this function
          */
        bool Circle::isPointInside(const sf::Vector2f& point) const
        {
                sf::Vector2f vectorCentro = center - point;
                return vectorCentro.x*vectorCentro.x + vectorCentro.y*vectorCentro.y <= ray*ray;
        }

        /** @brief getCenter
          *
          * @todo: document this function
          */
        const sf::Vector2f & Circle::getCenter() const
        {
                return center;
        }

        /** @brief getRay
          *
          * @todo: document this function
          */
        float Circle::getRay() const
        {
                return ray;
        }
}
