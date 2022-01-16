#ifndef TREES
#define TREES
#include <iostream>
#include <queue>
using namespace std;

typedef struct nod {
    int data;
    nod* left;
    nod* right;

    create(int data) {
        nod uj = new Node();
        if (!uj) {
            throw invalid_argument("Memory error");
            return NULL;
        }
        uj->data = data;
        uj->left = uj->right = NULL;
        return uj;
    }

    insert(nod* root, int data) {
    if (root == NULL) {
        root = create(data);
        return root;
    }

    queue<nod*> q;
    q.push(root);

    while (!q.empty()) {
        nod* temp = q.front();
        q.pop();

        if (temp->left != NULL)
            q.push(temp->left);
        else {
            temp->left = create(data);
            return root;
        }

        if (temp->right != NULL)
            q.push(temp->right);
        else {
            temp->right = create(data);
            return root;
        }
    }
}

    void inorder(nod* temp) {
        if (temp == NULL)
            return;
    
        inorder(temp->left);
        cout << temp->data << ' ';
        inorder(temp->right);
    }

    //^CHECK
    void preorder(nod* temp) {
        if (temp == NULL)
            return;
    
        cout << temp->data << ' ';
        preorder(temp->left);
        preorder(temp->right);
    }

    //^CHECK
    void postorder(nod* temp) {
        if (temp == NULL)
            return;
    
        postorder(temp->left);
        postorder(temp->right);
        cout << temp->data << ' ';
    }

    //^CHECK
    void deletDeepest(nod* root, nod* d_node) {
        queue<nod*> q;
        q.push(root);
    
        struct nod* temp;
        while (!q.empty()) {
            temp = q.front();
            q.pop();
            if (temp == d_node) {
                temp = NULL;
                delete (d_node);
                return;
            }
            if (temp->right) {
                if (temp->right == d_node) {
                    temp->right = NULL;
                    delete (d_node);
                    return;
                }
                else
                    q.push(temp->right);
            }
    
            if (temp->left) {
                if (temp->left == d_node) {
                    temp->left = NULL;
                    delete (d_node);
                    return;
                }
                else
                    q.push(temp->left);
            }
        }
    }
    
    //^CHECK
    nod* deletion(struct nod* root, int key) {
        if (root == NULL)
            return NULL;
    
        if (root->left == NULL && root->right == NULL) {
            if (root->key == key)
                return NULL;
            else
                return root;
        }
    
        queue<struct nod*> q;
        q.push(root);
    
        struct nod* temp;
        struct nod* key_node = NULL;
    
        while (!q.empty()) {
            temp = q.front();
            q.pop();
    
            if (temp->key == key)
                key_node = temp;
    
            if (temp->left)
                q.push(temp->left);
    
            if (temp->right)
                q.push(temp->right);
        }
    
        if (key_node != NULL) {
            int x = temp->key;
            deletDeepest(root, temp);
            key_node->key = x;
        }
        return root;
    }

} TREE_NODE;

#endif