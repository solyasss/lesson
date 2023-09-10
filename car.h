#pragma once //design file
class Car
{
    char *model;
    char *color;
    int year;
    double price;

public:
    Car();
    Car(const char *m, const char *c, int y, double pr);
    ~Car();
    void input();
    void print();

    // inspectors
    char *get_model();
    char *get_color();
    int get_year();
    double get_price();

    // modificators
    void set_model(const char *m);
    void set_color(const char *c);
    void set_year(int y);
    void set_price(double pr);
};