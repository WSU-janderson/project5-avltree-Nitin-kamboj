/*
Driver code for testing your AVL Tree
This is NOT the test code for grading,
instead for you to get an idea of how to test the tree
 */
// Author: Nitin kamboj
/* Description:
 * This file contains the implementation of an AVL Tree, a self-balancing binary search tree.
 * The AVL Tree automatically maintains balance by performing rotations (single and double) during insertions and deletions.
 * Each node stores a key, value, height, and pointers to left and right children.
 */
#include "AVLTree.h"
#include <iostream>
#include <string>
#include <ranges>
#include <vector>
using namespace std;


int main() {
    AVLTree tree;
    bool insertResult;
    insertResult = tree.insert("F", 'F');
    cout << insertResult << endl;
    insertResult = tree.insert("F", 'F'); // false, no duplicates allowed
    cout << insertResult << endl;
    insertResult = tree.insert("K", 'K');
    cout << insertResult << endl;
    insertResult = tree.insert("B", 'B');// single rotate left
    cout << insertResult << endl;
    insertResult = tree.insert("C", 'C');
    cout << insertResult << endl;
    insertResult = tree.insert("D", 'D');
    cout << insertResult << endl;
    insertResult = tree.insert("E", 'E');
    cout << insertResult << endl;
    insertResult = tree.insert("F", 'F');
    cout << size(tree) << endl;
    cout << insertResult << endl;
    insertResult = tree.insert("M", 'M');
    cout << insertResult << endl;
    bool removeResult;
    AVLTree newTree;
    newTree = tree;
    cout << newTree <<"hjvbjdsfnkabkjdbk"<< endl;
    removeResult = tree.remove("F");
    cout << removeResult << endl;
    // removeResult = tree.remove("K");
    cout << removeResult << endl;
    insertResult = tree.insert("F", 'F');
    cout << insertResult << endl;
    removeResult = tree.remove("C");
    cout << removeResult << endl;
    removeResult = tree.remove("D");
    cout << removeResult << endl;
    removeResult = tree.remove("B");
    cout << removeResult << endl;
    removeResult = tree.remove("E");
    cout << removeResult << endl;
    removeResult = tree.remove("M");
    cout << removeResult << endl;
    cout << endl << endl;
    // int value = tree["K"];
    // cout << value << endl;
    // tree["K"] = 70;
    // cout << tree["K"] << endl;
    // value = tree["K"];
    // cout << value << endl;
    // cout << tree << endl;
    // cout << size(tree) << endl;
    // cout << tree << endl;

    insertResult = tree.insert("C", 'C');
    insertResult = tree.insert("A", 'A'); // single rotate right
    cout << endl << endl;
    cout << tree << endl;

    insertResult = tree.insert("D", 'D'); // double rotate right
    cout << endl << endl;
    cout << tree << endl;

    insertResult = tree.insert("R", 'R'); // double rotate left
    cout << endl << endl;
    cout << tree << endl;

    insertResult = tree.insert("V", 'V');
    insertResult = tree.insert("A", 'A'); // false, duplicate
    insertResult = tree.insert("Z", 'Z');
    insertResult = tree.insert("M", 'M');
    insertResult = tree.insert("D", 'D'); // false, duplicate
    cout << endl << endl;
    cout << tree << endl;

    // size and getHeight
    cout << "tree size: " << tree.size() << endl; // 10
    cout << "tree height: " << tree.getHeight() << endl; // 3
    cout << endl;

    // contains
    bool containsResult;
    containsResult = tree.contains("A"); // true
    cout << containsResult << endl;
    containsResult = tree.contains("N"); // false
    cout << containsResult << endl;
    // get
    optional<int> getResult;

    getResult = tree.get("A"); // 65
    cout << "A: " << getResult.value() << endl;

    getResult = tree.get("C"); // 67
    cout << "C: " << getResult.value() << endl;

    getResult = tree.get("Q"); // getResult has no value
    cout << "Q: " << getResult.has_value() << endl; // print 0
    cout << endl;

    // findRange
    vector<size_t> rangeTest = tree.findRange("D", "W");
    // 70 68 82 75 77 86
    for (auto val: rangeTest) {
        cout << val << " ";
    }
    cout << endl << endl;

    // operator[]
    tree["A"] = 108;
    cout << tree << endl;
    cout << endl;

    // remove
    // bool removeResult;
    removeResult= tree.remove("A"); // "A" is a leaf
    cout << endl << endl;
    cout << tree << endl;

    removeResult = tree.remove("C"); // "C" has one child, single rotate left
    cout << endl << endl;
    cout << tree << endl;

    removeResult = tree.remove("F"); // "F" has two children
    cout << endl << endl;
    cout << tree << endl;

    removeResult = tree.remove("V");
    removeResult = tree.remove("X");
    removeResult = tree.remove("Z"); // double rotate right
    cout << endl << endl;
    cout << tree << endl;

    return 0;
}
