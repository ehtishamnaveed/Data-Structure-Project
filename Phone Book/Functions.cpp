#include "Structure.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <regex>

void makeContactList(PhoneBook* contactBook, Contact* record) {
    if (contactBook->head == nullptr) {
        contactBook->head = record;
        contactBook->rear = record;
        record->next = contactBook->head;
        record->previous = contactBook->rear;
    }
    else {
        record->previous = contactBook->rear;
        contactBook->rear->next = record;
        contactBook->rear = record;
        record->next = contactBook->head;
        record->previous = contactBook->rear;
    }
}


bool validateEmail(std::string& email) { 
	const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	return std::regex_match(email, pattern);
}


void parseFile(const std::string& filename, PhoneBook* Registry) {
	std::ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		std::cerr << "\nFile dont Exist\n";
		return;
	}
	std::string info;
	while (std::getline(inputFile,info)) {
		Contact* Entry = new Contact();

		std::istringstream data(info);
		data  >> Entry->PhoneNumber1 >> Entry->PhoneNumber2 >> Entry->FirstName >> Entry->LastName >> Entry->Email;
		if (!validateEmail(Entry->Email)) {
			std::cerr << "\nUser " << Entry->FirstName << Entry->LastName << " does not have a valid email address\n";
			delete Entry;
			continue;
		}
		if (Entry == nullptr) {
			std::cerr << "\nContact list is Empty\n";
			delete Entry;
			return;
		}
		makeContactList(Registry, Entry);
	}
	inputFile.close();
}

// Function to display the contents of a PhoneBook
void displayPhoneBook(const PhoneBook* phoneBook) {
	if (phoneBook == nullptr || phoneBook->head == nullptr) {
        std::cerr << "\nContact List is Empty\n";
        return;
    }

	Contact* entry = phoneBook->head;
	std::cout << "\nContact List:";
	do {
		std::cout << "\nName: " << entry->FirstName << " " << entry->LastName;
		std::cout << "\n1 Number: " << entry->PhoneNumber1;
		std::cout << "\n2 Number: " << entry->PhoneNumber2;
		std::cout << "\nEmail Address: " << entry->Email;
		std::cout << "\n------------------------\n";
		entry = entry->next;
	}while (entry != phoneBook->head);
}


Contact* searchPhoneNumber(Contact* registry, const std::string& number,const Contact* initialNode) {
	if (registry == nullptr ) {
		return nullptr;
	}
	else if (registry->next == initialNode) {
		return (registry->PhoneNumber1 == number || registry->PhoneNumber2 == number) ? registry : nullptr;
	}
	return searchPhoneNumber(registry->next,number,initialNode);
}


void getPhoneNumber(std::string& phonenumber,const std::string& position) {
	const std::regex pattern("^\\d{3}-\\d{3}-\\d{4}$");
	while (1) {
		std::cout << "Enter " << position << " Phone Number [***-***-****]: ";
		std::getline(std::cin, phonenumber);

		if (std::regex_match(phonenumber, pattern)) {break;}
		else {
				std::cerr << "\nPlease write in correct format\n";
				continue;
			}
	}
}


void getContactInfo(Contact* newContact) {
	std::cout << "Enter First Name: ";
	std::getline(std::cin, newContact->FirstName);
	std::cout << "Enter Last Name: ";
	std::getline(std::cin, newContact->LastName);

	getPhoneNumber(newContact->PhoneNumber1,"First");
	getPhoneNumber(newContact->PhoneNumber2,"Second");

	while (1) {
		std::cout << "Enter Email Address [xyz@uwx.com]: ";
		std::getline(std::cin, newContact->Email);
		 if (!validateEmail(newContact->Email)) {
		 	std::cerr << "\nPlease write in correct format\n";
		 	continue;}
		 else break;
	}
}


void writeContactsToFile(const std::string& filename,Contact* newContact,Contact* initialNode) {
	if (initialNode == nullptr) {
		std::cerr << "Error: Not data found in list to write\n";
		return;
	}
	remove("Contacts.txt");
	std::ofstream outputFile(filename, std::ios::app);
	if (!outputFile.is_open()) {
		std::cerr << "\nFile not Found\n";
		return;
	}
	do {
		outputFile << newContact->PhoneNumber1 
				   << " " << newContact->PhoneNumber2
				   << " " << newContact->FirstName
				   << " " << newContact->LastName
				   << " " << newContact->Email << "\n";
		newContact = newContact->next;
	}while (newContact->next != initialNode);
	outputFile.close();
}


void addNewContact(std::string& filename,Contact* newContact,PhoneBook* Registry) {
	getContactInfo(newContact);
	makeContactList(Registry,newContact);
	// writeContactsToFile(filename,newContact,Registry->head);
}


void removeContact(PhoneBook* Registry) {
	std::string number;
    std::cout << "\nEnter PhoneNumber: ";
    std::cin >> number;
    std::cout << number;
	Contact* contact = searchPhoneNumber(Registry->head,number,Registry->head);
    if (contact == nullptr) {
        std::cerr << "\nContact not Found";
        return;
    }
    else {
        std::cout << "\nContact Found: " << contact->FirstName;

        if (contact == Registry->head) {
	    	if (Registry->head == Registry->rear) {
	    		Registry->head = nullptr;
	    		Registry->rear = nullptr;
	    	}
	    	else {
		    	Registry->head = contact->next;
		    	Registry->rear->next = Registry->head;
		    	Registry->head->previous = Registry->rear;
		    }
	    }
	    else if(contact == Registry->rear) {
	    	Registry->rear = contact->previous;
	    	Registry->head->previous = Registry->rear;
	    	Registry->rear->next = Registry->head;
	    }
	    else {
	    	contact->previous->next = contact->next;
	    	contact->next->previous = contact->previous;
	    }
    }

    delete contact;
	std::cout << "\n Contact has been Deleted\n";
}


void checkForDuplication() {
	
}