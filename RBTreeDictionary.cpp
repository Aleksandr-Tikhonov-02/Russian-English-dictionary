#include "RBTreeDictionary.hpp"
#include <iostream>
#include "utility"
#include "orederedList.hpp"
#include "Stack.hpp"
#include "StackArray.hpp"

RBTreeDictionary::RBTreeDictionary() :
	root_()
{

}

RBTreeDictionary::RBTreeDictionary(const std::string& treeKey, const std::string& meaning)
{
	root_ = new treeNode(std::make_pair(treeKey, new OrderedList(meaning)));
};

RBTreeDictionary::~RBTreeDictionary()
{
	deleteSubtree(root_);
}

void RBTreeDictionary::deleteSubtree(treeNode* node)
{
	if (!root_)
	{
		return;
	}
	if (node->left_)
	{
		deleteSubtree(node->left_);
	}
	if (node->right_)
	{
		deleteSubtree(node->right_);
	}
	delete node;
}

void RBTreeDictionary::insert(const std::string& treeKey, const std::string& meaning)
{
	if (!root_)
	{
		root_ = new treeNode(std::make_pair(treeKey, new OrderedList(meaning)));
		return;
	}
	treeNode* parent = nullptr;
	treeNode* current = root_;
	while (current)
	{
		if (treeKey == current->treeKey_.first)
		{
			current->treeKey_.second->insertItem(meaning);
			return;
		}
		else if (treeKey > current->treeKey_.first)
		{
			parent = current;
			current = current->right_;
		}
		else
		{
			parent = current;
			current = current->left_;
		}
	}
	if (parent->treeKey_.first < treeKey)
	{
		parent->right_ = new treeNode(std::make_pair(treeKey, new OrderedList(meaning)), treeNode::Color::RED, parent);
		fixInsert(parent->right_);
	}
	else
	{
		parent->left_ = new treeNode(std::make_pair(treeKey, new OrderedList(meaning)), treeNode::Color::RED, parent);
		fixInsert(parent->left_);
	}
}

void RBTreeDictionary::fixInsert(treeNode* node)
{
	while (node != root_ && node->p_->color_ == treeNode::Color::RED)
	{
		if (node->p_ == node->p_->p_->left_)
		{
			treeNode* uncle = node->p_->p_->right_;
			if (uncle && uncle->color_ == treeNode::Color::RED)
			{
				node->p_->color_ = treeNode::Color::BLACK;
				uncle->color_ = treeNode::Color::BLACK;
				node->p_->p_->color_ = treeNode::Color::RED;
				node = node->p_->p_;
			}
			else
			{
				if (node == node->p_->right_)
				{
					node = node->p_;
					rotateLeft(node);
				}
				node->p_->color_ = treeNode::Color::BLACK;
				node->p_->p_->color_ = treeNode::Color::RED;
				rotateRight(node->p_->p_);
			}
		}
		else
		{
			treeNode* uncle = node->p_->p_->left_;
			if (uncle && uncle->color_ == treeNode::Color::RED)
			{
				node->p_->color_ = treeNode::Color::BLACK;
				uncle->color_ = treeNode::Color::BLACK;
				node->p_->p_->color_ = treeNode::Color::RED;
				node = node->p_->p_;
			}
			else
			{
				if (node == node->p_->left_)
				{
					node = node->p_;
					rotateRight(node);
				}
				node->p_->color_ = treeNode::Color::BLACK;
				node->p_->p_->color_ = treeNode::Color::RED;
				rotateLeft(node->p_->p_);
			}
		}
	}
	root_->color_ = treeNode::Color::BLACK;
}

bool RBTreeDictionary::search(const std::string& treeKey)
{
	return (searchTreeNode(treeKey) != nullptr);
}

void RBTreeDictionary::deleteWord(const std::string& treeKey)
{
	treeNode* current = root_;
	while (current)
	{
		if (current->treeKey_.first < treeKey)
		{
			current = current->right_;
		}
		else if (current->treeKey_.first > treeKey)
		{
			current = current->left_;
		}
		else
		{
			break;
		}
	}
	if (!current)
	{
		return;
	}
	deleteNode(current);
}

treeNode* RBTreeDictionary::searchTreeNode(const std::string& treeKey)
{
	treeNode* current = root_;
	while (current != nullptr)
	{
		if (treeKey < current->treeKey_.first)
		{
			current = current->left_;
		}
		else if (treeKey > current->treeKey_.first)
		{
			current = current->right_;
		}
		else
		{
			break;
		}
	}
	return current;
}

void RBTreeDictionary::deleteNode(treeNode* node)
{
	treeNode* replaceNode = findReplacement(node);
	bool bothBlack = ((replaceNode == nullptr || replaceNode->color_ == treeNode::Color::BLACK)
		             && (node->color_ == treeNode::Color::BLACK));
	treeNode* parent = node->p_;
	if (replaceNode == nullptr)
	{
		if (node == root_)
		{
			root_ = nullptr;
		}
		else
		{
			if (bothBlack)
			{
				fixDelete(node);
			}
			else
			{
				if (findSibling(node))
				{
					findSibling(node)->color_ = treeNode::Color::RED;
				}
			}
			if (node == node->p_->left_)
			{
				parent->left_ = nullptr;
			}
			else
			{
				parent->right_ = nullptr;
			}
		}
		delete node;
		return;
	}
	if (node->left_ == nullptr || node->right_ == nullptr)
	{
		if (node == root_)
		{
			swapData(replaceNode, node);
			node->left_ = node->right_ = nullptr;
			delete replaceNode;
		}
		else
		{
			if (node == node->p_->left_)
			{
				parent->left_ = replaceNode;
			}
			else
			{
				parent->right_ = replaceNode;
			}
			delete node;
			replaceNode->p_ = parent;
			if (bothBlack)
			{
				fixDelete(replaceNode);
			}
			else
			{
				replaceNode->color_ = treeNode::Color::BLACK;
			}
		}
		return;
	}
	swapData(replaceNode, node);
	deleteNode(replaceNode);
}

void RBTreeDictionary::fixDelete(treeNode* node)
{
	if (node == root_)
	{
		return;
	}
	treeNode* sibling = findSibling(node);
	treeNode* parent = node->p_;
	if (sibling == nullptr)
	{
		fixDelete(parent);
	}
	else
	{
		if (sibling->color_ == treeNode::Color::RED)
		{
			parent->color_ = treeNode::Color::RED;
			sibling->color_ = treeNode::Color::BLACK;
			if (sibling == sibling->p_->left_)
			{
				rotateRight(parent);
			}
			else
			{
				rotateLeft(parent);
			}
			fixDelete(node);
		}
		else
		{
			if ((sibling->left_ != nullptr && sibling->left_->color_ == treeNode::Color::RED) ||
				  (sibling->right_ != nullptr && sibling->right_->color_ == treeNode::Color::RED))
			{
				if (sibling == sibling->p_->left_)
				{
					if (sibling->left_ != nullptr && sibling->left_->color_ == treeNode::Color::RED)
					{
						sibling->left_->color_ = sibling->color_;
						sibling->color_ = parent->color_;
						rotateRight(parent);
					}
					else
					{
						sibling->right_->color_ = parent->color_;
						rotateLeft(sibling);
						rotateRight(parent);
					}
				}
				else
				{
					if (sibling->right_ != nullptr && sibling->right_->color_ == treeNode::Color::RED)
					{
						sibling->right_->color_ = sibling->color_;
						sibling->color_ = parent->color_;
						rotateLeft(parent);
					}
					else
					{
						sibling->left_->color_ = parent->color_;
						rotateRight(sibling);
						rotateLeft(parent);
					}
				}
				parent->color_ = treeNode::Color::BLACK;
			}
			else
			{
				sibling->color_ = treeNode::Color::RED;
				if (parent->color_ == treeNode::Color::BLACK)
				{
					fixDelete(parent); 
				}
				else
				{
					parent->color_ = treeNode::Color::BLACK;
				}
			}
		}
	}
}

void RBTreeDictionary::rotateLeft(treeNode* oldRoot)
{
	if (!oldRoot->right_)
	{
		return;
	}
	treeNode* newRoot = oldRoot->right_;
	oldRoot->right_ = newRoot->left_;
	if (newRoot->left_)
	{
		newRoot->left_->p_ = oldRoot;
	}
	newRoot->p_ = oldRoot->p_;
	if (oldRoot->p_)
	{
		if (oldRoot == oldRoot->p_->left_)
		{
			oldRoot->p_->left_ = newRoot;
		}
		else
		{
			oldRoot->p_->right_ = newRoot;
		}
	}
	else
	{
		root_ = newRoot;
	}
	newRoot->left_ = oldRoot;
	oldRoot->p_ = newRoot;
}

void RBTreeDictionary::rotateRight(treeNode* oldRoot)
{
	if (!oldRoot->left_)
	{
		return;
	}
	treeNode* newRoot = oldRoot->left_;
	oldRoot->left_ = newRoot->right_;
	if (newRoot->right_)
	{
		newRoot->right_->p_ = oldRoot;
	}
	newRoot->p_ = oldRoot->p_;
	if (oldRoot->p_)
	{
		if (oldRoot == oldRoot->p_->right_)
		{
			oldRoot->p_->right_ = newRoot;
		}
		else
		{
			oldRoot->p_->left_ = newRoot;
		}
	}
	else
	{
		root_ = newRoot;
	}
	newRoot->right_ = oldRoot;
	oldRoot->p_ = newRoot;
}

int RBTreeDictionary::getHeight()
{
	return getHeightSubTree(this->root_);;
}

int RBTreeDictionary::getHeightSubTree(treeNode* node)
{
	int left = 0, right = 0;
	if (node == nullptr)
	{
		return 0;
	}
	if (node->left_)
	{
		left = getHeightSubTree(node->left_);
	}
	if (node->right_)
	{
		right = getHeightSubTree(node->right_);
	}
	return (std::max(left, right) + 1);
}

treeNode* RBTreeDictionary::findSuccessor(treeNode* node)
{
	treeNode* temp = node;
	while (temp->left_ != nullptr)
	{
		temp = temp->left_;
	}
	return temp;
}

treeNode* RBTreeDictionary::findSibling(const treeNode* node)
{
	if (node->p_ == nullptr)
	{
		return nullptr;
	}
	if (node == node->p_->left_)
	{
		return node->p_->right_;
	}
	return node->p_->left_;
}

treeNode* RBTreeDictionary::findReplacement(const treeNode* node)
{
	if ((node->left_ != nullptr) && (node->right_ != nullptr))
	{
		return findSuccessor(node->right_);
	}
	if ((node->left_ == nullptr) && (node->right_ == nullptr))
	{
		return nullptr;
	}
	if (node->left_ != nullptr)
	{
		return node->left_;
	}
	else
	{
		return node->right_;
	}
}

void RBTreeDictionary::swapData(treeNode* node1, treeNode* node2)
{
	std::swap(node1->treeKey_, node2->treeKey_);
}

void RBTreeDictionary::printDictionary(std::ostream& out)
{
	StackArray<treeNode*> stack(getHeight());
	treeNode* current = root_;
	while (!stack.isEmpty() || current != nullptr)
	{
		if (current != nullptr)
		{
			stack.push(current);
			current = current->left_;
		}
		else
		{
			current = stack.pop();
			out << current->treeKey_.first << "\n";
		  current->treeKey_.second->print(out);
			current = current->right_;
		}
	}
}

void RBTreeDictionary::printWord(const std::string& treeKey, std::ostream& out)
{
	treeNode* current = root_;
	while (current != nullptr)
	{
		if (treeKey < current->treeKey_.first)
		{
			current = current->left_;
		}
		else if (treeKey > current->treeKey_.first)
		{
			current = current->right_;
		}
		else
		{
			std::cout << treeKey << "\n";
			current->treeKey_.second->print(out);
			return;
		}
	}
	std::cout << treeKey << " : there is no word with such a key in the dictionary\n";
}
