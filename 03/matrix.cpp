#include "matrix.hpp"

void ProxyRow::SetData(int* data_)
{
    this->data_ = data_;
}

int& ProxyRow::operator[](size_t j)
{
    return data_[j];
}

Matrix::Matrix(const size_t rows, const size_t cols)
{
    this->rows = rows;
    this->cols = cols;
    this->data_ = new int[rows * cols];
    this->rows_ = new ProxyRow[rows];
    for(size_t i = 0; i < rows; i++)
        this->rows_[i].SetData(this->data_ + i * cols);
}

Matrix::Matrix(const size_t rows, const size_t cols, int* data)
{
    this->rows = rows;
    this->cols = cols;

    this->data_ = new int[rows * cols];
    std::copy(data, data + rows*cols, this->data_);
    this->rows_ = new ProxyRow[rows];
    for(size_t i = 0; i < rows; i++)
        this->rows_[i].SetData(this->data_ + i * cols);
}

ProxyRow& Matrix::operator[](size_t i)
{
    return rows_[i];
}

Matrix& Matrix::operator*=(int j)
{
    for (size_t i = 0; i < this->rows*this->cols; i++)
        this->data_[i] *= j;
    return *this;
}

bool Matrix::operator==(Matrix& m)
{
    if (this->rows != m.rows || this->cols != m.cols)
        return false;

    for (size_t i = 0; i < this->rows*this->cols; i++)
        if (this->data_[i] != m.data_[i])
            return false;
    
    return true;
}

bool Matrix::operator!=(Matrix& m)
{
    return !(*this == m);
}

Matrix& Matrix::operator+=(Matrix& m)
{
    if (this->rows != m.rows || this->cols != m.cols)
        throw std::out_of_range("");

    for (size_t i = 0; i < this->rows*this->cols; i++)
    {
        this->data_[i] += m.data_[i]; 
    }
    return *this;
}

Matrix operator+(Matrix& left, Matrix& right)
{   
    if (left.rows != right.rows || left.cols != right.cols)
        throw std::out_of_range("");
    
    int* values = new int[left.rows * left.cols];

    for (size_t i = 0; i < left.rows*left.cols; i++)
    {
        values[i] = left.data_[i] + right.data_[i];
    }
    Matrix matr(left.rows, left.cols, values);
    return matr;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (size_t i = 0; i < m.rows; i++)
    {
        std::cout << '[';
        for (size_t j = 0; j < m.cols; j++)
            std::cout << m.data_[i*(m.rows) + j] << ((j == m.cols-1) ? "" : " ");
        std::cout << ']' << ((i == m.rows-1) ? "" : ",") << std::endl;
    }
    
    return os;
}


size_t Matrix::getRows()
{
    return this->rows;
}

size_t Matrix::getCols()
{
    return this->cols;
}