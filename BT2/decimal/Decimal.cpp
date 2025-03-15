#include "Decimal.h"
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <iomanip>

// Default constructor
Decimal::Decimal() : value(0), isNegative(false) {}

// Constructor from long long
Decimal::Decimal(long long val) {
    isNegative = val < 0;
    value = std::abs(val) * 1000;
}

// Constructor from int
Decimal::Decimal(int val) : Decimal(static_cast<long long>(val)) {}

// Constructor from string
Decimal::Decimal(const std::string& str) {
    *this = fromString(str);
}

// Convert to string
std::string Decimal::toString() const {
    std::stringstream ss;
    long long absValue = std::abs(value);
    long long intPart = absValue / 1000;
    long long fracPart = absValue % 1000;

    if (isNegative) ss << "-";
    ss << intPart << "." << std::setfill('0') << std::setw(3) << fracPart;
    return ss.str();
}

// Convert from string to Decimal
Decimal Decimal::fromString(const std::string& str) {
    Decimal result;
    std::string numStr = str;

    // Process sign
    result.isNegative = false;
    if (!numStr.empty() && numStr[0] == '-') {
        result.isNegative = true;
        numStr = numStr.substr(1);
    }

    // Find decimal point position
    size_t dotPos = numStr.find('.');
    std::string intPart, fracPart;

    if (dotPos == std::string::npos) {
        intPart = numStr;
        fracPart = "000";
    }
    else {
        intPart = numStr.substr(0, dotPos);
        fracPart = numStr.substr(dotPos + 1);
        // Normalize decimal part
        while (fracPart.length() < 3) fracPart += "0";
        if (fracPart.length() > 3) fracPart = fracPart.substr(0, 3);
    }

    result.value = std::stoll(intPart) * 1000 + std::stoll(fracPart);
    return result;
}

// Conversion methods
int Decimal::toInt() const {
    // Get integer part
    long long intPart = value / 1000;

    // Get remainder for rounding
    long long remainder = value % 1000;

    // Round up if remainder >= 500
    if (remainder >= 500) {
        intPart++;
    }

    return static_cast<int>(intPart) * (isNegative ? -1 : 1);
}

double Decimal::toDouble() const {
    return (value / 1000.0) * (isNegative ? -1.0 : 1.0);
}

// Conversion methods
Decimal Decimal::fromInt(int val) {
    return Decimal(val);
}

Decimal Decimal::fromDouble(double val) {
    Decimal result;
    result.isNegative = val < 0;

    // Get absolute value and multiply by 1000
    double absVal = std::abs(val) * 1000;

    // Round to avoid floating point errors
    // Add 0.5 for rounding: 123.4567 * 1000 = 123456.7 -> 123457
    //                       123.4564 * 1000 = 123456.4 -> 123456
    result.value = static_cast<long long>(absVal + 0.5);

    return result;
}

// Integer part, fractional part, and rounding operations
long long Decimal::getIntegerPart() const {
    long long intPart = value / 1000;
    return isNegative ? -intPart : intPart;
}

Decimal Decimal::getFractionalPart() const {
    Decimal result;
    result.isNegative = isNegative;
    result.value = value % 1000;
    return result;
}

Decimal Decimal::round(int precision) const {
    Decimal result = *this;

    // If precision >= 3, keep number as is since we only have 3 decimal places
    if (precision >= 3) {
        return result;
    }

    // Calculate factor to shift decimal point
    long long factor = 1;
    for (int i = 0; i < 3 - precision; i++) {
        factor *= 10;
    }

    // Get remainder for rounding check
    long long remainder = (result.value % factor);
    result.value -= remainder;

    // Round up if remainder >= half of factor
    if (remainder >= factor / 2) {
        result.value += factor;
    }

    return result;
}

// Basic arithmetic operations
Decimal Decimal::operator+(const Decimal& other) const {
    Decimal result;
    if (isNegative == other.isNegative) {
        result.value = value + other.value;
        result.isNegative = isNegative;
    }
    else {
        if (std::abs(value) >= std::abs(other.value)) {
            result.value = std::abs(value) - std::abs(other.value);
            result.isNegative = isNegative;
        }
        else {
            result.value = std::abs(other.value) - std::abs(value);
            result.isNegative = other.isNegative;
        }
    }
    return result;
}

// Arithmetic operations
Decimal Decimal::operator-(const Decimal& other) const {
    Decimal negOther = -other;
    return *this + negOther;
}

Decimal Decimal::operator*(const Decimal& other) const {
    Decimal result;
    // Multiply numbers and divide by 1000 to keep 3 decimal places
    result.value = (value * other.value) / 1000;
    result.isNegative = isNegative != other.isNegative;
    return result;
}

Decimal Decimal::operator/(const Decimal& other) const {
    if (other.value == 0) {
        throw std::runtime_error("Division by zero");
    }

    Decimal result;
    // Multiply by 1000 before division to maintain precision
    result.value = (value * 1000) / other.value;
    result.isNegative = isNegative != other.isNegative;
    return result;
}

Decimal Decimal::operator-() const {
    Decimal result = *this;
    result.isNegative = !isNegative;
    return result;
}

Decimal Decimal::abs() const {
    Decimal result = *this;
    result.isNegative = false;
    return result;
}

// Comparison operations
bool Decimal::operator==(const Decimal& other) const {
    return isNegative == other.isNegative && value == other.value;
}

bool Decimal::operator!=(const Decimal& other) const {
    return !(*this == other);
}

bool Decimal::operator<(const Decimal& other) const {
    if (isNegative != other.isNegative) return isNegative;
    if (isNegative) return value > other.value;
    return value < other.value;
}

bool Decimal::operator>(const Decimal& other) const {
    return other < *this;
}

bool Decimal::operator<=(const Decimal& other) const {
    return !(other < *this);
}

bool Decimal::operator>=(const Decimal& other) const {
    return !(*this < other);
}
