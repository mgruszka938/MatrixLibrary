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

	const T &operator()(size_t i, size_t j) const
	{
		return m_matrix[i][j];
	}

	friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
	{
		for (const auto &row : matrix.m_matrix)
		{
			for (const auto &elem : row)
			{
				os << elem << " ";
			}
			os << "\n";
		}
	}
};