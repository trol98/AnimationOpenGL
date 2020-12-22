#pragma once
#include "XMLNode.h"
#include <vector>
#include <string>

XMLNode::XMLNode(const std::string& name)
	:m_name(name)
{}

XMLNode::~XMLNode()
{
	delete m_attributes;
	delete m_childNodes;

	m_attributes = nullptr;
	m_childNodes = nullptr;
}

std::string XMLNode::getName() const
{
	return m_name;
}

std::string XMLNode::getData() const
{
	return m_data;
}

void XMLNode::setData(const std::string& data)
{
	m_data = data;
}

std::string XMLNode::getAttribute(const std::string& attrib) const
{
	if (m_attributes != nullptr) 
	{
		return m_attributes->at(attrib);
	}
	return nullptr;
}

XMLNode* XMLNode::getChild(const std::string& childName) const
{
	if (m_childNodes != nullptr) 
	{
		const auto nodes = m_childNodes->at(childName);
		if (nodes != nullptr && !nodes->empty()) 
		{
			return &nodes->at(0);
		}
	}
	return nullptr;
}

XMLNode* XMLNode::getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const
{
	const auto children = getChildren(childName);
	if (children == nullptr || children->empty()) {
		return nullptr;
	}
	for (XMLNode child : *children) 
	{
		std::string val = child.getAttribute(attrib);
		if (value == val) 
		{
			return &child;
		}
	}
	return nullptr;
}

std::vector<XMLNode> XMLNode::getChildren(const std::string& name) const
{
	std::vector<XMLNode>* children = m_childNodes->at(name);
	if (!children->empty())
	{
		return m_childNodes->at(name);
	}
	return nullptr;
}

void XMLNode::addAttribute(const std::string& attrib, const std::string& value)
{
	if (m_attributes == nullptr)
	{
		m_attributes = new std::unordered_map<std::string, std::string>();
	}
	m_attributes->at(attrib) = value;
}

void XMLNode::addChild(XMLNode* child)
{
	m_childNodes.at(child->getName())->emplace_back(child);
}
