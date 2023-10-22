#include <string>

struct Contact {
	Contact():next(nullptr),previous(nullptr) {}

	std::string PhoneNumber1;
	std::string PhoneNumber2;
	std::string FirstName;
	std::string LastName;
	std::string Email;
	Contact *next;
	Contact *previous;
};

struct PhoneBook {
	PhoneBook():head(nullptr),rear(nullptr) {}

	Contact *head;
	Contact *rear;
};