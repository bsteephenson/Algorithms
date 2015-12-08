#include "iostream"

using namespace std;

struct Node {
	int start;
	int end;
	int max; // represents the max end in my subtree
	Node *left;
	Node *right;
};

Node * insert(Node *tree, int start, int end);
// returns NULL or a node that intersects with interval
Node * search(Node *tree, int start, int end);
Node * remove(Node *tree, int start);
void print(Node * tree);

int main() {
	Node *t = NULL;
	t = insert(t, 6, 8);
	t = insert(t, 1, 4);
	t = insert(t, 5, 10);
	print(t);
	cout << endl;
	cout << "removing 6-8" << endl;

	t = remove(t, 6);
	print(t);
	cout << endl;
	cout << "searching for interval intersecting 7-12" << endl;
	Node *s = search(t, 7, 12);
	if (s != NULL) {
		cout << s->start << " - " << s->end << endl;	
	}
	else {
		cout << "no intersection" << endl;
	}
}

Node *insert(Node *tree, int start, int end)
{
	if (tree == NULL) {
		tree = new Node;
		tree->start = start;
		tree->end = end;
		tree->max = end;
		tree->left = NULL;
		tree->right = NULL;
		return tree;
	}
	else {

		tree->max = max(tree->max, end);

		if (start < tree->start) {
			tree->left = insert(tree->left, start, end);
		}
		else {
			tree->right = insert(tree->right, start, end);			
		}
		return tree;
	}
}

Node * search(Node *tree, int start, int end)
{
	if (tree == NULL) {
		return tree;
	}

	if (!(start > tree->end || end < tree->start)) {
		return tree;
	}
	else {
		// if left's max is < the start, go left
		// otherwise go right
		if (tree->left != NULL && start <= tree->max) {
			return search(tree->left, start, end);
		}
		else {
			return search(tree->right, start, end);
		}
	}
}
Node * remove(Node *tree, int start)
{
	if (tree == NULL) {
		return tree;
	}
	if (start < tree->start) {
		tree->left = remove(tree->left, start);
	}
	else if (tree->start < start) {
		tree->right = remove(tree->right, start);		
	}
	else if (tree->start == start) {
		// case I have no children
		if (tree->left == NULL && tree->right == NULL) {
			return NULL;
		}
		// case I have only left child
		else if (tree->left != NULL) {
			return tree->left;
		}
		// case I have only a right child
		else if (tree->right != NULL) {
			return tree->right;
		}
		// case I have two children
		else {
			Node *temp = tree;
			// get the min on the right
			temp = temp->right;
			while (temp->left != NULL) {
				temp = temp->left;
			}
			tree->start = temp->start;
			tree->end = temp->end;
			tree->right = remove(tree->right, temp->start);
		}
	}

	// recalculate max value

	int max = tree->max;
	if (tree->left != NULL && max < tree->left->max) {
		max = tree->left->max;
	}
	if (tree->right != NULL && max < tree->right->max) {
		max = tree->right->max;
	}
	tree->max = max;
	return tree;
}


void print(Node * tree)
{
    if (tree == NULL) {
        cout << " * ";
        return;
    }
    else {
        cout << "( s";
        cout << tree->start;
        cout << "-e";
        cout << tree->end;
        cout << "-m";
        cout << tree->max;
        cout << " ";
        print(tree->left);
        print(tree->right);
        cout << ")";
    }
}

