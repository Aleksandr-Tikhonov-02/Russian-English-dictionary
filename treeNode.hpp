#ifndef _TREE_NODE_
#define _TREE_NODE_

#include <utility>
#include <string>
#include "orederedList.hpp"

struct treeNode
{
	enum class Color
	{
		BLACK,
		RED
	};
	treeNode* left_;
	treeNode* right_;
	treeNode* p_;
	std::pair<std::string, OrderedList*> treeKey_;
	Color color_;

	treeNode(std::pair<std::string, OrderedList*> treeKey = std::make_pair(std::string(), nullptr), 
		Color color = Color::BLACK, treeNode* p = nullptr, treeNode* left = nullptr, treeNode* right = nullptr):
		left_(left), color_(color), p_(p), right_(right), treeKey_(treeKey)
	{};
	~treeNode()
	{
		delete treeKey_.second;
	}
};

#endif
