#ifndef ARTEFACTBUILDER_H
#define ARTEFACTBUILDER_H

#include "../actor/Artefact.h"

namespace factory
{
        class ArtefactBuilder
        {
                public:
                        ArtefactBuilder();
                        virtual ~ArtefactBuilder();
                        void update();
#ifdef DEBUG_DRAW
                        void draw() const;
#endif
                        void setArtefactDefinition(actor::Artefact::ArtefactDefinition*);
                protected:
                private:
                        actor::Artefact::ArtefactDefinition* artefactDefinitionSelected;
        };

}


#endif // ARTEFACTBUILDER_H
