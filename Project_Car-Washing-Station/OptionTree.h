#pragma once

#include<iostream>
#include "Util.h"
#include<vector>

struct OptionTreeNode {
public:
	std::string content;
	float price = 0;
	std::vector< OptionTreeNode*> children;

	OptionTreeNode() : content() {

	}
	OptionTreeNode(std::string content) : content(content) {

	}

	~OptionTreeNode() {
		for (OptionTreeNode* child : children) {
			delete child;
		}
	}

};



class OptionTree
{
protected:

	OptionTreeNode root;

	OptionTreeNode* getNode(const std::vector<std::string>& nodePath) {
		if (nodePath.size() == 0) {
			return nullptr;
		}
		else if (nodePath[0] != root.content) {
			return nullptr;
		}
		else {
			OptionTreeNode* current = &root;
			// Reserved index 0 for root
			for (size_t i = 1; i < nodePath.size(); i++) {
				bool found = false;
				for (OptionTreeNode* next : current->children) {
					if (next->content == nodePath[i]) {
						current = next;
						found = true;
						break;
					}
				}
				if (!found) {
					return nullptr;
				}
			}
			return current;
		}
	}

public:
	OptionTree() {
		root = OptionTreeNode("Service");
	}

	void GetOptions(const std::vector<std::string>& nodePath, std::vector<std::string>& out) {
		OptionTreeNode* node = getNode(nodePath);
		if (node == nullptr) {
			return;
		}
		for (OptionTreeNode* next : node->children) {
			out.push_back(next->content);
		}
	}

	bool AddOption(const std::vector<std::string>& nodePath, const std::string& option) {
		OptionTreeNode* node = getNode(nodePath);
		if (node == nullptr) {
			return false;
		}
		// If the option already exists, ignore
		for (OptionTreeNode* next : node->children) {
			if (next->content == option) {
				return false;
			}
		}
		node->children.push_back(new OptionTreeNode(option));
		return true;
	}

	bool AddOption(const std::string& option) {
		// If the option already exists, ignore
		for (OptionTreeNode* next : root.children) {
			if (next->content == option) {
				return false;
			}
		}
		root.children.push_back(new OptionTreeNode(option));
		return true;
	}

	bool RemoveService(std::vector<std::string> path) {
		if (path.size() < 2) {
			return false;
		}
		std::string last = path[path.size() - 1];
		path.pop_back();
		OptionTreeNode* node = getNode(path);
		if (node == nullptr) {
			return false;
		}
		for (size_t i = 0; i < node->children.size(); i++) {
			OptionTreeNode* child = node->children[i];
			if (child->content == last) {
				node->children.erase(node->children.begin() + i);
				return true;
			}
		}
		return false;
	}

	// Adds all children and their children of 'current' as paths to the results array. Performs a preorder traversal.
	// Path of current: for the root it would be {root.content}, for a node A if would be {root.content, ... , a.content}
	// Function DOES NOT add this node to results if the condition
	void FindAllExclusive(std::vector<std::vector<std::string>>& results, const std::vector<std::string>& pathOfCurrent, OptionTreeNode* current) {
		for (OptionTreeNode* child : current->children) {
			results.push_back(pathOfCurrent);
			std::vector<std::string>& pathToChild = results[results.size() - 1];
			pathToChild.push_back(child->content);
			FindAllExclusive(results, pathToChild, child);
		}
	}

	// Finds all paths that have 'query' as a substring
	// Path of current: for the root it would be {root.content}, for a node A if would be {root.content, ... , a.content}
	// Function DOES add this node to results if the condition
	void FindAllInclusive(std::string query, std::vector<std::vector<std::string>>& results, const std::vector<std::string>& pathOfCurrent, OptionTreeNode* current) {

		if (pathOfCurrent.size() == 0 || current == nullptr) {
			// Error: function should not work without path
			return;
		}
		if (Util::containsIgnoreCase(pathOfCurrent[pathOfCurrent.size() - 1], query)) {
			results.push_back(pathOfCurrent);
			FindAllExclusive(results, pathOfCurrent, current);
			return;
		}

		// If content if this does not include the query, iterate over children
		for (OptionTreeNode* child : current->children) {
			std::vector<std::string> pathToChild = pathOfCurrent;
			pathToChild.push_back(child->content);
			FindAllInclusive(query, results, pathToChild, child);
		}
	}

	void FindAll(std::string query, std::vector<std::vector<std::string>>& results) {

		std::vector<std::string> pathOfRoot = { root.content };
		FindAllInclusive(query, results, pathOfRoot, &root);
	}


};

