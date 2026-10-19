#include "../headers/avl.h"
#include <algorithm>


int getHeight(ANode* node) {
    if (!node) return 0;
    return node->height;
}

int getBalance(ANode* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void updateHeight(ANode* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

ANode* rotateRight(ANode* y) {
    ANode* x = y->left;
    ANode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

ANode* rotateLeft(ANode* x) {
    ANode* y = x->right;
    ANode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

ANode* balance(ANode* node) {
    if (!node) return node;
    updateHeight(node);
    int balanceFactor = getBalance(node);
    if (balanceFactor > 1 && getBalance(node->left) >= 0) return rotateRight(node);
    if (balanceFactor < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
    if (balanceFactor > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);}
    if (balanceFactor < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);}
    return node;
}


ANode* insert(ANode* node, int key) {
    if (!node) return new ANode{key, nullptr, nullptr, 1};
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;
    return balance(node);
}

ANode* findMin(ANode* node) {
    while (node && node->left) node = node->left;
    return node;
}

ANode* remove(ANode* node, int key) {
    if (!node) return nullptr;
    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        if (!node->left || !node->right) {
            ANode* child = node->left ? node->left : node->right;
            delete node;
            return child;
        } else {
            ANode* successor = findMin(node->right);
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        }
    }
    return balance(node);
}

ANode* search(ANode* node, int key) {
    if (!node || node->key == key) return node;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

void TINSERT(ANode*& node, int key) { node = insert(node, key); }
void TDEL(ANode*& node, int key) { node = remove(node, key); }
ANode* TGET(ANode* node, int key) { return search(node, key); }


void PRINT(ANode* n) {
    if (!n) return;
    cout << n->key << " ";
    PRINT(n->left);
    PRINT(n->right);
}

void PRINT_PRE(ANode* n) {
    if (!n) return;
    PRINT_PRE(n->left);
    cout << n->key << " ";
    PRINT_PRE(n->right);
}

void PRINT_IN(ANode* n) {
    if (!n) return;
    PRINT_IN(n->left);
    PRINT_IN(n->right);
    cout << n->key << " ";
}


void CleanTree(ANode*& node) {
    if (!node) return;
    CleanTree(node->left);
    CleanTree(node->right);
    delete node;
    node = nullptr;
}


static int CountNodes(ANode* node) {
    if (!node) return 0;
    return 1 + CountNodes(node->left) + CountNodes(node->right);
}

static void WritePreorder(ANode* node, ostream& out) {
    if (!node) return;
    out << " " << node->key;             
    WritePreorder(node->left, out);
    WritePreorder(node->right, out);
}

void SaveTree(ANode* node, ostream& out) {
    out << CountNodes(node);             
    WritePreorder(node, out);            
    out << "\n";                         
}

void LoadTree(ANode*& node, istream& in) {
    CleanTree(node);
    int count; in >> count;
    for (int i = 0; i < count; i++) {
        int v;
        in >> v;
        TINSERT(node, v);
    }
}