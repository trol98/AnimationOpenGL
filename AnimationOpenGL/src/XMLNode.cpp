#pragma once
#include "XMLNode.h"
#include <vector>
#include <string>

XMLNode::XMLNode(const std::string& name)
	:m_name(name), m_childNodes(nullptr), m_attributes(nullptr)
{}

XMLNode::~XMLNode()
{
	m_attributes = nullptr;
	m_childNodes = nullptr;
}

XMLNode::XMLNode(const XMLNode& other)
	:m_name(other.m_name),
	 m_data(other.m_data)
{
	m_attributes = std::make_shared<std::unordered_map<std::string, std::string>>();
	for (const auto& elem : *other.m_attributes)
	{
		this->m_attributes->emplace(elem);
	}

	m_childNodes = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>>>();
	for (const auto& elem : *other.m_childNodes)
	{
		this->m_childNodes->emplace(std::make_pair(elem.first, std::make_shared<std::vector<std::shared_ptr<XMLNode>>>(elem.second)));
		// TODO: Check if this part doesn't make a copy of sha
	}
}

XMLNode& XMLNode::operator=(const XMLNode& other)
{
	// check for self-assignment
	if (&other == this)
		return *this;

	m_name = other.m_name;
	m_data = other.m_data;

	if (m_childNodes != nullptr)
	{
		for (auto& elem : *m_childNodes)
		{
			elem.second = nullptr;
		}
	}
	m_childNodes = nullptr;
	m_attributes = nullptr;

	m_attributes = std::make_shared<std::unordered_map<std::string, std::string>>();
	for (const auto& elem : *other.m_attributes)
	{
		this->m_attributes->emplace(elem);
	}

	m_childNodes = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>>>();
	for (const auto& elem : *other.m_childNodes)
	{
		this->m_childNodes->emplace(std::make_pair(elem.first, std::make_shared<std::vector<std::shared_ptr<XMLNode>>>()));
		this->m_childNodes->at(elem.first) = elem.second;
	}

	return *this;
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

std::shared_ptr<XMLNode>& XMLNode::getChild(const std::string& childName) const
{
	if (m_childNodes != nullptr) 
	{
		const auto& nodes = m_childNodes->at(childName);
		if ((nodes != nullptr) && (!nodes->empty()))
		{
			return nodes->at(0);
		}
	}
	return std::shared_ptr<XMLNode>(nullptr);
}

std::shared_ptr<XMLNode>& XMLNode::getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const
{
	const std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>& children = getChildren(childName);
	if (!(children == nullptr || children->empty())) 
	{
		for (size_t i = 0; i < children->size(); i++)
		{
			std::string val = children->at(i)->getAttribute(attrib);
			if (value == val)
			{
				return children->at(i);
			}
		}

		/*
		for (const XMLNode child : *children)
		{
			std::string val = child.getAttribute(attrib);
			if (value == val)
			{
				return child;
			}
		}
		*/
	}

	return std::shared_ptr<XMLNode>(nullptr);
}

std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>& XMLNode::getChildren(const std::string& name) const
{
	if (!(m_childNodes->at(name)->empty()))
	{
		return m_childNodes->at(name);
	}
	return std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>(nullptr);
}

void XMLNode::addAttribute(const std::string& attrib, const std::string& value)
{
	if (m_attributes == nullptr)
	{
		m_attributes = std::make_shared<std::unordered_map<std::string, std::string>>();
	}

	m_attributes->emplace(std::make_pair(attrib, value));
}

void XMLNode::addChild(std::shared_ptr<XMLNode>& child)
{
	if (m_childNodes == nullptr)
	{
		m_childNodes = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<XMLNode>>>>();
	}

	if (m_childNodes->find(child->getName()) == m_childNodes->end())
	{
		m_childNodes->emplace(std::make_pair(child->getName(), std::make_shared<std::vector<XMLNode>>()));
	}

	(m_childNodes->at(child->getName()))->emplace_back(child);
	// TODO: change this code to emplace a new pair and allocate memory
	// Check deconstructor
}


// DEBUG ONLY

std::shared_ptr<std::unordered_map<std::string, std::string>>& XMLNode::get_attributes()
{
	return m_attributes;
}
std::shared_ptr<std::unordered_map<std::string, std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>>>& XMLNode::get_children()
{
	return m_childNodes;
}
