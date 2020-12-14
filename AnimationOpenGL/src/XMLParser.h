#pragma once

#include <list>
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
	static std::string& getStartTag(const std::string& line);
private:
	static const std::string DATA;
	static const std::string START_TAG;
	static const std::string ATTR_NAME;
	static const std::string ATTR_VAL;
	static const std::string CLOSED;
private:
	static std::string WHITESPACE;

	static std::string ltrim(const std::string& s);
	static std::string rtrim(const std::string& s);
	static std::string trim(const std::string& s);
};

std::string DATA = R"(>(.+?)<)";
std::string START_TAG = R"(<(.+?)>)";
std::string ATTR_NAME = R"((.+?)=)";
std::string ATTR_VAL = R"(\"(.+?)\")";
std::string CLOSED = R"((</|/>))";

std::string XMLParser::WHITESPACE = " \n\r\t\f\v";