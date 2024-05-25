#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Contact {
public:
    string name;
    string phoneNumber;

    Contact(string name, string phoneNumber) {
      this->name = name;
      this->phoneNumber = phoneNumber;
    }
};

class MobilePhone {
private:
    vector<Contact> contacts;

public:
    void addContact(const Contact *contact) {
        this->contacts.push_back(*contact);
    }

    void call(const string *number) {
        cout << "CALL " << *number << endl;
    }

    void sendSMS(const string *number) {
        cout << "SMS sent to " << *number << endl;
    }

    bool findContact(const string *searchQuery, Contact *foundContact) {
        for (Contact contact : this->contacts) {
            if (contact.name == *searchQuery || contact.phoneNumber == *searchQuery) {
                *foundContact = contact;

                return true;
            }
        }
        return false;
    }
};

int main() {
    MobilePhone phone;
    string command;

    while (true) {
        cout << "Enter a command: ";
        getline(cin, command);

        if (command == "exit") {
            break;

        } else if (command == "add") {
            string name;
            string phoneNumber;
            Contact *contact;

            cout << "Enter contact's name: ";
            getline(cin, name);

            cout << "Enter contact's phone number: ";
            getline(cin, phoneNumber);

            contact = new Contact(name, phoneNumber);

            phone.addContact(contact);

            delete contact;

        } else if (command == "call") {
            string number;
            Contact *foundContact;

            cout << "Enter the phone number or contact's name to call: ";
            getline(cin, number);

            foundContact = new Contact("", "");

            if (phone.findContact(&number, foundContact))
                phone.call(&foundContact->phoneNumber);
            else
                cout << "Contact not found." << endl;

            delete foundContact;

        } else if (command == "sms") {
            string number;
            Contact *foundContact;

            cout << "Enter the phone number or contact's name to send SMS: ";
            getline(cin, number);

            foundContact = new Contact("", "");

            if (phone.findContact(&number, foundContact))
                phone.sendSMS(&foundContact->phoneNumber);
            else
                cout << "Contact not found." << endl;

            delete foundContact;
        }
    }

    return 0;
}