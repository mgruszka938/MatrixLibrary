#pragma once

#include <iostream>
#include "matrix.hpp"

template <typename T>
class SquareMatrix : public Matrix<T>
{
public:
    SquareMatrix(int n, T initialValue = T()) : Matrix<T>(n, n, initialValue) {}

    SquareMatrix(const std::vector<std::vector<T>> &matrix) : Matrix<T>(matrix)
    {
        if (this->getRows() != this->getCols())
        {
            std::cout << "Matrix must be square" << std::endl;
        }
    }

    static SquareMatrix<T> identity(size_t n)
    {
        SquareMatrix<T> result(n, 0);

        for (int i = 0; i < n; i++)
        {
            result(i, i) = 1;
        }
        return result;
    }

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
