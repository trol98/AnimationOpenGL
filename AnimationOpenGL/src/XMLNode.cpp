#pragma once
#include "XMLNode.h"
#include <vector>
#include <string>

XMLNode::XMLNode(const std::string& name)
	:m_name(name), m_childNodes(nullptr), m_attributes(nullptr)
{}

XMLNode::~XMLNode()
{
	if (m_childNodes != nullptr)
	{
		for (const auto& elem : *m_childNodes)
		{
			delete elem.second;
		}
	}
	delete m_childNodes;
	delete m_attributes;

	m_attributes = nullptr;
	m_childNodes = nullptr;
}

XMLNode::XMLNode(const XMLNode& other)
	:m_name(other.m_name),
	 m_data(other.m_data)
{
	m_attributes = new std::unordered_map<std::string, std::string>;
	for (const auto& elem : *other.m_attributes)
	{
		this->m_attributes->emplace(elem);
	}

	m_childNodes = new std::unordered_map<std::string, std::vector<XMLNode>* >;
	// TODO: finish this method
}

XMLNode& XMLNode::operator=(const XMLNode& other)
{
	// TODO: insert return statement here
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
		if ((nodes != nullptr) && (!nodes->empty()))
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

	/*
	for (XMLNode child : *children) 
	{
		std::string val = child.getAttribute(attrib);
		if (value == val) 
		{
			return &child;
		}
	}
	*/

	for (size_t i = 0; i < children->size(); i++)
	{
		std::string val = children->at(i).getAttribute(attrib);
		if (value == val)
		{
			// TODO: Examine this part, returning address to a local variable
			return &children->at(i);
		}
	}
	return nullptr;
}

std::vector<XMLNode>* XMLNode::getChildren(const std::string& name) const
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

	m_attributes->emplace(std::make_pair(attrib, value));
}

void XMLNode::addChild(XMLNode* child)
{
	if (m_childNodes == nullptr)
	{
		m_childNodes = new std::unordered_map<std::string, std::vector<XMLNode>*>();
	}

	if (m_childNodes->find(child->getName()) == m_childNodes->end())
	{
		m_childNodes->emplace(std::make_pair(child->getName(), new std::vector<XMLNode>()));
	}

	(m_childNodes->at(child->getName()))->emplace_back(child);
	// TODO: change this code to emplace a new pair and allocate memory
	// Check deconstructor
}


// DEBUG ONLY

std::unordered_map<std::string, std::string>* XMLNode::get_attributes()
{
	return m_attributes;
}
std::unordered_map<std::string, std::vector<XMLNode>*>* XMLNode::get_children()
{
	return m_childNodes;
}