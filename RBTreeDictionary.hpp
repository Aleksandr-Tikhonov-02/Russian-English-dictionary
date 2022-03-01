#ifndef _RB_TREE_DICTIONARY_
#define _RB_TREE_DICTIONARY_

#include <string>
#include "treeNode.hpp"

class RBTreeDictionary
{
public:
	RBTreeDictionary();
	RBTreeDictionary(const std::string& treeKey, const std::string& meaning);
	RBTreeDictionary(const RBTreeDictionary& src) = delete;
	RBTreeDictionary(RBTreeDictionary&& src) noexcept = delete;
	RBTreeDictionary& operator=(const RBTreeDictionary& src) = delete;
	RBTreeDictionary& operator=(RBTreeDictionary&& src) noexcept = delete;
	~RBTreeDictionary();

	void insert(const std::string& treeKey, const std::string& meaning);
	bool search(const std::string& treeKey);
	void deleteWord(const std::string& treeKey); 
	void printDictionary(std::ostream& out);
	void printWord(const std::string& treeKey, std::ostream& out);

private:
	treeNode* root_;
	void deleteNode(treeNode* node);
	treeNode* searchTreeNode(const std::string& treeKey);
	void deleteSubtree(treeNode* node);
	void fixInsert(treeNode* son);
	void rotateLeft(treeNode* oldRoot);
	void rotateRight(treeNode* oldRoot);
	void fixDelete(treeNode* node);
	int getHeight();
	int getHeightSubTree(treeNode* node);
	treeNode* findSuccessor(treeNode* node);
	treeNode* findSibling(const treeNode* node);
	treeNode* findReplacement(const treeNode* node);
	void swapData(treeNode* node1, treeNode* node2);
};

#endif 
