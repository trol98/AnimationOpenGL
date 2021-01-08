#pragma once
#include "XMLNode.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>



XMLNode::XMLNode(const std::string& name)
	:m_name(name), m_childNodes(nullptr), m_attributes(nullptr)
{}

XMLNode::~XMLNode()
{
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

std::shared_ptr<XMLNode> XMLNode::getChild(const std::string& childName) const
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

std::shared_ptr<XMLNode> XMLNode::getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const
{
	const auto& children = getChildren(childName);
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
	}
	
	return std::shared_ptr<XMLNode>(nullptr);
}

std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>> XMLNode::getChildren(const std::string& name) const
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
		m_childNodes = std::make_shared<std::unordered_map<std::string, std::shared_ptr<std::vector<std::shared_ptr<XMLNode>>>>>();
	}

	// if child doesn't exist in m_childNodes add a new map entry
	if (m_childNodes->find(child->getName()) == m_childNodes->end())
	{
		m_childNodes->emplace(std::make_pair(child->getName(), std::make_shared<std::vector<std::shared_ptr<XMLNode>>>()));
	}

	// add child node to map 
	m_childNodes->at(child->getName())->emplace_back(child);
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
