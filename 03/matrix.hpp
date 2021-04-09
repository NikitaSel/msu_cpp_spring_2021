#pragma once

#include <iostream>
#include <algorithm>
// 1 2
// 3 4
// [1 2 3 4]

class ProxyRow
{
private:
    int *data_;
    // friend Matrix;

public:
    void SetData(int* data_);
    int& operator[](size_t j);
};

class Matrix
{
public:    
    Matrix(size_t rows, size_t cols);
    Matrix(size_t rows, size_t cols, int* array);
    size_t getRows();
    size_t getCols();
    // ...
    ProxyRow& operator[](size_t i);
    Matrix& operator*=(int j);
    Matrix& operator+=(Matrix& m);
    bool operator==(Matrix& m);
    bool operator!=(Matrix& m);
    
    friend Matrix operator+(Matrix& left, Matrix& right);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

private:
    size_t rows;
    size_t cols;
    int* data_;
    ProxyRow *rows_;
};