#ifndef ARTEFACT_H
#define ARTEFACT_H

#include "GameActor.h"
#include "bullet/Bullet.h"

namespace actor
{
        class Artefact: public GameActor
        {
                public:
                        struct ArtefactDefinition
                        {
                                float ray;
                                sf::Vector2i position;
                        };
                private:
                        enum EArtefactAnimation
                        {
                                EArtefactAnimationBuilding,
                                EArtefactAnimationReloading,
                                EArtefactAnimationShooting,
                                EArtefactAnimationAiming,
                                EArtefactAnimationCount
                        };
                public:
                        Artefact(const ArtefactDefinition& def);
                        virtual ~Artefact();
                        virtual void upgrade();
                        virtual void init();
                        virtual void load();
                protected:
                private:
                        virtual void childUpdate(float deltaTime);
                        virtual void handleCollision(control::Collidable&);
                        virtual void unload();
                        void toAim();

                        //Constantes
                        int coast;
                        int sellCoast;
                        int upgradeCoast;
                        float reloadTime;//in seconds
                        float buildTime; //in seconds
                        unsigned char bulletId;

                        //Controles
                        float buildTimePassed;//in seconds
                        float reloadTimePassed;//in seconds
                        bool building;
                        bool reloading;
                        bool shooting;
        };

}//namespace actor
#endif // ARTEFACT_H
