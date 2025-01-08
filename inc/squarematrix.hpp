#pragma once

#include <iostream>
#include "matrix.hpp"

template <typename T>
class SquareMatrix : public Matrix<T>
{
private:
    void addRow(int, const std::vector<T> &) override {}
    void removeRow(int) override {}
    void addCol(int, const std::vector<T> &) override {}
    void removeCol(int) override {}

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

    SquareMatrix<T> inverse() const
    {
        T det = this->determinant();

        if (det == 0)
        {
            throw std::runtime_error("Matrix cannot be inverted");
        }

        int n = this->getRows();
        SquareMatrix<T> subMatrix0(n);
        SquareMatrix<T> subMatrix1(n - 1);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int subRow = 0;
                for (int row = 0; row < n; row++)
                {
                    if (row == i)
                        continue;
                    int subCol = 0;
                    for (int col = 0; col < n; col++)
                    {
                        if (col == j)
                            continue;
                        subMatrix1(subRow, subCol) = (*this)(row, col);
                        subCol++;
                    }
                    subRow++;
                }
                T sign = ((i + j) % 2 == 0) ? 1 : -1;
                subMatrix0(j, i) = sign * subMatrix.determinant();
            }
        }
        return subMatrix0 * (1 / det);
    }
};
