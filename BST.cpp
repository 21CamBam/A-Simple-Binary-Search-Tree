#include "BST.h"

using namespace std;

HW2BST::Node::Node(int dataValue)
{
	Data = dataValue;
	Left = Right = NULL;
}

HW2BST::HW2BST(void)
{
	m_root = NULL;
}

HW2BST::~HW2BST(void)
{
	DeleteTree(m_root);
	m_root = NULL;
}

// Should return false if the value already exists in the tree or if memory 
// for a new node could not be allocated.
bool HW2BST::Add(int dataValue)
{
	return insert(&m_root, dataValue);
}

bool HW2BST::insert(Node **rootptr, int data_value)
{
	if (*rootptr == nullptr) // New root
	{
		*rootptr = new Node(data_value);
		return true;
	}

	if ((*rootptr)->Data == data_value) // No duplicates test
		return false;

	if ((*rootptr)->Data > data_value) // If num is less than root
	{
		if ((*rootptr)->Left == NULL) // If root has no left child
		{
			Node* new_leaf = new Node(data_value);
			(*rootptr)->Left = new_leaf;
			return true;
		}
		insert(&(*rootptr)->Left, data_value);
	}
	else // If num is more than root
	{
		if ((*rootptr)->Right == NULL) // If root has no right child
		{
			Node* new_leaf = new Node(data_value);
			(*rootptr)->Right = new_leaf;
			return true;
		}
		insert(&(*rootptr)->Right, data_value);
	}
}

// Returns the number of levels in the tree. A tree with no contents (null root) will have 
// zero levels. A tree with just the root and no children has 1 level. For all other cases 
// the number of levels must be counted. There is a linear-time algorithm for this.
int HW2BST::CountLevels()
{
	return count(m_root) - 1;
}

int HW2BST::count(Node *rootptr)
{
	if (rootptr == nullptr)
	{
		return -1;
	}

	int l_height = count(rootptr->Left);
	int r_height = count(rootptr->Right);

	if (l_height > r_height)
	{
		return l_height + 1;
	}
	else
	{
		return r_height + 1;
	}
}

void HW2BST::DeleteTree(Node* root)
{
	if (root)
	{
		DeleteTree(root->Left);
		DeleteTree(root->Right);
		delete root;
	}
}

void HW2BST::DisplayContents(Node* node, ostream& outputStream)
{
	if (node)
	{
		DisplayContents(node->Left, outputStream);

		// Display the numerical value for this node
		outputStream << node->Data << " ";

		// Display the entire right subtree
		DisplayContents(node->Right, outputStream);
	}
}

void HW2BST::DisplayContents(ostream& outputStream)
{
	outputStream << "BST Contents: ";
	DisplayContents(m_root, outputStream);
	outputStream << endl;
}

void HW2BST::DisplayLevels(std::ostream& outputStream)
{
	int levels = CountLevels();
	outputStream << "Tree with " << levels << " levels:" << endl;
	queue<Node*> current_level, next_level;
	current_level.push(m_root);

	while (!current_level.empty())
	{
		Node *current_node = current_level.front();
		current_level.pop();
		if (current_node != nullptr)
		{
			outputStream << current_node->Data << " ";
			next_level.push(current_node->Left);
			next_level.push(current_node->Right);
		}
		else
		{
			outputStream << "<0> ";
		}
		if (current_level.empty())
		{
			outputStream << endl;
			swap(current_level, next_level);
		}
	}
}

// Gets the maximum value in the tree. Returns 0 if the tree is empty.
int HW2BST::GetMax()
{
	if (m_root)
	{
		Node* n = m_root;
		while (n->Right)
		{
			n = n->Right;
		}
		return n->Data;
	}
	return 0;
}

bool HW2BST::IsEmpty()
{
	return (NULL == m_root);
}

// Returns true if the value was found and removed, false if it was not found
bool HW2BST::Remove(int dataValue)
{
	return search_and_destroy(m_root, dataValue);
}

bool HW2BST::search_and_destroy(Node* parent, int num)
{
	if (parent->Data == num)
	{
		if (parent->Left == nullptr && parent->Right == nullptr)
		{
			delete parent;
			return true;
		}
		else if (parent->Left == nullptr && parent->Right != nullptr)
		{
			parent = parent->Right;
			return true;
		}
		else if (parent->Left != nullptr && parent->Right == nullptr)
		{
			parent = parent->Left;
			return true;
		}
		else
		{
			Node* rightmost_in_left = find_rightmost_in_left(parent->Left);
			parent->Data = rightmost_in_left->Data;
			if (rightmost_in_left->Left == nullptr && rightmost_in_left->Right != nullptr)
			{
				rightmost_in_left = rightmost_in_left->Right;
				return true;
			}
			else if (rightmost_in_left->Left != nullptr && rightmost_in_left->Right == nullptr)
			{
				rightmost_in_left = rightmost_in_left->Left;
				return true;
			}
			return true;
		}
	}
	else if (parent->Data > num)
	{
		return search_and_destroy(parent->Left, num);
	}
	else if (parent->Data < num)
	{
		return search_and_destroy(parent->Right, num);
	}
	else
	{
		return false;
	}
}

HW2BST::Node* HW2BST::find_rightmost_in_left(Node *rootptr)
{
	Node *rightmost;
	if (rootptr->Right == nullptr)
	{
		return rootptr;
	}
	rightmost = find_rightmost_in_left(rootptr->Right);
	return rightmost;
}
