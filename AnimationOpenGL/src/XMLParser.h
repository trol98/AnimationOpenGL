#pragma once

#include <regex>
#include <string>
#include <memory>
#include <vector>

#include "XMLNode.h"

class XMLParser
{
public:
	static std::shared_ptr<XMLNode> loadXMLFile(const std::string& path);
private:
	static std::shared_ptr<XMLNode> loadNode(std::ifstream& file);
	static void addData(const std::string& line, std::shared_ptr<XMLNode>& node);
	static void addAttributes(const std::vector<std::string>& titleParts, std::shared_ptr<XMLNode>& node);
	static void addAttribute(const std::string& attributeLine, std::shared_ptr<XMLNode>& node);
	static std::string getStartTag(const std::string& line);
	static bool checkClosedTag(const std::string& line);
private:
	static const std::regex DATA;
	static const std::regex START_TAG;
	static const std::regex ATTR_NAME;
	static const std::regex ATTR_VAL;
	static const std::regex CLOSED;
	static const std::string WHITESPACE;
private:
	// string utility methods
	static std::string ltrim(const std::string& s);
	static std::string rtrim(const std::string& s);
	static std::string trim(const std::string& s);
	static std::string remove(const std::string& s, char oldChar);

	static bool contains(const std::string& s, char ch);
	static std::vector<std::string> split(const std::string& s, char splitCharacter);
};

