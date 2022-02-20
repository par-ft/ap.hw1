#include "hw1.h"

using Matrix = std::vector<std::vector<double>>;

// zero matrix
Matrix zeros(size_t n, size_t m) {}

// one matrix
Matrix ones(size_t n, size_t m) {}

// random matrix min<x<max
Matrix random(size_t n, size_t m, double min, double max) {}

// show matrix
void show(const Matrix &matrix) {}

// multiply matrix in C
Matrix multiply(const Matrix &matrix, double c) {}

// matrixb multiply to matrixa
Matrix multiply(const Matrix &matrix1, const Matrix &matrix2) {}

// add c to all
Matrix sum(const Matrix &matrix, double c) {}

// add matrixa to matrixb
Matrix sum(const Matrix &matrix1, const Matrix &matrix2) {}

// transpose of matrix
Matrix transpose(const Matrix &matrix) {}

// Mnm
Matrix minor(const Matrix &matrix, size_t n, size_t m) {}

// determinant of matrix
double determinant(const Matrix &matrix) {}

// inverse of matrix
Matrix inverse(const Matrix &matrix) {}

// axis=0: on top of each other & axis=1: alongside each othe
Matrix concatenate(const Matrix &matrix1, const Matrix &matrix2, int axis = 0) {}

// swap r1 to r2
Matrix ero_swap(const Matrix &matrix, size_t r1, size_t r2) {}

// multiply a row with c
Matrix ero_multiply(const Matrix &matrix, size_t r, double c) {}

// add c*r1 to r2
Matrix ero_sum(const Matrix &matrix, size_t r1, double c, size_t r2) {}

// upper triangular matrix
Matrix upper_triangular(const Matrix &matrix) {}
