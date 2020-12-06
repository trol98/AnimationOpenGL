#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class XMLNode
{
private:
	std::string m_name;
	std::unordered_map<std::string, std::string> m_attributes;
	std::string m_data;
	std::unordered_map<std::string, std::vector<XMLNode>> m_childNodes;
public:
	XMLNode(const std::string& name)
		:m_name(name)
	{}

	std::string getName() const
	{
		return m_name;
	}

	std::string getData() const
	{
		return m_data;
	}

	std::string getAttribute(const std::string& attrib) const
	{
		return m_attributes.at(attrib);
	}

	XMLNode getChild(const std::string& childName) const 
	{
		const auto& nodes = m_childNodes.at(childName);
		if (!nodes.empty())
		{
			return nodes[0];
		}
		return nullptr;
	}

	XMLNode getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const 
	{
		const auto& nodes = m_childNodes.at(childName);
		if (nodes.empty())
		{
			return nullptr;
		}
		for (const auto& node : nodes)
		{
			if (node.getAttribute(attrib) == value)
				return node;
		}
		return nullptr;
	}

	std::vector<XMLNode> getChildren(const std::string& name) const 
	{
		std::vector<XMLNode> children = m_childNodes.at(name);
		if (!children.empty())
			return children;
		return std::vector<XMLNode>();
	}

	void addAttribute(const std::string& attrib, const std::string& value)
	{
		m_attributes[attrib] = value;
	}

	void addChild(XMLNode child)
	{
		m_childNodes.at(child.getName()).emplace_back(child);
	}

	void setData(const std::string& data)
	{
		m_data = data;
	}
};
