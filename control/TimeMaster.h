#ifndef TIMEMASTER_H
#define TIMEMASTER_H

#include <SFML/System.hpp>

namespace control
{

        class TimeMaster
        {
                public:
                        TimeMaster();
                        virtual ~TimeMaster();

                        static void DistortTime(float factor);
                        static void PauseResume();
                        static bool IsPaused();
                        void restoreOriginalTime();
                        float getEllapsedTimeInSeconds() const;
                        float getEllapsedTimeInMilliseconds() const;
                        float getEllapsedTimeInMicroseconds() const;
                        void restart();
                protected:
                private:
                        sf::Clock clock;
                        static float timeFactor;
                        static bool paused;
        };
}

#endif // TIMEMASTER_H
