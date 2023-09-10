#include "Car.h"
#include <iostream>
#include <cstring> // for strcpy

using namespace std;

Car::Car()
{
    model = nullptr;
    color = nullptr;
    year = 0;
    price = 0.0;
}

Car::Car(const char *m, const char *c, int y, double pr)
{
    this->model = new char[strlen(m) + 1];
    strcpy(model, m);

    this->color = new char[strlen(c) + 1];
    strcpy(color, c);

    this->year = y;
    this->price = pr;
}

Car::~Car()
{
    delete[] model;
    delete[] color;
}

void Car::input()
{
    char temp[64];

    cout << "Enter model: ";
    cin.getline(temp, sizeof(temp));

    if (model != nullptr)
    {
        cout << model << " Delete model." << endl;
        delete[] model;
    }

    this->model = new char[strlen(temp) + 1];
    strcpy(model, temp);

    cout << "Enter color: ";
    cin.getline(temp, sizeof(temp));

    if (color != nullptr)
    {
        cout << color << " Delete color." << endl;
        delete[] color;
    }

    this->color = new char[strlen(temp) + 1];
    strcpy(color, temp);

    cout << "Enter year: ";
    cin >> this->year;

    cout << "Enter price: ";
    cin >> this->price;
    cin.ignore();
}

void Car::print()
{
    cout << "Car: " << this->model << " Model: " << this->color << " Color: " << this->year << ", Price: " << this->price << endl;
}

char *Car::get_model()
{
    return model;
}

char *Car::get_color()
{
    return color;
}

int Car::get_year()
{
    return year;
}

double Car::get_price()
{
    return price;
}

void Car::set_model(const char *m)
{
    if (model != nullptr)
    {
        cout << model << " Delete model." << endl;
        delete[] model;
    }
    this->model = new char[strlen(m) + 1];
    strcpy(model, m);
}

void Car::set_color(const char *c)
{
    if (color != nullptr)
    {
        cout << color << " Delete color." << endl;
        delete[] color;
    }
    this->color = new char[strlen(c) + 1];
    strcpy(color, c);
}

void Car::set_year(int y)
{
    this->year = y;
}

void Car::set_price(double pr)
{
    if (pr > 0)
    {
        this->price = pr;
    }
}
