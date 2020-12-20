#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class XMLNode
{
private:
	std::string m_name;
	std::string m_data;
	std::unordered_map<std::string, std::string>* m_attributes;
	std::unordered_map<std::string, std::vector<XMLNode>* >* m_childNodes;
public:
	XMLNode(const std::string& name);
	~XMLNode();

	std::string getName() const;

	std::string getData() const;

	std::string getAttribute(const std::string& attrib) const;

	XMLNode getChild(const std::string& childName) const;

	XMLNode getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const;

	std::vector<XMLNode> getChildren(const std::string& name) const;

	void addAttribute(const std::string& attrib, const std::string& value);

	void addChild(XMLNode child);

	void setData(const std::string& data);
};
