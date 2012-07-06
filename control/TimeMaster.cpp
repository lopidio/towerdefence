/** ********************/
//***************
//  - Lopidio
#include "TimeMaster.h"

namespace control
{
        float TimeMaster::timeFactor = 1.f;
        bool TimeMaster::paused = false;

        TimeMaster::TimeMaster()
        {
                //ctor
        }

        TimeMaster::~TimeMaster()
        {
                //dtor
        }


        /** @brief restart
          *
          * @todo: document this function
          */
        void TimeMaster::restart()
        {
                clock.restart();
        }

        /** @brief getEllapsedTimeInMicroseconds
          *
          * @todo: document this function
          */
        float TimeMaster::getEllapsedTimeInMicroseconds() const
        {
                return clock.getElapsedTime().asMicroseconds()*timeFactor*!paused;
        }

        /** @brief getEllapsedTimeInMilliseconds
          *
          * @todo: document this function
          */
        float TimeMaster::getEllapsedTimeInMilliseconds() const
        {
                return clock.getElapsedTime().asMilliseconds()*timeFactor*!paused;
        }

        /** @brief getEllapsedTimeInSeconds
          *
          * @todo: document this function
          */
        float TimeMaster::getEllapsedTimeInSeconds() const
        {
                return clock.getElapsedTime().asSeconds()*timeFactor*!paused;
        }

        /** @brief restoreOriginalTime
          *
          * @todo: document this function
          */
        void TimeMaster::restoreOriginalTime()
        {
                timeFactor = 1;
        }

        /** @brief DistortTime
          *
          * @todo: document this function
          */
        void TimeMaster::DistortTime(float factor)
        {
                if (factor > 0)
                        timeFactor = factor;
        }

        /** @brief IsPaused
          *
          * @todo: document this function
          */
        bool TimeMaster::IsPaused()
        {
                return paused;
        }

        /** @brief Pause
          *
          * @todo: document this function
          */
        void TimeMaster::PauseResume()
        {
                paused = !paused;
        }

} //namespace control
