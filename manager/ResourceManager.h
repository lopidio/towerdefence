#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <cstring>
#include <map>
#include <iostream>

namespace manager
{
        template<typename ResourceType>
        class ResourceManager
        {
                protected:
                        struct Resource
                        {
                                public:
                                        Resource(const char* fileName_):refCount(1) //Se foi criado, j� come�a com 1, n�?
                                        {
                                                fileName = new char[strlen(fileName_)];
                                                strcpy(fileName, fileName_);
                                        }
                                        ResourceType* getData(){return data;}
                                        virtual ~Resource()
                                        {
                                                std::cout << "Deletou a referencia: " << fileName << "\n" ;
                                                delete[] fileName;
                                                delete data;
                                        }
                                public:
                                        int refCount;
                                        char* fileName;
                                        ResourceType* data;
                        };
                protected:
                        ResourceManager()//Construtor
                                :
                                resourceMap()
                        {
                                //do nothing
                        }
                        virtual ResourceType* createResource(const char* fileName) = 0; //Fun��o sobrecarregada pelo filho
                public:
                        typedef std::map<const char*, Resource*>  ResourceMap;
                        //Destrutor
                        virtual ~ResourceManager()
                        {
                                for (typename ResourceMap::iterator it = resourceMap.begin(); it != resourceMap.end(); it++)
                                        delete it->second;
                                resourceMap.clear();
                        }
                        //Principais m�todos
                        ResourceType* loadResource(const char* fileName) //Sobrecarreg�vel
                        {
                                typename ResourceMap::iterator it = resourceMap.find(fileName);
                                if (it != resourceMap.end())//J� foi alocado
                                {
                                        ++(it->second->refCount);
                                        std::cout << "Recurso:" << fileName << " j� alocado \n" ;
                                        return it->second->getData();
                                }
                                else
                                {
                                        std::cout << "Recurso:" << fileName << " preparando para alocar \n" ;
                                        return createResource(fileName);
                                }

                        }
                        void destroyResource(const char* fileName)
                        {
                                typename ResourceMap::iterator it = resourceMap.find(fileName);
                                if (it != resourceMap.end())
                                {
                                        Resource* rsc = it->second; //Pego o recurso

                                        --(rsc->refCount); //Decrementa o contador de refer�ncias
                                        std::cout << "Uma referencia a menos para o recurso: " << fileName << "\n" ;
                                        if (rsc->refCount <= 0)
                                        {
                                                //Retira do mapa
                                                resourceMap.erase(rsc->fileName);
                                                delete rsc;
                                        }
                                }

                        }
                protected:
                //Atributos
                        ResourceMap resourceMap;
        };

}

#endif // RESOURCEMANAGER_H
