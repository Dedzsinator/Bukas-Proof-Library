#include <iostream>
#include <unordered_map>
#include "../headers/Trees/AVLTree.cpp"
#include "../headers/Trees/binarySearchTree.cpp"
#include "../headers/Trees/redBlackTree.cpp"
#include "../headers/Trees/SplayTree.cpp"
using namespace std;

//function to let the user choose the tree to work with
string chooseTree() {
  int choice;
  cout << "Choose the tree you want to work with: " << endl;
  cout << "1. AVL Tree" << endl;
  cout << "2. Binary Search Tree" << endl;
  cout << "3. Red Black Tree" << endl;
  cout << "4. Splay Tree" << endl;
  cout << "5. Exit" << endl;
  cin >> choice;
  switch(choice) {
    case 1:
      return "AVLTree";
      break;
    case 2:
      return "BSTree";
      break;
    case 3:
      return "RBTree";
      break;
    case 4:
      return "SplayTree";
      break;
    case 5:
      return "Exit";
      break;
    default:
      cout << "Invalid choice" << endl;
      break;
  }
}

int main() {

  string tree = chooseTree(); 
  if(tree == "Exit") {
    return 0;
  }

  //create the tree object from the user's choice and test every function, dont try too hard
  
  if(tree == "AVLTree") {
    AVLTree<int> avl;
    //insert
    cout<<"Inserting 10, 20, 30, 40, 50, 25, 35, 45, 55"<<endl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);
    avl.insert(35);
    avl.insert(45);
    avl.insert(55);
    //search print 
    fancyPrint(avl);
    //Search
    cout<<"Searching for 30: "<<avl.search(30)<<endl;

    //Delete
    cout<<"Deleting 30"<<endl;
    avl.remove(30);
    
    fancyPrint(avl);
 }

  return 0;
}
