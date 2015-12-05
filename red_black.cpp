/*
    A red black tree that only supports insertion and unique values.
*/

#include "iostream"

using namespace std;

enum Color {RED, BLACK};
enum Violation {LEFT_LEFT, LEFT_RIGHT, RIGHT_LEFT, RIGHT_RIGHT, NONE};

struct Node {
    int value;
    Color color;
    Node *left;
    Node *right;
};

Node * make_node(int value); // initialize new node
Node * insert(Node * tree, int value);
Node * insert_r(Node * tree, int value);
Node * rotate_left(Node * tree); // makes right child become root of subtree
Node * rotate_right(Node * tree); // makes left child become root of subtree
Node * insert_checkup(Node *tree); // ensures RB properties hold in subtree
int height(Node *tree);
int black_height(Node *tree);
void print(Node * tree);

int main() {

    cout << "inserting 1 million nodes [0 - 999,999]" << endl;
    Node *t = NULL;
    for (int i = 0; i < 1000*1000; i++) {
        t = insert(t, i);
    }
    cout << "height: " << height(t) << endl;
    cout << "black height: " << black_height(t) << endl;
    cout << "------------" << endl;
    cout << "testing case when you need two rotations" << endl;
    Node *t2 = NULL;
    t2 = insert(t2, 10);
    t2 = insert(t2, 2);
    t2 = insert(t2, 12);
    t2 = insert(t2, 8);
    print(t2);
    cout << endl;
    cout << "inserting 5" << endl;
    t2 = insert(t2, 5);
    print(t2);
    cout << endl;


}


Node * make_node(int value)
{
    Node *t = new Node;
    t->value = value;
    t->left = NULL;
    t->right = NULL;
    t->color = RED;
    return t;
}

Node * insert(Node * tree, int value)
{
    tree = insert_r(tree, value);
    tree->color = BLACK; // ensure root is BLACK
    return tree;
}

Node * insert_r(Node * tree, int value)
{
    if (tree == NULL) {
        tree = make_node(value);
    }
    else {
        if (value < tree->value) {
            tree->left = insert_r(tree->left, value);
        }
        else {
            tree->right = insert_r(tree->right, value);         
        }

        tree = insert_checkup(tree);

    }
    return tree;
}

Node * insert_checkup(Node *tree)
{
    // I am the grandparent of the violating node

    // guarunteed only one violation. Find out which one.
    Violation violation = NONE;
    if (tree->left != NULL) {
        if (tree->left->left != NULL) {
            if (tree->left->color == RED && tree->left->left->color == RED) {
                violation = LEFT_LEFT;
            }
        }
        if (tree->left->right != NULL) {
            if (tree->left->color == RED && tree->left->right->color == RED) {
                violation = LEFT_RIGHT;
            }
        }
    }
    if (tree->right != NULL) {
        if (tree->right->left != NULL) {
            if (tree->right->color == RED && tree->right->left->color == RED) {
                violation = RIGHT_LEFT;
            }
        }
        if (tree->right->right != NULL) {
            if (tree->right->color == RED && tree->right->right->color == RED) {
                violation = RIGHT_RIGHT;
            }
        }
    }

    if (violation == NONE) {
        return tree;
    }

    // CASE 1: uncle is RED

    bool can_color_uncle = false;
    can_color_uncle |= (violation == LEFT_LEFT || violation == LEFT_RIGHT) 
                       && (tree->right != NULL && tree->right->color == RED);
    can_color_uncle |= (violation == RIGHT_LEFT || violation == RIGHT_RIGHT) 
                       && (tree->left != NULL && tree->left->color == RED);

    if (can_color_uncle) {
        tree->left->color = BLACK;
        tree->right->color = BLACK;
        tree->color = RED;
        return tree;
    }

    // CASE 2: uncle is BLACK

    if (violation == LEFT_RIGHT) {
        tree->left = rotate_left(tree->left);
        violation = LEFT_LEFT;
    }
    if (violation == LEFT_LEFT) {
        tree = rotate_right(tree);
        tree->color = BLACK;
        tree->right->color = RED;
        return tree;
    }

    if (violation == RIGHT_LEFT) {
        tree->right = rotate_right(tree->right);
        violation = RIGHT_RIGHT;
    }

    if (violation == RIGHT_RIGHT) {
        tree = rotate_left(tree);
        tree->color = BLACK;
        tree->left->color = RED;
        return tree;
    }
    return tree;
}


Node * rotate_left(Node * tree)
{
    if (tree == NULL || tree->right == NULL) {
        return tree;
    }
    else {
        
        // order is left < me < right's left < right < right's right
        // need to make right the new root

        Node *temp_right = tree->right;
        
        // make right's left my right
        tree->right = tree->right->left;

        // make right's left me
        temp_right->left = tree;

        return temp_right;
    }
}

Node * rotate_right(Node * tree)
{
    if (tree == NULL || tree->left == NULL) {
        return tree;
    }
    else {
        
        // order is left's left < left < left's right < me < right
        // need to make left the new root

        Node *temp_left = tree->left;
        
        // make left's right my left
        tree->left = tree->left->right;

        // make left's right me
        temp_left->right = tree;

        return temp_left;
    }
}



void print(Node * tree)
{
    if (tree == NULL) {
        cout << " - ";
        return;
    }
    else {
        cout << "( ";
        cout << tree->value;
        if (tree->color == RED) {
            cout << 'r';
        }
        else {
            cout << 'b';
        }
        cout << " ";
        print(tree->left);
        print(tree->right);
        cout << ")";
    }
}

int height(Node *tree)
{
    if (tree == NULL) {
        return 0;
    }
    else {
        return max(height(tree->left), height(tree->right)) + 1;
    }
}

int black_height(Node *tree)
{
    if (tree == NULL) {
        return 1;
    }
    else {
        int left = black_height(tree->left);
        if (tree->color == BLACK) {
            left++;
        }
        return left;
    }
}

