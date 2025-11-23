#include<iostream>
#include<queue>
#include<stack>
using namespace std;

class node {
public:
	node* left;
	node* right;
	string destination;
	int expense;
	int height;

	node(int d, string place) {
		left = NULL;
		right = NULL;
		expense = d;
		this->destination = place;
		height = 0;
	}
};

class AVLTree {
	//node* checkBFandUpdate(node* root);
private:

	int height(node* N) {	//getter for the node's height, NOT TREE HEIGHT
		if (N == NULL) {
			return -1;
		}
		return N->height;
	}

	int max(int a, int b) {
		return (a > b) ? a : b;
	}

	node* rightRotate(node* x) {
		node* y = x->left;
		node* temp = y->right;
		y->right = x;
		x->left = temp;
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;
		//cout << "Rotating to the right" << endl;
		return y;
	}

	node* leftRotate(node* x) {
		node* y = x->right;
		node* temp = y->left;
		y->left = x;
		x->right = temp;
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;
		//cout << "Rotating to the left" << endl;
		return y;
	}

	int getBalance(node* N) {
		if (N == NULL) return 0;
		return height(N->left) - height(N->right);
	}

	node* insertNode(node* root, int givenData, string name) {
		if (root == NULL) {
			node* myNode = new node(givenData, name);
			return myNode;
		}
		if (givenData < root->expense) {
			root->left = insertNode(root->left, givenData,name);
		}
		else if (givenData > root->expense) {
			root->right = insertNode(root->right, givenData, name);
		}
		else return root;

		root->height = 1 + max(height(root->left), height(root->right));

		return checkBFandUpdate(root);
	}

	node* maxValueNode(node* n) {	//because of predecessor logic
		node* current = n;
		while (current->right != NULL)
			current = current->right;
		return current;
	}

	node* deleteNode(node* root, int data) {
		if (root == NULL) {
			cout << "Node to delete wasn't found, ending operations" << endl;
			return root;
		}
		if (data < root->expense)
			root->left = deleteNode(root->left, data);
		else if (data > root->expense)
			root->right = deleteNode(root->right, data);
		else {		
			if ((root->left == nullptr) || (root->right == nullptr)) {
				node* temp;
				if (root->left == NULL) { temp = root->right; }
				else { temp = root->left; }
				if (temp == nullptr) {	
					temp = root;
					root = nullptr;
				}
				else {// One child case
					*root = *temp; 
				}
				free(temp);
			}
			else {	// node with two children: 
				//Get the inorder predecessor (largest in the right subtree)
				node* temp = maxValueNode(root->right);

				root->expense = temp->expense;

				root->right = deleteNode(root->right, temp->expense);
			}
		}

		// If the tree had only one node then return
		if (root == nullptr)
			return root;


		root->height = 1 + max(height(root->left), height(root->right));

		return checkBFandUpdate(root);
	}

	bool searchNode(node* root, int val) {	//uneeded for AVL, maybe for BST
		if (root == NULL) return false;
		if (root->expense == val) return true;
		if (val < root->expense)
			return searchNode(root->left, val);
		return searchNode(root->right, val);
	}

	node* checkBFandUpdate(node* root) {
		int balance = getBalance(root);

		if (balance > 1 && getBalance(root->left) >= 0) {
			return rightRotate(root);
		}

		if (balance > 1 && getBalance(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		if (balance < -1 && getBalance(root->right) <= 0) {
			return leftRotate(root);
		}

		if (balance < -1 && getBalance(root->right) > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		return root;
	}

	void print(node* a) {
		if (a == NULL) {
			return;
		}
		print(a->left);
		cout << a->destination << " costs $" << a->expense << endl;
		print(a->right);
	}

	// Levelwise searching
	void BFS(node* root) {
		// we will do this via Queue and this is not a recursive function
		//cout << "Breadth-First searching:" << endl;
		queue<node*> myQueue;
		myQueue.push(root);
		//myQueue.push(NULL);

		while (myQueue.size() > 0) {
			node* current = myQueue.front();
			myQueue.pop();	//We'll enqueue the children then dequeue for real

			//if (current == NULL) {	// For printing newspace between levels
			//	if (!myQueue.empty()) {
			//		cout << endl;
			//		myQueue.push(NULL);
			//		continue;	//We will skip to next iteration without running the below code
			//	}
			//	else {
			//		cout << endl;
			//		break;
			//	}
			//}

			cout << current->destination << " - $" << current->expense << endl;

			if (current->left != NULL) {
				myQueue.push(current->left);
			}
			if (current->right != NULL) {
				myQueue.push(current->right);
			}
		}
	}

	// DFS below - explore the branch then move forward

	void inorderTraversal(node* root) {
		// left root right
		if (root == NULL) {
			return;
		}
		inorderTraversal(root->left);
		cout << root->destination << " - $" << root->expense << endl;
		inorderTraversal(root->right);
	}

	void reverseInorderTraversal(node* root, stack<node*>& myStack) {
		if (root == NULL) {
			return;
		}
		reverseInorderTraversal(root->left, myStack);
		myStack.push(root);
		reverseInorderTraversal(root->right, myStack);
	}
		node* root;
	public:
	AVLTree() {
		root  = NULL;
		root = insertNode(root, 12000, "Paris");
		root = insertNode(root, 6500, "Oslo");
		root = insertNode(root, 3500, "Budapest");
		root = insertNode(root, 9000, "Berlin");
		root = insertNode(root, 19500, "London");
		root = insertNode(root, 14000, "New York");
		root = insertNode(root, 8500, "Reykjavik");
	}

	void printDecider(char letter) {
		stack<node*> myStack;
		switch (letter) {
			case'A':BFS(root); break;
			case'B':inorderTraversal(root); break;
			case'C':
				reverseInorderTraversal(root, myStack);
				while (!myStack.empty()) {
					node* temp = myStack.top();
					cout << temp->destination << " - $" << temp->expense << endl;
					myStack.pop();
				}
				break;
			default:cout << "Input error" << endl; break;
		}
	}
};
