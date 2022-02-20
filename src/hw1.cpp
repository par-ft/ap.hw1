#include "hw1.h"

using Matrix = std::vector<std::vector<double>>;

// zero matrix
Matrix algebra::zeros(size_t n, size_t m)
{
    Matrix matrix;
    std::vector<double> inner(m);

    for (size_t i{}; i < n; i++)
        matrix.push_back(inner);

    return matrix;
}

// one matrix
Matrix algebra::ones(size_t n, size_t m)
{
    Matrix matrix;
    std::vector<double> inner(m, 1);

    for (size_t i{}; i < n; i++)
        matrix.push_back(inner);

    return matrix;
}

// random matrix min<x<max
Matrix algebra::random(size_t n, size_t m, double min, double max)
{
    Matrix matrix;

    unsigned seed{std::chrono::system_clock::now().time_since_epoch().count()};
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<double> distribution(min, max);

    for (size_t i{}; i < n; i++)
    {
        std::vector<double> inner;

        for (size_t j{}; j < m; j++)
            inner.push_back(distribution(generator));

        matrix.push_back(inner);
    }

    return matrix;
}

// show matrix
void algebra::show(const Matrix &matrix) {}

// multiply matrix in C
Matrix algebra::multiply(const Matrix &matrix, double c) {}

// matrixb multiply to matrixa
Matrix algebra::multiply(const Matrix &matrix1, const Matrix &matrix2) {}

// add c to all
Matrix algebra::sum(const Matrix &matrix, double c) {}

// add matrixa to matrixb
Matrix algebra::sum(const Matrix &matrix1, const Matrix &matrix2) {}

// transpose of matrix
Matrix algebra::transpose(const Matrix &matrix) {}

// Mnm
Matrix algebra::minor(const Matrix &matrix, size_t n, size_t m) {}

// determinant of matrix
double algebra::determinant(const Matrix &matrix) {}

// inverse of matrix
Matrix algebra::inverse(const Matrix &matrix) {}

// axis=0: on top of each other & axis=1: alongside each othe
Matrix algebra::concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis = 0) {}

// swap r1 to r2
Matrix algebra::ero_swap(const Matrix &matrix, size_t r1, size_t r2) {}

// multiply a row with c
Matrix algebra::ero_multiply(const Matrix &matrix, size_t r, double c) {}

// add c*r1 to r2
Matrix algebra::ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2) {}

// upper triangular matrix
Matrix algebra::upper_triangular(const Matrix &matrix) {}
