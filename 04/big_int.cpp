#include "big_int.h"
#include <cstddef>
#include <cstring>
#include <exception>
#include <sstream>
#include <iostream>
#include <iomanip>


/* BigInt constructors, operator =, destructor */
BigInt::BigInt(const int64_t n) {
    if (n < 0) {
        neg = true;
    }
    digits = new uint64_t[1];
    digits[0] = neg ? -n : n;
}

BigInt::BigInt(const std::string &s) {
    auto it1 = s.cbegin();
    for (; it1 != s.cend() && isspace(*it1); ++it1) {}
    if (*it1 == '-' || *it1 == '+') {
        neg = *it1 == '-';
        ++it1;
    } else if (!isdigit(*it1)) {
        throw std::logic_error("Invalid string to interpret as a number");
    }
    bool pre_zeros{false};
    for (; it1 != s.cend() && *it1 == '0'; ++it1) {
        pre_zeros = true;
    }

    auto it2 = it1;
    for (; it2 != s.cend() && isdigit(*it2); ++it2) {}
    std::string s_norm(it1, it2);
    size_t s_len = s_norm.size();
    if (s_len == 0) {
        if (pre_zeros) {
            digits = new uint64_t[1];
            digits[0] = 0;
            neg = false;
            len = 1;
        } else {
            throw std::logic_error("Invalid string to interpret as a number");
        }
    } else {
        len = (s_len + BASE_LEN - 1) / BASE_LEN;
        size_t head = s_len % BASE_LEN;
        digits = new uint64_t[len];
        size_t idx = 0;
        if (head > 0) {
            std::string tmp(s_norm.cbegin(), s_norm.cbegin() + head);
            digits[len - 1] = std::stoull(tmp);
            ++idx;
        }
        it1 = s_norm.cbegin() + head;
        for (; it1 != s_norm.cend() ; it1 += BASE_LEN, ++idx) {
            digits[len - 1 - idx] = std::stoull(std::string(it1, it1 + BASE_LEN));
        }
    }
}


BigInt::BigInt(const BigInt &n) : neg{n.neg}, len{n.len} {
    digits = new uint64_t[len];
    std::copy(n.digits, n.digits + len, digits);
}

BigInt::BigInt(BigInt &&n) : neg{std::move(n.neg)}, len{std::move(n.len)}{
    digits = n.digits;
    n.digits = nullptr;
    n.neg = false;
    n.len = 0;
}
    
BigInt::~BigInt() {
    delete[] digits;
}
    

BigInt &BigInt::operator =(const BigInt &n) {
    std::cout << "Copy operator=" << std::endl;
    if (this == &n) {
        return *this;
    }
    if (len != n.len) {
        uint64_t *tmp = new uint64_t[n.len];
        delete[] digits;
        digits = tmp;
    }
    len = n.len;
    neg = n.neg;
    std::copy(n.digits, n.digits + len, digits);
    return *this;
}

BigInt &BigInt::operator =(BigInt &&n) {
    std::cout << "Move operator=" << std::endl;
    if (this == &n) {
        return *this;
    }
    neg = std::move(n.neg);
    len = std::move(n.len);
    digits = n.digits;
    n.digits = nullptr;
    n.neg = false;
    n.len = 0;
    return *this;
}


BigInt BigInt::operator -() const {
    BigInt tmp(*this);
    tmp.neg = !neg;
    if (tmp.digits[tmp.len - 1] == 0) {
        tmp.neg = false;
    }
    return tmp;
}
    
    
/* BigInt & BigInt operations */
BigInt &BigInt::operator +=(const BigInt &n) {
    if (neg ^ n.neg) {
        *this -= -n;
        return *this;
    }
    
    uint64_t *short_ptr{digits}, *long_ptr{n.digits};
    size_t short_len{len}, long_len{n.len};
    if (short_len > long_len) {
        std::swap(short_len, long_len);
        std::swap(short_ptr, long_ptr);
    }
    uint64_t *tmp = new uint64_t[long_len + 1];
    uint64_t over_flag = 0;
    for (size_t i = 0; i < short_len; ++i) {
        tmp[i] = short_ptr[i] + long_ptr[i] + over_flag;
        if (tmp[i] >= BASE) {
            tmp[i] -= BASE;
            over_flag = 1;
        } else {
            over_flag = 0;
        }
        for (size_t j = 0; j < i; ++ j) {
            //std::cout << "TMP[" << j << "] = " << tmp[j] << std::endl;
        }
    }
    for (size_t i = short_len; i < long_len; ++i) {
        tmp[i] = long_ptr[i] + over_flag;
        for (size_t j = 0; j < i; ++ j) {
            //std::cout << "TMP[" << j << "] = " << tmp[j] << std::endl;
        }
        if (tmp[i] >= BASE) {
            tmp[i] -= BASE;
            over_flag = 1;
        } else {
            over_flag = 0;
            break;
        }
        
    }
    len = long_len;
    if (over_flag == 1) {
        tmp[long_len] = 1;
        ++len;
    }
    delete[] digits;
    digits = tmp;
    return *this;
}

BigInt &BigInt::operator -=(const BigInt &n) {
    if (neg ^ n.neg) {
        *this += -n;
        return *this;
    }
    uint64_t *short_ptr{digits}, *long_ptr{n.digits};
    size_t short_len{len}, long_len{n.len};
    if ((*this >= n) ^ neg) {
        neg = false;
        std::swap(short_len, long_len);
        std::swap(short_ptr, long_ptr);
    } else {
        neg = true;
    }
    //std::cout << long_ptr[0] << "   " << short_ptr[0] << std::endl;
    
    /* We consider [long] - [short] */
    uint64_t *tmp = new uint64_t[long_len];
    uint64_t over_flag = 0;
    for (size_t i = 0; i < short_len; ++i) {
        if (long_ptr[i] >= over_flag + short_ptr[i]) {
            tmp[i] = long_ptr[i];
            tmp[i] -= over_flag + short_ptr[i];
            over_flag = 0;
        } else {
            tmp[i] = long_ptr[i] + BASE;
            tmp[i] -= over_flag + short_ptr[i];
            over_flag = 1;
        }        
    }
    for (size_t i = short_len; i < long_len; ++i) {
        if (long_ptr[i] < over_flag) {
            tmp[i] = long_ptr[i] + BASE - over_flag;
            over_flag = 1;
            //std::cout << i << "  " << tmp[i] << std::endl;
        } else {
            tmp[i] = long_ptr[i] - over_flag;
            over_flag = 0;
            //std::cout << i << "  " << tmp[i] << std::endl;
            break;
        }   
    }
    int new_len = long_len - 1;
    for (; new_len >= 0 && tmp[new_len] == 0; --new_len) {}
    if (new_len < 0) {  /* Result is zero */
        len = 1;
        neg = false;
    } else {
        len = new_len + 1;
    }
    //std::cout << len << std::endl;
    uint64_t *tmp2 = new uint64_t[len];
    std::copy(tmp, tmp + len, tmp2);
    delete[] tmp;
    delete[] digits;
    digits = tmp2;
    return *this;
}

BigInt &BigInt::operator *=(const BigInt &n) {
    int new_len = len + n.len;
    uint64_t *res = new uint64_t[new_len];
    memset(res, 0, new_len * sizeof(res[0]));
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < n.len; ++j) {
            res[i + j] += digits[i] * n.digits[j];
            if (res[i + j] >= BASE) {
                res[i + j + 1] += res[i + j] / BASE;
                res[i + j] %= BASE;
            }
        }
    }
    neg = neg ^ n.neg;
    for (--new_len; new_len >= 0 && res[new_len] == 0; --new_len) {}
    if (new_len < 0) {  /* Result is zero */
        len = 1;
        delete[] res;
        res = new uint64_t[1];
        res[0] = 0;
        neg = false;
    } else {
        len = new_len + 1;
    }
    //std::cout << "LEN: " << len << std::endl;
    delete[] digits;
    digits = res;
    return *this;
}


/* Output */
std::ostream &operator <<(std::ostream &out, const BigInt &n) {
    if (n.neg) {
    out << '-';
    }
    out << n.digits[n.len - 1];
    char old_fill;
    size_t old_width;
    old_width = out.width();
    old_fill = out.fill();
    for (int l = (int)n.len - 2; l >= 0; --l) {
        out.width(BASE_LEN);
        out.fill('0');
        out << n.digits[l];
    }
    out.width(old_width);
    out.fill(old_fill);
    return out;
}


/* BigInt comparisons */
bool operator ==(const BigInt &a, const BigInt &b) {
    if (a.neg != b.neg && a.len != b.len) {
        return false;
    }
    for (size_t i = 0; i < a.len; ++i) {
        if (a.digits[i] != b.digits[i]) {
            return false;
        }
    }
    return true;
}

bool operator <(const BigInt &a, const BigInt &b) {
    if (a.neg ^ b.neg) {  /* a and b have different signs */
        return a.neg;
    }
    if (a.neg) {
        if (a.len != b.len) {
            return a.len > b.len;
        }
        for (int l = a.len - 1; l >= 0; --l) {
            if (a.digits[l] != b.digits[l]) {
                return a.digits[l] > b.digits[l];
            }
        }
        return false;
    } else {
        if (a.len != b.len) {
            return a.len < b.len;
        }
        for (int l = a.len - 1; l >= 0; --l) {
            if (a.digits[l] != b.digits[l]) {
                return a.digits[l] < b.digits[l];
            }
        }
        return false;
    }
}

bool operator <=(const BigInt &a, const BigInt &b) {
    if (a.neg ^ b.neg) {  /* a and b have different signs */
        return a.neg;
    }
    if (a.neg) {
        if (a.len != b.len) {
            return a.len > b.len;
        }
        for (int l = a.len - 1; l >= 0; --l) {
            if (a.digits[l] != b.digits[l]) {
                return a.digits[l] > b.digits[l];
            }
            
        }
        return true;
    } else {
        if (a.len != b.len) {
            return a.len < b.len;
        }
        for (int l = a.len - 1; l >= 0; --l) {
            if (a.digits[l] != b.digits[l]) {
                return a.digits[l] < b.digits[l];
            }
        }
        return true;
    }
}

bool operator !=(const BigInt &a, const BigInt &b) {
    return !(a == b);
}

bool operator >(const BigInt &a, const BigInt &b) {
    return b < a;
}

bool operator >=(const BigInt &a, const BigInt &b) {
    return b <= a;
}


/* Binary operations */
BigInt operator +(const BigInt &a, const BigInt &b) {
    return BigInt(a) += b;
}

BigInt operator -(const BigInt &a, const BigInt &b) {
    return BigInt(a) -= b;
}

BigInt operator *(const BigInt &a, const BigInt &b) {
    return BigInt(a) *= b;
}

