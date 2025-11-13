/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
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
    ~AVLTree();
    AVLTree(const KeyType& key, const ValueType& value);
    AVLTree(const AVLTree &other);
    void copyTree(AVLNode* node) ;
    //INSERT
    bool insert(const string& key, size_t value);
    bool insertKey(const KeyType& key, const ValueType& value, AVLNode* node);
    //REMOVE
    bool remove(const string& key);
    //CONTAINS
    bool contains(const string& key);
    //GET
    optional< size_t> get(string& key);
    //[] operator
    size_t& operator[](const string& key);
    //KEYS
    vector<string> findRange(const KeyType& lowKey, const KeyType& highKey);
    void findRangeKeys(AVLNode* rootKey, const KeyType& highKey, vector<KeyType>& keys);
    vector<string> keys() const;
    void findAllKeys(AVLNode* root, vector<string>& keys) const;
    size_t size() const;
    // size_t  getHeight() const;
    void operator=(const AVLTree& other);
    friend ostream& operator<<(ostream& os, const AVLTree& avlTree);
    void print(ostream& os , AVLNode* current) const;




    private:
    AVLNode* root ;
    int size_;

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);
    void rotateLeft(AVLNode*& node);
    void rotateRight(AVLNode*& node);




};

#endif //AVLTREE_H
