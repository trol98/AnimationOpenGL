#pragma once

#include <string>
#include <vector>
#include <sstream>

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
	return rtrim(ltrim(s));
}

std::string remove(const std::string& s, char oldChar)
{
	std::string temp(s);
	temp.erase(std::remove(temp.begin(), temp.end(), oldChar), temp.end());
	return temp;
}

std::vector<std::string> split(const std::string& s, char splitCharacter)
{
	std::istringstream ss(s);
	std::vector<std::string> output;

	std::string substring;
	while (getline(ss, substring, splitCharacter))
	{
		output.emplace_back(substring);
	}

	return output;
}

bool contains(const std::string& s, char ch)
{
	return (s.find(ch) != std::string::npos);
}