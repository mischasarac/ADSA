#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string add(string l1, string l2, string base);
string subtract(string l1, string l2, string base);
string multiplyBase(string l1, string l2, string base);
string karatsuba(string l1, string l2, string base);

int main() {
    string l1, l2, base;
    // Taking inputs
    cout << "Enter values for operations l1 l2 B" << endl;
    cin >> l1 >> l2 >> base;

    cout << "Addition: " << add(l1, l2, base) << endl;
    cout << "Subtraction: " << subtract(l1, l2, base) << endl;
    cout << "Karatsuba: " << karatsuba(l1, l2, base) << endl;

    return 0;
}

int matchSize(string &l1, string &l2) {
    // Matching sizes while one size is greater than another
    while (l1.size() < l2.size()) l1 = '0' + l1;
    while (l2.size() < l1.size()) l2 = '0' + l2;
    return l1.size();
}

string add(string l1, string l2, string base) {
    string result = "";
    // Picking smaller size for efficiency
    if (l1.size() < l2.size()) {
        swap(l1, l2);
    }

    int carry = 0;
    int diff = l1.size() - l2.size();
    int baseInt = stoi(base);

    for (int i = l1.size() - 1; i >= 0; i--) {
        int sum = l1[i] - '0' + carry;
        if (i - diff >= 0) {
            sum += l2[i - diff] - '0';
        }
        result += (sum % baseInt) + '0';
        carry = sum / baseInt;
    }

    if (carry > 0) {
        result += carry + '0';
    }

    reverse(result.begin(), result.end());
    return result;
}

string subtract(string l1, string l2, string base) {
    int len = matchSize(l1, l2);
    int baseInt = stoi(base);
    int borrow = 0;
    string res;

    for (int i = len - 1; i >= 0; i--) {
        int digit1 = l1[i] - '0' - borrow;
        int digit2 = l2[i] - '0';

        if (digit1 < digit2) {
            digit1 += baseInt;
            borrow = 1;
        } else {
            borrow = 0;
        }

        int diff = digit1 - digit2;
        res = to_string(diff) + res;
    }

    // Remove leading zeros
    while (res.size() > 1 && res[0] == '0') {
        res.erase(0, 1);
    }

    return res;
}

string multiplyBase(string l1, string l2, string base) {
    int baseInt = stoi(base);
    int num1 = stoi(l1);
    int num2 = stoi(l2);
    int result = num1 * num2;
    string res = "";

    // Convert result to the given base
    while (result > 0) {
        res = char((result % baseInt) + '0') + res;
        result /= baseInt;
    }

    return res == "" ? "0" : res;
}

string shift(string str, int steps) {
    for (int i = 0; i < steps; i++) {
        str = str + '0';
    }
    return str;
}

string karatsuba(string l1, string l2, string base) {
    int n = matchSize(l1, l2);

    if (n == 0) return "";
    if (n == 1) return multiplyBase(l1, l2, base);

    // Approximately halving size
    int n2 = n / 2;
    int sp = n - n2; // Second part size

    string x1 = l1.substr(0, n2);
    string x0 = l1.substr(n2, sp);

    string y1 = l2.substr(0, n2);
    string y0 = l2.substr(n2, sp);

    // Applying 3 different multiplications needed recursively
    string z2 = karatsuba(x1, y1, base);
    string z0 = karatsuba(x0, y0, base);
    string z3 = karatsuba(add(x0, x1, base), add(y0, y1, base), base);

    z3 = subtract(subtract(z3, z2, base), z0, base);

    string result = add(add(shift(z2, 2 * sp), shift(z3, sp), base), z0, base);

    // Remove leading zeros
    while (result.size() > 1 && result[0] == '0') {
        result.erase(0, 1);
    }

    return result;
}
