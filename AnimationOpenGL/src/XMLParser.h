#pragma once

#include <regex>
#include <string>

#include "XMLNode.h"

class XMLParser
{
public:
	static XMLNode loadXMLFile(const std::string& path);
private:
	static XMLNode loadNode(std::ifstream& file);
	static void addData(const std::string& line, XMLNode node);
	static void addAttributes(const std::vector<std::string>& titleParts, XMLNode node);
	static void addAttribute(const std::string& attributeLine, XMLNode node);
	static std::string getStartTag(const std::string& line);
	static bool checkClosedTag(const std::string& line);
private:
	static const std::regex DATA;
	static const std::regex START_TAG;
	static const std::regex ATTR_NAME;
	static const std::regex ATTR_VAL;
	static const std::regex CLOSED;
private:
	static const std::string WHITESPACE;

	static std::string ltrim(const std::string& s);
	static std::string rtrim(const std::string& s);
	static std::string trim(const std::string& s);
	static std::string remove(const std::string& s, char oldChar);
	static bool contains(const std::string& s, char ch);

	static std::vector<std::string> split(const std::string& s);
};

