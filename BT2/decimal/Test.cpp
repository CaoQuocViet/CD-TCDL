#include <iostream>
#include "Test.h"
#include "Decimal.h"

// a,b) Test Constructors and Conversion
void testConstructorsAndConversion() {
    std::cout << "\n=== Test Constructors and Conversion ===\n";

    Decimal d1("0123.5678");
    std::cout << "From string '0123.5678': " << d1.toString() << std::endl;

    Decimal d2 = Decimal::fromInt(123);
    std::cout << "From int 123: " << d2.toString() << std::endl;

    Decimal d3 = Decimal::fromDouble(123.4567);
    std::cout << "From double 123.4567: " << d3.toString() << std::endl;

    std::cout << "To int: " << d1.toInt() << std::endl;
    std::cout << "To double: " << d1.toDouble() << std::endl;
}

// c) Test Parts and Rounding       
void testPartsAndRounding() {
    std::cout << "\n=== Test Parts and Rounding ===\n";

    Decimal d("123.5678");
    std::cout << "Number: " << d.toString() << std::endl;
    std::cout << "Integer part: " << d.getIntegerPart() << std::endl;
    std::cout << "Fractional part: " << d.getFractionalPart().toString() << std::endl;

    // Test rounding with different precisions
    std::cout << "Rounded to -2 decimal places: " << d.round(-10).toString() << std::endl;
    std::cout << "Rounded to -1 decimal places: " << d.round(-1).toString() << std::endl;
    std::cout << "Rounded to 0 decimal places: " << d.round(0).toString() << std::endl;
    std::cout << "Rounded to 1 decimal place: " << d.round(1).toString() << std::endl;
    std::cout << "Rounded to 2 decimal places: " << d.round(2).toString() << std::endl;
    std::cout << "Rounded to 3 decimal places: " << d.round(3).toString() << std::endl;
    std::cout << "Rounded to 4 decimal places: " << d.round(4).toString() << std::endl;

    // Test negative numbers
    Decimal d2("-123.567");
    std::cout << "\nNegative number: " << d2.toString() << std::endl;
    std::cout << "Integer part: " << d2.getIntegerPart() << std::endl;
    std::cout << "Rounded to 1 decimal place: " << d2.round(1).toString() << std::endl;
}

// d) Test Arithmetic
void testArithmetic() {
    std::cout << "\n=== Test Arithmetic Operations ===\n";

    Decimal d1("123.456");
    Decimal d2("456.789");
    Decimal d3("0.123");

    std::cout << d1.toString() << " + " << d2.toString() << " = "
        << (d1 + d2).toString() << std::endl;

    std::cout << d1.toString() << " - " << d2.toString() << " = "
        << (d1 - d2).toString() << std::endl;

    std::cout << d1.toString() << " * " << d2.toString() << " = "
        << (d1 * d2).toString() << std::endl;

    std::cout << d1.toString() << " / " << d2.toString() << " = "
        << (d1 / d2).toString() << std::endl;

    std::cout << "Absolute of -" << d1.toString() << " = "
        << (-d1).abs().toString() << std::endl;
    std::cout << "Absolute of " << d3.toString() << " = "
        << (d3).abs().toString() << std::endl;
}

// e) Test Comparison
void testComparison() {
    std::cout << "\n=== Test Comparison Operations ===\n";

    Decimal d1("123.456");
    Decimal d2("456.789");
    Decimal d3("-234.567");

    std::cout << d1.toString() << " == " << d2.toString() << ": "
        << (d1 == d2) << std::endl;
    std::cout << d1.toString() << " != " << d2.toString() << ": "
        << (d1 != d2) << std::endl;
    std::cout << d1.toString() << " < " << d2.toString() << ": "
        << (d1 < d2) << std::endl;
    std::cout << d1.toString() << " <= " << d2.toString() << ": "
        << (d1 <= d2) << std::endl;
    std::cout << d1.toString() << " > " << d2.toString() << ": "
        << (d1 > d2) << std::endl;
    std::cout << d1.toString() << " >= " << d2.toString() << ": "
        << (d1 >= d2) << std::endl;


    std::cout << d1.toString() << " == " << d3.toString() << ": "
        << (d1 == d3) << std::endl;
    std::cout << d1.toString() << " != " << d3.toString() << ": "
        << (d1 != d3) << std::endl;
    std::cout << d1.toString() << " < " << d3.toString() << ": "
        << (d1 < d3) << std::endl;
    std::cout << d1.toString() << " <= " << d3.toString() << ": "
        << (d1 <= d3) << std::endl;
    std::cout << d1.toString() << " > " << d3.toString() << ": "
        << (d1 > d3) << std::endl;
    std::cout << d1.toString() << " >= " << d3.toString() << ": "
        << (d1 >= d3) << std::endl;

    std::cout << d3.toString() << " == " << d2.toString() << ": "
        << (d3 == d2) << std::endl;
    std::cout << d3.toString() << " != " << d2.toString() << ": "
        << (d3 != d2) << std::endl;
    std::cout << d3.toString() << " < " << d2.toString() << ": "
        << (d3 < d2) << std::endl;
    std::cout << d3.toString() << " <= " << d2.toString() << ": "
        << (d3 <= d2) << std::endl;
    std::cout << d3.toString() << " > " << d2.toString() << ": "
        << (d3 > d2) << std::endl;
    std::cout << d3.toString() << " >= " << d2.toString() << ": "
        << (d3 >= d2) << std::endl;
}