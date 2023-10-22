#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Structure.h"
#include <string> 

void makeContactList(PhoneBook* contactBook, Contact* record);
void parseFile(const std::string& filename, PhoneBook* Registry);
void displayPhoneBook(const PhoneBook* phoneBook);
Contact* searchPhoneNumber(Contact* registry, const std::string& number,const Contact* initialNode);
bool validateEmail(std::string& email);
void addNewContact(std::string& filename,Contact* newContact,PhoneBook* Registry);
void getContactInfo(Contact* newContact);
void getPhoneNumber(std::string& phonenumber);
void writeContactsToFile(const std::string& filename,Contact* newContact,Contact* initialNode);
void removeContact(PhoneBook* Registry);
void checkForDuplication();

#endif
