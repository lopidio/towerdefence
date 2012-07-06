#ifndef ARTEFACTFACTORY_H
#define ARTEFACTFACTORY_H

#include "../actor/Artefact.h"
#include <map>

namespace factory
{
        class ArtefactFactory
        {
                private: //static attributes
                        typedef std::map<unsigned char, actor::Artefact::ArtefactDefinition> ArtefactDefinitionMap;
                public: //static methods
                        static const actor::Artefact::ArtefactDefinition& GetArtefactDefinnition(unsigned char);
                        static void LoadArtefactDefinitions(); //Lê a partir do XML
                        static void UnloadArtefactDefinitions(); //Limpa o mapa
                        static actor::Artefact* Factory(const actor::Artefact::ArtefactDefinition&);
                private:
                        static ArtefactDefinitionMap artefactDefinitionMap;


                public:
                        ArtefactFactory();
                        virtual ~ArtefactFactory();
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
#endif // ARTEFACTFACTORY_H
