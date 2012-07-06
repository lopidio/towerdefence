#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "../actor/Unit.h"
#include <list>
#include <math.h>

//Forward declaration
namespace actor
{
        class Unit;
}

namespace control
{
        typedef std::list<Vector2f> Path;
        class PathFinder
        {
                struct PathNode
                {
                        Vector2f posicao;
                        const PathNode * pai;
                        int custoAteAqui;
                        float custoEstimadoAoObjetivo;
                        PathNode(const Vector2f& posicao_, const PathNode* pai_, int custoAteAqui_, float custoEstimadoAoObjetivo_);
                        bool equals(const PathNode& x) const;
                };
                typedef std::list<PathNode> PathNodeList;

                public:
                        PathFinder();
                        virtual ~PathFinder();
                        Path getPathFromUnit(const actor::Unit& unit);
                        void setBoard(const Board* board_);
                        const Board* getBoard() const;
                        void setGoal(const Vector2f& goal_);
                        const Vector2f& getGoal() const;
                protected:
                private:
                        Path construirRetorno(PathNode& first);
                        Path iterate(bool flies);
                        void analisarPosicao(const Vector2f& posicao, int custo, const PathNode* pai, bool flies);
                        static PathNode PegarMenor(const PathNodeList& lista);

                        //Atributos
                        const Board* board;
                        Vector2f goal;
                        PathNodeList visitados;
                        PathNodeList paraVisitar;
        };

}

#endif // PATHFINDER_H
