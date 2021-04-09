#include "matrix.hpp"

int main()
{
    int values[] = {1, 2, 3, 4};
    Matrix matr(2, 2, values);
    // std::cout << matr[1][1] << std::endl;
    // matr[1][1] = 1;

    std::cout << matr;
    Matrix matr2 (2, 2, values);
    matr2 *= 2;
    std::cout << matr2;
    matr2 += matr;
    std::cout << matr2;
    std::cout << matr + matr2 << std::endl;
    

    if (matr != matr2)
        std::cout << "good\n";
    return 0;
}