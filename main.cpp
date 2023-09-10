#include <iostream>
#include "car.h"

using namespace std;

int main()
{
    Car a("Audi A5", "Red", 2021, 25000);

    a.set_model("BMW M2 Coupe");
    char *model = a.get_model();
    cout << model << endl;
    a.set_color("Titanic Blue");
    char *color = a.get_color();
    cout << color << endl;
    a.set_year(2023);
    int year = a.get_year();
    cout << year << endl;
    a.set_price(2000000);
    double price = a.get_price();
    cout << price << endl;

    a.input();
    a.print();
}