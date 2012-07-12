#ifndef BOARD_H
#define BOARD_H

namespace control
{

        class Board
        {
                public:
                        Board(int linhas, int colunas);
                        virtual ~Board();
                        bool getCell(int linha, int coluna) const;
                        void setCell(int linha, int coluna, bool newValue);
                        unsigned int getNumLinhas() const;
                        unsigned int getNumColunas() const;
                        unsigned int getNumCells() const;
                        unsigned int getNumBlockedCells() const;
                        unsigned int getNumFreeCells() const;
                protected:
                private:
                        bool **matrix;
                        int numLinhas;
                        int numColunas;
        };

}
#endif // BOARD_H
