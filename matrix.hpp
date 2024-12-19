#pragma once

#include <iostream>
#include <vector>

template <typename T>
class Matrix
{
private:
	std::vector<std::vector<T>> m_matrix;
	size_t m_rows;
	size_t m_cols;

public:
	Matrix() : m_rows(0), m_cols(0) {}

	Matrix(size_t rows, size_t cols, T initialValue = T()) : m_rows(rows), m_cols(cols), m_matrix(rows, std::vector<T>(cols, initialValue)) {}

	Matrix(const std::vector<std::vector<T>> &matrix) : m_matrix(matrix)
	{
		m_rows = matrix.size();
		m_cols = matrix.empty() ? 0 : matrix[0].size();
		for (const auto &row : matrix)
		{
			if (row.size() != m_cols)
			{
				throw std::invalid_argument("All rows must have the same number of columns.");
			}
		}
	}

	size_t getRows() const
	{
		return m_rows;
	}

	size_t getCols() const
	{
		return m_cols;
	}

	T &operator()(size_t i, size_t j)
	{
		return m_matrix[i][j];
	}

	const T &operator()(size_t i, size_t j) const
	{
		return m_matrix[i][j];
	}

	Matrix<T> operator+(const Matrix<T> &other) const
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
		{
			throw std::invalid_argument("Matrix dimensions must match");
		}

		Matrix<T> result(m_rows, m_cols); // Result matrix

		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				result(i, j) = (*this)(i, j) + other(i, j); // Addition
			}
		}
		return result;
	}

	Matrix<T> operator-(const Matrix<T> &other) const
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
		{
			throw std::invalid_argument("Matrix dimensions must match");
		}

		Matrix<T> result(m_rows, m_cols); // Result matrix

		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				result(i, j) = (*this)(i, j) - other(i, j); // Substraction
			}
		}
		return result;
	}

	Matrix<T> operator*(const Matrix<T> &other) const
	{
		if (m_cols != other.m_rows)
		{
			throw std::invalid_argument("Matrix dimensions are wrong");
		}

		Matrix<T> result(m_rows, other.m_cols, 0); // Result matrix

		for (size_t i = 0; i < m_rows; ++i)
		{
			for (size_t j = 0; j < other.m_cols; ++j)
			{
				for (size_t k = 0; k < m_cols; ++k)
				{
					result(i, j) += (*this)(i, k) * other(k, j); // Multiplication
				}
			}
		}
		return result;
	}

	friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
	{
		for (const auto &row : matrix.m_matrix)
		{
			for (const auto &elem : row)
			{
				os << elem << " ";
			}
			os << std::endl;
		}
		return os;
	}
};