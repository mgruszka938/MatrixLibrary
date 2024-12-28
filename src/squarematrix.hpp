#pragma once

#include <iostream>
#include "matrix.hpp"

template <typename T>
class SquareMatrix : public Matrix<T>
{
public:
    SquareMatrix(size_t n, T initialValue = T()) : Matrix<T>(n, n, initialValue) {}

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

        for (size_t i = 0; i < n, i++)
        {
            result(i, i) = 1;
        }
        return result;
    }
};
