#include <iostream>
#include <cstdio>
#include <cstring> 

using namespace std;

const int MAX_EMPLOYEES = 100;

struct Employee
{
    char first_name[50];
    char last_name[50];
    char phone_number[15];
    double salary;
};

void display_employee(const Employee &emp)
{
    cout << "Last Name: " << emp.last_name << endl;
    cout << "First Name: " << emp.first_name << endl;
    cout << "Phone Number: " << emp.phone_number << endl;
    cout << "Salary: " << emp.salary << endl;
}

void save_employees(Employee *employees, int num_employees, const char *filename)
{
    FILE *file = fopen(filename, "wb"); // binary file
    if (!file)
    {
        cout << "Error opening the file for." << endl;
        return;
    }

    // write data in a binary file
    fwrite(employees, sizeof(Employee), num_employees, file);

    fclose(file);
    cout << "Data saved to the file " << filename << endl;
}

void load_employees(Employee *employees, int &num_employees, const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        cout << "Error opening the file." << endl;
        return;
    }

    // read data from file
    num_employees = fread(employees, sizeof(Employee), MAX_EMPLOYEES, file);

    fclose(file);
    cout << "Data loaded from the file " << filename << endl;
}

int find_employee_by_last_name(Employee *employees, int num_employees, const char *last_name)
{
    for (int i = 0; i < num_employees; i++)
    {
        if (strcmp(employees[i].last_name, last_name) == 0)
        {
            return i;
        }
    }
    return -1; // employee not found
}

void search_by_salary_range(Employee *employees, int num_employees, double min_salary, double max_salary)
{
    bool found = false;
    for (int i = 0; i < num_employees; i++)
    {
        if (employees[i].salary >= min_salary && employees[i].salary <= max_salary)
        {
            display_employee(employees[i]);
            found = true;
        }
    }
    if (!found)
    {
        cout << "Employees with salaries in the range not found." << endl;
    }
}

void sort_by_last_name(Employee *employees, int num_employees)
{
    for (int i = 0; i < num_employees - 1; i++)
    {
        for (int j = 0; j < num_employees - i - 1; j++)
        {
            if (strcmp(employees[j].last_name, employees[j + 1].last_name) > 0)
            {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    cout << "Employees sorted by last name." << endl;
}

void add_employee(Employee *employees, int &num_employees)
{
    if (num_employees >= MAX_EMPLOYEES)
    {
        cout << "No space to add new employees." << endl;
        return;
    }

    Employee employee;

    cout << "Enter last name: ";
    cin >> employee.last_name;

    cout << "Enter first name: ";
    cin >> employee.first_name;

    do
    {
        cout << "Enter phone number (in the format (XXX) XXXXXXX): ";
        cin >> employee.phone_number;
    } while (strlen(employee.phone_number) != 13); // check phone number by length

    cout << "Enter salary: ";
    cin >> employee.salary;

    employees[num_employees] = employee;
    num_employees++;
}

void delete_employee(Employee *employees, int &num_employees, const char *last_name)
{
    for (int i = 0; i < num_employees; i++)
    {
        if (strcmp(employees[i].last_name, last_name) == 0)
        {
            for (int j = i; j < num_employees - 1; j++)
            {
                employees[j] = employees[j + 1];
            }
            num_employees--;
            cout << "Employee " << last_name << " has been deleted." << endl;
            return;
        }
    }
    cout << "Employee " << last_name << " not found." << endl;
}

int main()
{
    Employee employees[MAX_EMPLOYEES];
    int num_employees = 0;

    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Add an employee" << endl;
        cout << "2. Delete an employee" << endl;
        cout << "3. Display all employees" << endl;
        cout << "4. Save data to a file" << endl;
        cout << "5. Load data from a file" << endl;
        cout << "6. Search by last name" << endl;
        cout << "7. Search by salary range" << endl;
        cout << "8. Sort by last name" << endl;
        cout << "9. Exit" << endl;
        cout << "Choose an action: ";
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            add_employee(employees, num_employees);
            break;
        case 2:
        {
            char last_name[50];
            cout << "Enter the last name of the employee to delete: ";
            cin >> last_name;
            delete_employee(employees, num_employees, last_name);
            break;
        }
        case 3:
            cout << "List of all employees:" << endl;
            for (int i = 0; i < num_employees; i++)
            {
                display_employee(employees[i]);
            }
            break;
        case 4:
        {
            char filename[100];
            cout << "Enter the filename to save data: ";
            cin >> filename;
            save_employees(employees, num_employees, filename);
            break;
        }
        case 5:
        {
            char filename[100];
            cout << "Enter the filename to load data: ";
            cin >> filename;
            load_employees(employees, num_employees, filename);
            break;
        }
        case 6:
        {
            char last_name[50];
            cout << "Enter the last name to search: ";
            cin >> last_name;
            int index = find_employee_by_last_name(employees, num_employees, last_name);
            if (index != -1)
            {
                cout << "Employee found:" << endl;
                display_employee(employees[index]);
            }
            else
            {
                cout << "Employee with last name " << last_name << " not found." << endl;
            }
            break;
        }
        case 7:
        {
            double min_salary, max_salary;
            cout << "Enter the minimum and maximum salary: ";
            cin >> min_salary >> max_salary;
            search_by_salary_range(employees, num_employees, min_salary, max_salary);
            break;
        }
        case 8:
            sort_by_last_name(employees, num_employees);
            break;
        case 9:
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
