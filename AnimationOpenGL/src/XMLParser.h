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
	static void addData(const std::string& line, XMLNode& node);
	static void addAttributes(const std::string& titleParts, XMLNode& node);
	static void addAttribute(const std::string& attributeLine, XMLNode& node);
	static std::string getStartTag(const std::string& line);
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

	static std::string replace(const std::string& s, char oldChar, char newChar);

	static std::vector<std::string> split(const std::string& s);
};

const std::regex XMLParser::DATA			(R"(>(.+?)<)");
const std::regex XMLParser::START_TAG		(R"(<(.+?)>)");
const std::regex XMLParser::ATTR_NAME		(R"((.+?)=)");
const std::regex XMLParser::ATTR_VAL		(R"(\"(.+?)\")");
const std::regex XMLParser::CLOSED			(R"((</|/>))");


const std::string XMLParser::WHITESPACE = " \n\r\t\f\v";