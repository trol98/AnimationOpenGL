#include "XMLParser.h"

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <sstream>

XMLNode XMLParser::loadXMLFile(const std::string& path)
{
	std::ifstream file(path);
	
	if (!file)
	{
		std::cout << "Can't find the XML file: " << path << '\n';
		return nullptr;
	}

	file.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::failbit);

	XMLNode node = nullptr;

	try
	{
		std::string temp;
		std::getline(file, temp);
		node = loadNode(file);
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

	file.close();
	return node;
}
XMLNode XMLParser::loadNode(std::ifstream& file)
{
	
	std::string line;
	std::getline(file, line);
	trim(line);


	if (line.rfind(R"(</)", 0) == 0) 
	{
		return nullptr;
	}

	// spliting by space
	std::vector<std::string> startTagParts = split(getStartTag(line));


}
void XMLParser::addData(const std::string& line, XMLNode& node)
{

}
void XMLParser::addAttributes(const std::string& titleParts, XMLNode& node)
{

}
void XMLParser::addAttribute(const std::string& attributeLine, XMLNode& node)
{

}

std::string XMLParser::getStartTag(const std::string& line)
{
	std::smatch matches;
	std::regex_search(line, matches, START_TAG);
	return matches.str(1);
}




std::string XMLParser::ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string XMLParser::rtrim(const std::string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string XMLParser::trim(const std::string& s)
{
	return rtrim(ltrim(s));
}

std::vector<std::string> XMLParser::split(const std::string& s)
{
	std::istringstream ss(s);
	std::vector<std::string> output;

	std::string substring;
	while (ss)
	{
		ss >> substring;
		output.emplace_back(substring);
	}

	return output;
}