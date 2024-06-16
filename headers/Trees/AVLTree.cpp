#pragma once 

#include "../../headers/Trees/narySearchTree.cpp"

template <typename T> 
class AVLTree {
    using Node = typename NaryTree<T>::Node;
    
    Node* root;

public:
    void insert(Node* node, const T& data) {
      
      if(node == nullptr) {
        node = new Node;
        node->data = data;
        node->parent = nullptr;
        node->firstChild = nullptr;
        node->nextSibling = nullptr;
      
      } else {
        
        if(data < node->data) {
          
          if(node->firstChild == nullptr) {
            
            Node* newNode = new Node;
            newNode->data = data;
            newNode->parent = node;
            newNode->firstChild = nullptr;
            newNode->nextSibling = nullptr;
            
            node->firstChild = newNode;
          } else {
            
            insert(node->firstChild, data);
          }
        } else {
          
          if(node->nextSibling == nullptr) {
            
            Node* newNode = new Node;
            newNode->data = data;
            newNode->parent = node;
            newNode->firstChild = nullptr;
            newNode->nextSibling = nullptr;
            
            node->nextSibling = newNode;
          } else {
            
            insert(node->nextSibling, data);
          }
        }
      }
    }
    
    void remove(Node* node, const T& data) {
      
      if(node == nullptr) {
        return;
      } else {
        
        if(data < node->data) {
          
          remove(node->firstChild, data);
        } else if(data > node->data) {
          
          remove(node->nextSibling, data);
        } else {
          
          if(node->firstChild == nullptr && node->nextSibling == nullptr) {
            
            if(node->parent == nullptr) {
              
              delete node;
              node = nullptr;
            } else {
              
              if(node->parent->firstChild == node) {
                
                node->parent->firstChild = nullptr;
              } else {
                
                node->parent->nextSibling = nullptr;
              }
              
              delete node;
              node = nullptr;
            }
          } else if(node->firstChild == nullptr) {
            
            if(node->parent == nullptr) {
              
              root = node->nextSibling;
            } else {
              
              if(node->parent->firstChild == node) {
                
                node->parent->firstChild = node->nextSibling;
              } else {
                
                node->parent->nextSibling = node->nextSibling;
              }
            }
            
            delete node;
            node = nullptr;
          } else if(node->nextSibling == nullptr) {
            
            if(node->parent == nullptr) {
              
              root = node->firstChild;
            } else {
              
              if(node->parent->firstChild == node) {
                
                node->parent->firstChild = node->firstChild;
              } else {
                
                node->parent->nextSibling = node->firstChild;
              }
            }
          } else {
            
            Node* min = findMin(node->nextSibling);
            
            node->data = min->data;
            
            remove(node->nextSibling, min->data);
          }
        }
      }
    }

    
    bool search(Node* node, const T& data) const {
      
      
      if(node == nullptr) {
        return false;
      } else {
        
        if(data < node->data) {
          
          return search(node->firstChild, data);
        } else if(data > node->data) {
          
          return search(node->nextSibling, data);
        } else {
          return true;
        }
      }
    }

    
    void print(Node* node, int depth) const {
      
      
      if(node == nullptr) {
        return;
      } else {
        
        for(int i = 0; i < depth; i++) {
          std::cout << "  ";
        }
        std::cout << node->data << std::endl;
        
        print(node->firstChild, depth + 1);
        
        print(node->nextSibling, depth);
      }
    }

    
    Node* search(Node* node, const T& data) {
      
      
      if(node == nullptr) {
        return nullptr;
      } else {
        
        if(data < node->data) {
          
          return search(node->firstChild, data);
        } else if(data > node->data) {
          
          return search(node->nextSibling, data);
        } else {
          return node;
        }
      }
    }

    
    Node* findMin(Node* node) {
      
      
      if(node == nullptr) {
        return nullptr;
      } else {
        
        if(node->firstChild == nullptr) {
          return node;
        } else {
          
          return findMin(node->firstChild);
        }
      }
    }

    
    Node* findMax(Node* node) {
      
      
      if(node == nullptr) {
        return nullptr;
      } else {
        
        if(node->nextSibling == nullptr) {
          return node;
        } else {
          
          return findMax(node->nextSibling);
        }
      }
    }

    
    Node* findSuccessor(Node* node) {
      
      
      if(node->nextSibling != nullptr) {
        
        return findMin(node->nextSibling);
      } else {
        
        if(node->parent == nullptr) {
          return nullptr;
        } else {
          
          if(node->parent->firstChild == node) {
            return node->parent;
          } else {
            
            return findSuccessor(node->parent);
          }
        }
      }
    }

    
    Node* findPredecessor(Node* node) {
      
      
      if(node->firstChild != nullptr) {
        
        return findMax(node->firstChild);
      } else {
        
        if(node->parent == nullptr) {
          return nullptr;
        } else {
          
          if(node->parent->nextSibling == node) {
            return node->parent;
          } else {
            
            return findPredecessor(node->parent);
          }
        }
      }
    }

    
    void transplant(Node* u, Node* v) {

    }

    
    void insertFixup(Node* node) {
      
    }

    
    void removeFixup(Node* node){}

    
    void leftRotate(Node* node) {
      
      
      if(node->nextSibling == nullptr) {
        return;
      } else {
        
        Node* newNode = new Node;
        newNode->data = node->data;
        newNode->parent = node->parent;
        newNode->firstChild = node->firstChild;
        newNode->nextSibling = node->nextSibling->firstChild;
        
        if(node->parent == nullptr) {
          
          root = newNode;
        } else {
          
          if(node->parent->firstChild == node) {
            
            node->parent->firstChild = newNode;
          } else {
            
            node->parent->nextSibling = newNode;
          }
        }
        
        node->nextSibling->parent = node;
        
        node->parent = node->nextSibling;
        
        node->nextSibling->firstChild = node;
      }
    }

    
    void rightRotate(Node* node) {
      
      
      if(node->firstChild == nullptr) {
        return;
      } else {
        
        Node* newNode = new Node;
        newNode->data = node->data;
        newNode->parent = node->parent;
        newNode->firstChild = node->firstChild->nextSibling;
        newNode->nextSibling = node->nextSibling;
        
        if(node->parent == nullptr) {
          
          root = newNode;
        } else {
          
          if(node->parent->firstChild == node) {
            
            node->parent->firstChild = newNode;
          } else {
            
            node->parent->nextSibling = newNode;
          }
        }
        
        node->firstChild->parent = node;
        
        node->parent = node->firstChild;
        
        node->firstChild->nextSibling = node;
      }
    }

    
    int height(Node* node) const {
      
      
      if(node == nullptr) {
        return -1;
      } else {
        
        int leftHeight = height(node->firstChild);
        
        int rightHeight = height(node->nextSibling);
        
        return 1 + std::max(leftHeight, rightHeight);
      }
    }

    
    int balanceFactor(Node* node) const {
      
      
      if(node == nullptr) {
        return 0;
      } else {
        
        int leftHeight = height(node->firstChild);
        
        int rightHeight = height(node->nextSibling);
        
        return rightHeight - leftHeight;
      }
    }

    
    void updateHeight(Node* node) {
      
      
      if(node == nullptr) {
        return;
      } else {
        
        int leftHeight = height(node->firstChild);
        
        int rightHeight = height(node->nextSibling);
        
        node->height = 1 + std::max(leftHeight, rightHeight);
      }
    }

    
    void updateBalanceFactor(Node* node) {
      
      
      if(node == nullptr) {
        return;
      } else {
        
        node->balanceFactor = balanceFactor(node);
      }
    }

    
    void rebalance(Node* node) {
      
      
      if(node == nullptr) {
        return;
      } else {
        
        updateHeight(node);
        
        updateBalanceFactor(node);
        
        if(node->balanceFactor > 1) {
          
          if(node->nextSibling->balanceFactor < 0) {
            
            rightLeftRotate(node);
          } else {
            
            leftRotate(node);
          }
        } else if(node->balanceFactor < -1) {
          
          if(node->firstChild->balanceFactor > 0) {
            
            leftRightRotate(node);
          } else {
            
            rightRotate(node);
          }
        }
        
        rebalance(node->parent);
      }
    }

    
    AVLTree() {
      
      root = nullptr;
    }

    
    AVLTree(const T& data) {
      
      root = new Node;
      root->data = data;
      root->parent = nullptr;
      root->firstChild = nullptr;
      root->nextSibling = nullptr;
    }

    
    ~AVLTree() {
      
      
      if(root == nullptr) {
        return;
      } else {
        
        delete root;
        root = nullptr;
      }
    }

    
    void insert(const T& data) {
      
      
      if(root == nullptr) {
        root = new Node;
        root->data = data;
        root->parent = nullptr;
        root->firstChild = nullptr;
        root->nextSibling = nullptr;
      } else {
        
        if(data < root->data) {
          
          if(root->firstChild == nullptr) {
            
            Node* newNode = new Node;
            newNode->data = data;
            newNode->parent = root;
            newNode->firstChild = nullptr;
            newNode->nextSibling = nullptr;
            
            root->firstChild = newNode;
          } else {
            
            insert(root->firstChild, data);
          }
        } else {
          
          if(root->nextSibling == nullptr) {
            
            Node* newNode = new Node;
            newNode->data = data;
            newNode->parent = root;
            newNode->firstChild = nullptr;
            newNode->nextSibling = nullptr;
            
            root->nextSibling = newNode;
          } else {
            
            insert(root->nextSibling, data);
          }
        }
      }
    }

    
    void remove(const T& data) {
      
      
      if(root == nullptr) {
        return;
      } else {
        
        if(data < root->data) {
          
          remove(root->firstChild, data);
        } else if(data > root->data) {
          
          remove(root->nextSibling, data);
        } else {
          
          if(root->firstChild == nullptr && root->nextSibling == nullptr) {
            
            delete root;
            root = nullptr;
          } else if(root->firstChild == nullptr) {
            
            root = root->nextSibling;
          } else if(root->nextSibling == nullptr) {
            
            root = root->firstChild;
          } else {
            
            Node* min = findMin(root->nextSibling);
            
            root->data = min->data;
            
            remove(root->nextSibling, min->data);
          }
        }
      }
    }

    
    bool search(const T& data) const {
      
      
      if(root == nullptr) {
        return false;
      } else {
        
        if(data < root->data) {
          
          return search(root->firstChild, data);
        } else if(data > root->data) {
          
          return search(root->nextSibling, data);
        } else {
          return true;
        }
      }
    }

    
    bool empty() const {
      
      return root == nullptr;
    }
};
