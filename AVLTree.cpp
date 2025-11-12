#include "AVLTree.h"
#include <iostream>
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
    if(left == nullptr && right == nullptr) {
    return 0;
    }
        if(left == nullptr){
         return right->height + 1;
    }
        if(right == nullptr){
        return left->height + 1;
}
else {
    return max(left->height , right->height) + 1;
}
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
        remove(current, smallestInRight->key);
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
    if (!current) {
        return false;
    }
        if (current->key == key) {
           bool found = removeNode(current);
            if (current)
            current->height = current->getHeight();
            return found;
        }
        if (key > (current)->key) {
           bool found = remove(current->right, key);
            if (current)
            current->height = current->getHeight();
            return found;
        }
        if (key < (current)->key) {
           bool found = remove(current->left, key);
            current->height = current->getHeight();
            return found;
        }
}

void AVLTree::balanceNode(AVLNode *&node) {
}
AVLTree::AVLTree() {
    root = nullptr;
    }
AVLTree::AVLNode::AVLNode(const KeyType& k, const ValueType& v) {
    key = k;
    value = v;
    height = 0;
    left = nullptr;
    right = nullptr;
}






// functions created

bool AVLTree::insert(const string& key, size_t value) {
    if (root == nullptr) {
        root = new AVLNode(key, value);
        return true;
    }
       if ( insertKey(key, value, root)) {
           return true;
       }
    return false;
}
bool AVLTree::insertKey(const KeyType &key, const ValueType &value, AVLNode *current) {
    if (current->key == key) {
        return false;
    }
    if (key > current->key) {
        if (current->right == nullptr) {
            current->right = new AVLNode(key, value);
            current->height = current->getHeight();
            balanceNode(current);
            return true;
        }
        if ( insertKey(key, value, current->right)) {
            current->height = current->getHeight();
            return true;
        }
        return false;
    }
    else if (key < current->key) {
        if (current->left == nullptr) {
            current->left = new AVLNode(key,value);
            // current->height = max(current->left->height, current->right->height) + 1;
            current->height = current->getHeight();
            balanceNode(current);
            return true;
        }
        insertKey(key, value, current->left);
        current->height = current->getHeight();
        return true;
    }
}

bool AVLTree::remove(const string &key) {
            if (remove(root, key)) {
                return true;
            }
    return false;
        }
bool AVLTree::contains(const string &key) {
    AVLNode* current = root;
    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        if (key > (current)->key) {
            current = current->right;
        }
        else if (key < (current)->key) {
            current = current->left;
        }
    }
    return false;
}
optional<size_t> AVLTree::get(string &key) {
    AVLNode* current = root;
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        if (key > (current)->key) {
            current = current->right;
        }
        else if (key < (current)->key) {
            current = current->left;
        }
    }
    return std::nullopt;
}
size_t &AVLTree::operator[](const string &key) {
    AVLNode* current = root;
    while (current != nullptr) {
        if (current->key == key) {
            return current->value;
        }
        if (key > (current)->key) {
            current = current->right;
        }
        else if (key < (current)->key) {
            current = current->left;
        }
    }
    throw std::runtime_error("Key not found in AVLTree");
}

vector<string> AVLTree::findRange(const KeyType &lowKey, const KeyType &highKey) {
    AVLNode* current = root;
    vector<string> keys;
    while (current != nullptr) {
        if (current->key == lowKey) {
            findRangeKeys(current, highKey, keys);
            return keys;
        }
        if (lowKey > (current)->key && highKey < (current)->key) {
            current = current->right;
        }
        else if (lowKey < (current)->key) {
            current = current->left;
        }
    }
    return keys;
}

void AVLTree::findRangeKeys(AVLNode* rootKey, const KeyType &highKey, vector<KeyType> &keys) {
    if (rootKey->key > highKey) {
        return;
    }
    findRangeKeys(rootKey->left, highKey, keys);
    if (rootKey->key < highKey) {
        keys.push_back(rootKey->key);
    }
    findRangeKeys(rootKey->right, highKey, keys);
}



vector<string> AVLTree::keys() const {
    AVLNode* current = root;
    vector<string> keys ;
    findAllKeys(current, keys);
    return keys;
}
void AVLTree::findAllKeys(AVLNode* current, vector<string>& keys) const {
    if (current == nullptr) {
        return;
    }
    findAllKeys(current->left, keys);
    keys.push_back(current->key);
    findAllKeys(current->right, keys);
}

void AVLTree::operator=(const AVLTree &other) {

}
ostream& operator<<(ostream& os, const AVLTree& avlTree) {
    avlTree.print(os, avlTree.root);
    return os;
}
void AVLTree::print(ostream &os, AVLNode *current) const {
    if (current->right == nullptr) {
        return;
    }
    print(os, current->right);
    os <<"{" << current->key<<":"<<current->value << "}";
    if (current->left != nullptr)
    print(os, current->left);
}
