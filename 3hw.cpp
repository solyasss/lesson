#include <iostream>
using namespace std;

class Fraction
{
private:
    int numerator = 1;
    int denominator = 1;

public:
    void set_fraction(int n, int d)
    {
        numerator = n;
        denominator = d;
    }

    void display_fraction()
    {
        cout << "Here is your fraction: " << numerator << "/" << denominator << endl;
    }

    void add(int n, int d)
    {

        if (n > 0 && d > 0)
        {
            numerator += n;
            denominator += d;
        }
        else
        {
            cout << "Addition failed." << endl;
        }
    }

    Fraction add(Fraction n)
    {

        Fraction result;

        result.numerator = numerator + n.numerator;
        result.denominator = denominator + n.denominator;

        return result;
    }

    void multiply(int n, int d)
    {

        if (n > 0 && d > 0)
        {
            numerator *= n;
            denominator *= d;
        }
        else
        {
            cout << " Multiplication failed." << endl;
        }
    }

    Fraction multiply(Fraction n)
    {
        Fraction result;

        result.numerator = numerator * n.numerator;
        result.denominator = denominator * n.denominator;

        return result;
    }

    void subtract(int n, int d)
    {

        if (n > 0 && d > 0)
        {
            numerator -= n;
            denominator -= d;
        }
        else
        {
            cout << " Subtraction failed." << endl;
        }
    }

    Fraction subtract(Fraction n)
    {
        Fraction result;

        result.numerator = numerator - n.numerator;
        result.denominator = denominator - n.denominator;

        return result;
    }

    void divide(int n, int d)
    {

        if (n > 0 && d > 0)
        {
            numerator /= n;
            denominator /= d;
        }
        else
        {
            cout << " Division failed." << endl;
        }
    }

    Fraction divide(Fraction n)
    {
        Fraction result;

        result.numerator = numerator / n.numerator;
        result.denominator = denominator / n.denominator;

        return result;
    }

    void add_to_numerator(int n)
    {
        numerator += n;

        if (n > 0)
        {
            numerator += n;
        }
        else
        {
            cout << "Failed " << endl;
        }
    }

    void add_to_denominator(int n)
    {
        if (n > 0)
        {
            denominator += n;
        }
        else
        {
            cout << "Failed" << endl;
        }
    }

    void set_numerator(int n)
    {
        if (n > 0)
        {
            numerator = n;
        }
        else
        {
            cout << "Failed" << endl;
        }
    }

    void set_denominator(int n)
    {
        if (n > 0)
        {
            denominator = n;
        }
        else
        {
            cout << "Failed" << endl;
        }
    }

    int get_numerator()
    {
        return numerator;
    }

    int get_denominator()
    {
        return denominator;
    }
};

int main()
{

    Fraction n;
    n.set_fraction(50, 100);
    n.display_fraction();

    n.add(50, 20);
    n.display_fraction();

    Fraction d;
    d.set_fraction(100, 150);

    Fraction sum = n.add(d);
    sum.display_fraction();
}