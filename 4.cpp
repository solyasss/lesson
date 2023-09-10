#include <iostream>
#include <cstring>

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
    Contact() : full_name(nullptr), home_phone(nullptr), work_phone(nullptr), mobile_phone(nullptr), additional_info(nullptr) {}

    Contact(const char *name, const char *home, const char *work, const char *mobile, const char *info)
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

    char *get_name()
    {
        return full_name;
    }

    void display()
    {
        cout << " Name: " << full_name << endl;
        cout << "Home phone: " << home_phone << endl;
        cout << "Work phone: " << work_phone << endl;
        cout << "Mobile phone: " << mobile_phone << endl;
        cout << "Additional info: " << additional_info << endl;
    }

    void save_to_file(FILE *file)
    {
        fwrite(full_name, sizeof(char), strlen(full_name) + 1, file);
        fwrite(home_phone, sizeof(char), strlen(home_phone) + 1, file);
        fwrite(work_phone, sizeof(char), strlen(work_phone) + 1, file);
        fwrite(mobile_phone, sizeof(char), strlen(mobile_phone) + 1, file);
        fwrite(additional_info, sizeof(char), strlen(additional_info) + 1, file);
    }

    void load_from_file(FILE *file)
    {
        fread(full_name, sizeof(char), 256, file);
        fread(home_phone, sizeof(char), 256, file);
        fread(work_phone, sizeof(char), 256, file);
        fread(mobile_phone, sizeof(char), 256, file);
        fread(additional_info, sizeof(char), 256, file);
    }
};

int main()
{
    Contact contacts[200];
    int num_contacts = 0;
    FILE *file = nullptr;

    while (true)
    {
        cout << "Menu:" << endl;
        cout << "1. Add contact" << endl;
        cout << "2. Delete contact" << endl;
        cout << "3. Search contact by name" << endl;
        cout << "4. Display all contacts" << endl;
        cout << "5. Save contacts to file" << endl;
        cout << "6. Load contacts from file" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            if (num_contacts < 100)
            {
                char name[256], home[256], work[256], mobile[256], info[256];
                cout << "Enter name: ";
                cin.ignore();
                cin.getline(name, sizeof(name));
                cout << "Enter home phone: ";
                cin.getline(home, sizeof(home));
                cout << "Enter work phone: ";
                cin.getline(work, sizeof(work));
                cout << "Enter mobile phone: ";
                cin.getline(mobile, sizeof(mobile));
                cout << "Enter additional info: ";
                cin.getline(info, sizeof(info));

                contacts[num_contacts] = Contact(name, home, work, mobile, info);
                num_contacts++;
                cout << "Contact added." << endl;
            }
            else
            {
                cout << "Phone book is full." << endl;
            }
            break;
        case 2:
            if (num_contacts > 0)
            {
                char name_to_delete[256];
                cout << "Enter name to delete: ";
                cin.ignore();
                cin.getline(name_to_delete, sizeof(name_to_delete));

                bool contact_deleted = false;
                for (int i = 0; i < num_contacts; i++)
                {
                    if (strcmp(contacts[i].get_name(), name_to_delete) == 0)
                    {
                        for (int j = i; j < num_contacts - 1; j++)
                        {
                            contacts[j] = contacts[j + 1];
                        }
                        num_contacts--;
                        contact_deleted = true;
                        cout << "Contact deleted." << endl;
                        break;
                    }
                }

                if (!contact_deleted)
                {
                    cout << "Contact not found." << endl;
                }
            }
            else
            {
                cout << "Phone book is empty." << endl;
            }
            break;
        case 3:
            if (num_contacts > 0)
            {
                char name_to_search[256];
                cout << "Enter full name to search: ";
                cin.ignore();
                cin.getline(name_to_search, sizeof(name_to_search));

                bool contact_found = false;
                for (int i = 0; i < num_contacts; i++)
                {
                    if (strcmp(contacts[i].get_name(), name_to_search) == 0)
                    {
                        contacts[i].display();
                        contact_found = true;
                        break;
                    }
                }

                if (!contact_found)
                {
                    cout << "Contact not found." << endl;
                }
            }
            else
            {
                cout << "Phone book is empty." << endl;
            }
            break;
        case 4:
            if (num_contacts > 0)
            {
                cout << "All contacts:" << endl;
                for (int i = 0; i < num_contacts; i++)
                {
                    contacts[i].display();
                }
            }
            else
            {
                cout << "Phone book is empty." << endl;
            }
            break;
        case 5:
            if (num_contacts > 0)
            {
                char file_name[256];
                cout << "Enter file name to save contacts: ";
                cin.getline(file_name, sizeof(file_name));

                file = fopen(file_name, "wb");
                if (file != nullptr)
                {
                    fwrite(&num_contacts, sizeof(int), 1, file);

                    for (int i = 0; i < num_contacts; i++)
                    {
                        contacts[i].save_to_file(file);
                    }
                    fclose(file);
                    cout << "Contacts saved to file." << endl;
                }
                else
                {
                    cout << "Failed to open the file." << endl;
                }
            }
            else
            {
                cout << "Phone book is empty." << endl;
            }
            break;
        case 6:
        {
            char file_name[256];
            cout << "Enter file name to load contacts: ";
            cin.getline(file_name, sizeof(file_name));

            file = fopen(file_name, "rb");
            if (file != nullptr)
            {
                fread(&num_contacts, sizeof(int), 1, file);

                for (int i = 0; i < num_contacts; i++)
                {
                    Contact contact;
                    contact.load_from_file(file);
                    contacts[i] = contact;
                }
                fclose(file);
                cout << "Contacts loaded from file." << endl;
            }
            else
            {
                cout << "Failed to open the file." << endl;
            }
        }
        break;
        case 7:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
