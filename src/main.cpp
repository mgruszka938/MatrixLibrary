#include "../inc/matrix.hpp"
#include "../inc/squarematrix.hpp"
#include <iostream>

void printSeparator()
{
    std::cout << "\n----------------------------------------\n"
              << std::endl;
}

template <typename T>
void printMatrix(const std::string &label, const mg::Matrix<T> &matrix)
{
    std::cout << label << ":\n"
              << matrix << std::endl;
}

int main()
{
    try
    {
        std::cout << "Testing Matrix Class" << std::endl;

        printSeparator();

        std::cout << "Testing Constructors:" << std::endl;
        mg::Matrix<int> emptyMatrix;
        mg::Matrix<int> matrix1(3, 4, 1);
        std::vector<std::vector<int>> vec = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        mg::Matrix<int> matrix2(vec);

        printMatrix("Empty Matrix", emptyMatrix);

        printMatrix("3x4 Matrix with all ones", matrix1);

        printMatrix("3x3 Matrix from vector", matrix2);

        std::cout << "Matrix2 Dimensions: " << matrix2.getRows() << "x" << matrix2.getCols() << std::endl;

        std::cout << "\nTesting Row and Column Operations:" << std::endl;
        std::vector<int> newRow = {10, 11, 12};
        std::vector<int> newCol = {13, 14, 15};

        matrix2.addRow(1, newRow);
        printMatrix("After adding row", matrix2);

        matrix2.removeRow(1);
        printMatrix("After removing row", matrix2);

        matrix2.addCol(1, newCol);
        printMatrix("After adding column", matrix2);

        matrix2.removeCol(1);
        printMatrix("After removing column", matrix2);

        printSeparator();

        std::cout << "\nTesting Element Access:" << std::endl;
        std::cout << "Element at (1,1): " << matrix2(1, 1) << std::endl;

        std::cout << "\nTesting Value Setting:" << std::endl;
        mg::Matrix<int> matrix3(2, 2);

        matrix3.setOnes();
        printMatrix("Matrix with all ones", matrix3);

        matrix3.setZeroes();
        printMatrix("Matrix with all zeroes", matrix3);

        matrix3.setRandomValues(1, 10);
        printMatrix("Matrix with random values", matrix3);

        printSeparator();

        std::cout << "\nTesting Matrix Operations:" << std::endl;
        mg::Matrix<int> a({{1, 1, 1}, {2, 2, 2}});
        mg::Matrix<int> b({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        printMatrix("Matrix A", a);
        printMatrix("Matrix B", b);

        mg::Matrix<int> prod = a * b;
        printMatrix("A * B", prod);

        mg::Matrix<int> scaled = a * 3;
        printMatrix("A * 3", scaled);

        mg::Matrix<int> transposed = a.transpose();
        printMatrix("A transposed", transposed);

        std::cout << "\nTesting SquareMatrix Class" << std::endl;

        printSeparator();

        mg::SquareMatrix<int> square1(3, 2);
        printMatrix("3x3 Square Matrix with all twos", square1);

        mg::SquareMatrix<int> identity = mg::SquareMatrix<int>::identity(3);
        printMatrix("3x3 Identity Matrix", identity);

        mg::Matrix<int> sum = square1 + identity;
        printMatrix("Sum of the above", sum);

        mg::Matrix<int> sub = square1 - identity;
        printMatrix("Difference of the above", sub);

        std::cout << "Determinant of identity matrix: " << identity.determinant() << std::endl;
        std::vector<std::vector<int>> squareVec = {{13, 2, 4}, {0, 7, 3}, {0, 0, 23}};
        mg::SquareMatrix<int> square2(squareVec);

        printSeparator();

        printMatrix("Square Matrix from vector", square2);
        std::cout << "Determinant of square matrix: " << square2.determinant() << std::endl;

        printSeparator();

        std::cout << "\nTesting Comparison Operators:" << std::endl;
        mg::SquareMatrix<int> m1(2, 12);
        mg::SquareMatrix<int> m2(2, 11);
        mg::SquareMatrix<int> m3(2, 13);

        printMatrix("m1", m1);
        printMatrix("m2", m2);
        printMatrix("m3", m3);

        std::cout << "m1 == m2: " << (m1 == m2) << std::endl;
        std::cout << "m1 != m3: " << (m1 != m3) << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}