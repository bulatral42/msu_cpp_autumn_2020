#pragma once

#include <cstddef>
#include <sstream>

class ProxyMatrix{
    int32_t *row_ptr;
    size_t col_cnt; 
public:
    ProxyMatrix(int32_t *row_ptr, size_t col_cnt);
    int32_t &operator[](const size_t idx);
};
    
class Matrix{

    int32_t *head{nullptr};
    size_t rows{}, columns{};
    
public:
    Matrix(const size_t, const size_t, const int32_t val = 0);
    Matrix(const int32_t val = 0);  /* For integer conversions */
    Matrix(const Matrix &);
    ~Matrix();
    const Matrix &operator =(const Matrix &mat);
    
    
    size_t get_rows() const;
    size_t get_columns() const;
    
    ProxyMatrix operator [](const size_t m) const;
    friend std::ostream &operator <<(std::ostream &, const Matrix &);
    
    Matrix transp(bool inplace = true);  /* Inplace is only for squared */
    
    const Matrix &operator +=(const Matrix &);
    const Matrix &operator -=(const Matrix &);
    const Matrix &operator *=(const Matrix &);
    const Matrix &operator /=(const Matrix &);
    bool operator ==(const Matrix &);
    
    const Matrix &operator +=(const int32_t);
    const Matrix &operator -=(const int32_t);
    const Matrix &operator *=(const int32_t);
    const Matrix &operator /=(const int32_t);
    
    
    friend Matrix dot(const Matrix &, const Matrix &);  /* Matrix multiplication */
};

std::ostream &operator <<(std::ostream &, const Matrix &);

Matrix dot(const Matrix &, const Matrix &);

Matrix operator +(const Matrix &, const Matrix &);
Matrix operator -(const Matrix &, const Matrix &);
Matrix operator *(const Matrix &, const Matrix &);
Matrix operator /(const Matrix &, const Matrix &);

Matrix operator +(const Matrix &, const int32_t);
Matrix operator -(const Matrix &, const int32_t);
Matrix operator *(const Matrix &, const int32_t);
Matrix operator /(const Matrix &, const int32_t);

