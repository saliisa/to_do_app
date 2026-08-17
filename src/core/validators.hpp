#ifndef VALIDATORS_HPP
#define VALIDATORS_HPP
#include <string>
#include <cctype>


bool checkLeapYear(int year);
bool validateTitle(std::string title);
bool validatePriority(std::string priority);
bool validateDate(std::string date);
bool validateStatus(std::string status);
bool validateInt(int value, int min, int max);


#endif