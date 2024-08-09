#include <iostream>
#include <unordered_map>
#include "../headers/Trees/AVLTree.cpp"
#include "../headers/Trees/binarySearchTree.cpp"
#include "../headers/Trees/redBlackTree.cpp"
#include "../headers/Trees/SplayTree.cpp"
#include "../headers/Trees/BTree.cpp" // Include the BTree header
#include "../headers/Trees/k-arySearchTree.cpp"
#include "../headers/Trees/expressionTree.cpp"
using namespace std;

// Function to let the user choose the tree to work with
string chooseTree() {
  int choice;
  cout << "Choose the tree you want to work with: " << endl;
  cout << "1. AVL Tree" << endl;
  cout << "2. Binary Search Tree" << endl;
  cout << "3. Red Black Tree" << endl;
  cout << "4. Splay Tree" << endl;
  cout << "5. BTree" << endl; // Add BTree option
  cout<< "6. K-ary Search Tree" << endl;
  cout << "7. Expression Tree" << endl;
  cout << "8. Exit" << endl;
  cin >> choice;
  switch(choice) {
    case 1:
      return "AVLTree";
    case 2:
      return "BSTree";
    case 3:
      return "RBTree";
    case 4:
      return "SplayTree";
    case 5:
      return "BTree"; // Return BTree
    case 6:
      return "K-arySTree";
    case 7:
      return "ExpressionTree";
    case 8:
      return "Exit";
    default:
      cout << "Invalid choice" << endl;
      return "Invalid";
  }
}

int main() {
  string tree = chooseTree(); 
  if(tree == "Exit") {
    return 0;
  }

  // Create the tree object from the user's choice and test every function
  if(tree == "AVLTree") {
    AVLTree<int> avl;
    // Insert
    cout << "Inserting 10, 20, 30, 40, 50, 25, 35, 45, 55" << endl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    avl.insert(35);
    avl.insert(45);
    avl.insert(55);
    // Print
    avl.print();
    // Search
    cout << "Searching for 30: " << avl.search(30) << endl;
    // Delete
    cout << "Deleting 30" << endl;
    avl.remove(30);
    avl.print();
  } else if(tree == "BTree") {
    BTree<int, 2> btree;
    // Insert
    cout << "Inserting 10, 20, 30, 40, 50, 25, 35, 45, 55" << endl;
    btree.insert(1);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(2);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(3);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(4);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(5);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(6);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(7);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(8);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(9);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(10);
    cout<<endl;
    btree.prettyPrint();
    btree.insert(11);
    cout<<endl;
    btree.prettyPrint();
    // Print
    btree.print();
    // Search
    cout << "Searching for 30: " << btree.search(30) << endl;
    // Delete
    cout << "Deleting 30" << endl;
    btree.remove(30);
    btree.print();
    // Save to disk
    cout << "Saving BTree to disk" << endl;
    btree.saveToDisk("btree.dat");
    // Load from disk
    cout << "Loading BTree from disk" << endl;
    BTree<int, 3> loadedBTree;
    loadedBTree.loadFromDisk("btree.dat");
    loadedBTree.print();
  } else if(tree == "K-arySTree") {
    KarySearchTree<int> karyTree(3); // Assuming 3-ary tree
    // Insert
    cout << "Inserting 10, 20, 30, 40, 50, 25, 35, 45, 55" << endl;
    karyTree.insert(10);
    karyTree.insert(20);
    karyTree.insert(30);
    karyTree.insert(40);
    karyTree.insert(50);
    karyTree.insert(25);
    karyTree.insert(35);
    karyTree.insert(45);
    karyTree.insert(55);
    // Print
    karyTree.print();
    // Search
    cout << "Searching for 30: " << karyTree.search(30) << endl;
    // Delete
    cout << "Deleting 30" << endl;
    karyTree.remove(30);
    karyTree.print();
  } else if(tree == "BSTree") {
    BinarySearchTree<int> bst;
    // Insert
    cout << "Inserting 10, 20, 30, 40, 50, 25, 35, 45, 55" << endl;
    bst.insert(10);
    bst.insert(20);
    bst.insert(30);
    bst.insert(40);
    bst.insert(50);
    bst.insert(25);
    bst.insert(35);
    bst.insert(45);
    bst.insert(55);
    // Print
    bst.print();
    // Search
    cout << "Searching for 30: " << bst.search(30) << endl;
    // Delete
    cout << "Deleting 30" << endl;
    bst.remove(30);
    bst.print();
  } else if(tree == "RBTree") {
    RedBlackTree<int> rbt;
    // Insert
    cout << "Inserting 10, 20, 30, 40, 50, 25, 35, 45, 55" << endl;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(40);
    rbt.insert(50);
    rbt.insert(25);
    rbt.insert(35);
    rbt.insert(45);
    rbt.insert(55);
    // Print
    rbt.print();
    // Search
    cout << "Searching for 30: " << rbt.search(30) << endl;
    // Delete
    cout << "Deleting 30" << endl;
    rbt.remove(30);
    rbt.print();
  } else if(tree == "SplayTree") {
    SplayTree<int> splay;
    // Insert
    cout << "Inserting 10, 20, 30, 40, 50, 25, 35, 45, 55" << endl;
    splay.insert(10);
    splay.insert(20);
    splay.insert(30);
    splay.insert(40);
    splay.insert(50);
    splay.insert(25);
    splay.insert(35);
    splay.insert(45);
    splay.insert(55);
    // Print
    splay.print();
    // Search
    cout << "Searching for 30: " << splay.search(30) << endl;
    // Delete
    cout << "Deleting 30" << endl;
    splay.remove(30);
    splay.print();
  } else if(tree == "ExpressionTree") {
    ExpressionTree<const char*> exprTree;
    // Insert
    cout << "Inserting '10', '20', '30', '40', '50', '25', '35', '45', '55'" << endl;
    exprTree.insert("10");
    exprTree.insert("20");
    exprTree.insert("30");
    exprTree.insert("40");
    exprTree.insert("50");
    exprTree.insert("25");
    exprTree.insert("35");
    exprTree.insert("45");
    exprTree.insert("55");
    // Print
    exprTree.print();
    // Search
    cout << "Searching for '30': " << exprTree.search("30") << endl;
    // Delete
    cout << "Deleting '30'" << endl;
    exprTree.remove("30");
    exprTree.print();
  }

  return 0;
}
