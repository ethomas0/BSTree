// ------------------------------bintree.cpp--------------------------------
// --Ethan Thomas, CSS 343
// -------------------------------------------------------------------------
// Purpose: 
// --A binary search tree class called BinTree that allows a user 
//   to build a BST of strings with functions that allow for tree building, 
//   tree modifing, retrieval of data, retrieval of data height, 
//   and tree destroying. Also allows user to convert BST to array and from
//   array back to a balanced BST.

#include "bintree.h"


// --------------------- Overloaded << --------------------------
// --Displays data from the BSTree in order.
// --Uses helper function inorderHelper to traverse tree
// --------------------------------------------------------------
ostream& operator<<(ostream& outPut, const BinTree& tree)
{
	tree.inorderHelper(tree.root);
	outPut << std::endl;
	return outPut;
}

// --------------------- inorderHelper --------------------------
// --Helper function for overloaded operator <<
// --Prints in order alphabetically 
// --------------------------------------------------------------
void BinTree::inorderHelper(Node* current) const
{
	if (current != nullptr)  
	{
		// Traverse left side of tree
		inorderHelper(current->left);
		// Print current data
		std::cout << *current->data << " ";
		// Traverse right side of tree
		inorderHelper(current->right);
	}
}

// --------------------- Default Constructor --------------------
// --Creates an empty BSTree
// --------------------------------------------------------------
BinTree::BinTree()
{
	this->root = nullptr;
}

// --------------------- Copy Constructor -----------------------
// --Creates a deep copy of a BSTree passed in
// --------------------------------------------------------------
BinTree::BinTree(const BinTree& copy)
{
	this->root = nullptr;
	*this = copy;
}

// --------------------- Destructor -----------------------------
// --Calls makeEmpty to delete a BSTree
// --------------------------------------------------------------
BinTree::~BinTree()
{
	this->makeEmpty();
}

// --------------------- isEmpty --------------------------------
// --Checks whether a BSTree is empty or not
// --Returns true if empty, else returns false
// --------------------------------------------------------------
bool BinTree::isEmpty() const
{
	return (root == nullptr);
}

// --------------------- makeEmpty ------------------------------
// --Deletes and entire BSTree
// --Uses helper function makeEmptyHelpter
// --------------------------------------------------------------
void BinTree::makeEmpty()
{
	makeEmptyHelper(root);
}

// --------------------- makeEmptyHelper ------------------------
// --Helper function for makeEmpty
// --Deletes all nodes of a tree
//   and sets nodes to nullptr
// --------------------------------------------------------------
void BinTree::makeEmptyHelper(Node*& current)
{
	if (current != nullptr)    
	{
		// Post order traversal
		makeEmptyHelper(current->left); 
		makeEmptyHelper(current->right);    

		// Deletes NodeData
		delete current->data;   
		current->data = nullptr;
		
		// Deletes Node
		delete current; 
		current = nullptr;
	}
}

// --------------------- Overloaded = ---------------------------
// --Makes the left tree a deep copy of the right tree(otherTree)
// --Uses helper function assignmentHelper
// --------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree& otherTree)
{
	// Check if both trees are the same
	if (*this != otherTree) 
	{
		// If not the same, clears right tree,
		// and then calls helper function
		this->makeEmpty();
		assignmentHelper(this->root, otherTree.root);
	}
	

	// Either returns copied new tree 
	// or old tree if bool was false
	return *this;   
}

// --------------------- assignmentHelper -----------------------
// --Helper function for overloaded assignment operator =.
// --Left tree(leftNode) becomes a deep copy of 
//   right tree (rightNode)
// --------------------------------------------------------------
void BinTree::assignmentHelper(Node*& leftNode, Node* rightNode)
{
	if (rightNode != nullptr) // Preorder traverse right tree
	{		
		NodeData *temp = new NodeData(*rightNode->data);    //Copies right tree NodeData to temp
		leftNode = new Node(temp);   // New node for left tree
		
		assignmentHelper(leftNode->left, rightNode->left); // Traverse left side of both trees
		assignmentHelper(leftNode->right, rightNode->right); // Traverse right side of both trees   
	}
	
}

// --------------------- Overloaded == --------------------------
// --Checks if two BSTrees are exactly the 
//   same (value and structure wise)
// --Uses helper function equalityComparisonHelper
// --------------------------------------------------------------
bool BinTree::operator==(const BinTree& rightTree) const
{
	return equalityComparisonHelper(this->root, rightTree.root);	
}

// --------------------- equalityComparisonHelper ---------------
// --Helper function to overloaded operator ==
// --Compares left tree (leftNode) and right tree(rightNode).
// --If both trees have the same values and structure then 
//   returns true, else returns false
// --------------------------------------------------------------
bool BinTree::equalityComparisonHelper(Node* leftNode, Node* rightNode) const
{
	// Both nodes are empty
	if (leftNode == nullptr && rightNode == nullptr)
	{
		return true;
	}
	// One node is empty while the other is not
	else if (leftNode == nullptr || rightNode == nullptr)
	{
		return false;
	}
	// Both nodes are not empty. Compare and traverse down
	else
	{
		return (*leftNode->data == *rightNode->data
			&& equalityComparisonHelper(leftNode->left, rightNode->left)
			&& equalityComparisonHelper(leftNode->right, rightNode->right));
	}
	
	
}

// --------------------- Overloaded != --------------------------
// --Checks if two BSTrees are not exactly the same
// --Returns true if they are not the same, else returns false
// --------------------------------------------------------------
bool BinTree::operator!=(const BinTree& rightTree) const
{
	return !(*this == rightTree);
}

// --------------------- insert ---------------------------------
// --Inserts a new node containing NodeData into a BST
// --Uses helper function insertHelper
// --------------------------------------------------------------
bool BinTree::insert(NodeData* value)
{
	return insertHelper(this->root, value);
}

// --------------------- insertHelper ---------------------------
// --Helper function to insert
// --If NodeData does not already exsist in tree then it will 
//   insert and return true. Does not allow duplicates. 
// --If duplicate is found then does nothing and returns false
// --------------------------------------------------------------
bool BinTree::insertHelper(Node*& current, NodeData* value)
{
	// Insert new node here
	if (current == nullptr)   
	{
		current = new Node(value);   
		return true;
	}
	else if (*value < *current->data)
	{
		// Traverse left side of tree
		insertHelper(current->left, value); 
	}
	else if (*value > *current->data)
	{
		// Traverse right side of tree
		insertHelper(current->right, value); 
	}
	else
	{
		// Node is already in tree
		return false;   
	}

	
}

// --------------------- retrieve -------------------------------
// --Checks whether or not a NodeData is in a BST
// --If found returns a pointer to that node
// --Uses helper function retrieveHelper
// --------------------------------------------------------------
bool BinTree::retrieve(const NodeData& targetValue, NodeData*& ptrToTarget)
{
	return (retrieveHelper(this->root, targetValue, ptrToTarget));
}

// --------------------- retrieveHelper --------------------------
// --Helper function to retrieve
// --Sets a pointer to the target value if found and returns true
//   else sets pointer to nullptr and returns false
// --------------------------------------------------------------
bool BinTree::retrieveHelper(Node* current, const NodeData& targetValue, NodeData*& ptrToTarget) const
{
	// Target Value was not found
	if (current == nullptr)    
	{
		ptrToTarget = nullptr;   
		return false;
	}
	// Target Value was found
	else if (*current->data == targetValue)   
	{
		ptrToTarget = current->data;  
		return true;
	}
	else if (*current->data < targetValue)
	{
		// Traverse right side of tree
		retrieveHelper(current->right, targetValue, ptrToTarget); 
	}
	else if (*current->data > targetValue)
	{
		// Travers left side of tree
		retrieveHelper(current->left, targetValue, ptrToTarget);   
	}
	
}

// --------------------- getHeight --------------------------------
// --Returns the height of a given node in a binary tree
// --(Assumes function does not know if tree that called function
//    is a BST or BT)
// --Uses helper function getHeightHelper
// --------------------------------------------------------------
int BinTree::getHeight(const NodeData& targetValue) const
{
	return getHeightHelper(targetValue, this->root);
}

// --------------------- getHeightHelper -------------------------
// --Helper function to getHeight
// --Finds the specific node in the tree, if it exists else it
//   will return 0
// --Uses preorder traversal
// --Uses helper function recursiveGetHeightHelper
// --------------------------------------------------------------
int BinTree::getHeightHelper(const NodeData& targetValue, Node* current) const
{
	if (current == nullptr)
	{
		// Node is not found
		return 0; 
	}
	else if (*current->data == targetValue)
	{
		// Node found
		return recurGetHeightHelper(current);   
	}
	else
	{
		// Search left side of tree
		int left = getHeightHelper(targetValue, current->left);  
		// Search right side of tree
		int right = getHeightHelper(targetValue, current->right);   

		// Returns larger value of the two
		return maxUtility(left, right);
	}
}

// --------------------- recurGetHeightHelper --------------------
// --Helper function to getHeightHelper
// --Determines the height of the node subtree
// --Leafs have value of 1, height of node at next level 
//   is 2, and so on
// --------------------------------------------------------------
int BinTree::recurGetHeightHelper(Node* current) const
{
	// Reached end of subtree
	if (current == nullptr)
	{
		return 0; 
	}
	else
	{
		// Counts the amount of levels in the subtree from node
		// and returns largerest path
		return 1 + maxUtility (recurGetHeightHelper(current->left), recurGetHeightHelper(current->right));
	}
}

// --------------------- maxUtility -----------------------------
// --Utility function used by getHeight that returns larger of 
//   two integers 
// --------------------------------------------------------------
const int BinTree::maxUtility(const int& input1, const int& input2) const
{
	return (input1 > input2 ? input1 : input2);
}

// --------------------- bstreeToArrayHelper --------------------
// --Transfers all of the nodes from a BST into an array and then
//   deletes the BST. 
// --Uses helper function bstreeToArrayHelper
// --------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* array[])
{
	bstreeToArrayHelper(this->root, array);

	this->makeEmpty();
}

// --------------------- bstreeToArrayHelper --------------------
// --Helper function to bstreeToArrayHelper
// --Parents = n/2, LeftChild = 2n, RightChild = 2n + 1
// --Fills an array that is assumed to be no larger than 100
//   elements using inorder traversal
// --------------------------------------------------------------
int BinTree::bstreeToArrayHelper(Node* current, NodeData* array[])
{
	// End of BST
	if (current == nullptr)
	{
		return 0; 
	}

	// Traverse left side of tree
	int left = bstreeToArrayHelper(current->left, array);

	// Array points to current data
	*(array + left) = current->data;
	current->data = nullptr;	

	// Traverse right side of tree
	int right = bstreeToArrayHelper(current->right, array + left + 1);

	// Return position
	return left + right + 1;
}

// --------------------- arrayToBSTree --------------------------
// --Builds a balanced BST from a sorted array of NodeData
// --Assumes array has only 100 elements max
// --Array is filled with nullptr's at the end
// --Uses helper function arrayToBSTreeHelper
// --------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* array[])
{
	if (this != nullptr)
	{
		// If not empty delets current BST
		this->makeEmpty();  
	}
	
	// Used to determine how many elements point to NodeData
	int high = 0;

	for (int i = 0; i < 100; i++)    
	{
		if (array[i] != nullptr)
		{
			// NodeData found, increment counter
			high++;
		}
		
	}

	arrayToBSTreeHelper(root, array, 0, high - 1);
}

// --------------------- arrayToBSTreeHelper --------------------
// Helper function to arrayToBSTree
// Builds a balanced BST and sets array to nullptr
// --------------------------------------------------------------
void BinTree::arrayToBSTreeHelper(Node* current, NodeData* array[], int low, int high)
{
	if (low > high) // end of array NodeData
	{
		current = nullptr;
	}
	else
	{
		int mid = (low + high) / 2; // picks NodeData from array to build balanced tree		

		insert(array[mid]);   // Inserts NodeData using mid as index into BST
		array[mid] = nullptr; // Sets that array element to nullptr

		arrayToBSTreeHelper(current, array, low, mid - 1);    // Fill left
		arrayToBSTreeHelper(current, array, mid + 1, high);   // Fill right
	}
}

// --------------------- displaySideways ------------------------
// --Prints out BST from a side view perspective
// --Uses helper function sideways
// --------------------------------------------------------------
void BinTree::displaySideways() const
{
	sideways(root, 0);  
}

// --------------------- sideways -------------------------------
// --displaySideways helper function that prints BST from a side
//   view perspective
// --------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const
{
	if (current != nullptr) 
	{
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}


