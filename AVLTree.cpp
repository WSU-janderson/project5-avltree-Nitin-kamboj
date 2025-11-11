#include "AVLTree.h"

#include <string>

size_t AVLTree::AVLNode::numChildren() const {
    if (left != nullptr && right != nullptr) {
        return 2;
    }
    if (left != nullptr || right != nullptr) {
        return 1;
    }
    return 0;
}

bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

bool AVLTree::removeNode(AVLNode*& current){
    if (!current) {
        return false;
    }
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        delete current;
        current = NULL;
        return true;
    }
    AVLNode* toDelete = current;
    if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            if (current == root) {
                root = current->right;
            }
            current = current->right;
        } else {
            if (current == root) {
                root = current->left;
            }
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        // remove(root, smallestInRight->key); // delete this one
        remove(toDelete, smallestInRight->key);
        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;
    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    AVLNode* smallestInRight;
    // if there is somethig in right
    if (current->right) {
        smallestInRight = current->right;
        // if right is leaf node
        if (smallestInRight->key == key && smallestInRight->isLeaf()) {
            AVLNode* todelete = smallestInRight;
            if (smallestInRight == root) {
                root = nullptr;
            }
            smallestInRight = nullptr;
            delete todelete;
            todelete = nullptr;
            return true;
        }
        // if right is not leaf node
        if (smallestInRight->key == key && !smallestInRight->isLeaf()) {
            AVLNode* todelete = smallestInRight;
            if (smallestInRight == root) {
                root = smallestInRight->right;
            }
            current->right = smallestInRight->right;
            delete todelete;
            return true;
        }
        // if there is left key after going right
        while (smallestInRight->left->key != key) {
            smallestInRight = smallestInRight->left;
        }
        AVLNode* todelete = smallestInRight->left;
        if (smallestInRight->left->isLeaf()) {
            smallestInRight->left = nullptr;
            delete todelete;
            return true;
        }
        if (!smallestInRight->left->isLeaf()) {
            smallestInRight->left = smallestInRight->left->right;
            delete todelete;
            return true;
        }
    }
    else {
        smallestInRight = current->left;
        current = smallestInRight;
        return true;
    }
    return true;
}

void AVLTree::balanceNode(AVLNode *&node) {
}
AVLTree::AVLTree() {
    root = nullptr;
    }
AVLTree::AVLNode::AVLNode(const KeyType& k, const ValueType& v)
    : key(k), value(v), height(1), left(nullptr), right(nullptr) {}






// functions created

bool AVLTree::insert(const string& key, size_t value) {
    if (root == nullptr) {
        root = new AVLNode(key, value);
        return true;
    }
    AVLNode* current = root;
    while (true) {
        if (current->key == key) {
            return false;
        }
        if (key > current->key) {
            if (current->right == nullptr) {
                current->right = new AVLNode(key, value);
                return true;
            }
            current = current->right;
        }
        else if (key < current->key) {
            if (current->left == nullptr) {
                current->left = new AVLNode(key,value);
                return true;
            }
            current = current->left;
        }
    }
}
bool AVLTree::remove(const string &key) {
        AVLNode* current = root;
        while (current != nullptr) {
            if (current->key == key) {
                removeNode(current);
                current = nullptr;
                return true;
            }
            if (key > (current)->key) {
                current = ((current)->right);
            }
            else if (key < (current)->key) {
                current = (current->left);
            }
        }
    return false;
        }