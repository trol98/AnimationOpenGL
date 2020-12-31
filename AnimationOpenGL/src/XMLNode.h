#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

class XMLNode
{
private:
	std::string m_name;
	std::string m_data;
	std::unique_ptr<std::unordered_map<std::string, std::string>> m_attributes;
	std::unique_ptr<std::unordered_map<std::string, std::unique_ptr<std::vector<XMLNode>>>> m_childNodes;
public:
	XMLNode(const std::string& name);
	~XMLNode();
	XMLNode(const XMLNode& other);
	XMLNode& operator=(const XMLNode& other);

	std::string getName() const;

	std::string getData() const;

	std::string getAttribute(const std::string& attrib) const;

	std::unique_ptr<XMLNode> getChild(const std::string& childName) const;

	std::unique_ptr<XMLNode> getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const;

	std::unique_ptr<std::vector<XMLNode>> getChildren(const std::string& name) const;

	void addAttribute(const std::string& attrib, const std::string& value);

	void addChild(std::unique_ptr<XMLNode>& child);

	void setData(const std::string& data);

	// FOR DEBUG ONLY

	std::unique_ptr<std::unordered_map<std::string, std::string>>& get_attributes();
	std::unique_ptr<std::unordered_map<std::string, std::unique_ptr<std::vector<XMLNode>>>>& get_children();
};
