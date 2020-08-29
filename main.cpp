/*
BigInt/main.cpp - C++
Author - Rishikesh Rachchh
*/
#include <iostream>
#include "BigInt.h"
using namespace std;

void menu();

int main()
{
    menu();
    return 0;
}

void menu()
{
    BigInt a, b, res;
    int n; char ch = 'y';
    do{
        cout << "~~~~~~~~~MENU~~~~~~~~~\n1. Add\n2. Subtract";
        cout << "\n3. Multiply\nEnter a choice: ";
        cin >> n;
        switch (n)
        {
        case 1:
            cout << "Enter BigInts a and b: ";
            cin >> a;
            cin >> b;
            res = a + b;
            cout << "a + b = " << res << endl;
            break;
        case 2:
            cout << "Enter BigInts a and b: ";
            cin >> a;
            cin >> b;
            res = a - b;
            cout << "a - b = " << res << endl;
            break;
        case 3:
            cout << "Enter BigInts a and b: ";
            cin >> a;
            cin >> b;
            res = a * b;
            cout << "a * b = " << res << endl;
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
        cout << "Do you want to continue? [y/n]: ";
        cin >> ch;
    }while(ch == 'y');
}