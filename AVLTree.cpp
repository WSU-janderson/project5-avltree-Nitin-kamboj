#include "AVLTree.h"
#include <iostream>
#include <string>

// This method is used to check the number of children for each member of tree.
size_t AVLTree::AVLNode::numChildren() const {
    if (left != nullptr && right != nullptr) {
        return 2;
    }
    if (left != nullptr || right != nullptr) {
        return 1;
    }
    return 0;
}

// To check whether the given node has zero children or not
bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    }
    return false;
}

// To check the height of the node with O(1) complexity
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

// This method is used to remove the node if the node is leaf , 1 child or 2 child.
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
            balanceNode(current);
        } else {
            if (current == root) {
                root = current->left;
            }
            current = current->left;
            balanceNode(current);
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

// This remove function is used to find the key to be removed and then if found go to removeNode function.
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

// This method is used to check the balance of nodes and do rotation on the basis of that.
void AVLTree::balanceNode(AVLNode *&node) {
    int lheight;
    int rheight;
    int llheight;
    int lrheight;
    int rlheight;
    int rrheight;
    if (node->left != nullptr) {
        lheight = node->left->height;
        if (node->left->left != nullptr) {
            llheight = node->left->left->height;
        }
        else {
            llheight = -1;
        }
        if (node->left->right != nullptr) {
            lrheight = node->left->right->height;
        }
        else {
            lrheight = -1;
        }
    }
    else {
        lheight = -1;
        llheight = -1;
        lrheight = -1;
    }
    if (node->right != nullptr) {
        rheight = node->right->height;
        if (node->right->left != nullptr) {
            rlheight = node->right->left->height;
        }
        else {
            rlheight = -1;
        }
        if (node->right->right != nullptr) {
            rrheight = node->right->right->height;
        }
        else {
            rrheight = -1;
        }
    }
    else {
        rheight = -1;
        rlheight = -1;
        rrheight = -1;
    }

// condition to check if the node to be rotated or not.
        if (lheight - rheight > 1 ) {
            if (llheight - lrheight < 0 ) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        }
        else if (lheight - rheight < -1) {
            if (rlheight - rrheight > 0 ) {
                rotateRight(node->right);
            }
            rotateLeft(node);
    }
}
// Left rotation method is used to do the left rotation of node.
void AVLTree::rotateLeft(AVLNode *&node) {
    AVLNode* problemNode = node;
    AVLNode* hook = problemNode->right;
    AVLNode* temp = hook->left;
    problemNode->right = temp;
    hook->left = problemNode;

    node = hook;
    AVLNode* newHook = node->left;
    newHook->height = newHook->getHeight();
    node->height = node->getHeight();

}
// Right rotation is used to do the right rotation of node.
void AVLTree::rotateRight(AVLNode *&node) {
    AVLNode* problemNode = node;
    AVLNode* hook = node->left;
    AVLNode* temp = hook->right;
    problemNode->left = temp;
    hook->right = problemNode;
    node = hook;
    AVLNode* newHook = node->right;
    newHook->height = newHook->getHeight();
    node->height = node->getHeight();

}
// This is default constructor.
AVLTree::AVLTree() {
    root = nullptr;
    size_ = 0;
    }
// Constructor of AVLNode to store its values.
AVLTree::AVLNode::AVLNode(const KeyType& k, const ValueType& v) {
    key = k;
    value = v;
    height = 0;
    left = nullptr;
    right = nullptr;
}





// This method is used to insert the key using calling insertKey method and insert directly if root is nullptr and the size increment by 1.
bool AVLTree::insert(const string& key, size_t value) {
    if (root == nullptr) {
        root = new AVLNode(key, value);
        size_++;
        return true;
    }
       if ( insertKey(key, value, root)) {
           size_++;
           return true;
       }
    return false;
}

// This is the recursive method of insert to insert the key if there is no duplication and set the height.
bool AVLTree::insertKey(const KeyType &key, const ValueType &value, AVLNode *&current) {
    if (current->key == key) {
        return false;
    }
    // check the condition whether the given key is greater or not and go right and left on the basis of that.
    if (key > current->key) {
        if (current->right == nullptr) {
            current->right = new AVLNode(key, value);
            current->height = current->getHeight();
            balanceNode(current);
            return true;
        }
        if ( insertKey(key, value, current->right)) {
            current->height = current->getHeight();
            balanceNode(current);
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
        balanceNode(current);
        return true;
    }
}

// This method is only used to call remove function that works recursively to find tha key for removal and do size--;
bool AVLTree::remove(const string &key) {
            if (remove(root, key)) {
                size_--;
                return true;
            }
    return false;
        }
// To check whether the given key is the tree or not
// return boolean type
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
// return the value of the given key if found or else return nullopt.
optional<size_t> AVLTree::get(const string &key) {
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
// The bracket operator, operator[], allows us to use our map the same way various programming languages such as C++ and Python allow us to use keys to access values.
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

// This method is used to call findrangeKeys function that works recurisvely to return the values in that particular range.
vector<size_t> AVLTree::findRange(const KeyType &lowKey, const KeyType &highKey) {
    vector<size_t> keys;
    findRangeKeys(root,highKey,lowKey,keys);
    return keys;
}

// returns the value that are between the high and low keys recurisvely.
void AVLTree::findRangeKeys(AVLNode* rootKey, const KeyType &highKey,const KeyType &lowkey, vector<ValueType> &keys) {
    if (rootKey == nullptr) {
        return;
    }
    findRangeKeys(rootKey->left, highKey, lowkey, keys);
    if (rootKey->key <= highKey && rootKey->key >= lowkey) {
        keys.push_back(rootKey->value);
    }
    findRangeKeys(rootKey->right, highKey, lowkey, keys);

}
// The keys() method will return a std::vector with all of the keys currently in the tree. The length of the vector should be the same as the size of the tree
vector<string> AVLTree::keys() const {
    AVLNode* current = root;
    vector<string> keys ;
    findAllKeys(current, keys);
    return keys;
}

// This wroks recursively to find all keys of the trees and push back in the keys vectors.
void AVLTree::findAllKeys(AVLNode* current, vector<string>& keys) const {
    if (current == nullptr) {
        return;
    }
    findAllKeys(current->left, keys);
    keys.push_back(current->key);
    findAllKeys(current->right, keys);
}

ostream& operator<<(ostream& os, const AVLTree& avlTree) {
    avlTree.print(os, avlTree.root, 0);
    return os;
}
void AVLTree::print(ostream &os, AVLNode *current, int depth) const {
    if (current == nullptr) {
        return;
    }
    print(os, current->right , depth + 1);
    for (int i =0 ; i< depth; i++) {
        os << "  ";
    }
    os <<"{" << current->key<<":"<<current->value << "}" << endl;
    print(os, current->left, depth + 1);
}
// The size() method returns how many key-value pairs are in the tree.
// The time complexity for this method must be 𝒪︀(1).
size_t AVLTree::size() const {
    return  size_;
}

// COPY CONSTRUCTOR
AVLTree::AVLTree(const AVLTree &other) {
    root = nullptr;
    size_ = 0;
    copyTree(other.root);
}
// this method copies all the keys and values to new tree uses insert method  and works recusively.
void AVLTree::copyTree(AVLNode *node)  {
    if (!node) {
        return;
    }
    insert(node->key, node->value);
    copyTree(node->left);
    copyTree(node->right);
}
// operator == function create a deep copy of the other tree. The main difference is the tree we want to copy into may already have had elements inserted, so that memory needs to be released.
void AVLTree::operator=(const AVLTree &other) {
    if (this == &other) return;
    clear(root);
    root = nullptr;
    size_ = 0;
    copyTree(other.root);
}
// descructor
AVLTree::~AVLTree() {
    clear(root);
    root = nullptr;
    size_ = 0;
}

// this method is used to clear the tree
void AVLTree::clear(AVLNode *&node) {
    if (node == nullptr) {
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}
// this method is used to return the height of node in O(1) complexity.
size_t AVLTree::getHeight() const {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}