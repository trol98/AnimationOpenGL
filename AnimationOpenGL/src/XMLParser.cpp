#include "XMLParser.h"

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include <sstream>

const std::regex XMLParser::DATA(R"(>(.+?)<)");
const std::regex XMLParser::START_TAG(R"(<(.+?)>)");
const std::regex XMLParser::ATTR_NAME(R"((.+?)=)");
const std::regex XMLParser::ATTR_VAL(R"(\"(.+?)\")");
const std::regex XMLParser::CLOSED(R"((</|/>))");


const std::string XMLParser::WHITESPACE = " \n\r\t\f\v";

std::shared_ptr<XMLNode> XMLParser::loadXMLFile(const std::string& path)
{
	std::ifstream file(path);
	
	if (!file)
	{
		std::cout << "Can't find the XML file: " << path << '\n';
		return std::shared_ptr<XMLNode>(nullptr);
	}

	file.exceptions(std::ios::badbit | std::ios::failbit);

	std::shared_ptr<XMLNode> node = nullptr;

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
std::shared_ptr<XMLNode> XMLParser::loadNode(std::ifstream& file)
{
	std::string line;
	std::getline(file, line);
	line = trim(line);
	

	if (line.rfind(R"(</)", 0) == 0) 
	{
		return std::shared_ptr<XMLNode>(nullptr);
	}

	// spliting by space
	std::vector<std::string> startTagParts = split(getStartTag(line), ' ');

	std::shared_ptr<XMLNode> node = std::make_shared<XMLNode>(remove(startTagParts[0], '/'));
	
	std::cout << node->getName() << std::endl; // ONLY FOR DEBUGGING

	addAttributes(startTagParts, node);
	addData(line, node);

	if (checkClosedTag(line)) 
	{
		return node;
	}
	std::shared_ptr<XMLNode> child = nullptr;
	while ((child = loadNode(file)) != nullptr)
	{
		node->addChild(child);
	}
	return node;
}
void XMLParser::addData(const std::string& line, std::shared_ptr<XMLNode>& node)
{
	std::smatch matches;
	std::regex_search(line, matches, DATA);
	if (!matches.empty())
	{
		node->setData(matches.str(1));
	}
}
void XMLParser::addAttributes(const std::vector<std::string>& titleParts, std::shared_ptr<XMLNode>& node)
{
	std::smatch nameMatch, valMatch;
	for (size_t i = 1; i < titleParts.size(); i++) 
	{
			if (contains(titleParts[i],'=')) 
			{
				// NOTE: resetting the state of smatch objects is not needed

				std::regex_search(titleParts[i], nameMatch, ATTR_NAME);
				std::regex_search(titleParts[i], valMatch, ATTR_VAL);

				node->addAttribute(nameMatch.str(1), valMatch.str(1));
			}
	}
}
void XMLParser::addAttribute(const std::string& attributeLine, std::shared_ptr<XMLNode>& node)
{
	// NOTE: This method is currently not used anywhere
	std::smatch nameMatch, valMatch;

	std::regex_search(attributeLine, nameMatch, ATTR_NAME);
	std::regex_search(attributeLine, valMatch, ATTR_VAL);
		
	node->addAttribute(nameMatch.str(1), valMatch.str(1));
}

std::string XMLParser::getStartTag(const std::string& line)
{
	std::smatch matches;
	std::regex_search(line, matches, START_TAG);
	return matches.str(1);
}

bool XMLParser::checkClosedTag(const std::string& line)
{
	std::smatch matches;
	return std::regex_search(line, matches, CLOSED);
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

std::string XMLParser::remove(const std::string& s, char oldChar)
{
	std::string temp(s);
	temp.erase(std::remove(temp.begin(), temp.end(), oldChar), temp.end());
	return temp;
}

std::vector<std::string> XMLParser::split(const std::string& s, char splitCharacter)
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

bool XMLParser::contains(const std::string& s, char ch)
{
	return (s.find(ch) != std::string::npos);
}