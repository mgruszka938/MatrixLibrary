#pragma once

#include <iostream>
#include <vector>

template <typename T>
class Matrix
{
private:
	std::vector<std::vector<T>> m_matrix;
	int m_rows;
	int m_cols;

public:
	Matrix() : m_rows(0), m_cols(0) {}

	Matrix(int rows, int cols, T initialValue = T()) : m_rows(rows), m_cols(cols), m_matrix(rows, std::vector<T>(cols, initialValue)) {}

	Matrix(const std::vector<std::vector<T>> &matrix) : m_matrix(matrix)
	{
		m_rows = matrix.size();
		m_cols = matrix.empty() ? 0 : matrix[0].size();
		for (const auto &row : matrix)
		{
			if (row.size() != m_cols)
			{
				throw std::runtime_error("All rows must have the same number of columns");
			}
		}
	}

	int getRows() const
	{
		return m_rows;
	}

	int getCols() const
	{
		return m_cols;
	}

	std::vector<T> getRow(int i) const
	{
		if (i >= m_rows || i < 0)
		{
			throw std::out_of_range("Out of bounds");
			return std::vector<T>();
		}
		return m_matrix[i];
	}

	std::vector<T> getCol(int j) const
	{
		if (j >= m_cols || j < 0)
		{
			throw std::out_of_range("Out of bounds");
			return std::vector<T>();
		}

		std::vector<T> col(m_rows);

		for (int i = 0; i < m_rows; i++)
		{
			col[i] = m_matrix[i][j];
		}

		return col;
	}

	void addRow(int i, const std::vector<T> &row)
	{
		if (row.size() != m_cols)
		{
			throw std::invalid_argument("New row must have the same number of columns");
		}
		if (i < 0 || i > m_rows)
		{
			throw std::out_of_range("Row index out of bounds");
		}
		m_matrix.insert(m_matrix.begin() + i, row);
		++m_rows;
	}

	void removeRow(int i)
	{
		if (i < 0 || i >= m_rows)
		{
			throw std::out_of_range("Row index out of bounds");
		}
		m_matrix.erase(m_matrix.begin() + i);
		--m_rows;
	}

	void addCol(int j, const std::vector<T> &col)
	{
		if (col.size() != m_rows)
		{
			throw std::invalid_argument("New column must have the same number of rows");
		}
		if (j < 0 || j > m_cols)
		{
			throw std::out_of_range("Column index out of bounds");
		}
		for (int i = 0; i < m_rows; i++)
		{
			m_matrix[i].insert(m_matrix[i].begin() + j, col[i]);
		}
		++m_cols;
	}

	void removeCol(int j)
	{
		if (j < 0 || j >= m_cols)
		{
			throw std::out_of_range("Column index out of bounds");
		}
		for (int i = 0; i < m_rows; i++)
		{
			m_matrix[i].erase(m_matrix[i].begin() + j);
		}
		--m_cols;
	}

	T &operator()(int i, int j)
	{
		if (i >= m_rows || j >= m_cols || i < 0 || j < 0)
		{
			throw std::out_of_range("Matrix indices out of bounds");
		}
		return m_matrix[i][j];
	}

	const T &operator()(int i, int j) const
	{
		if (i >= m_rows || j >= m_cols || i < 0 || j < 0)
		{
			throw std::out_of_range("Matrix indices out of bounds");
		}
		return m_matrix[i][j];
	}

	void setValues(T val)
	{
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_cols; j++)
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
			throw std::invalid_argument("Min cannot be greater than Max");
		}

		srand((unsigned)time(NULL));
		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_cols; j++)
			{
				(*this)(i, j) = n + (rand() % m);
			}
		}
	}

	Matrix<T> transpose()
	{
		Matrix<T> result(this->getCols(), this->getRows());

		for (int i = 0; i < this->getRows(); i++)
		{
			for (int j = 0; j < this->getCols(); j++)
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

		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_cols; j++)
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

		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_cols; j++)
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

		for (int i = 0; i < m_rows; ++i)
		{
			for (int j = 0; j < other.m_cols; ++j)
			{
				for (int k = 0; k < m_cols; ++k)
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

		for (int i = 0; i < m_rows; i++)
		{
			for (int j = 0; j < m_rows; j++)
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