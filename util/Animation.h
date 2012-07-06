#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

using namespace sf;

namespace util
{

        class Animation
        {
                public:
                        Animation(Texture* texture_, short numFrames = 1, bool looping_ = true, short framePerSecond_ = 12);
                        virtual ~Animation();

                        //--------

                        void update(float seconds);
                        Sprite& getSprite();
                        void setFrameCount(short);
                        void setFramePerSecond(short framePerSecond_);
                        void setPosition(const Vector2f&);
                        void setNumFrames(short numFrames);
                        void setLooping(bool _looping);
                        void setPingpong(bool pingpong_);
                        bool getLooping() const;
                        bool isPaused() const;
                        void pauseResume();
                        bool isanimationFinalized() const;
                        const sf::IntRect& getFrameRect() const;
                protected:
                private:
                        Texture* texture;
                        short numFrames;
                        short framePerSecond;
                        bool looping;
                        float timeFromLastUpdate;
                        short frameCount;
                        short frameWidth;
                        IntRect frameRect;
                        Sprite sprite;
                        bool pingpong; //Indica se a animação seria assim: 1,2,3,2,1,2,3 ao invés de 1,2,3,1,2,3...
                        short incrementValue;
                        bool paused;
        };

}
#endif // ANIMATION_H
