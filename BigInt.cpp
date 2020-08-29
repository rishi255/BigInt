/*
BigInt.cpp - C++
Author - Rishikesh Rachchh
*/
#include <iostream>
#include <vector>
#include "BigInt.h"
using namespace std;

// ************ BigInt :: ALL CONSTRUCTORS  ***************

BigInt::BigInt (const string& str) : sign(1), n() 
{
    string res(str);

    if(res[0] == '-') { res.erase(0, 1); sign = -1; }

    int i = 0;
    while(res[i] == '0') ++i; // count number of preceding zeros

    if(i>0) res.erase(0,i); // trim preceding zeros

    if(res.size() == 0) {sign = 0; return;}

    n.assign(res.rbegin(), res.rend());
}

// ************ BigInt :: OPERATOR OVERLOADS ***************
BigInt BigInt::operator + (const BigInt &b) const
// appropriately decides add/sub result considering sign of operands
{
    if(sign == 0) return b;
    if(b.sign == 0) return *this;

    BigInt sum;
    string s1, s2, max, min;
    s1.assign(n.rbegin(), n.rend());
    s2.assign(b.n.rbegin(), b.n.rend());
    max = !lt(s1, s2) ? s1 : s2;     
    min = lt(s1, s2) ? s1 : s2;

    if(sign != b.sign)
    {
        if(n == b.n)    // result zero
        {
            sum.n = "";
            sum.sign = 0;
        }
        else
        {
            sum.n = sub(max, min);  // passing non reversed strings
            if(*this < b)
                sum.sign = b.sign;
            else 
                sum.sign = sign;
        }
    }
    else    // same sign, pure "add" only needed
    {
        sum.n = add(max, min);
        sum.sign = sign;
    }
    return sum;
}


// appropriately decides whether to add/sub result considering sign of operands
BigInt BigInt::operator - (BigInt const &b) const
{
    if(sign == 0) return b;
    if(b.sign == 0) return *this;
    
    BigInt diff; 
    bool revm;
    if(*this == b)
    {
        diff.sign = 0;
        diff.n = "";
        return diff;
    }

    string s1, s2, max, min;
    s1.assign(n.rbegin(), n.rend());
    s2.assign(b.n.rbegin(), b.n.rend());
    max = !lt(s1, s2) ? s1 : s2;     
    min = lt(s1, s2) ? s1 : s2;
        
    if(sign == b.sign)
    {
        diff.n = sub(max, min);
        diff.sign = !(lt(s1, s2)) ? sign : sign*-1;
        return diff;
    }

    // if it reaches this point, signs are unequal

    if(*this < b) diff.sign = -1;
    else diff.sign = 1;

    diff.n = add(max, min);

    if(max == min)        // if max and min are equal, 
        diff.sign = 0;    //  -> make diff.sign = 0
    
    return diff;
}

BigInt BigInt::operator * (BigInt const &b) const
{
    BigInt prod;
    if(sign == 0 || b.sign == 0) 
    {
        prod.sign = 0; 
        prod.n = ""; 
        return prod;
    }
    string max = (n.compare(b.n) < 0) ? b.n : n;
    string min = (n.compare(b.n) < 0) ? n : b.n;

    prod.n = mul(max, min);
    prod.sign = sign * b.sign;
    return prod;
}

BigInt BigInt::operator = (const BigInt &b)
{
    n = b.n; sign = b.sign;
    return *this;
}

// ************ BigInt :: ALL OTHER METHODS  *************** 

std::ostream& operator <<(std::ostream &o, const BigInt &b)
{
    if(b.sign == -1)      { o << "-"; }
    else if(b.sign == 0)  { o << "0"; return o;}
    string s; 
    s.assign(b.n.rbegin(), b.n.rend()); 
    o << s;
    return o; 
}

std::istream& operator >>(std::istream &in, BigInt &b)
{
    in >> b.n;
    
    if(b.n[0] == '-') 
    {
        b.sign = -1;
        b.n.erase(0,1);
    }
    else if (b.n.find_first_not_of("0") == string::npos) // means if all chars in string are zero
    {
        b.sign = 0; 
        b.n = "";
    }
    else b.sign = +1;

    int i = 0;
    while(b.n[i] == '0') i++;
//    cout <<"Before : " << b.n;
    b.n.erase(0, i);
//    cout <<"After :"<<b.n;

    /// reverse string (least significant digits stored first)
    b.n.assign(b.n.rbegin(), b.n.rend());
    return in;
}

bool BigInt::operator< (const BigInt &b) const
{
    if(sign == 0 || b.sign == 0)   
        return (sign < b.sign) ? true : false;
    else
    {
        if(sign == b.sign)
            return (sign == 1) ? lt(n, b.n) : !lt(n, b.n);
        else
            return (sign < b.sign) ? true : false;
    }
}

// ************ FUNCTIONS OUTSIDE BigInt ***************

bool lt (const string& s1, const string& s2)
{ return (s1.compare(s2) < 0 ? true : false); }

// This is called by operator overloads "+" and "-" of class BigInt and returns result string = |n1| + |n2|
string add(const string& n1, const string& n2)
{
    string s1, s2;
    string min = n2;
    string max = n1;
    max.assign(max.rbegin(), max.rend());
    min.assign(min.rbegin(), min.rend());
    
    int minsize = min.size();
    int maxsize = max.size();

    string res;
    int carry = 0, j = 0;
    for(j=0; j<minsize; j++)
    {
        int sum = carry + (max[j]-'0') + (min[j]-'0');
        carry = sum/10;
        res.push_back(sum%10+'0');
    }
    for(j=minsize; j<maxsize; j++)
    {
        int sum = carry + max[j]-'0';
        carry = sum/10;
        res.push_back(sum%10+'0' );
    }
    if(carry) res.push_back(carry+'0');

    return res;
}

// This is called by operator overloads "+" and "-" of class BigInt and returns result string = |n1| - |n2|
string sub(const string& n1, const string &n2)
{
    string min = n1;
    string max = n2;
    
    max.assign(max.rbegin(), max.rend()); //cout << "MAX: " << max;
    min.assign(min.rbegin(), min.rend()); //cout << "MIN: " << min;
    int minsize = min.size();
    int maxsize = max.size();

    string diff;
    diff.reserve(maxsize);
    int i = 0, borrow = 0;
    for(i = 0; i < minsize; i++)
    {
        int sub = ((max[i]-'0') - (min[i]-'0') - borrow);
        if(sub < 0)
        {
            borrow = 1;
            sub = sub + 10;
        }
        else
            borrow = 0;    
        diff.push_back(sub + '0');
    }
    for(i = minsize; i < maxsize; i++)
    {
        int sub = ((max[i] - '0') - borrow); 
        if(sub < 0)
        {
            borrow = 1;
            sub = sub + 10;
        }
        else
            borrow = 0;
        
        diff.push_back(sub + '0');
    }
    return diff;
}

// This is called by operator overload "*" of class BigInt and returns result string = |n1| * |n2|
string mul(const string& n1, const string &n2)
{
    string prod;
    int i_n1 = 0, i_n2 = 0, carry = 0;
    vector<int> result(n1.size() + n2.size(), 0);

    for(int i = 0; i < n1.size(); i++)
    {
        carry = 0;
        int d1 = n1[i] - '0';

        i_n2 = 0;

        for(int j = 0; j < n2.size(); j++)
        {
            int d2 = n2[j] - '0';
            int sum = (d1*d2) + result[i_n1 + i_n2] + carry;

            carry = sum/10;
            result[i_n1 + i_n2] = sum%10;
            i_n2++;
        }
        if (carry > 0) 
            result[i_n1 + i_n2] += carry; 
        i_n1++;
    }

    int i = result.size() - 1; 
    while (i>=0 && result[i] == 0) 
    i--;  
    
    while (i >= 0) 
        prod += std::to_string(result[i--]); 

    prod.assign(prod.rbegin(), prod.rend());
    return prod; 
}