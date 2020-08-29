/*
BigInt.h - C++
Author - Rishikesh Rachchh
*/
#ifndef BIGINT_H
#define BIGINT_H

#include <string>
#include <iostream>
using namespace std;

class BigInt
{
private:
    int sign;          // sign: can be -1, +1 or 0 (zero)
    std::string n;     // string that stores the BigInt in reverse (i.e. least significant digit of number is first in the string)

public:
    BigInt(): sign(0), n() {}
    BigInt(const string&);
    BigInt(long long);
    BigInt(int s, const string &str) : sign(s!=0), n(str) {}

    BigInt operator + (const BigInt &) const;
    BigInt operator - (const BigInt &) const;
    BigInt operator * (const BigInt &) const;
    BigInt operator / (const BigInt &) const;
    BigInt operator = (const BigInt &);
    friend std::ostream& operator<< (std::ostream &, const BigInt &);
    friend std::istream& operator>> (std::istream &, BigInt &);

    bool operator==(const BigInt &b) const {return sign == b.sign && n == b.n;}
    bool operator!=(const BigInt &b) const {return !(*this == b);}

    bool operator< (const BigInt &b) const;
    bool operator<=(const BigInt &b) const {return *this == b || *this < b;}
    bool operator> (const BigInt &b) const {return !(*this <= b);}
    bool operator>=(const BigInt &b) const {return !(*this < b);}

    BigInt      abs()               const {int a = (sign!=0) ? 1 : 0; return BigInt(a, n);}
    BigInt      reverseDigits()     const {std::string t; t.assign(n.rbegin(),n.rend()); return BigInt(sign, t);}
};

string longToString(long long num);
bool lt (const string&, const string&);
string add (const string &, const string &);
string sub (const string &, const string &);
string mul (const string &, const string &);
#endif /* BIGINT_H */