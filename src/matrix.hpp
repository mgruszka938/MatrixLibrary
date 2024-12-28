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
				std::cout << "All rows must have the same number of columns." << std::endl;
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

	void setValues(T val)
	{
		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				(*this)(i, j) = val;
			}
		}
	}

	void setOnes()
	{
		this->setValues(1);
	}

	void setZeroes()
	{
		this->setValues(0);
	}

	void setRandomValues(T n, T m)
	{
		if (n > m)
		{
			std::cout << "Min cannot be greater than Max";
		}

		srand((unsigned)time(NULL));
		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_cols; j++)
			{
				(*this)(i, j) = n + (rand() % m);
			}
		}
	}

	Matrix<T> transpose()
	{
		Matrix<T> result(this->getCols(), this->getRows());

		for (size_t i = 0; i < this->getRows(); i++)
		{
			for (size_t j = 0; j < this->getCols(); j++)
			{
				result(j, i) = (*this)(i, j);
			}
		}
		return result;
	}

	Matrix<T> operator+(const Matrix<T> &other) const
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
		{
			std::cout << "Matrix dimensions must match" << std::endl;
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

	Matrix<T> &operator+=(const Matrix<T> &other)
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
		{
			std::cout << "Matrix dimensions must match" << std::endl;
		}

		*this = (*this) + other;

		return *this;
	}

	Matrix<T> operator-(const Matrix<T> &other) const
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
		{
			std::cout << "Matrix dimensions must match" << std::endl;
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

	Matrix<T> &operator-=(const Matrix<T> &other)
	{
		if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
		{
			std::cout << "Matrix dimensions must match" << std::endl;
		}

		*this = (*this) - other;

		return *this;
	}

	Matrix<T> operator*(const Matrix<T> &other) const
	{
		if (m_cols != other.m_rows)
		{
			std::cout << "Matrix dimensions are wrong" << std::endl;
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

	Matrix<T> &operator*=(const Matrix<T> &other)
	{
		if (m_cols != other.m_rows)
		{
			std::cout << "Matrix dimensions are wrong" << std::endl;
		}

		*this = (*this) * other;

		return *this;
	}

	Matrix<T> operator*(const T &scalar) const
	{
		Matrix<T> result(m_rows, m_cols);

		for (size_t i = 0; i < m_rows; i++)
		{
			for (size_t j = 0; j < m_rows; j++)
			{
				result(i, j) = (*this)(i, j) * scalar;
			}
		}
		return result;
	}

	Matrix<T> &operator*=(const T &scalar)
	{
		*this = (*this) * scalar;
		return *this;
	}

	bool operator==(const Matrix<T> &other) const
	{
		return m_matrix == other.m_matrix;
	}

	bool operator!=(const Matrix<T> &other) const
	{
		return !(*this == other);
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