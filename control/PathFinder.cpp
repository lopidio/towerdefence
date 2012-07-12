/** ********************/
//***************
//  - Lopidio
#include "PathFinder.h"
#include "../machine/MainGameState.h"
#include <stdio.h>

using namespace sf;
using namespace actor;

namespace control
{
        PathFinder::PathNode::PathNode(const Vector2f& posicao_, const PathNode* pai_, int custoAteAqui_, float custoEstimadoAoObjetivo_)
                                :
                                posicao(posicao_),
                                 pai(pai_),
                                custoAteAqui(custoAteAqui_),
                                 custoEstimadoAoObjetivo(custoEstimadoAoObjetivo_)
        {
        }

        bool PathFinder::PathNode::equals(const PathFinder::PathNode& x) const
        {
                return posicao == x.posicao;
        }


        PathFinder::PathFinder(const sf::Vector2f& startPoint_, const sf::Vector2f& endPoint_)
                :
                board(NULL),
                endPoint(endPoint_),
                startPoint(startPoint_),
                defaultPath(),
                visitados(),
                paraVisitar()
        {
                //ctor
        }


        PathFinder::~PathFinder()
        {
                //dtor
        }

        void PathFinder::check(const sf::Vector2f& pos, std::list<sf::Vector2f>& visited, std::list<sf::Vector2f>& toVisit) const
        {
                if (!board->getCell(pos.x, pos.y) && !util::Util::Find(toVisit, pos) && !util::Util::Find(visited, pos))
                {
                        toVisit.push_back(pos);
                }
        }
        bool PathFinder::isPossibleBuildPath(const sf::Vector2f& point) const
        {
                //Se o board ainda não foi setado
                if (!board)
                        return false;

                if (board->getCell(point.y, point.x))
                        return false;

                std::list<Vector2f> toVisit, visited;
                toVisit.push_back(startPoint);
                while (toVisit.size() > 0)
                {
                        const Vector2f& firstPosition = toVisit.front();
                        visited.push_back(firstPosition);
                        toVisit.remove(firstPosition);


                        //Repete o processo para todos os lados
                        check(sf::Vector2f(firstPosition.x + 1, firstPosition.y), visited, toVisit); //dir
                        check(sf::Vector2f(firstPosition.x, firstPosition.y + 1), visited, toVisit); //baixo
                        check(sf::Vector2f(firstPosition.x - 1, firstPosition.y), visited, toVisit); //esq
                        check(sf::Vector2f(firstPosition.x, firstPosition.y - 1), visited, toVisit); //cim
                }
                bool endPointWasFound = board->getCell(endPoint.y, endPoint.x);
                return visited.size() == board->getNumFreeCells() && endPointWasFound;//Tenho que ter varrido todas as casas livre E não posso tampar a saída, né?
        }

        bool PathFinder::buildDefaultPath()
        {
                defaultPath.clear(); //Limpa o caminho default
                paraVisitar.clear();
                visitados.clear();

                PathNode first(startPoint, NULL, 0, DummyDistance(startPoint, endPoint)); //posição, pai, custo, distância estimada
                paraVisitar.push_back(first);
                defaultPath = iterate();

                return false;
        }
        Path PathFinder::buildPathFromUnit(const actor::Unit& unit)
        {
                //Se o board ainda não foi setado
                if (!board)
                        return Path(); //Retorna vazio


                const sf::Vector2f& from = unit.getPosition();
                if (board->getCell(from.y, from.x))
                        return Path(); //Retorna vazio

                PathNode first(from, NULL, 0, DummyDistance(from, endPoint)); //posição, pai, custo, distância estimada
                paraVisitar.push_back(first);
                Path retorno = iterate(unit.isFlyer());

                paraVisitar.clear();
                visitados.clear();

                return retorno;
        }

        Path PathFinder::iterate(bool flies)
        {
                if (paraVisitar.size() > 0)
                {
                        PathNode first = PegarMenor(paraVisitar);
                        util::Util::Remove(paraVisitar, first);
                        visitados.push_back(first);

                        //verifica sucesso
                        if (first.posicao == endPoint)
                        {
                                return construirRetorno(first);
                        }
                        //@TODO
                        //Ajustar esse valor!
                        int custoDoProximo = first.custoAteAqui + 1;

                        analisarPosicao(Vector2f(first.posicao.x - 1, first.posicao.y), custoDoProximo, &first, flies); //Esq
                        analisarPosicao(Vector2f(first.posicao.x + 1, first.posicao.y), custoDoProximo, &first, flies); //Dir
                        analisarPosicao(Vector2f(first.posicao.x, first.posicao.y - 1), custoDoProximo, &first, flies); //Cima
                        analisarPosicao(Vector2f(first.posicao.x, first.posicao.y + 1), custoDoProximo, &first, flies);// Baixo

                        return iterate(flies);
                }

                return Path();
        }

        /** @brief verificaFimDoAlgoritmo
          *
          * @todo: document this function
          */
        Path PathFinder::construirRetorno(PathNode first)
        {
                //monta retorno e retorna
                Path retorno;
                retorno.push_front(first.posicao);
                do
                {
                        first = *first.pai;
                        retorno.push_front(first.posicao);
                }
                while (first.pai);
                return retorno;
        }



        void PathFinder::analisarPosicao(const Vector2f& posicao, int custo, const PathNode* pai, bool flies)
        {
                if (posicao.x >= 0 && posicao.x < board->getNumColunas() && posicao.y >= 0 && posicao.y < board->getNumLinhas()) //Verifico os limites do tabuleiro
                {
                        if (flies || !board->getCell(posicao.y,posicao.x))//verifico se não é um obstáculo (ou se a unidade voa)
                        {
                                PathNode toAdd(posicao, pai, custo, DummyDistance(posicao, endPoint));
                                if (!util::Util::ListHas(visitados, toAdd) && //Se ainda não foi visitado
                                    !util::Util::ListHas(paraVisitar, toAdd)) //Se ainda não está na lista de para verificar
                                        paraVisitar.push_back(toAdd); //Add pra verificar
                        }

                }
        }
        PathFinder::PathNode PathFinder::PegarMenor(const PathNodeList& lista)
        {
                PathNodeList::const_iterator it = lista.begin();
                PathNode menor = lista.front();
                it++;
                for (; it != lista.end(); it++)
                        //@TODO Ajeitar isso, pelo amor de deus.
                        if (it->custoEstimadoAoObjetivo + it->custoAteAqui < menor.custoEstimadoAoObjetivo + menor.custoAteAqui)
                        {
                                menor = *it;
                        }
                return menor;
        }

        /** @brief setEndPoint
          *
          * @todo: document this function
          */
        void PathFinder::setEndPoint(const Vector2f& endPoint_)
        {
                endPoint = endPoint_;
        }

        /** @brief getBoard
          *
          * @todo: document this function
          */
        const Board* PathFinder::getBoard() const
        {
                return board;
        }

        /** @brief setBoard
          *
          * @todo: document this function
          */
        void PathFinder::setBoard(const Board* board_)
        {
                board = board_;
        }

        /** @brief getEndPoint
          *
          * @todo: document this function
          */
        const sf::Vector2f & PathFinder::getEndPoint() const
        {
                return endPoint;
        }

        const Path& PathFinder::getDefaultPath() const
        {
                return defaultPath;
        }


#ifdef DEBUG_DRAW
        void PathFinder::draw() const
        {
               // printf("Tamanho do caminho: %d\n", defaultPath.size());
                for (Path::const_iterator it = defaultPath.begin(); it != defaultPath.end(); ++it)
                {

                        float ray = 18;
                        sf::CircleShape c(ray);
                        c.setPosition(it->x*32 - ray, it->y*32 - ray);
                        c.setFillColor(sf::Color::Green);
                        machine::GameMachine::Draw(c);

                }
        }
#endif
} //namespace control

