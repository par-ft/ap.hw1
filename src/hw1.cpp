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

    if (min >= max)
        throw std::logic_error("Caution: min cannot be greater than max");
    else
    {
        long seed{std::chrono::system_clock::now().time_since_epoch().count()};
        std::default_random_engine generator(seed);
        std::uniform_real_distribution<double> distribution(min, max);

        for (size_t i{}; i < n; i++)
        {
            std::vector<double> inner;

            for (size_t j{}; j < m; j++)
                inner.push_back(distribution(generator));

            matrix.push_back(inner);
        }
    }

    return matrix;
}

// show matrix
void algebra::show(const Matrix &matrix)
{
    for (auto inner : matrix)
    {
        for (double num : inner)
        {
            // printing all numbers in a beautiful way
            if (num >= 0)
                std::cout << " ";

            std::cout << std::fixed << std::setprecision(3) << num << " ";
        }

        std::cout << std::endl;
    }
}

// multiply matrix in C
Matrix algebra::multiply(const Matrix &matrix, double c)
{
    if (matrix.size() != 0)
    {
        Matrix new_matrix{algebra::zeros(matrix.size(), matrix[0].size())};

        for (ssize_t i{}; i < matrix.size(); i++)
            for (size_t j{}; j < matrix[0].size(); j++)
                new_matrix[i][j] = matrix[i][j] * c;

        return new_matrix;
    }
    else
        throw std::logic_error("Input matrix is empty");

    return Matrix{};
}

// matrix1 multiply to matrix2
Matrix algebra::multiply(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.size() == 0 && matrix2.size() == 0)
        return Matrix{};

    else if (matrix1[0].size() != matrix2.size())
        throw std::logic_error("Caution: matrices with wrong dimensions cannot be multiplied");

    else
    {
        Matrix new_matrix{};

        for (ssize_t i{}; i < matrix1.size(); i++)
        {
            std::vector<double> inner;

            for (size_t j{}; j < matrix2[0].size(); j++)
            {
                double num{};

                for (size_t k{}; k < matrix2.size(); k++)
                    num += matrix1[i][k] * matrix2[k][j];

                inner.push_back(num);
            }

            new_matrix.push_back(inner);
        }

        return new_matrix;
    }

    return Matrix{};
}

// add c to all
Matrix algebra::sum(const Matrix &matrix, double c)
{
    if (matrix.size() != 0)
    {
        Matrix new_matrix{algebra::zeros(matrix.size(), matrix[0].size())};

        for (ssize_t i{}; i < matrix.size(); i++)
            for (size_t j{}; j < matrix[0].size(); j++)
                new_matrix[i][j] = matrix[i][j] + c;

        return new_matrix;
    }

    return Matrix{};
}

// add matrix1 to matrix2
Matrix algebra::sum(const Matrix &matrix1, const Matrix &matrix2)
{
    if (matrix1.size() != 0)
    {
        if (matrix1.size() == matrix2.size() && matrix1[0].size() == matrix2[0].size())
        {
            Matrix new_matrix{algebra::zeros(matrix1.size(), matrix1[0].size())};

            for (ssize_t i{}; i < matrix1.size(); i++)
                for (size_t j{}; j < matrix1[0].size(); j++)
                    new_matrix[i][j] = matrix1[i][j] + matrix2[i][j];

            return new_matrix;
        }
        else
            throw std::logic_error("Caution: matrices with wrong dimensions cannot be summed");
    }

    return Matrix{};
}

// transpose of matrix
Matrix algebra::transpose(const Matrix &matrix)
{
    if (matrix.size() != 0)
    {
        Matrix new_matrix{algebra::zeros(matrix[0].size(), matrix.size())};

        for (size_t i{}; i < matrix.size(); i++)
            for (size_t j{}; j < matrix[0].size(); j++)
                new_matrix[j][i] = matrix[i][j];

        return new_matrix;
    }

    return Matrix{};
}

// minor of matrix
Matrix algebra::minor(const Matrix &matrix, size_t n, size_t m)
{
    Matrix new_matrix{matrix};

    // removing nth row
    new_matrix.erase(new_matrix.begin() + n);

    // removing mth column
    new_matrix = algebra::transpose(new_matrix);
    new_matrix.erase(new_matrix.begin() + m);
    new_matrix = algebra::transpose(new_matrix);

    return new_matrix;
}

// determinant of matrix
double algebra::determinant(const Matrix &matrix)
{
    double determinant{};

    if (matrix.size() != 0)
    {
        if (matrix.size() == matrix[0].size())
        {
            if (matrix.size() != 1)
                for (size_t i{}; i < matrix.size(); i++)
                    determinant += matrix[0][i] * pow(-1, i) * algebra::determinant(algebra::minor(matrix, 0, i));
            else
                determinant = matrix[0][0];
        }
        else
            throw std::logic_error("Caution: non-square matrices have no determinant");
    }
    else
    {
        determinant = 1;
    }

    return determinant;
}

// inverse of matrix
Matrix algebra::inverse(const Matrix &matrix)
{
    if (matrix.size() != 0)
    {
        if (matrix.size() == matrix[0].size())
        {
            Matrix adjugate_matrix{matrix};
            double determinant{algebra::determinant(matrix)};
            if (determinant != 0)
            {
                for (size_t i{}; i < matrix.size(); i++)
                    for (size_t j{}; j < matrix[0].size(); j++)
                        adjugate_matrix[i][j] = pow(-1, i + j) * algebra::determinant(algebra::minor(matrix, i, j));

                adjugate_matrix = algebra::transpose(adjugate_matrix);

                return algebra::multiply(adjugate_matrix, 1 / determinant);
            }
            else
                throw std::logic_error("Caution: singular matrices have no inverse");
        }
        else
            throw std::logic_error("Caution: non-square matrices have no inverse");
    }
    else
        return Matrix{};
}

// axis=0: on top of each other & axis=1: alongside each othe
Matrix algebra::concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis)
{
    Matrix matrix;

    if (axis == 0)
    {
        if (matrix1[0].size() == matrix2[0].size())
        {
            matrix = matrix1;

            for (size_t i{}; i < matrix2.size(); i++)
                matrix.push_back(matrix2[i]);

            return matrix;
        }
        else
            throw std::logic_error("Caution: matrices with wrong dimensions cannot be concatenated");
    }
    else if (axis == 1)
    {
        if (matrix1.size() == matrix2.size())
        {
            matrix = matrix1;

            for (size_t i{}; i < matrix2.size(); i++)
                for (size_t j{}; j < matrix2[0].size(); j++)
                    matrix[i].push_back(matrix2[i][j]);

            return matrix;
        }
        else
            throw std::logic_error("Caution: matrices with wrong dimensions cannot be concatenated");
    }

    return matrix;
}

// // swap r1 to r2
// Matrix algebra::ero_swap(const Matrix &matrix, size_t r1, size_t r2) {}

// // multiply a row with c
// Matrix algebra::ero_multiply(const Matrix &matrix, size_t r, double c) {}

// // add c*r1 to r2
// Matrix algebra::ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2) {}

// // upper triangular matrix
// Matrix algebra::upper_triangular(const Matrix &matrix) {}
