#pragma once

#include <iostream>
#include "matrix.hpp"

/**
 * @class SquareMatrix
 * @brief Represents a square matrix, which is a specialized form of the Matrix class.
 *
 * @tparam T The type of the elements in the matrix.
 */
namespace mg
{
    template <typename T>
    class SquareMatrix : public Matrix<T>
    {
    private:
        /**
         * @brief Overridden method to prevent adding a row in a square matrix.
         * @param i The index at which the row will be added.
         * @param row The row to add.
         */
        void addRow(int i, const std::vector<T> &row) override {}

        /**
         * @brief Overridden method to prevent removing a row in a square matrix.
         * @param i The index of the row to remove.
         */
        void removeRow(int i) override {}

        /**
         * @brief Overridden method to prevent adding a column in a square matrix.
         * @param j The index at which the column will be added.
         * @param col The column to add.
         */
        void addCol(int j, const std::vector<T> &col) override {}

        /**
         * @brief Overridden method to prevent removing a column in a square matrix.
         * @param index The index of the column to remove.
         */
        void removeCol(int j) override {}

    public:
        /**
         * @brief Constructs a square matrix of size n x n with an initial value for all elements.
         * @param n The size of the square matrix.
         * @param initialValue Initial value for all elements.
         */
        SquareMatrix(int n, T initialValue = T()) : Matrix<T>(n, n, initialValue) {}

        /**
         * @brief Constructs a square matrix from a 2D vector.
         * @param matrix A 2D vector representing the initial matrix.
         * @throws std::runtime_error If the input matrix is not square.
         */
        SquareMatrix(const std::vector<std::vector<T>> &matrix) : Matrix<T>(matrix)
        {
            if (this->getRows() != this->getCols())
            {
                throw std::runtime_error("Matrix must be square");
            }
        }

        /**
         * @brief Creates an identity matrix of size n x n.
         * @param n The size of the identity matrix.
         * @return A SquareMatrix representing the identity matrix.
         */
        static SquareMatrix<T> identity(size_t n)
        {
            SquareMatrix<T> result(n, 0);

            for (int i = 0; i < n; i++)
            {
                result(i, i) = 1;
            }
            return result;
        }

        /**
         * @brief Computes the determinant of the square matrix.
         * @return The determinant of the matrix.
         */
        T determinant() const
        {
            int n = this->getRows();
            if (n == 1)
            {
                return (*this)(0, 0);
            }
            if (n == 2)
            {
                return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
            }

            T det = 0;
            for (int p = 0; p < n; p++)
            {
                SquareMatrix<T> subMatrix(n - 1);
                for (int i = 1; i < n; i++)
                {
                    int subCol = 0;
                    for (int j = 0; j < n; j++)
                    {
                        if (j == p)
                            continue;
                        subMatrix(i - 1, subCol) = (*this)(i, j);
                        subCol++;
                    }
                }
                T sign = (p % 2 == 0) ? 1 : -1;
                det += sign * (*this)(0, p) * subMatrix.determinant();
            }
            return det;
        }
    };
}
