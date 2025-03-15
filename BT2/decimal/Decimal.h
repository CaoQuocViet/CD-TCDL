#pragma once
#ifndef DECIMAL_H
#define DECIMAL_H

#include <string>

struct Decimal {
    // Store integer = real number * 1000
    long long value;  // Value * 1000
    bool isNegative; // Sign of number

    // Constructors
    Decimal();
    Decimal(long long val);
    Decimal(int val);
    Decimal(const std::string& str);

    // a) String input/output and conversion
    std::string toString() const;
    static Decimal fromString(const std::string& str);

    // b) Convert to/from int and double
    int toInt() const;
    double toDouble() const;
    static Decimal fromInt(int val);
    static Decimal fromDouble(double val);

    // c) Integer part, fractional part, and rounding operations
    long long getIntegerPart() const;
    Decimal getFractionalPart() const;
    Decimal round(int precision) const; // precision: number of decimal places to round to

    // d) Arithmetic operations
    Decimal operator+(const Decimal& other) const;
    Decimal operator-(const Decimal& other) const;
    Decimal operator*(const Decimal& other) const;
    Decimal operator/(const Decimal& other) const;
    Decimal operator-() const; // Negation
    Decimal abs() const;       // Absolute value

    // e) Comparison operations
    bool operator==(const Decimal& other) const;
    bool operator!=(const Decimal& other) const;
    bool operator<(const Decimal& other) const;
    bool operator>(const Decimal& other) const;
    bool operator<=(const Decimal& other) const;
    bool operator>=(const Decimal& other) const;
};

#endif 