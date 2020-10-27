#include "matrix.h"
//#include <cstddef>
#include <exception>
#include <sstream>
#include <iostream>

/* Proxy Class*/
ProxyMatrix::ProxyMatrix(int *ptr, size_t cnt) : row_ptr{ptr}, col_cnt{cnt} {}
int32_t &ProxyMatrix::operator[](const size_t idx) {
    if (idx >= col_cnt) {
        throw std::out_of_range("Out of column index");
    }
    return row_ptr[idx];
}
/*const int32_t ProxyMatrix::operator[](const size_t idx) {
    if (idx >= col_cnt) {
        throw std::out_of_range("Out of column index");
    }
    return row_ptr[idx];
}*/

/* Matrix constructors, operator=, destructor */
Matrix::Matrix(const size_t m, const size_t n, const int32_t val) : rows{m}, columns{n} {
    head = new int32_t[m * n];
    for (size_t i = 0; i < m * n; ++i) {
        head[i] = val;
    }
}
Matrix::Matrix(const int32_t val) {
    head = new int32_t;
    columns = rows = 1;
    head[0] = val;
}
Matrix::Matrix(const Matrix &mat) : rows{mat.rows}, columns{mat.columns} {
    head = new int32_t[rows * columns];
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] = mat.head[i];
    }
}
const Matrix &Matrix::operator =(const Matrix &mat) {
    if (rows * columns != mat.rows * mat.columns) {
        head = new int32_t[mat.rows * mat.columns];
    }
    rows = mat.rows;
    columns = mat.columns;
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] = mat.head[i];
    }
    return *this;
}
Matrix::~Matrix() {
    delete[] head;
}

/* Getters */
size_t Matrix::get_rows() const {
    return rows;
}
size_t Matrix::get_columns() const {
    return columns;
}

/* Element indexing */
ProxyMatrix Matrix::operator [](const size_t idx) const {
    if (idx >= rows) {
        throw std::out_of_range("Out of row index");
    }
    return ProxyMatrix(head + columns * idx, columns);
}

/* Matrix & Matrix operations */
const Matrix &Matrix::operator +=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        std::cout << mat.rows << ", " << rows << std::endl;
        std::cout << mat.columns << ", " << columns << std::endl;
        throw std::logic_error("Matrices shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] += mat.head[i];
    }
    return *this;
}
const Matrix &Matrix::operator -=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        throw std::logic_error("Matrices shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] -= mat.head[i];
    }
    return *this;
}
const Matrix &Matrix::operator *=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        throw std::logic_error("Matrices shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] *= mat.head[i];
    }
    return *this;
}
const Matrix &Matrix::operator /=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        throw std::logic_error("Matrices shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        if (mat.head[i] == 0) {
            throw std::logic_error("Divide by zero");
        }
        head[i] /= mat.head[i];
    }
    return *this;
}

/* Matrix & Number operations */
const Matrix &Matrix::operator +=(const int32_t val) {
    for (size_t i = 0; i < columns * rows; ++i) {
        head[i] += val;
    }
    return *this;
}
const Matrix &Matrix::operator -=(const int32_t val) {
    for (size_t i = 0; i < columns * rows; ++i) {
        head[i] -= val;
    }
    return *this;
}
const Matrix &Matrix::operator *=(const int32_t val) {
    for (size_t i = 0; i < columns * rows; ++i) {
        head[i] *= val;
    }
    return *this;
}
const Matrix &Matrix::operator /=(const int32_t val) {
    if (val == 0) {
        throw std::logic_error("Divide by zero");
    }
    for (size_t i = 0; i < columns * rows; ++i) {
        head[i] /= val;
    }
    return *this;
}
/* Output */
std::ostream &operator <<(std::ostream &out, Matrix &mat) {
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.columns - 1; ++j) {
            std::cout << mat.head[i * mat.columns + j] << "\t";
        }
        std::cout << mat.head[i * mat.columns + mat.columns - 1];
        if (i < mat.rows - 1) {
            std::cout << std::endl;
        }
    }

    return out;
}

Matrix operator +(const Matrix &a, const Matrix &b) {
    if (a.get_rows() == 1 && a.get_columns() == 1) {
        return Matrix(b) += a[0][0];
    } else {
        return Matrix(a) += b;
    }
}
Matrix operator -(const Matrix &a, const Matrix &b) {
    if (a.get_rows() == 1 && a.get_columns() == 1) {
        return Matrix(b) -= a[0][0];
    } else {
        return Matrix(a) += b;
    }
}
Matrix operator *(const Matrix &a, const Matrix &b) {
    if (a.get_rows() == 1 && a.get_columns() == 1) {
        return Matrix(b) *= a[0][0];
    } else {
        return Matrix(a) += b;
    }
}
Matrix operator /(const Matrix &a, const Matrix &b) {
    if (a.get_rows() == 1 && a.get_columns() == 1) {
        return Matrix(b) /= a[0][0];
    } else {
        return Matrix(a) += b;
    }
}

Matrix operator +(const Matrix &a, const int32_t b) {
    return Matrix(a) += b;
}
Matrix operator -(const Matrix &a, const int32_t b) {
    return Matrix(a) -= b;
}
Matrix operator *(const Matrix &a, const int32_t b) {
    return Matrix(a) *= b;
}
Matrix operator /(const Matrix &a, const int32_t b) {
    return Matrix(a) /= b;
}


