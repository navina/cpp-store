#include <iostream>
#include <fstream>
#include <google/protobuf/stubs/common.h>
#include "addressbook.pb.h"

using namespace std;

void promptForAddress(addressbook::Person* person) {
    cout << "Id? " ;
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Name? ";
    getline(cin, *person->mutable_name());

    cout << "Email? ";
    string email;
    getline(cin, email);
    if (!email.empty()) {
        person->set_email(email);
    }

    while (true) {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) {
            break;
        }

        addressbook::Person::PhoneNumber* phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") {
            phone_number->set_type(addressbook::Person::MOBILE);
        } else if (type == "home") {
            phone_number->set_type(addressbook::Person::HOME);
        } else if (type == "work") {
            phone_number->set_type(addressbook::Person::WORK);
        } else {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}

void showContacts(const addressbook::AddressBook& addr_book) {
    for (int i = 0; i < addr_book.people_size(); i++) {
        const addressbook::Person& person = addr_book.people(i);
        cout << "Person ID: " << person.id() << endl;
        cout << "Name: " << person.name() << endl;

        if (person.has_email()) {
            cout << "Email: " << person.email() << endl;
        }

        for (int j = 0; j < person.phones_size(); j++) {
            const addressbook::Person_PhoneNumber& phone = person.phones(j);
            switch(phone.type()) {
                case addressbook::Person::MOBILE:   //Not clear why this reference works for enum
                    cout << " Mobile #: ";
                    break;
                case addressbook::Person::HOME:
                    cout << "Home #: ";
                    break;
                case addressbook::Person::WORK:
                    cout << "Work #: ";
                    break;
            }
            cout << phone.number() << endl;
        }
    }
}

int main(int argc, char const *argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << "ADDRESS_BOOK_FILE" << endl;
        return -1;
    }
    addressbook::AddressBook address_book;

    // Read from file, if any data
    {
        fstream input(argv[1], ios::in | ios::binary);
        if (!input) {
            cout << argv[1] << " : File not found.  Creating a new file." << endl;
        } else if (!address_book.ParseFromIstream(&input)) {
            cerr << "Failed to parse address book." << endl;
            return -1;
        }
    }

    // Get input
    promptForAddress(address_book.add_people());

    // Serialize the data back to disk
    {
        fstream output(argv[1], ios::out | ios::trunc | ios::binary);
        if (!address_book.SerializeToOstream(&output)) {
            cerr << "Failed to write to address book!" << endl;
            return -1;
        }
    }

    // De-serialize data from file
    addressbook::AddressBook deserialized_address_book;

    {
        fstream input(argv[1], ios::in | ios::binary);
        if (!deserialized_address_book.ParseFromIstream(&input)) {
                cerr << argv[1] << " : Failed to parse binary data from file!" << endl;
                return -1;
        }
    }

    showContacts(deserialized_address_book);

    // Optional: Deletes all global libprotobuf objects
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}