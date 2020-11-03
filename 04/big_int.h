#pragma once

#include <cstddef>
#include <sstream>

/* Numbers are presented in base 1e18 as arrays of digits */
constexpr int BASE_LEN = 6;
constexpr uint64_t BASE = 1000000;
class BigInt{

    bool neg_{false};  /* 0 is non-negative */
    uint64_t *digits_{nullptr};
    size_t len_{1};
    
    void check_() const;
    
public:
    BigInt(const int64_t n = 0);
    BigInt(const std::string &);
    BigInt(const BigInt &);
    BigInt(BigInt &&);
    
    ~BigInt();
    
    BigInt &operator =(const BigInt &);
    BigInt &operator =(BigInt &&);
    
    friend std::ostream &operator <<(std::ostream &, const BigInt &);
    std::string to_string() const;
    size_t get_len() const;
    
    BigInt &operator +=(const BigInt &);
    BigInt &operator -=(const BigInt &);
    BigInt &operator *=(const BigInt &);
    
    BigInt operator -() const;
    
    friend bool operator ==(const BigInt &, const BigInt &);
    friend bool operator !=(const BigInt &, const BigInt &);
    friend bool operator <(const BigInt &, const BigInt &);
    friend bool operator <=(const BigInt &, const BigInt &);
    friend bool operator >(const BigInt &, const BigInt &);
    friend bool operator >=(const BigInt &, const BigInt &);
    
};

std::ostream &operator <<(std::ostream &, const BigInt &);

bool operator ==(const BigInt &, const BigInt &);
bool operator !=(const BigInt &, const BigInt &);
bool operator <(const BigInt &, const BigInt &);
bool operator <=(const BigInt &, const BigInt &);
bool operator >(const BigInt &, const BigInt &);
bool operator >=(const BigInt &, const BigInt &);

BigInt operator +(const BigInt &, const BigInt &);
BigInt operator -(const BigInt &, const BigInt &);
BigInt operator *(const BigInt &, const BigInt &);

