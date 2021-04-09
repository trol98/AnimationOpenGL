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
	std::shared_ptr<std::unordered_map<std::string, std::string>> m_attributes;
	std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>>> m_childNodes;
public:
	XMLNode(const std::string& name);
	~XMLNode();

	std::string getName() const;

	std::string getData() const;

	std::string getAttribute(const std::string& attrib) const;

	std::shared_ptr<XMLNode> getChild(const std::string& childName) const;

	std::shared_ptr<XMLNode> getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const;

	std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>> getChildren(const std::string& name) const;

	void addAttribute(const std::string& attrib, const std::string& value);

	void addChild(std::shared_ptr<XMLNode>& child);

	void setData(const std::string& data);
};
