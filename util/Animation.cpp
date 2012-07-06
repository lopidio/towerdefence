/** ********************/
//***************
//  - Lopidio
#include "Animation.h"
#include "Util.h"

namespace util
{



        /** @brief Animation
          *
          * @todo: document this function
          */
         Animation::Animation(Texture* texture_, short numFrames_, bool looping_, short framePerSecond_)
                :
                texture(texture_),
                numFrames(numFrames_),
                framePerSecond(framePerSecond_),
                looping(looping_),
                timeFromLastUpdate(0),
                frameCount(0),
                frameWidth( (int)(texture->getSize().x/numFrames) ),
                frameRect(0,0, frameWidth, texture->getSize().y),
                sprite(*texture),
                pingpong(false),
                incrementValue(1),
                paused(false)
        {
                sprite.setTextureRect(frameRect);
        }

        Animation::~Animation()
        {
                //dtor
        }

        void Animation::setNumFrames(short numFrames_)
        {
                numFrames = numFrames_;
                frameWidth = (int)(texture->getSize().x/numFrames);
                frameRect = sf::IntRect(0,0, frameWidth, texture->getSize().y);
        }
        /** @brief getLooping
          *
          * @todo: document this function
          */
        bool Animation::getLooping() const
        {
                return looping;
        }

        /** @brief setLooping
          *
          * @todo: document this function
          */
        void Animation::setLooping(bool _looping)
        {
                looping = _looping;
        }

        /** @brief setPosition
          *
          * @todo: document this function
          */
        void Animation::setPosition(const Vector2f& position)
        {
                sprite.setPosition(position);
        }

        /** @brief setFrameCount
          *
          * @todo: document this function
          */
        void Animation::setFrameCount(short frameCount_)
        {
                if (frameCount_ >= 0 && frameCount_ < numFrames)
                {
                        frameCount = frameCount_;

                        //mudo a posição do rect
                        frameRect.left = frameWidth*frameCount;
                        sprite.setTextureRect(frameRect);
                }
        }

        /** @brief getSprite
          *
          * @todo: document this function
          */
        Sprite & Animation::getSprite()
        {
                return sprite;
        }

        /** @brief update
          *
          * @todo: document this function
          */
        void Animation::update(float seconds)
        {
                if (paused)
                        return;
                timeFromLastUpdate += seconds;
                //timeFromLastUpdate > 1/ framePerSecond
                short multiplicationValue = timeFromLastUpdate * framePerSecond;
                if (multiplicationValue >= 1)
                {
                        timeFromLastUpdate = multiplicationValue - 1;
                        frameCount += incrementValue;

                        if (frameCount >= numFrames || frameCount < 0)
                        {
                                if (pingpong)
                                {
                                        incrementValue *= -1;
                                        frameCount += incrementValue;
                                        frameCount += incrementValue;
                                }
                                else
                                {
                                        if (looping)
                                                frameCount = 0;
                                }

                        }

                        //mudo a posição do rect
                        frameRect.left = frameWidth*Util::Minimal(frameCount,(short)(numFrames-1));
                        sprite.setTextureRect(frameRect);
                }
        }
        void Animation::setFramePerSecond(short framePerSecond_)
        {
                framePerSecond = framePerSecond_;
        }

        void Animation::setPingpong(bool pingpong_)
        {
                pingpong = pingpong_;
        }

        bool Animation::isanimationFinalized() const
        {
                return !looping && !pingpong && frameCount == numFrames - 1;
        }
        const sf::IntRect& Animation::getFrameRect() const
        {
                return frameRect;
        }
} // namespace util
