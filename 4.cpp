#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

class Contact
{
private:
    char *full_name;
    char *home_phone;
    char *work_phone;
    char *mobile_phone;
    char *additional_info;

public:
    Contact(const char *name, const char *home, const char *work, const char *mobile, const char *info)
        : full_name(nullptr), home_phone(nullptr), work_phone(nullptr), mobile_phone(nullptr), additional_info(nullptr)
    {
        full_name = new char[strlen(name) + 1];
        strcpy(full_name, name);
        home_phone = new char[strlen(home) + 1];
        strcpy(home_phone, home);
        work_phone = new char[strlen(work) + 1];
        strcpy(work_phone, work);
        mobile_phone = new char[strlen(mobile) + 1];
        strcpy(mobile_phone, mobile);
        additional_info = new char[strlen(info) + 1];
        strcpy(additional_info, info);
    }

    ~Contact()
    {
        delete[] full_name;
        delete[] home_phone;
        delete[] work_phone;
        delete[] mobile_phone;
        delete[] additional_info;
    }

    const char *get_name() const
    {
        return full_name;
    }

    const char *get_home_phone() const
    {
        return home_phone;
    }

    const char *get_work_phone() const
    {
        return work_phone;
    }

    const char *get_mobile_phone() const
    {
        return mobile_phone;
    }

    const char *get_additional_info() const
    {
        return additional_info;
    }

    void display() const
    {
        cout << "Full Name: " << full_name << endl;
        cout << "Home Phone: " << home_phone << endl;
        cout << "Work Phone: " << work_phone << endl;
        cout << "Mobile Phone: " << mobile_phone << endl;
        cout << "Additional Info: " << additional_info << endl;
    }

    bool match(const char *name) const
    {
        return strcmp(full_name, name) == 0;
    }
};

class PhoneBook
{
private:
    Contact **contacts;
    int cap;
    int size;

public:
    PhoneBook() : contacts(nullptr), cap(0), size(0) {}

    ~PhoneBook()
    {
        clearContacts();
    }

    void add(const Contact &contact)
    {
        if (size >= cap)
        {
            int new_cap = cap + 10;
            Contact **new_contacts = new Contact *[new_cap];
            for (int i = 0; i < size; ++i)
            {
                new_contacts[i] = contacts[i];
            }
            delete[] contacts;
            contacts = new_contacts;
            cap = new_cap;
        }
        contacts[size++] = new Contact(contact);
    }

    bool remove_contact(const char *name)
    {
        for (int i = 0; i < size; ++i)
        {
            if (contacts[i]->match(name))
            {
                delete contacts[i];
                for (int j = i; j < size - 1; ++j)
                {
                    contacts[j] = contacts[j + 1];
                }
                size--;
                return true;
            }
        }
        return false;
    }

    Contact *find(const char *name)
    {
        for (int i = 0; i < size; ++i)
        {
            if (contacts[i]->match(name))
            {
                return contacts[i];
            }
        }
        return nullptr;
    }

    void display() const
    {
        for (int i = 0; i < size; ++i)
        {
            contacts[i]->display();
            cout << endl;
        }
    }

    void save_to_file(const char *filename)
    {
        FILE *file = fopen(filename, "wb");

        if (file)
        {
            for (int i = 0; i < size; ++i)
            {
                fwrite(contacts[i]->get_name(), sizeof(char), strlen(contacts[i]->get_name()), file);
                fwrite("\n", sizeof(char), 1, file);
                fwrite(contacts[i]->get_home_phone(), sizeof(char), strlen(contacts[i]->get_home_phone()), file);
                fwrite("\n", sizeof(char), 1, file);
                fwrite(contacts[i]->get_work_phone(), sizeof(char), strlen(contacts[i]->get_work_phone()), file);
                fwrite("\n", sizeof(char), 1, file);
                fwrite(contacts[i]->get_mobile_phone(), sizeof(char), strlen(contacts[i]->get_mobile_phone()), file);
                fwrite("\n", sizeof(char), 1, file);
                fwrite(contacts[i]->get_additional_info(), sizeof(char), strlen(contacts[i]->get_additional_info()), file);
                fwrite("\n", sizeof(char), 1, file);
            }
            fclose(file);
            cout << "Phonebook data saved to " << filename << endl;
        }
        else
        {
            cout << "Unable to open " << filename << " for writing." << endl;
        }
    }

    void load_from_file(const char *filename)
    {
        FILE *file = fopen(filename, "rb");

        if (file)
        {
            clearContacts();

            char name[100], home[100], work[100], mobile[100], info[100];
            while (fgets(name, sizeof(name), file))
            {
                fgets(home, sizeof(home), file);
                fgets(work, sizeof(work), file);
                fgets(mobile, sizeof(mobile), file);
                fgets(info, sizeof(info), file);

                name[strcspn(name, "\n")] = '\0';
                home[strcspn(home, "\n")] = '\0';
                work[strcspn(work, "\n")] = '\0';
                mobile[strcspn(mobile, "\n")] = '\0';
                info[strcspn(info, "\n")] = '\0';

                Contact contact(name, home, work, mobile, info);
                add(contact);
            }
            fclose(file);
            cout << "Phonebook data loaded from " << filename << endl;
        }
        else
        {
            cout << "Unable to open " << filename << " for reading" << endl;
        }
    }

private:
    void clearContacts()
    {
        for (int i = 0; i < size; ++i)
        {
            delete contacts[i];
        }
        delete[] contacts;
        contacts = nullptr;
        size = 0;
        cap = 0;
    }
};

int main()
{
    PhoneBook phoneBook;

    while (true)
    {
        cout << "Select an action:" << endl;
        cout << "1. Add a contact" << endl;
        cout << "2. Remove a contact" << endl;
        cout << "3. Find a contact" << endl;
        cout << "4. Display all contacts" << endl;
        cout << "5. Save to file" << endl;
        cout << "6. Load from file" << endl;
        cout << "7. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            char name[256], home[256], work[256], mobile[256], info[256];
            cout << "Enter Full Name: ";
            cin.ignore();
            cin.getline(name, sizeof(name));
            cout << "Enter Home Phone: ";
            cin.getline(home, sizeof(home));
            cout << "Enter Work Phone: ";
            cin.getline(work, sizeof(work));
            cout << "Enter Mobile Phone: ";
            cin.getline(mobile, sizeof(mobile));
            cout << "Enter Additional Info: ";
            cin.getline(info, sizeof(info));

            Contact contact(name, home, work, mobile, info);
            phoneBook.add(contact);
        }
        else if (choice == 2)
        {
            char name[100];
            cout << "Enter Full Name to remove: ";
            cin.ignore();
            cin.getline(name, sizeof(name));

            if (phoneBook.remove_contact(name))
            {
                cout << "Contact removed." << endl;
            }
            else
            {
                cout << "Contact not found." << endl;
            }
        }
        else if (choice == 3)
        {
            char name[100];
            cout << "Enter Full Name to find: ";
            cin.ignore();
            cin.getline(name, sizeof(name));

            Contact *foundContact = phoneBook.find(name);
            if (foundContact)
            {
                foundContact->display();
            }
            else
            {
                cout << "Contact not found." << endl;
            }
        }
        else if (choice == 4)
        {
            phoneBook.display();
        }
        else if (choice == 5)
        {
            char filename[100];
            cout << "Enter file name to save: ";
            cin.ignore();
            cin.getline(filename, sizeof(filename));
            phoneBook.save_to_file(filename);
        }
        else if (choice == 6)
        {
            char filename[256];
            cout << "Enter file name to load: ";
            cin.ignore();
            cin.getline(filename, sizeof(filename));
            phoneBook.load_from_file(filename);
        }
        else if (choice == 7)
        {
            cout << "Bye";
            break;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
