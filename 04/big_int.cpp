#include "big_int.h"
#include <cstddef>
#include <cstring>
#include <exception>
#include <sstream>
#include <iostream>
#include <iomanip>


/* BigInt constructors, copy and move, destructor */
BigInt::BigInt(const int64_t n) {
    if (n < 0) {
        neg_ = true;
    }
    digits_ = new uint64_t[1];
    digits_[0] = neg_ ? -n : n;
}

BigInt::BigInt(const std::string &s) {
    auto it1 = s.cbegin();
    for (; it1 != s.cend() && isspace(*it1); ++it1) {}
    if (*it1 == '-' || *it1 == '+') {
        neg_ = *it1 == '-';
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
            digits_ = new uint64_t[1];
            digits_[0] = 0;
            neg_ = false;
            len_ = 1;
        } else {
            throw std::logic_error("Invalid string to interpret as a number");
        }
    } else {
        len_ = (s_len + BASE_LEN - 1) / BASE_LEN;
        size_t head = s_len % BASE_LEN;
        digits_ = new uint64_t[len_];
        size_t idx = 0;
        if (head > 0) {
            std::string tmp(s_norm.cbegin(), s_norm.cbegin() + head);
            digits_[len_ - 1] = std::stoull(tmp);
            ++idx;
        }
        it1 = s_norm.cbegin() + head;
        for (; it1 != s_norm.cend() ; it1 += BASE_LEN, ++idx) {
            digits_[len_ - 1 - idx] = std::stoull(std::string(it1, it1 + BASE_LEN));
        }
    }
}


BigInt::BigInt(const BigInt &n) : neg_{n.neg_}, len_{n.len_} {
    digits_ = new uint64_t[len_];
    std::copy(n.digits_, n.digits_ + len_, digits_);
}

BigInt::BigInt(BigInt &&n) : neg_{std::move(n.neg_)}, len_{std::move(n.len_)}{
    digits_ = n.digits_;
    n.digits_ = nullptr;
    n.neg_ = false;
    n.len_ = 0;
}
    
BigInt::~BigInt() {
    delete[] digits_;
}
    

BigInt &BigInt::operator =(const BigInt &n) {
    if (this == &n) {
        return *this;
    }
    if (len_ != n.len_) {
        uint64_t *tmp = new uint64_t[n.len_];
        delete[] digits_;
        digits_ = tmp;
    }
    len_ = n.len_;
    neg_ = n.neg_;
    std::copy(n.digits_, n.digits_ + len_, digits_);
    return *this;
}

BigInt &BigInt::operator =(BigInt &&n) {
    if (this == &n) {
        return *this;
    }
    neg_ = std::move(n.neg_);
    len_ = std::move(n.len_);
    digits_ = n.digits_;
    n.digits_ = nullptr;
    n.neg_ = false;
    n.len_ = 0;
    return *this;
}
    
    
/* BigInt & BigInt operations */
BigInt &BigInt::operator +=(const BigInt &n) {
    if (neg_ ^ n.neg_) {
        *this -= -n;
        return *this;
    }
    
    uint64_t *short_ptr{digits_}, *long_ptr{n.digits_};
    size_t short_len{len_}, long_len{n.len_};
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
    }
    for (size_t i = short_len; i < long_len; ++i) {
        tmp[i] = long_ptr[i] + over_flag;
        if (tmp[i] >= BASE) {
            tmp[i] -= BASE;
            over_flag = 1;
        } else {
            over_flag = 0;
            break;
        }
        
    }
    len_ = long_len;
    if (over_flag == 1) {
        tmp[long_len] = 1;
        ++len_;
    }
    delete[] digits_;
    digits_ = tmp;
    return *this;
}

BigInt &BigInt::operator -=(const BigInt &n) {
    if (neg_ ^ n.neg_) {
        *this += -n;
        return *this;
    }
    uint64_t *short_ptr{digits_}, *long_ptr{n.digits_};
    size_t short_len{len_}, long_len{n.len_};
    if ((*this >= n) ^ neg_) {
        neg_ = false;
        std::swap(short_len, long_len);
        std::swap(short_ptr, long_ptr);
    } else {
        neg_ = true;
    }    
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
        } else {
            tmp[i] = long_ptr[i] - over_flag;
            over_flag = 0;
            break;
        }   
    }
    int new_len = long_len - 1;
    for (; new_len >= 0 && tmp[new_len] == 0; --new_len) {}
    if (new_len < 0) {  /* Result is zero */
        len_ = 1;
        neg_ = false;
    } else {
        len_ = new_len + 1;
    }
    uint64_t *tmp2 = new uint64_t[len_];
    std::copy(tmp, tmp + len_, tmp2);
    delete[] tmp;
    delete[] digits_;
    digits_ = tmp2;
    return *this;
}

BigInt &BigInt::operator *=(const BigInt &n) {
    int new_len = len_ + n.len_;
    uint64_t *res = new uint64_t[new_len];
    memset(res, 0, new_len * sizeof(res[0]));
    for (size_t i = 0; i < len_; ++i) {
        for (size_t j = 0; j < n.len_; ++j) {
            res[i + j] += digits_[i] * n.digits_[j];
            if (res[i + j] >= BASE) {
                res[i + j + 1] += res[i + j] / BASE;
                res[i + j] %= BASE;
            }
        }
    }
    for (--new_len; new_len >= 0 && res[new_len] == 0; --new_len) {}
    if (new_len < 0) {  /* Result is zero */
        len_ = 1;
        delete[] res;
        res = new uint64_t[1];
        res[0] = 0;
        neg_ = false;
    } else {
        len_ = new_len + 1;
    }
    delete[] digits_;
    digits_ = res;
    neg_ ^= n.neg_;
    return *this;
}


/* Unary minus */
BigInt BigInt::operator -() const {
    BigInt tmp(*this);
    tmp.neg_ = !neg_;
    if (tmp.digits_[tmp.len_ - 1] == 0) {
        tmp.neg_ = false;
    }
    return tmp;
}

/* Output */
std::ostream &operator <<(std::ostream &out, const BigInt &n) {
    if (n.neg_) {
    out << '-';
    }
    out << n.digits_[n.len_ - 1];
    char old_fill;
    size_t old_width;
    old_width = out.width();
    old_fill = out.fill();
    for (int l = (int)n.len_ - 2; l >= 0; --l) {
        out.width(BASE_LEN);
        out.fill('0');
        out << n.digits_[l];
    }
    out.width(old_width);
    out.fill(old_fill);
    return out;
}

std::string BigInt::to_string() const {
    std::ostringstream tmp;
    tmp << *this;
    return tmp.str();
}


/* BigInt comparisons */
bool operator ==(const BigInt &a, const BigInt &b) {
    if (a.neg_ != b.neg_ && a.len_ != b.len_) {
        return false;
    }
    for (size_t i = 0; i < a.len_; ++i) {
        if (a.digits_[i] != b.digits_[i]) {
            return false;
        }
    }
    return true;
}

bool operator <(const BigInt &a, const BigInt &b) {
    if (a.neg_ ^ b.neg_) {  /* a and b have different signs */
        return a.neg_;
    }
    if (a.neg_) {
        if (a.len_ != b.len_) {
            return a.len_ > b.len_;
        }
        for (int l = a.len_ - 1; l >= 0; --l) {
            if (a.digits_[l] != b.digits_[l]) {
                return a.digits_[l] > b.digits_[l];
            }
        }
        return false;
    } else {
        if (a.len_ != b.len_) {
            return a.len_ < b.len_;
        }
        for (int l = a.len_ - 1; l >= 0; --l) {
            if (a.digits_[l] != b.digits_[l]) {
                return a.digits_[l] < b.digits_[l];
            }
        }
        return false;
    }
}

bool operator <=(const BigInt &a, const BigInt &b) {
    if (a.neg_ ^ b.neg_) {  /* a and b have different signs */
        return a.neg_;
    }
    if (a.neg_) {
        if (a.len_ != b.len_) {
            return a.len_ > b.len_;
        }
        for (int l = a.len_ - 1; l >= 0; --l) {
            if (a.digits_[l] != b.digits_[l]) {
                return a.digits_[l] > b.digits_[l];
            }
            
        }
        return true;
    } else {
        if (a.len_ != b.len_) {
            return a.len_ < b.len_;
        }
        for (int l = a.len_ - 1; l >= 0; --l) {
            if (a.digits_[l] != b.digits_[l]) {
                return a.digits_[l] < b.digits_[l];
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

