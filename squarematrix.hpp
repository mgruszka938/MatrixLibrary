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
            throw std::invalid_argument("Matrix must be square.");
        }
    }
};
