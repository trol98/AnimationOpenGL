#pragma once
#include "XMLNode.h"


XMLNode::XMLNode(const std::string& name)
	:m_name(name)
{}

XMLNode::~XMLNode()
{
	delete m_attributes;
	delete m_childNodes;
}

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
	if (m_attributes != nullptr) 
	{
		return m_attributes->at(attrib);
	}
	return nullptr;
}

XMLNode XMLNode::getChild(const std::string& childName) const
{
	if (m_childNodes != nullptr) 
	{
		const auto nodes = m_childNodes->at(childName);
		if (nodes != nullptr && !nodes->empty()) 
		{
			return nodes->at(0);
		}
	}
	return nullptr;
}

XMLNode* XMLNode::getChildWithAttribute(const std::string& childName, const std::string& attrib, const std::string& value) const
{
	const auto children = getChildren(childName);
	if (children == nullptr || children.isEmpty()) {
		return null;
	}
	for (XmlNode child : children) {
		String val = child.getAttribute(attr);
		if (value.equals(val)) {
			return child;
		}
	}
	return null;
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

/*
public class XmlNode {

	private String name;
	private Map<String, String> attributes;
	private String data;
	private Map<String, List<XmlNode>> childNodes;

public XmlNode getChildWithAttribute(String childName, String attr, String value) {
	List<XmlNode> children = getChildren(childName);
	if (children == null || children.isEmpty()) {
		return null;
	}
	for (XmlNode child : children) {
		String val = child.getAttribute(attr);
		if (value.equals(val)) {
			return child;
		}
	}
	return null;
}

public List<XmlNode> getChildren(String name) {
	if (childNodes != null) {
		List<XmlNode> children = childNodes.get(name);
		if (children != null) {
			return children;
		}
	}
	return new ArrayList<XmlNode>();
}

protected void addAttribute(String attr, String value) {
	if (attributes == null) {
		attributes = new HashMap<String, String>();
	}
	attributes.put(attr, value);
}

protected void addChild(XmlNode child) {
	if (childNodes == null) {
		childNodes = new HashMap<String, List<XmlNode>>();
	}
	List<XmlNode> list = childNodes.get(child.name);
	if (list == null) {
		list = new ArrayList<XmlNode>();
		childNodes.put(child.name, list);
	}
	list.add(child);
}
public String getAttribute(String attr) {
	if (attributes != null) {
		return attributes.get(attr);
	}
	else {
		return null;
	}
}
public XmlNode getChild(String childName) {
	if (childNodes != null) {
		List<XmlNode> nodes = childNodes.get(childName);
		if (nodes != null && !nodes.isEmpty()) {
			return nodes.get(0);
		}
	}
	return null;

}

}
*/