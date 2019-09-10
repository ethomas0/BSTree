// ------------------------------bintree.h----------------------------------
// --Ethan Thomas, CSS 343
// -------------------------------------------------------------------------
// Purpose: 
// --A binary search tree class called BinTree that allows a user 
//   to build a BST of strings with functions that allow for tree building, 
//   tree modifing, retrieval of data, retrieval of data height, 
//   and tree destroying. Also allows user to convert BST to array and from
//   array back to a balanced BST.


// --Functions are explained in cpp file
// -------------------------------------------------------------------------
// Assumptions: 
// --All data is assumed to be correct and all of the
//   BSTs are assumed to be 100 nodes or less.
// -------------------------------------------------------------------------

//--------------------------------------------------------------------------
// Side Notes: 
// --I know this is not the most efficient BST(Due to all the recursive
//   calls, but I had already done this project in a different class so my
//   goal was to try and take advantage of the fact that almost all the
//   solutions could be solved with recursion. The reason is because I do not
//   like recursion and I am not comfertable with it. So I thought I would 
//   go out of my comfort zone and try something different. I figured this 
//   would be ok since the assingment does not specifically state that I
//   I need to match the Big O cases (time complexity, space allocation, etc.)
// --Also I apologize if my in function comments have too many comments.
//   Last assignment I was marked down for it and so I am still trying to
//   find the sweet spot.
//--------------------------------------------------------------------------


#ifndef BINTREE_H
#define BINTREE_H


#include "nodedata.h"

class BinTree
{
	friend std::ostream& operator<<(std::ostream &outPut, const BinTree& tree);

public:
	
	BinTree();								
	BinTree(const BinTree& copy);		    
	~BinTree();								

	bool isEmpty() const;					
	void makeEmpty();		

	BinTree& operator=(const BinTree& copy);

	bool operator==(const BinTree& otherTree) const;
	bool operator!=(const BinTree& otherTree) const;

	bool insert(NodeData* value);

	bool retrieve(const NodeData& targetValue, NodeData*& ptrToTarget);

	int getHeight(const NodeData& target) const;

	void bstreeToArray(NodeData* array[]);

	void arrayToBSTree(NodeData* array[]);

	void displaySideways() const;

private:

	struct Node
	{
		NodeData* data;						
		Node* left;							
		Node* right;						

		Node(NodeData* value) : data(value), left(nullptr), right(nullptr) {}; //constructor for Node
	};
	Node* root;								

	void inorderHelper(Node* current) const;

	void makeEmptyHelper(Node*& current);

	void assignmentHelper(Node*& leftNode, Node* rightNode);

	bool equalityComparisonHelper(Node*leftNode, Node* rightNode) const;

	bool insertHelper(Node*& current, NodeData* value);

	bool retrieveHelper(Node* current, const NodeData& targetValue, NodeData*& ptrToTarget) const;

	int getHeightHelper(const NodeData& targetValue, Node* current) const;

	int recurGetHeightHelper(Node* current) const;

	const int maxUtility(const int& input1, const int& input2) const;

	int bstreeToArrayHelper(Node* current, NodeData* array[]);

	void arrayToBSTreeHelper(Node* current, NodeData* array[], int low, int high);

	void sideways(Node* current, int level) const;	
};


#endif //BINTREE_H