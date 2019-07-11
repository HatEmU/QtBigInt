//#
//# Copyright (C) 2018-2019 QuasarApp.
//# Distributed under the lgplv3 software license, see the accompanying
//# Everyone is permitted to copy and distribute verbatim copies
//# of this license document, but changing it is not allowed.
//#

#include "bigint.h"
#include <limits>

// constructors
BigInt::BigInt() {
    mpz_init(data);
}

BigInt::BigInt(const BigInt &val):
    BigInt() {
    mpz_set(data, val.data);
}

BigInt::BigInt(long long val):
    BigInt() {
    mpz_set_si(data, static_cast<int>(val >> 32));          /* n = (int)sll >> 32 */
    mpz_mul_2exp(data, data, 32 );                          /* n <<= 32 */
    mpz_add_ui(data, data, static_cast<unsigned int>(val)); /* n += (unsigned int)sll */
}

BigInt::BigInt(unsigned long long val):
    BigInt() {
    mpz_set_ui(data, static_cast<unsigned int>(val >> 32));          /* n = (int)sll >> 32 */
    mpz_mul_2exp(data, data, 32 );                          /* n <<= 32 */
    mpz_add_ui(data, data, static_cast<unsigned int>(val)); /* n += (unsigned int)sll */
}

BigInt::BigInt(const char *str, int base):
    BigInt() {

    mpz_set_str(data, str, base);
}

BigInt::BigInt(std::string imput, int base):
    BigInt(imput.c_str(), base) {
}

BigInt::BigInt(int val):
    BigInt() {
    mpz_set_si(data, val);
}

BigInt::BigInt(unsigned int val):
    BigInt() {
    mpz_set_ui(data, val);
}

BigInt::BigInt(double val):
    BigInt() {
    mpz_set_d(data, val);
}

std::string BigInt::getString(int base) const {
    char *str = mpz_get_str(nullptr, base, data);
    return str;
}

BigInt::~BigInt() {
    mpz_clear(data);
}

BigInt &BigInt::powm(const BigInt &pow, const BigInt &mod) {
    mpz_powm(data, data, pow.data, mod.data);
    return *this;
}

BigInt &BigInt::pow(unsigned int pow) {
    mpz_pow_ui(data, data, pow);
    return *this;
}

int BigInt::sizeBits() const {
    return sizeBytes() * 8;
}

int BigInt::sizeBytes() const {
    return static_cast<int>(mpz_size(data) * sizeof ((*data->_mp_d)));
}

BigInt BigInt::bigPow10(unsigned int pow) {
    return "1" + std::string(pow, '0');
}


BigInt &BigInt::operator =(const BigInt &val) {
    mpz_set(data, val.data);
    return *this;
}

//  add operators
BigInt operator +(BigInt left, unsigned int right) {
    mpz_add_ui(left.data, left.data, right);
    return left;
}

BigInt operator +(BigInt left, int right) {
    if (right >= 0) {
        return left + static_cast<unsigned int>(right);
    }

    return left - static_cast<unsigned int>(std::abs(right));
}

BigInt operator +(BigInt left, const BigInt &right) {
    mpz_add(left.data, left.data, right.data);
    return left;
}

BigInt& operator +=(BigInt &left, unsigned int right) {
    mpz_add_ui(left.data, left.data, right);
    return left;
}

BigInt& operator +=(BigInt &left, int right) {
    if (right >= 0) {
        return left += static_cast<unsigned int>(right);
    }
    return left -= static_cast<unsigned int>(std::abs(right));
}

BigInt& operator +=(BigInt &left, const BigInt &right) {
    mpz_add(left.data, left.data, right.data);
    return left;
}

//  sub operators

BigInt operator -(BigInt left, const BigInt &right) {
    mpz_sub(left.data, left.data, right.data);
    return left;
}

BigInt operator -(BigInt left, unsigned int right) {
    mpz_sub_ui(left.data, left.data, right);
    return left;
}

BigInt operator -(unsigned int left, BigInt right) {
    mpz_ui_sub(right.data, left, right.data);
    return right;
}

BigInt operator -(BigInt left, int right) {
    if (right >= 0) {
        return left - static_cast<unsigned int>(right);
    }
    return left + static_cast<unsigned int>(std::abs(right));
}

BigInt operator -(int left, BigInt right) {
    if (right >= 0) {
        return static_cast<unsigned int>(left) - right;
    }
    return right + static_cast<unsigned int>(std::abs(left));
}

BigInt operator-(BigInt val) {
    mpz_neg(val.data, val.data);
    return val;
}


BigInt& operator -=(BigInt &left, const BigInt &right) {
    mpz_sub(left.data, left.data, right.data);
    return left;
}

BigInt& operator -=(BigInt &left, unsigned int right) {
    mpz_sub_ui(left.data, left.data, right);
    return left;
}

BigInt& operator -=(BigInt &left, int right) {
    if (right >= 0) {
        return left -= static_cast<unsigned int>(right);
    }
    return left += static_cast<unsigned int>(std::abs(right));
}

BigInt& operator -=(int left, BigInt & right) {
    if (left >= 0) {
        return static_cast<unsigned int>(left) -= right;
    }

    return right =  right + static_cast<unsigned int>(std::abs(left));
}

BigInt& operator -=(unsigned int left, BigInt & right) {
    return right = left - right;
}

//  div operators

BigInt operator /(BigInt left, const BigInt &right) {
    mpz_tdiv_q(left.data, left.data, right.data);
    return left;
}

BigInt operator /(BigInt left, unsigned int right) {
    mpz_tdiv_q_ui(left.data, left.data, right);
    return left;
}

BigInt operator /(BigInt left, int right) {
    if (right >= 0) {
        return left / static_cast<unsigned int>(right);
    }
    return 0 - (left / static_cast<unsigned int>(std::abs(right)));
}

BigInt& operator /=(BigInt &left, const BigInt &right) {
    mpz_tdiv_q(left.data, left.data, right.data);
    return left;
}

BigInt& operator /=(BigInt &left, unsigned int right) {
    mpz_tdiv_q_ui(left.data, left.data, right);
    return left;
}

BigInt& operator /=(BigInt &left, int right) {
    if (right >= 0) {
        return left /= static_cast<unsigned int>(right);
    }
    return 0 -= (left /= static_cast<unsigned int>(std::abs(right)));
}

// mul operators



BigInt operator *(BigInt left, const BigInt &right) {
    mpz_mul(left.data, left.data, right.data);
    return left;
}

BigInt operator *(BigInt left, int right) {
    if (right >= 0) {
        return left * static_cast<unsigned int>(right);
    }
    return 0 - (left * static_cast<unsigned int>(std::abs(right)));
}

BigInt operator *(BigInt left, unsigned int right) {
    mpz_mul_ui(left.data, left.data, right);
    return left;
}

BigInt& operator *=(BigInt &left, const BigInt &right) {
    mpz_mul(left.data, left.data, right.data);
    return left;
}

BigInt& operator *=(BigInt &left, int right) {
    if (right >= 0) {
        return left *= static_cast<unsigned int>(right);
    }
    return 0 -= (left *= static_cast<unsigned int>(std::abs(right)));
}

BigInt& operator *=(BigInt &left, unsigned int right) {
    mpz_mul_ui(left.data, left.data, right);
    return left;
}

//mod operations
BigInt operator %(BigInt left, const BigInt &right) {
    mpz_tdiv_r(left.data, left.data, right.data);
    return left;
}

BigInt operator %(BigInt left, unsigned int right) {
    mpz_tdiv_r_ui(left.data, left.data, right);
    return left;
}

BigInt operator %(BigInt left, int right) {
    return left % static_cast<unsigned int>(std::abs(right));
}

BigInt& operator %=(BigInt& left, const BigInt &right) {
    mpz_tdiv_r(left.data, left.data, right.data);
    return left;
}

BigInt& operator %=(BigInt& left, unsigned int right) {
    mpz_tdiv_r_ui(left.data, left.data, right);
    return left;
}

BigInt& operator %=(BigInt& left, int right) {
    return left %= static_cast<unsigned int>(std::abs(right));
}


// incriment and dicriment
BigInt &BigInt::operator--() {
    *this -= 1;
    return *this;
}

BigInt &BigInt::operator++() {
    *this += 1;
    return *this;
}

BigInt BigInt::operator--(int) {
    BigInt temp(*this);
    --*this;
    return temp;
}

BigInt BigInt::operator++(int) {
    BigInt temp(*this);
    ++*this;
    return temp;
}

// move operators

BigInt operator >>(BigInt left, unsigned int right) {
    mpn_rshift(left.data->_mp_d,
               left.data->_mp_d,
               left.data->_mp_size,
               right);
    return left;
}

BigInt operator <<(BigInt left, unsigned int right) {
    mpn_lshift(left.data->_mp_d,
               left.data->_mp_d,
               left.data->_mp_size,
               static_cast<unsigned int>(right));
    return left;
}

BigInt& operator >>=(BigInt &left, unsigned int right) {
    mpn_rshift(left.data->_mp_d,
               left.data->_mp_d,
               left.data->_mp_size,
               static_cast<unsigned int>(right));
    return left;
}

BigInt& operator <<=(BigInt &left, unsigned int right) {
    mpn_lshift(left.data->_mp_d,
               left.data->_mp_d,
               left.data->_mp_size,
               static_cast<unsigned int>(right));
    return left;
}


BigInt operator >>(BigInt left, int right) {
    if (right >= 0) {
        return left >> static_cast<unsigned int> (right);
    }

    return left << static_cast<unsigned int>(std::abs(right));
}

BigInt operator <<(BigInt left, int right) {
    if (right >= 0) {
        return left << static_cast<unsigned int> (right);
    }

    return left >> static_cast<unsigned int>(std::abs(right));
}

BigInt& operator >>=(BigInt &left, int right) {
    if (right >= 0) {
        return left >>= static_cast<unsigned int>(right);
    }

    return left <<= static_cast<unsigned int>(std::abs(right));
}

BigInt& operator <<=(BigInt &left, int right) {
    if (right >= 0) {
        return left <<= static_cast<unsigned int>(right);
    }

    return left >>= static_cast<unsigned int>(std::abs(right));
}

// other bin operators
BigInt operator ~(BigInt left) {
    mpz_com(left.data, left.data);
    return left;
}

BigInt operator |(BigInt left, const BigInt &right) {
    mpz_ior(left.data, left.data, right.data);
    return left;
}

BigInt operator |(const BigInt &left, int right) {
    return left | BigInt(right);
}

BigInt operator |(const BigInt &left, unsigned int right) {
    return left | BigInt(right);
}

BigInt& operator |=(BigInt &left, const BigInt &right) {
    mpz_ior(left.data, left.data, right.data);
    return left;
}

BigInt& operator |=(BigInt &left, int right) {
    return left |= BigInt(right);
}

BigInt& operator |=(BigInt &left, unsigned int right) {
    return left |= BigInt(right);
}

BigInt operator &(BigInt left, const BigInt &right) {
    mpz_and(left.data, left.data, right.data);
    return left;
}

BigInt operator &(const BigInt &left, int right) {
    return left & BigInt(right);
}

BigInt operator &(const BigInt &left, unsigned int right) {
    return left & BigInt(right);
}

BigInt& operator &=(BigInt &left, const BigInt &right) {
    mpz_and(left.data, left.data, right.data);
    return left;
}

BigInt& operator &=(BigInt &left, int right) {
    return left &= BigInt(right);
}

BigInt& operator &=(BigInt &left, unsigned int right) {
    return left &= BigInt(right);
}

BigInt operator ^(BigInt left, const BigInt &right) {
    mpz_xor(left.data, left.data, right.data);
    return left;
}

BigInt operator ^(const BigInt &left, int right) {
    return left ^ BigInt(right);
}

BigInt operator ^(const BigInt &left, unsigned int right) {
    return left ^ BigInt(right);
}

BigInt& operator ^=(BigInt &left, const BigInt &right) {
    mpz_xor(left.data, left.data, right.data);
    return left;
}

BigInt& operator ^=(BigInt &left, int right) {
    return left ^= BigInt(right);
}

BigInt& operator ^=(BigInt &left, unsigned int right) {
    return left ^= BigInt(right);
}


// logic operators

bool operator!(const BigInt &val) {
    return val == 0;
}

bool operator == (const BigInt& left, const BigInt& right) {
    return mpz_cmp(left.data, right.data) == 0;
}

bool operator == (const BigInt& left, unsigned int right) {
    return mpz_cmp_ui(left.data, right) == 0;
}

bool operator == (const BigInt& left, int right) {
    return mpz_cmp_si(left.data, right) == 0;
}

bool operator != (const BigInt &left, const BigInt& right) {
    return !(left == right);
}

bool operator != (const BigInt &left, unsigned int right) {
    return !(left == right);
}

bool operator != (const BigInt &left, int right) {
    return !(left == right);
}

bool operator < ( const BigInt &left, const BigInt& right) {
    return mpz_cmp(left.data, right.data) < 0;
}

bool operator < ( const BigInt &left, unsigned int right) {
    return mpz_cmp_ui(left.data, right) < 0;
}

bool operator < ( const BigInt &left, int right) {
    return mpz_cmp_si(left.data, right) < 0;
}

bool operator > ( const BigInt &left, const BigInt& right) {
    return mpz_cmp(left.data, right.data) > 0;
}

bool operator > ( const BigInt &left, unsigned int right) {
    return mpz_cmp_ui(left.data, right) > 0;
}

bool operator > ( const BigInt &left, int right) {
    return mpz_cmp_si(left.data, right) > 0;
}


bool operator <= ( const BigInt &left, const BigInt& right) {
    return mpz_cmp(left.data, right.data) <= 0;
}

bool operator <= ( const BigInt &left, unsigned int right) {
    return mpz_cmp_ui(left.data, right) <= 0;
}

bool operator <= ( const BigInt &left, int right) {
    return mpz_cmp_si(left.data, right) <= 0;
}

bool operator >= ( const BigInt &left, const BigInt& right) {
    return mpz_cmp(left.data, right.data) >= 0;
}

bool operator >= ( const BigInt &left, unsigned int right) {
    return mpz_cmp_ui(left.data, right) >= 0;
}

bool operator >= ( const BigInt &left, int right) {
    return mpz_cmp_si(left.data, right) >= 0;
}

//// cast operations

//BigInt::operator bool() const {
//    return *this != 0;
//}
