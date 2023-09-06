#include <iostream>
using namespace std;

class Fraction
{
private:
    int numerator;
    int denominator;

public:
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom)
    {
        // check for a denominator equal to zero
        if (denominator == 0)
        {
            cerr << "Error: Denominator cannot be zero." << endl;
            exit(1);
        }
    }

    // function to set the numerator
    void set_numerator(int num)
    {
        numerator = num;
    }

    // function to set the denominator
    void set_denominator(int denom)
    {
        if (denom != 0)
        {
            denominator = denom;
        }
        else
        {
            cerr << "Error! Denominator cannot be zero." << endl;
            exit(1);
        }
    }

    int get_numerator() const
    {
        return numerator;
    }

    int get_denominator() const
    {
        return denominator;
    }

    // function to add fractions
    Fraction add(const Fraction &other) const
    {
        int result_numerator = numerator * other.denominator + other.numerator * denominator;
        int result_denominator = denominator * other.denominator;
        return Fraction(result_numerator, result_denominator);
    }

    // function to subtract fractions
    Fraction subtract(const Fraction &other) const
    {
        int result_numerator = numerator * other.denominator - other.numerator * denominator;
        int result_denominator = denominator * other.denominator;
        return Fraction(result_numerator, result_denominator);
    }

    // Function to multiply fractions
    Fraction multiply(const Fraction &other) const
    {
        int result_numerator = numerator * other.numerator;
        int result_denominator = denominator * other.denominator;
        return Fraction(result_numerator, result_denominator);
    }

    // Function to divide fractions
    Fraction divide(const Fraction &other) const
    {
        if (other.numerator != 0)
        {
            int result_numerator = numerator * other.denominator;
            int result_denominator = denominator * other.numerator;
            return Fraction(result_numerator, result_denominator);
        }
        else
        {
            cerr << "Error: Division by zero." << endl;
            exit(1);
        }
    }

    // Function to display the fraction
    void display() const
    {
        cout << numerator << "/" << denominator;
    }
};

int main()
{
    Fraction fraction1(1, 2);
    Fraction fraction2(3, 4);

    Fraction result_add = fraction1.add(fraction2);
    Fraction resul_subtract = fraction1.subtract(fraction2);
    Fraction result_multiply = fraction1.multiply(fraction2);
    Fraction result_divide = fraction1.divide(fraction2);

    cout << "Addition: ";
    result_add.display();
    cout << endl;

    cout << "Subtraction: ";
    resul_subtract.display();
    cout << endl;

    cout << "Multiplication: ";
    result_multiply.display();
    cout << endl;

    cout << "Division: ";
    result_divide.display();
    cout << endl;

    return 0;
}
