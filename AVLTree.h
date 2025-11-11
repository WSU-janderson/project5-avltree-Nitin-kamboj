/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;

protected:
    class AVLNode {
    public:
        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;

        AVLNode (const KeyType& k, const ValueType& v);

    };

public:
    AVLTree();
    AVLTree(const KeyType& key, const ValueType& value);
    //INSERT
    bool insert(const string& key, size_t value);
    //REMOVE
    bool remove(const string& key);
    //CONTAINS
    bool contains(const string& key);
    //GET
    optional< size_t> get(string& key);
    //[] operator
    string& operator[](const size_t& key);
    //KEYS
    vector<string> keys() const;
    size_t size() const;
    size_t  getHeight() const;
    void operator=(const AVLTree& other);
    friend ostream& operator<<(ostream& os, const AVLTree& avlTree);



    private:
    AVLNode* root ;

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);


};

#endif //AVLTREE_H
