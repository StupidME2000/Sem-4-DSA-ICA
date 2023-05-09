#include <iostream>
using namespace std;

struct node {
    int key;
    struct node *left, *right;
};

// create a new node
struct node* New_node(int data){
    node* temp = new node();
    temp -> key = data;
    temp -> left = NULL;
    temp -> right = NULL;
    return temp;
}

//Returns the node with minimum key value
struct node* minimum(struct node* node){
    struct node* NowNode = node;
    while (NowNode->left != NULL){
        NowNode = NowNode -> left;
    }
    return NowNode;
}

// Inorder traversal
void traverseInOrder(struct node *root) {
    if(root == NULL){
        return;
    }
    else {
        traverseInOrder(root -> left);
        cout << root -> key << " ";
        traverseInOrder(root -> right);
    }
}


// Insert a node
struct node *insertNode(struct node *node, int key) {

    if (node == NULL){
        return New_node(key);
    }
    else if (key < node -> key){
        node -> left = insertNode(node -> left, key);
    }
    else {
        node -> right = insertNode(node->right,key);
    }
    return node;
}


// Deleting a node
struct node *deleteNode(struct node *root, int data) {
    if (root ==NULL){
        return root;
    }
    if (data < root -> key){
        root -> left = deleteNode(root->left,data);
    }
    else if (data > root -> key){
        root -> right = deleteNode(root->right,data);

    }
    else{
        //no child
        if (root -> left == NULL and root -> right == NULL){
            return NULL;
        }

            //only right Child
        else if (root -> left == NULL){
            struct node* temp = root -> right;
            free(root);
            return temp;
        }

            //only left child
        else if (root -> right == NULL){
            struct node* temp = root -> left;
            free(root);
            return temp;
        }

            //Node with two children
        else{
            struct node* temp = minimum(root->right);
            root -> key = temp -> key;
            root -> right = deleteNode(root->right, temp -> key);
        }

    }
    return root;
}

// Driver code
int main() {
    struct node *root = NULL;

    int operation;
    int operand;
    cin >> operation;

    while (operation != -1) {
        switch(operation) {
            case 1: // insert
                cin >> operand;
                root = insertNode(root, operand);
                cin >> operation;
                break;
            case 2: // delete
                cin >> operand;
                root = deleteNode(root, operand);
                cin >> operation;
                break;
            default:
                cout << "Invalid Operator!\n";
                return 0;
        }
    }

    traverseInOrder(root);
}
