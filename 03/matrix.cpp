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


/* Matrix constructors, operator =, destructor */
Matrix::Matrix(const size_t m, const size_t n, const int32_t val) : rows{m}, columns{n} {
    if (m <= 0 || n <= 0) {
        throw std::logic_error("Invalid matrix shape");
    }
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

Matrix::~Matrix() {
    delete[] head;
}

const Matrix &Matrix::operator =(const Matrix &mat) {
    if (rows * columns != mat.rows * mat.columns) {
        delete[] head;
        head = new int32_t[mat.rows * mat.columns];
    }
    rows = mat.rows;
    columns = mat.columns;
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] = mat.head[i];
    }
    return *this;
}


/* Getters */
size_t Matrix::get_rows() const {
    return rows;
}

size_t Matrix::get_columns() const {
    return columns;
}

bool Matrix::operator ==(const Matrix &other) {
    if (rows != other.rows || columns != other.columns) {
        throw std::logic_error("Matrices' shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        if (head[i] != other.head[i]) {
            return false;
        }
    }
    return true;
}

/* Element indexing */
ProxyMatrix Matrix::operator [](const size_t idx) const {
    if (idx >= rows) {
        throw std::out_of_range("Out of row index");
    }
    return ProxyMatrix(head + columns * idx, columns);
}

const Matrix Matrix::transp(bool inplace) {
    if (inplace && rows == columns) {
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < i; ++j) {
                std::swap(head[i * rows + j], head[j * rows + i]);
            }
        }
        return *this;
    } else {
        Matrix res(columns, rows, 0);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < columns; ++j) {
                res.head[j * rows + i] = head[i * columns + j];
            }
        }
        return res;
    }
}

/* Matrix & Matrix operations */
const Matrix &Matrix::operator +=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        throw std::logic_error("Matrices shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] += mat.head[i];
    }
    return *this;
}

const Matrix &Matrix::operator -=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        throw std::logic_error("Matrices' shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] -= mat.head[i];
    }
    return *this;
}

const Matrix &Matrix::operator *=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        throw std::logic_error("Matrices' shapes do not match");
    }
    for (size_t i = 0; i < rows * columns; ++i) {
        head[i] *= mat.head[i];
    }
    return *this;
}

const Matrix &Matrix::operator /=(const Matrix &mat) {
    if (mat.rows != rows || mat.columns != columns) {
        throw std::logic_error("Matrices' shapes do not match");
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
std::ostream &operator <<(std::ostream &out, const Matrix &mat) {
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

Matrix dot(const Matrix &a, const Matrix &b) {
    size_t m = a.rows, n = a.columns, k = b.columns;
    if (n != b.rows) {
        throw std::logic_error("Matroces' shapes do not match");
    }
    Matrix c(m, k, 0);
    for (size_t i = 0; i < m; ++i) {
        for (size_t p = 0; p < n; ++p) {
            for (size_t j = 0; j < k; ++j) {
                c.head[i * k + j] += a.head[i * n + p] * b.head[p * k + j];
            }
        }
    }
    return c;
}





