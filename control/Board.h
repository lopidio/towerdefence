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
                        int getNumLinhas() const;
                        int getNumColunas() const;
                protected:
                private:
                        bool **matrix;
                        int numLinhas;
                        int numColunas;
        };

}
#endif // BOARD_H
