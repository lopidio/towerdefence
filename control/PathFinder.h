#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "../actor/Unit.h"
#include "../util/Util.h"

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
                        PathFinder(const sf::Vector2f& startPoint_, const sf::Vector2f& endPoint_);
                        virtual ~PathFinder();
                        Path buildPathFromUnit(const actor::Unit& unit);
                        bool isPossibleBuildPath(const sf::Vector2f& point) const;
                        const Path& getDefaultPath() const;
                        bool buildDefaultPath();
                        void setBoard(const Board* board_);
                        const Board* getBoard() const;
                        void setEndPoint(const Vector2f& endPoint_);
                        const sf::Vector2f& getEndPoint() const;
                        const Vector2f& getGoal() const;
#ifdef DEBUG_DRAW
                        void draw() const;
#endif
                protected:
                private:
                        template<typename T> static int DummyDistance(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
                        {
                                return util::Util::Absolute(v1.x - v2.x) + util::Util::Absolute(v1.y - v2.y);
                        }
                        void check(const sf::Vector2f& pos, std::list<sf::Vector2f>& visited, std::list<sf::Vector2f>& toVisit) const;
                        Path construirRetorno(PathNode first);
                        Path iterate(bool flies = false);
                        void analisarPosicao(const Vector2f& posicao, int custo, const PathNode* pai, bool flies);
                        static PathNode PegarMenor(const PathNodeList& lista);

                        //Atributos
                        const Board* board;
                        Vector2f endPoint;
                        Vector2f startPoint;
                        Path defaultPath;
                        PathNodeList visitados;
                        PathNodeList paraVisitar;
        };

}

#endif // PATHFINDER_H
