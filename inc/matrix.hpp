#pragma once

#include <iostream>
#include <vector>

/**
 * @brief A templated Matrix class for managing 2D matrices.
 *
 * @tparam T The data type of the matrix elements.
 */

namespace mg
{
	template <typename T>
	class Matrix
	{
	protected:
		/**
		 * @brief 2D vector storage for the matrix.
		 */
		std::vector<std::vector<T>> m_matrix;

		/**
		 * @brief Number of rows in the matrix.
		 */
		int m_rows;

		/**
		 * @brief Number of columns in the matrix.
		 */
		int m_cols;

	public:
		/**
		 * @brief Default constructor initializing an empty matrix.
		 */
		Matrix() : m_rows(0), m_cols(0) {}

		/**
		 * @brief Constructs a matrix with given dimensions and an initial value for all elements.
		 *
		 * @param rows Number of rows in the matrix.
		 * @param cols Number of columns in the matrix.
		 * @param initialValue Initial value for all elements.
		 */
		Matrix(int rows, int cols, T initialValue = T()) : m_rows(rows), m_cols(cols), m_matrix(rows, std::vector<T>(cols, initialValue)) {}

		/**
		 * @brief Constructs a matrix from a given 2D vector.
		 *
		 * @param matrix A 2D vector representing the initial matrix.
		 * @throws std::runtime_error If the rows don't have the same number of columns.
		 */
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

		/**
		 * @brief Gets the number of rows in the matrix.
		 *
		 * @return Number of rows.
		 */
		int getRows() const
		{
			return m_rows;
		}

		/**
		 * @brief Gets the number of columns in the matrix.
		 *
		 * @return Number of columns.
		 */
		int getCols() const
		{
			return m_cols;
		}

		/**
		 * @brief Retrieves a specific row from the matrix.
		 *
		 * @param i The index of the row to retrieve.
		 * @return A vector representing the row.
		 * @throws std::out_of_range If the row index is out of bounds.
		 */
		std::vector<T> getRow(int i) const
		{
			if (i >= m_rows || i < 0)
			{
				throw std::out_of_range("Out of bounds");
				return std::vector<T>();
			}
			return m_matrix[i];
		}

		/**
		 * @brief Retrieves a specific column from the matrix.
		 *
		 * @param j The index of the column to retrieve.
		 * @return A vector representing the column.
		 * @throws std::out_of_range If the column index is out of bounds.
		 */
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

		/**
		 * @brief Adds a row to the matrix at a specified position.
		 *
		 * @param i The index at which the row will be added.
		 * @param row The row to add.
		 * @throws std::invalid_argument If the size of the row does not match the number of columns.
		 * @throws std::out_of_range If the row index is out of bounds.
		 */
		virtual void addRow(int i, const std::vector<T> &row)
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

		/**
		 * @brief Removes a row from the matrix at a specified position.
		 *
		 * @param i The index of the row to remove.
		 * @throws std::out_of_range If the row index is out of bounds.
		 */
		virtual void removeRow(int i)
		{
			if (i < 0 || i >= m_rows)
			{
				throw std::out_of_range("Row index out of bounds");
			}
			m_matrix.erase(m_matrix.begin() + i);
			--m_rows;
		}

		/**
		 * @brief Adds a column to the matrix at a specified position.
		 *
		 * @param j The index at which the column will be added.
		 * @param col The column to add.
		 * @throws std::invalid_argument If the size of the column does not match the number of rows.
		 * @throws std::out_of_range If the column index is out of bounds.
		 */
		virtual void addCol(int j, const std::vector<T> &col)
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

		/**
		 * @brief Removes a column from the matrix at a specified position.
		 *
		 * @param j The index of the column to remove.
		 * @throws std::out_of_range If the column index is out of bounds.
		 */
		virtual void removeCol(int j)
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

		/**
		 * @brief Accesses an element of the matrix.
		 *
		 * @param i The row index.
		 * @param j The column index.
		 * @return Reference to the element at the specified position.
		 * @throws std::out_of_range If the indices are out of bounds.
		 */
		T &operator()(int i, int j)
		{
			if (i >= m_rows || j >= m_cols || i < 0 || j < 0)
			{
				throw std::out_of_range("Matrix indices out of bounds");
			}
			return m_matrix[i][j];
		}

		/**
		 * @brief Accesses an element of the matrix (const version).
		 *
		 * @param i The row index.
		 * @param j The column index.
		 * @return Const reference to the element at the specified position.
		 * @throws std::out_of_range If the indices are out of bounds.
		 */
		const T &operator()(int i, int j) const
		{
			if (i >= m_rows || j >= m_cols || i < 0 || j < 0)
			{
				throw std::out_of_range("Matrix indices out of bounds");
			}
			return m_matrix[i][j];
		}

		/**
		 * @brief Sets all elements of the matrix to a specified value.
		 *
		 * @param val The value to set.
		 */
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

		/**
		 * @brief Sets all elements of the matrix to 1.
		 */
		void setOnes()
		{
			this->setValues(1);
		}

		/**
		 * @brief Sets all elements of the matrix to 0.
		 */
		void setZeroes()
		{
			this->setValues(0);
		}

		/**
		 * @brief Sets all elements of the matrix to random values within a specified range.
		 *
		 * @param n The minimum value of the range.
		 * @param m The maximum value of the range.
		 * @throws std::invalid_argument If the minimum value is greater than the maximum value.
		 */
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

		/**
		 * @brief Transposes the matrix.
		 *
		 * @return A new transposed matrix.
		 */
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

		/**
		 * @brief Adds two matrices.
		 *
		 * @param other The matrix to add.
		 * @return A new matrix representing the sum.
		 */
		Matrix<T> operator+(const Matrix<T> &other) const
		{
			if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
			{
				throw std::invalid_argument("Matrix dimensions must match");
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

		/**
		 * @brief Adds another matrix to the current matrix.
		 *
		 * @param other The matrix to add.
		 * @return Reference to the modified matrix.
		 */
		Matrix<T> &operator+=(const Matrix<T> &other)
		{
			if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
			{
				throw std::invalid_argument("Matrix dimensions must match");
			}

			*this = (*this) + other;

			return *this;
		}

		/**
		 * @brief Subtracts two matrices.
		 *
		 * @param other The matrix to subtract.
		 * @return A new matrix representing the difference.
		 */
		Matrix<T> operator-(const Matrix<T> &other) const
		{
			if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
			{
				throw std::invalid_argument("Matrix dimensions must match");
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

		/**
		 * @brief Subtracts another matrix from the current matrix.
		 *
		 * @param other The matrix to subtract.
		 * @return Reference to the modified matrix.
		 */
		Matrix<T> &operator-=(const Matrix<T> &other)
		{
			if (m_rows != other.m_rows || m_cols != other.m_cols) // Checks if both matrices are the same size
			{
				throw std::invalid_argument("Matrix dimensions must match");
			}

			*this = (*this) - other;

			return *this;
		}

		/**
		 * @brief Multiplies two matrices.
		 *
		 * @param other The matrix to multiply with.
		 * @return A new matrix representing the product.
		 * @throws std::invalid_argument If the matrices have incompatible dimensions.
		 */
		Matrix<T> operator*(const Matrix<T> &other) const
		{
			if (m_cols != other.m_rows)
			{
				throw std::invalid_argument("Matrix dimensions must match");
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

		/**
		 * @brief Multiplies the current matrix with another matrix.
		 *
		 * @param other The matrix to multiply with.
		 * @return Reference to the modified matrix.
		 */
		Matrix<T> &operator*=(const Matrix<T> &other)
		{
			if (m_cols != other.m_rows)
			{
				throw std::invalid_argument("Matrix dimensions must match");
			}

			*this = (*this) * other;

			return *this;
		}

		/**
		 * @brief Multiplies the matrix by a scalar.
		 *
		 * @param scalar The scalar value.
		 * @return A new matrix representing the scaled matrix.
		 */
		Matrix<T> operator*(const T &scalar) const
		{
			Matrix<T> result(m_rows, m_cols);

			for (int i = 0; i < m_rows; i++)
			{
				for (int j = 0; j < m_cols; j++)
				{
					result(i, j) = (*this)(i, j) * scalar;
				}
			}
			return result;
		}

		/**
		 * @brief Scales the current matrix by a scalar.
		 *
		 * @param scalar The scalar value.
		 * @return Reference to the modified matrix.
		 */
		Matrix<T> &operator*=(const T &scalar)
		{
			*this = (*this) * scalar;
			return *this;
		}

		/**
		 * @brief Makes one matrix another.
		 *
		 * @param other Other matrix.
		 * @return Reference to the modified matrix.
		 */
		Matrix<T> &operator=(const Matrix &other)
		{
			m_matrix = other.m_matrix;
			return *this;
		}

		/**
		 * @brief Compares two matrices for equality.
		 *
		 * @param other The matrix to compare with.
		 * @return True if the matrices are equal, false otherwise.
		 */
		bool operator==(const Matrix<T> &other) const
		{
			return m_matrix == other.m_matrix;
		}

		/**
		 * @brief Compares two matrices for inequality.
		 *
		 * @param other The matrix to compare with.
		 * @return True if the matrices are not equal, false otherwise.
		 */
		bool operator!=(const Matrix<T> &other) const
		{
			return !(*this == other);
		}

		/**
		 * @brief Prints the matrix to an output stream.
		 *
		 * @param os The output stream.
		 * @param matrix The matrix to print.
		 * @return The output stream with the matrix printed.
		 */
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
}