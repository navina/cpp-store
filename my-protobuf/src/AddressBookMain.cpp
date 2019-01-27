#include <iostream>
#include <fstream>
#include "addressbook.pb.h"

using namespace std;

void promptForAddress(addressbook::Person* person) {
    cout << "Id? " ;
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, "\n");

    cout << "Name? ";
    getline(cin, *person->mutable_name());

    cout << "Email? ";
    string email;
    getline(cin, email);
    if (!email.isEmpty()) {
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
            cout << argv[1] << ": File not found.  Creating a new file." << endl;
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
        if (!address_book.SerializeToStream(output)) {
            cerr << "Failed to write to address book!" << endl;
            return -1;
        }
    }

    // Optional: Deletes all global libprotobuf objects
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}