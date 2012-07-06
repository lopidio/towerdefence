#ifndef TEXTURERESOURCEMANAGER_H
#define TEXTURERESOURCEMANAGER_H

#include "ResourceManager.h"
#include <SFML/Graphics.hpp>

namespace manager
{
        class TextureResourceManager: public ResourceManager<sf::Texture>
        {
                public:
                        TextureResourceManager()
                        {

                        }
                        virtual ~TextureResourceManager()
                        {

                        }
                        virtual sf::Texture* createResource(const char* fileName)//Função sobrecarregada pelo filho
                        {
                                sf::Texture* nova = new sf::Texture();
                                if (nova->loadFromFile(fileName)) //Se o carregamento foi bem sucedido
                                {
                                        Resource* rsc = new Resource(fileName);
                                        rsc->data = nova;
                                        resourceMap[fileName] = rsc;
                                }
                                else
                                        nova = NULL; //Se não for, não faz nada
                                return nova;

                        }
                protected:
                private:
        };
}
#endif // TEXTURERESOURCEMANAGER_H
