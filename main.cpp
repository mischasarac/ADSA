#include <iostream>
#include <vector>
using namespace std;


struct Node{
    int val;
    int height;
    Node* left;
    Node* right;
    Node(){
        this->val = 0;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }

    Node(int val){
        this->val = val;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

int height(Node* n){
    if(!n) { return 0; }
    return n->height;
}

// Rotate right
Node* rRight(Node* n){
    Node* l = n->left;
    Node* temp = l->right;

    l->right = n;
    n->left = temp;

    l->height = 1 + max(height(l->left), height(l->right));
    n->height = 1 + max(height(n->left), height(n->right));

    return l;
}

// Rotate left
Node* rLeft(Node* n){

    Node* r = n->right;
    Node* temp = r->left;

    r->left = n;
    n->right = temp;

    r->height = 1 + max(height(r->left), height(r->right));
    n->height = 1 + max(height(n->left), height(n->right));

    return r;
}

// gets current balance as negative or positive value
// left_height - right_height
int currBalance(Node* n){
    if(!n){
        return 0;
    }

    return height(n->left) - height(n->right);
}

// head -> left -> right
void preOrder(Node* root){
    if(root){
        cout << root->val << endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}

// left -> right -> head
void postOrder(Node* root){
    if(root){
        postOrder(root->left);
        postOrder(root->right);
        cout << root->val << endl;
    }
}

// left -> head -> right
void inOrder(Node* root){
    if(root){
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
}


Node* insert(Node* root, int val){
    // Base condition of recursive return
    if(!root){ // Triggers only when root is nullptr
        return new Node(val);
    }

    // Travelling down recursive tree
    if(val < root->val){
        root->left = insert(root->left, val);
    } else if(val > root->val){
        root->right = insert(root->right, val);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int cost = currBalance(root);

    if(cost < -1){
        if(val < (root->right)->val){
            cout << "rl : " << root->val << endl;
            root->right = rRight(root->right);
        }
        return rLeft(root);
    }
    if(cost > 1){
        if(val > (root->left)->val){
            cout << "lr : " << root->val << endl;
            root->left = rLeft(root->left);
        }
        return rRight(root);
    }

    return root;

}


Node* leftmostRight(Node* root){
    while(root && root->left)
        root = root->left;
    return root;
}


Node* remove(Node* root, int val){
    if(!root){
        return nullptr;
    }

    if(val < root->val){
        root->left = remove(root->left, val);
    } else if(val > root->val){
        root->right = remove(root->right, val);
    } else { // Value is one needing to be deleted
        if(root->left == nullptr || root->right == nullptr){ 
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) { // No child case
                temp = root;
                root = nullptr;
            } else { // One child case
                *root = *temp;
            }
            delete temp;
        } else {// Has 2 children
            Node* temp = leftmostRight(root->right);
            root->val = temp->val;
            root->right = remove(root->right, val); // Fixing up order of remaining parts of tree
        }
    }

    if(!root){
        return nullptr;
    }

    root->height = 1 + max(height(root->left), height(root->right));
;

    int balance = currBalance(root);

    if(balance < -1){
        if(currBalance(root->right) >= 0){
            root->right = rRight(root->right);
            return rLeft(root);
        } else if(currBalance(root->right) < 0){
            return rLeft(root);
        }
    } else if(balance > 1){
        if(currBalance(root->left) >= 0){
            return rRight(root);
        } else if(currBalance(root->left) < 0){
            root->left = rLeft(root->left);
            return rRight(root);
        }
    }

    return root;

}



int main(){
    Node *root = nullptr;

    // Constructing tree given in the 
    // above figure
    cout << "Inserting 9" << endl;
    root = insert(root, 9);
    cout << "Inserting 5" << endl;
    root = insert(root, 5);
    cout << "Inserting 10" << endl;
    root = insert(root, 10);
    cout << "Inserting 0" << endl;
    root = insert(root, 0);
    cout << "Inserting 6" << endl;
    root = insert(root, 6);
    cout << "Inserting 11" << endl;
    root = insert(root, 11);
    cout << "Inserting -1" << endl;
    root = insert(root, -1);
    cout << "Inserting 1" << endl;
    root = insert(root, 1);
    cout << "Inserting " << endl;
    root = insert(root, 2);

    cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    preOrder(root);

    root = remove(root, 10);

    cout << "\nPreorder traversal after"
            " deletion of 10 \n";
    preOrder(root);

    return 0;
}
