#pragma once

#include <string>
#include <vector>
#include <sstream>

class StringUtils
{
	static const std::string WHITESPACE;
public:
	static std::string trim(const std::string& s);
	static std::string ltrim(const std::string& s);
	static std::string rtrim(const std::string& s);

	static std::string remove(const std::string& s, char oldChar);

	static std::vector<std::string> split(const std::string& s, char splitCharacter);

	static bool contains(const std::string& s, char ch);
};
