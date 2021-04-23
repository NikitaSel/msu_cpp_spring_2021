#include "BigInt.hpp"

BigInt::BigInt(){
    this->blocks_number = 0;
    this->is_negative = false;
    this->blocks = nullptr;
}

BigInt::BigInt(std::string s){
    if (s[0] == '-')
        this->is_negative = true;
    
    this->blocks_number = (s.length() - (this->is_negative ? 1 : 0)) / BIGINTBASE;
    if ((s.length() - (this->is_negative ? 1 : 0)) % BIGINTBASE)
        this->blocks_number++;

    this->blocks = new uint32_t[this->blocks_number];

    int offset = this->is_negative ? 1 : 0;
    for (uint64_t i = 0; i < this->blocks_number - 1; i++){ 
        this->blocks[i] = std::stoul(s.substr(s.length() - (i + 1) * BIGINTBASE, BIGINTBASE));
    }
    if (s.length() % BIGINTBASE - offset != 0)
        this->blocks[this->blocks_number - 1] = std::stoul(s.substr(offset, s.length() % BIGINTBASE));
    else
        this->blocks[this->blocks_number - 1] = std::stoul(s.substr(offset, BIGINTBASE));
}

BigInt::BigInt(const BigInt& right){
    this->blocks = new uint32_t[right.blocks_number];
    this->blocks_number = right.blocks_number;
    this->is_negative = right.is_negative;
    std::copy(right.blocks, right.blocks + right.blocks_number, this->blocks);
}

BigInt& BigInt::operator=(const BigInt& right){
    if (this == &right)
        return *this;

    delete[] this->blocks;
    this->blocks = new uint32_t[right.blocks_number];
    this->blocks_number = right.blocks_number;
    this->is_negative = right.is_negative;

    std::copy(right.blocks, right.blocks + right.blocks_number , this->blocks);
    return *this;
}

bool BigInt::operator ==(const BigInt& right){
    if ((this->blocks_number != right.blocks_number) || (this->is_negative != right.is_negative))
        return false;
    
    for (uint32_t i = 0; i < this->blocks_number; i++){
        if (this->blocks[i] != right.blocks[i])
            return false;
    }
    return true;
}

bool BigInt::operator !=(const BigInt& right){
    return !(*this == right);
}

bool BigInt::operator > (const BigInt& right){
    if (this->is_negative && !right.is_negative)
        return true;
    if (!this->is_negative && right.is_negative)
        return false;
    if (this->blocks_number < right.blocks_number)
        return this->is_negative;
    if (this->blocks_number > right.blocks_number)
        return !this->is_negative;

    for (int64_t i = this->blocks_number - 1; i >= 0; i--){
        if (this->blocks[i] < right.blocks[i])
            return this->is_negative;
        if (this->blocks[i] > right.blocks[i])
            return !this->is_negative;
    }
    
    return false;
}

bool BigInt::operator<=(const BigInt& right){
    return !(*this > right);
}


bool BigInt::operator < (const BigInt& right){
    if (this->is_negative && !right.is_negative)
        return false;
    if (!this->is_negative && right.is_negative)
        return true;
    if (this->blocks_number > right.blocks_number)
        return this->is_negative;
    if (this->blocks_number < right.blocks_number)
        return !this->is_negative;

    for (int64_t i = this->blocks_number - 1; i >= 0; i--){
        if (this->blocks[i] > right.blocks[i])
            return this->is_negative;
        if (this->blocks[i] < right.blocks[i])
            return !this->is_negative;
    }
    
    return false;
}

bool BigInt::operator>=(const BigInt& right){
    return !(*this < right);
}

BigInt BigInt::operator+(){
    return *this;
}

BigInt BigInt::operator-(){
    BigInt tmp = *this;
    tmp.is_negative = !this->is_negative;
    return tmp;
}

BigInt BigInt::operator+(const BigInt& right){
    BigInt tmp;
    tmp.blocks_number = std::max(this->blocks_number, right.blocks_number);
    if (this->is_negative == right.is_negative){
        tmp.blocks = new uint32_t[tmp.blocks_number + 1];
        tmp.is_negative = this->is_negative;

        int overflow = 0;
        for (uint32_t i = 0; i < tmp.blocks_number; i++){
            tmp.blocks[i] = (this->blocks[i] + right.blocks[i] + overflow) % (BIGINTMAX * 10);
            overflow = (this->blocks[i] + right.blocks[i]) / (BIGINTMAX * 10);
        }
        if (overflow){
            tmp.blocks[tmp.blocks_number] = overflow;
            tmp.blocks_number++;
        }
        return tmp;

    } else{
        this->is_negative ? tmp = *this : tmp = right;
        tmp.is_negative = false;
        return (this->is_negative ? (BigInt)right - tmp : *this - tmp); 
    }
}

BigInt BigInt::operator+(int32_t right){
    BigInt tmp(std::to_string(right));
    return *this + tmp;
}

BigInt BigInt::operator-(const BigInt& right){
    BigInt tmp;

    if (*this == right){
        tmp.blocks_number = 1;
        tmp.blocks = new uint32_t[tmp.blocks_number];
        tmp.blocks[0] = (uint32_t)0;
        return tmp;
    }

    tmp.blocks_number = std::max(this->blocks_number, right.blocks_number);
    if (this->is_negative != right.is_negative){
        !this->is_negative ? tmp = *this : tmp = right;
        tmp.is_negative = true;
        return (!this->is_negative ? -((BigInt)right + tmp) : (*this + tmp));
    }

    tmp.blocks = new uint32_t[tmp.blocks_number + 1];
    tmp.is_negative = !(*this > right);

    BigInt big, small;
    big = tmp.is_negative ? right : *this;
    small  = tmp.is_negative ? *this : right;
    int overdraft = 0;

    for (uint32_t i = 0; i < tmp.blocks_number; i++){
        if (big.blocks[i] < small.blocks[i]){
            tmp.blocks[i] = (big.blocks[i] + BIGINTMAX * 10 - small.blocks[i] + overdraft);
            overdraft = -1;
        }
        else{
            tmp.blocks[i] = (big.blocks[i] - small.blocks[i] + overdraft);  
            overdraft = 0;
        }
    }
    for (uint32_t i = 0; i < tmp.blocks_number; i++){
        if (tmp.blocks[i] == (uint32_t)0){
            tmp.blocks_number = i;
            break;
        }
    }
    return tmp;
}

BigInt BigInt::operator-(int32_t right){
    BigInt tmp(std::to_string(right));
    return *this - tmp;
}

BigInt BigInt::operator*(const BigInt& right){
    BigInt tmp;
    int offset = 0;
    tmp.blocks_number = this->blocks_number + right.blocks_number;
    tmp.blocks = new uint32_t[tmp.blocks_number];
    if (this->is_negative != right.is_negative)
        tmp.is_negative = true;
    else
        tmp.is_negative = false;

    for (uint32_t i = 0; i < this->blocks_number; i++){
        for (uint32_t j = 0; j < right.blocks_number; j++){
            tmp.blocks[i + j] = (this->blocks[i] * right.blocks[j] + offset) % (BIGINTMAX * 10);
            offset = (this->blocks[i] * right.blocks[j]) / (BIGINTMAX * 10);
        }
    }
    if (tmp.blocks[tmp.blocks_number] == (uint32_t)0)
        tmp.blocks_number -= 1;

    return tmp;
}

BigInt BigInt::operator*(int32_t right){
    BigInt tmp(std::to_string(right));
    return *this * tmp;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bigint){
    if (bigint.is_negative)
        os << "-";
    for (int64_t i = bigint.blocks_number - 1; i >= 0; i--){
        if (bigint.blocks[i] == (uint32_t)0)
            os << std::string("000000000");
        else
            os << bigint.blocks[i];
    }
    return os;
}
