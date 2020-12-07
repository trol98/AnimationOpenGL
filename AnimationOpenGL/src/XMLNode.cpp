#pragma once
#include "XMLNode.h"


XMLNode::XMLNode(const std::string& name)
	:m_name(name)
{}

std::string XMLNode::getName() const
{
	return m_name;
}

std::string XMLNode::getData() const
{
	return m_data;
}

std::string XMLNode::getAttribute(const std::string& attrib) const
{
	return m_attributes.at(attrib);
}

XMLNode XMLNode::getChild(const std::string& childName) const
{
	const auto& nodes = m_childNodes.at(childName);
	if (!nodes.empty())
	{
		return nodes[0];
	}
	return nullptr;
}

XMLNode XMLNode::getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const
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

std::vector<XMLNode> XMLNode::getChildren(const std::string& name) const
{
	std::vector<XMLNode> children = m_childNodes.at(name);
	if (!children.empty())
		return children;
	return std::vector<XMLNode>();
}

void XMLNode::addAttribute(const std::string& attrib, const std::string& value)
{
	m_attributes[attrib] = value;
}

void XMLNode::addChild(XMLNode child)
{
	m_childNodes.at(child.getName()).emplace_back(child);
}

void XMLNode::setData(const std::string& data)
{
	m_data = data;
}
