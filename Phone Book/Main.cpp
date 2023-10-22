#include "Functions.h"
#include <conio.h>
#include <iostream>
#include <string>

int main() {
    std::string filename = "Contacts.txt"; // Replace with your input file's name
    PhoneBook* Registry = new PhoneBook();
    Contact* newContact = new Contact();
    parseFile(filename,Registry);

    displayPhoneBook(Registry);
    std::cout << "\nAdd Record:\n";
    addNewContact(filename,newContact,Registry);

    displayPhoneBook(Registry);
    std::cout << "\nRemove Record:\n";
    removeContact(Registry);

    std::cout << "\nSearch Record:\n";
    std::string number;
    std::cout << "\nEnter PhoneNumber: ";
    std::cin >> number;
    Contact* info = searchPhoneNumber(Registry->head,number,Registry->head);
    if (info == nullptr) {
        std::cerr << "\nContact not Found";
    }
    else {
        std::cout << "\nContact Found: " << info->FirstName;
    }
    displayPhoneBook(Registry);
    writeContactsToFile(filename,Registry->head,Registry->head);

    // Contact* currentContact = Registry->head;
    // while (currentContact != nullptr) {
    //     Contact* temp = currentContact;
    //     currentContact = currentContact->next;
    //     delete temp;
    // }
    delete newContact;
    // delete info;
    delete Registry;
    getch();
}