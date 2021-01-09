#pragma once

#include <string>
#include <vector>
#include <sstream>

const std::string WHITESPACE = " \n\r\t\f\v";


std::string ltrim(const std::string& s);

std::string rtrim(const std::string& s);

std::string trim(const std::string& s);

std::string remove(const std::string& s, char oldChar);

std::vector<std::string> split(const std::string& s, char splitCharacter);

bool contains(const std::string& s, char ch);