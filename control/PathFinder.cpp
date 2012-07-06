/** ********************/
//***************
//  - Lopidio
#include "PathFinder.h"
#include "../util/Util.h"

using namespace sf;
using namespace actor;

namespace control
{
        PathFinder::PathNode::PathNode(const Vector2f& posicao_, const PathNode* pai_, int custoAteAqui_, float custoEstimadoAoObjetivo_):
                                posicao(posicao_), pai(pai_),
                                custoAteAqui(custoAteAqui_), custoEstimadoAoObjetivo(custoEstimadoAoObjetivo_)
        {
        }

        bool PathFinder::PathNode::equals(const PathFinder::PathNode& x) const
        {
                return posicao == x.posicao;
        }


        PathFinder::PathFinder()
        {
                //ctor
        }


        PathFinder::~PathFinder()
        {
                //dtor
        }

        Path PathFinder::getPathFromUnit(const actor::Unit& unit)
        {
                //Se o board ainda não foi setado
                if (!board)
                        return Path(); //Retorna vazio

                const sf::Vector2f& from = unit.getPosition();
                PathNode first(from, NULL, 0, util::Util::Distance(from, goal));
                if (board->getCell(from.y, from.x))
                        return Path(); //Retorna vazio
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
                        if (first.custoEstimadoAoObjetivo == 0)
                        {
                                return construirRetorno(first);
                        }
                        //@TODO
                        //Ajustar esse valor!
                        int custoDoProximo = first.custoAteAqui + 10;

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
        Path PathFinder::construirRetorno(PathNode& first)
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
                                PathNode toAdd(posicao, pai, custo, util::Util::Distance(posicao, goal));
                                if (!util::Util::ListHas(visitados, toAdd)) //Se não possui
                                        paraVisitar.push_back(toAdd); //Add pra verificar
                        }

                }
        }
        PathFinder::PathNode PathFinder::PegarMenor(const PathNodeList& lista)
        {
                PathNodeList::const_iterator it = lista.begin();
                PathNode menor = *it;
                it++;
                for (; it != lista.end(); it++)
                        //@TODO Ajeitar isso, pelo amor de deus.
                        if (it->custoEstimadoAoObjetivo + it->custoAteAqui < menor.custoEstimadoAoObjetivo + menor.custoAteAqui)
                        {
                                menor = *it;
                        }
                return menor;
        }

        /** @brief setGoal
          *
          * @todo: document this function
          */
        void PathFinder::setGoal(const Vector2f& goal_)
        {
                goal = goal_;
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

        /** @brief getGoal
          *
          * @todo: document this function
          */
        const Vector2f & PathFinder::getGoal() const
        {
                return goal;
        }

} //namespace control

