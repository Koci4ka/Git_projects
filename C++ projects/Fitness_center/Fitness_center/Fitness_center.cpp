//
//  lab5_3.cpp
//  Lab5
//

#include <iostream>
#include <stdlib.h>
#include <algorithm>               // max(x,y)
using namespace std;

template < class DT, class KF > // DT : tree data item
class BSTree                    // KF : key field
{
public:
	BSTree();  // Constructor
	~BSTree(); // Destructor
			   // Binary search tree status operations
	bool isEmpty() const;                 // Tree is empty
										  // Binary search tree manipulation operations
	void insert(const DT& newDataItem); // Insert data item
	void clear();                         // Clear tree
										  // Output the tree structure
	void show() const;
protected:
	class BSTreeNode       // Inner class: facilitator for the BSTree class
	{
	public:
		BSTreeNode(const DT& nodeDataItem, // Constructor
			BSTreeNode* leftPtr, BSTreeNode* rightPtr);
		// Data members
		DT dataItem;       // Binary search tree data item
		BSTreeNode* left,  // Pointer to the left child
			* right; // Pointer to the right child
	};
	// Recursive partners of the public member functions
	void insertHelper(const DT& newDataItem, BSTreeNode*& p);
	void clearHelper(BSTreeNode* p);
	void showHelper(BSTreeNode* p, int level) const;
	// insert your prototypes of these functions here...
	// Data member
	BSTreeNode* root;   // Pointer to the root node
};
//--------------------------------------------------------------------
template<class DT, class KF>
BSTree<DT, KF>::BSTree()
{
	root = NULL;
}
//--------------------------------------------------------------------
template<class DT, class KF>
BSTree<DT, KF>::~BSTree()
{
	clear();
}
//--------------------------------------------------------------------
template<class DT, class KF>
BSTree<DT, KF>::BSTreeNode::BSTreeNode(const DT& nodeDataItem,
	BSTreeNode* leftPtr, BSTreeNode* rightPtr)
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}
//--------------------------------------------------------------------
template<class DT, class KF>
bool BSTree<DT, KF>::isEmpty() const
{
	//If the root is NULL, then obviously the tree doesn't have anything in it
	return (root == NULL);
}
//--------------------------------------------------------------------
template<class DT, class KF>
void BSTree<DT, KF>::insert(const DT& newDataItem)
{
	insertHelper(newDataItem, root);
}

template<class DT, class KF>
void BSTree<DT, KF>::insertHelper(const DT& newDataItem, BSTreeNode*& p)
{
	//Base case, p is NULL so there is room to insert
	if (p == NULL)
	{
		p = new BSTreeNode(newDataItem, NULL, NULL);
	}
	else
	{
		//new data is equal to, so update
		if ((p->dataItem).getKey() == newDataItem.getKey())
			p->dataItem = newDataItem;
		//new data is less than, so insert left
		else if ((p->dataItem).getKey() > newDataItem.getKey())
			insertHelper(newDataItem, p->left);
		//new data is greater than, so insert right
		else
			insertHelper(newDataItem, p->right);
	}
}
//--------------------------------------------------------------------
template < class DT, class KF >
void BSTree<DT, KF>::clear()
// Removes all the nodes from a tree.
{
	clearHelper(root);
	root = 0;
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template < class DT, class KF >
void BSTree<DT, KF>::clearHelper(BSTreeNode* p)
// Recursive partner of the clear() function. Clears the subtree
// pointed to by p.
{
	if (p != 0)
	{
		clearHelper(p->left);
		clearHelper(p->right);
		delete p;
	}
}
//--------------------------------------------------------------------
template<class DT, class KF>
void BSTree<DT, KF>::show() const
{
	if (root == NULL)
		cout << "*** The tree is empty ***" << endl;
	else
	{
		cout << endl;
		showHelper(root, 1);
		cout << endl;
	}
}
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template<class DT, class KF>
void BSTree<DT, KF>::showHelper(BSTreeNode* p, int level) const
// Recursive helper for show.
{
	int j;   // Loop counter

	if (p != NULL)
	{
		showHelper(p->right, level + 1);         // Output right subtree
		for (j = 0; j < level; j++)       // Tab over to level
			cout << "\t";
		cout << " " << p->dataItem.getKey();  // Output key
		if ((p->left != NULL) &&           // Output "connector"
			(p->right != NULL))
			cout << "<";
		else if (p->right != NULL)
			cout << "/";
		else if (p->left != NULL)
			cout << "\\";
		cout << endl;
		showHelper(p->left, level + 1);          // Output left subtree
	}
}
//--------------------------------------------------------------------
void print_help();

class Fitness
{
public:
	void setKey(int newKey)
	{
		number = newKey;
	}   // Set the key
	void setMaxClients(int newMax) { max_clients = newMax; }

	char getKey() const
	{
		return number;
	}     // Returns the key
	int getMaxClients() const { return max_clients; }

private:
	int number, max_clients;
};

/*1. —оздать класс Ђ‘итнес - центрї, включающий данные :
Х номер фитнес - центра(число);
Х максимальное количество тренирующихс€;
и методы :
Х сеттеры / геттеры дл€ свойств класса;
—оздать класс Ђѕеречень фитнес - центровї как производный класс шаблона класса BSTree.
ƒобавить в интерактивную программу дл€ работы с классами Ђ‘итнес - центрї и Ђѕеречень фитнес - центровї через бинарное дерево поиска следующие методы :
Ј найти количество узлов бинарного дерева поиска, имеющих только левую ветвь
Ј вывести на экран максимальное количество тренирующихс€ в узлах, наход€щихс€ на четных уровн€х*/

class FitnessTree : public BSTree<Fitness, int>
{
public:
	int countOfLeft() const;          // найти количество узлов бинарного дерева поиска, имеющих только левую ветвь
	void printMaxClientsEven() const; //вывести на экран максимальное количество тренирующихс€ в узлах, наход€щихс€ на четных уровн€х
private:
	int countOfLeftHelper(BSTree<Fitness, int>::BSTreeNode* p) const;
	int printMaxClientsEvenHelper(BSTree<Fitness, int>::BSTreeNode* p, int level) const;
};

int FitnessTree::countOfLeft() const
{
	return countOfLeftHelper(root);
}

int FitnessTree::countOfLeftHelper(BSTree::BSTreeNode* p) const
{
	int result;   // Result returned
	if (p == 0)
		result = 0;
	else
		result = countOfLeftHelper(p->left) + countOfLeftHelper(p->right);
	if (p->left != 0 && p->right == 0)
	{
		result++;
	}
	return result;
}

void FitnessTree::printMaxClientsEven() const
{
	cout << printMaxClientsEvenHelper(root, 1) << endl;
}

int FitnessTree::printMaxClientsEvenHelper(BSTree::BSTreeNode* p, int level) const
{
	int result;   // Result returned
	if (p == 0)
	{
		result = 0;
	}
	else if (level % 2 != 0)
	{
		result = max(printMaxClientsEvenHelper(p->left, level + 1), printMaxClientsEvenHelper(p->right, level + 1));
		if (p->dataItem.getMaxClients() > result)
			result = p->dataItem.getMaxClients();
	}
	else
	{
		result = max(printMaxClientsEvenHelper(p->left, level + 1), printMaxClientsEvenHelper(p->right, level + 1));
	}
	return result;
}


int main()
{
	FitnessTree testTree;             // Test binary search tree
	Fitness testData;             // Binary search tree data item
	int inputKey = 0, inputMax = 0;     // User input data
	char cmd = NULL;        // Input command and key

	print_help();

	do
	{
		testTree.show();                     // Output tree

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;
		if (cmd == '+')
			cin >> inputKey >> inputMax;

		switch (cmd)
		{
		case 'P': case 'p':
			print_help();
			break;

		case '+':                                  // insert
			testData.setKey(inputKey);
			testData.setMaxClients(inputMax);
			cout << "Item is added: key = " << testData.getKey()
				<< endl;
			testTree.insert(testData);
			break;

		case 'C': case 'c':                       // clear
			cout << "Deleting the tree" << endl;
			testTree.clear();
			break;


		case 'E': case 'e':                       // empty
			if (testTree.isEmpty())
				cout << "Tree is empty" << endl;
			else
				cout << "Tree is NOT empty" << endl;
			break;

		case 'H': case 'h':
			cout << "Count of items only with left branch = " << testTree.countOfLeft() << endl;
			break;

		case 'S': case 's':
			cout << "Max number of clients on even levels = ";
			testTree.printMaxClientsEven();
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Wrong command. Use 'P' for help." << endl;
		}
	} while (cin && (cmd != 'Q') && (cmd != 'q'));

	if (!cin) {
		cerr << "Incorrect input. Quit." << endl;
	}

	return 0;
}

//--------------------------------------------------------------------

void print_help() {
	cout << endl << "Commands:" << endl;
	cout << "  P    : Help" << endl;
	cout << "+ key maxClients: Input of new item" << endl;
	cout << "  C    : Delete tree" << endl;
	cout << "  E    : Is tree empty?" << endl;
	cout << "  H    : Count of items only with left branch" << endl;
	cout << "  S    : Max number of clients on even levels" << endl;
	cout << "  Q    : Quit" << endl;
	cout << endl;
}