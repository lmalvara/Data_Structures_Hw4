#include<iostream>
#include<string>
#include<array>
#include<fstream>
#include"ArgumentManager.h"
using namespace std;

class tree
{

private:
	struct node
	{
		int data;
		node* left;
		node* right;
	};

	node* root;

	node* CreateLeaf(int data) {
		node* n = new node;
		n->data = data;
		n->left = NULL;
		n->right = NULL;

		return n;
	}

	node* ReturnNode(int data)
	{
		return ReturnNodePrivate(data, root);
	}

	node* ReturnNodePrivate(int data, node* ptr)
	{
		if (ptr != NULL)
		{
			if (ptr->data == data)
				return ptr;
			else {
				if (data < ptr->data)
					return ReturnNodePrivate(data, ptr->left);
				else
					return ReturnNodePrivate(data, ptr->right);
			}
		}
		else
			return NULL;
	}

	void AddLeafPrivate(int data, node* ptr)
	{
		if (root == NULL)
			root = CreateLeaf(data);
		else if (data < ptr->data)
		{
			if (ptr->left != NULL)
				AddLeafPrivate(data, ptr->left);
			else
				ptr->left = CreateLeaf(data);
		}

		else if (data > ptr->data)
		{
			if (ptr->right != NULL)
				AddLeafPrivate(data, ptr->right);
			else
				ptr->right = CreateLeaf(data);
		}
		else
			cout << "the number " << data << " has already been added!\n" << endl;

	}

	void PrintInOrderPrivate(node* ptr)
	{
		if (root != NULL)
		{
			if (ptr->left != NULL)
				PrintInOrderPrivate(ptr->left);

			cout << ptr->data << " ";

			if (ptr->right != NULL)
				PrintInOrderPrivate(ptr->right);

		}
		else
			cout << "tree is empty\n" << endl;

	}

	void PreorderPrivate(node* root) {
		if (root == NULL) {
			return;
		}
		cout << root->data << " ";
		PreorderPrivate(root->left);
		PreorderPrivate(root->right);

	}

	void PostorderPrivate(node* root) {
		if (root == NULL) {
			return;
		}
		PostorderPrivate(root->left);
		PostorderPrivate(root->right);
		cout << root->data << " ";
	}



public:

	tree()
	{
		root = NULL;
	};

	void AddLeaf(int data)
	{
		AddLeafPrivate(data, root);
	}

	void PrintInOrder()
	{
		PrintInOrderPrivate(root);
		cout << endl;
	}

	void Preorder()
	{
		PreorderPrivate(root);
		cout << endl;
	}

	void Postorder()
	{
		PostorderPrivate(root);
		cout << endl;
	}

	int ReturnRootData()
	{
		if (root != NULL)
			return root->data;
		else
			return -12345;
	}

	void PrintChildren(int data)
	{
		node* ptr = ReturnNode(data);

		if (ptr != NULL)
		{
			cout << "\nParrent node = " << ptr->data << endl;
			if (ptr->left != NULL)
				cout << "Left child = " << ptr->left->data << endl;
			else
				cout << "Left child = NULL" << endl;
			//right side
			if (ptr->right != NULL)
				cout << "Right child = " << ptr->right->data << endl;
			else
				cout << "Right child = NULL" << endl;
		}
		else
			cout << "\nNumber " << data << " is not in the tree!\n" << endl;
	}

};


int search(string array[], string num, int n)
{
	for (int i = 0; i < n; i++)
		if (array[i] == num)
			return i;
	return -1;
}


void printPostOrder(string inorder[], string preorder[], int n)
{
	int root = search(inorder, preorder[0], n);

	if (root != 0)
		printPostOrder(inorder, preorder + 1, root);
	
	if (root != n - 1)
		printPostOrder(inorder + root + 1, preorder + root + 1, n - root - 1);

	cout << preorder[0] << " ";
}



int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cerr << "preorder=<filename>;inorder=<filename>";
	}
	ArgumentManager am(argc, argv);
	string infilename = am.get("inorder");
	string prefilename = am.get("preorder");

	ifstream inorder(infilename.c_str());
	ifstream preorder(prefilename.c_str());

	string Inarray[1000];
	string Prearray[1000];

	//ifstream inorder("1.txt");
	//ifstream preorder("2.txt");
	
	string num;
	int i = 0;
	while (inorder >> num) {
		Inarray[i++] = num;
	}
	string *inarray = new string[i];
	string *prearray = new string[i];
	i = 0;
	while (preorder >> num) {
		Prearray[i++] = num;
	}
	int j = 0;
	while (j < i) {
		inarray[j] = Inarray[j];
		prearray[j] = Prearray[j];
		j++;

	}

	int n = i--;

	printPostOrder(inarray, prearray, n);
	cout << endl;
	//system("pause");
	return 0;
}