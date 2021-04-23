#pragma once

#include <iostream>
#include <limits>
#include <algorithm>
#include <string>

const uint32_t BIGINTBASE = 9;
const uint32_t BIGINTMAX = 100000000;

class BigInt{
    private:
        bool is_negative;
        uint32_t* blocks;
        uint32_t blocks_number;
    public:

    BigInt();
    BigInt(std::string s);

    BigInt(const BigInt& right);
    BigInt& operator=(const BigInt& right);

    BigInt operator+();
    BigInt operator-();
    
    BigInt operator+(const BigInt& right);
    BigInt operator+(int32_t right);
    
    BigInt operator-(const BigInt& right);
    BigInt operator-(int32_t right);

    BigInt operator*(const BigInt& right);
    BigInt operator*(int32_t right);

    bool operator ==(const BigInt& right);
    bool operator !=(const BigInt& right);
    bool operator <(const BigInt& right);
    bool operator <=(const BigInt& right);
    bool operator >(const BigInt& right);
    bool operator >=(const BigInt& right);

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bigint);
};