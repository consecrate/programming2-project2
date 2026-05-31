#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::vector<std::string> split(std::string line, char delimiter);
std::string getCurrentDateTime();
int getValidatedInt(std::string prompt);
double getValidatedDouble(std::string prompt);
std::string trim(std::string text);

#endif
