/** ********************/
//***************
//  - Lopidio
#include "Board.h"
#include <stdio.h>

namespace control
{

        /** @brief Board
          *
          * @todo: document this function
          */
        Board::Board(int linhas, int colunas): numLinhas(linhas), numColunas(colunas)
        {
                matrix = new bool*[numLinhas];
                for (int i = 0; i < numLinhas; ++i)
                        matrix[i] = new bool[numColunas];

                for (int i = 0; i < numLinhas; ++i)
                        for (int j = 0; j < numColunas; ++j)
                                matrix[i][j] = false; //Zero toda a matriz
        }

        Board::~Board()
        {
                //Deleto os ponteiros
                for (int i = 0; i < numLinhas; ++i)
                        delete[] matrix[i];

                delete[] matrix;
                //Aponto para nulo
                matrix = 0;
        }

        bool Board::getCell(int linha, int coluna) const
        {
                if (coluna >= 0 && coluna < numColunas)
                        if (linha >= 0 && linha < numLinhas)
                                return matrix[linha][coluna];
                return true;
        }

        /** @brief setCell
          *
          * @todo: document this function
          */
        void Board::setCell(int linha, int coluna, bool newValue)
        {
                if (coluna >= 0 && coluna < numColunas)
                        if (linha >= 0 && linha < numLinhas)
                                matrix[linha][coluna] = newValue;
        }

        /** @brief getNumColunas
          *
          * @todo: document this function
          */
        unsigned int Board::getNumColunas() const
        {
                return numColunas;
        }

        /** @brief getNumLinhas
          *
          * @todo: document this function
          */
        unsigned int Board::getNumLinhas() const
        {
                return numLinhas;
        }
        unsigned int Board::getNumCells() const
        {
                return numColunas*numLinhas;
        }
        unsigned int Board::getNumBlockedCells() const
        {
                int resultado = 0;
                for (int i = 0; i < numLinhas; ++i)
                        for (int j = 0; j < numColunas; ++j)
                                resultado += matrix[i][j];
                return resultado;
        }
        unsigned int Board::getNumFreeCells() const
        {
                int resultado = getNumCells();
                for (int i = 0; i < numLinhas; ++i)
                        for (int j = 0; j < numColunas; ++j)
                                resultado -= matrix[i][j];
                return resultado;
        }


}
