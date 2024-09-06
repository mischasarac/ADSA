#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int val;
    int height;
    Node* left;
    Node* right;

    Node(int val) {
        this->val = val;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Helper functions for AVL tree operations
int height(Node* n) {
    if (!n) return 0;
    return n->height;
}

// Rotate right
Node* rRight(Node* n) {
    Node* l = n->left;
    Node* temp = l->right;

    l->right = n;
    n->left = temp;

    l->height = 1 + max(height(l->left), height(l->right));
    n->height = 1 + max(height(n->left), height(n->right));

    return l;
}

// Rotate left
Node* rLeft(Node* n) {
    Node* r = n->right;
    Node* temp = r->left;

    r->left = n;
    n->right = temp;

    r->height = 1 + max(height(r->left), height(r->right));
    n->height = 1 + max(height(n->left), height(n->right));

    return r;
}

int currBalance(Node* n) {
    if (!n) return 0;
    return height(n->left) - height(n->right);
}

Node* insert(Node* root, int val) {
    if (!root) return new Node(val);

    if (val < root->val)
        root->left = insert(root->left, val);
    else if (val > root->val)
        root->right = insert(root->right, val);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = currBalance(root);

    // Left Right Case
    if (balance > 1 && val > root->left->val) {
        root->left = rLeft(root->left);
        return rRight(root);
    }
    // Left Left Case
    if (balance > 1 && val < root->left->val) {
        return rRight(root);
    }
    // Right Left Case
    if (balance < -1 && val < root->right->val) {
        root->right = rRight(root->right);
        return rLeft(root);
    }
    // Right Right Case
    if (balance < -1 && val > root->right->val) {
        return rLeft(root);
    }

    return root;
}

// AVL remove function
Node* leftmostRight(Node* root) {
    while (root && root->left) root = root->left;
    return root;
}

Node* remove(Node* root, int val) {
    if (!root) return nullptr;

    if (val < root->val)
        root->left = remove(root->left, val);
    else if (val > root->val)
        root->right = remove(root->right, val);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = leftmostRight(root->right);
            root->val = temp->val;
            root->right = remove(root->right, temp->val);
        }
    }

    if (!root) return nullptr;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = currBalance(root);

    if (balance > 1 && currBalance(root->left) < 0) {
        root->left = rLeft(root->left);
        return rRight(root);
    }
    if (balance > 1 && currBalance(root->left) >= 0)
        return rRight(root);

    if (balance < -1 && currBalance(root->right) > 0) {
        root->right = rRight(root->right);
        return rLeft(root);
    }
    if (balance < -1 && currBalance(root->right) <= 0)
        return rLeft(root);

    return root;
}

// Pre-order traversal
void preOrder(Node* root) {
    if (root) {
        cout << root->val << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Post-order traversal
void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->val << " ";
    }
}

// In-order traversal
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->val << " ";
        inOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    string input;
    vector<pair<int, bool>> vals;

    getline(cin, input);

    int i = 0;
    bool del;
    string num;

    // Parsing the input
    while (i < input.size()) {
        del = false;
        num = "";

        if (input[i] == 'D') {
            del = true;
            i++; // Move past 'D'
        } else if (input[i] == 'A') {
            i++; // Move past 'A'
        } else {
            break;
        }

        // Extract the numbers
        while (i < input.size() && isdigit(input[i])) {
            num += input[i];
            i++;
        }

        if (!num.empty()) {
            int a = stoi(num);
            vals.push_back({a, del});
        }

        // Skip any spaces
        while (i < input.size() && input[i] == ' ') {
            i++;
        }
    }

    for (auto j : vals) {
        if (j.second) {
            root = remove(root, j.first);
        } else {
            root = insert(root, j.first);
        }
    }

    // Handle output based on the command
    if (i < input.size()) {
        if (input[i] == 'I') {
            inOrder(root);
        } else if (input[i] == 'P' && input[i + 1] == 'O') {
            postOrder(root);
        } else {
            preOrder(root);
        }
    } else if (root == nullptr) {
        cout << "EMPTY";
    }

    cout << endl;
    return 0;
}
