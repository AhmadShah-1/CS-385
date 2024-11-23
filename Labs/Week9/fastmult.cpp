/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Syed Ahmad Shah
 * Version     : 1.0
 * Date        : 11/16/2024
 * Description : Karatsuba Algorithm for Multiplication of Large Integers
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor system
 ******************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

string add(const string &a, const string &b) {
    string result;
    int carry = 0, sum = 0;
    int n1 = a.size(), n2 = b.size();
    int i = n1 - 1, j = n2 - 1;

    while (i >= 0 || j >= 0 || carry > 0) {
        int digitA = 0;
        if (i >= 0) {
            digitA = a[i] - '0';
            i--;
        }
        int digitB = 0;
        if (j >= 0) {
            digitB = b[j] - '0';
            j--;
        }
        sum = digitA + digitB + carry;
        carry = sum / 10;
        result.push_back((sum % 10) + '0');
    }

    reverse(result.begin(), result.end());
    return result;
}

string subtract(const string &a, const string &b) {
    string result;
    int borrow = 0, diff = 0;
    int n1 = a.size(), n2 = b.size();
    int i = n1 - 1, j = n2 - 1;

    while (i >= 0) {
        int digitA = a[i--] - '0';
        int digitB = 0;
        if (j >= 0) {
            digitB = b[j--] - '0';
        }
        diff = digitA - digitB - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.push_back(diff + '0');
    }

    reverse(result.begin(), result.end());
    size_t startPos = 0;
    while (startPos < result.size() && result[startPos] == '0') {
        ++startPos;
    }

    if (startPos == string::npos) {
        return "0";
    } else {
        return result.substr(startPos);
    }
}

string singleDigitMultiply(const char a, const char b) {
    int product = (a - '0') * (b - '0');
    return to_string(product);
}

string karatsuba(const string &x, const string &y) {
    if (x.empty() || y.empty()) {
        return "0";
    }

    if (x.size() == 1 && y.size() == 1) {
        return singleDigitMultiply(x[0], y[0]);
    }

    int n = max(x.size(), y.size());
    int m = (n + 1) / 2;

    string x1 = x.substr(0, max(0, (int)x.size() - m));
    string x0 = x.substr(max(0, (int)x.size() - m));
    string y1 = y.substr(0, max(0, (int)y.size() - m));
    string y0 = y.substr(max(0, (int)y.size() - m));

    string z2 = karatsuba(x1, y1);
    string z0 = karatsuba(x0, y0);
    string z1 = karatsuba(add(x1, x0), add(y1, y0));
    z1 = subtract(subtract(z1, z2), z0);

    for (int i = 0; i < 2 * m; i++) {
        z2 += '0';
    }
    for (int i = 0; i < m; i++) {
        z1 += '0';
    }
    return add(add(z2, z1), z0);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <num1> <num2>" << endl;
        return 1;
    }
    string a = argv[1];
    string b = argv[2];

    size_t maxLen = max(a.size(), b.size());
    size_t nextPowerOf2 = 1;
    while (nextPowerOf2 < maxLen) nextPowerOf2 *= 2;
    while (a.size() < nextPowerOf2) a = "0" + a;
    while (b.size() < nextPowerOf2) b = "0" + b;

    string result = karatsuba(a, b);

    if (result.empty()) {
        cout << "0" << endl;
    } else {
        size_t startPos = 0;
        while (startPos < result.size() && result[startPos] == '0') {
            ++startPos;
        }
        if (startPos == result.size()) {
            cout << "0" << endl;
        } else {
            cout << result.substr(startPos) << endl;
        }
    }

    return 0;
}
