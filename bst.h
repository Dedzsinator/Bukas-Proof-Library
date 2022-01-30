#ifndef BST
#define BST
#include <bits/stdc++.h>
using namespace std;
ifstream fin("bst.in");

int compUtil(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

typedef struct f {
    int adat;
    struct f *bal, *jobb;

    //!!! Template for main:
    /*
    BST* bst = new BST;
    bst->root = NULL;
    */

} bst_node;

typedef struct binary_search_tree {
    bst_node *root;

    int BTCntNodes(bst_node* root) {
    if (root == NULL)
        return 0;
    return BTCntNodes(root->bal) + BTCntNodes(root->jobb) + 1;
}

    void BSTStoreInord(bst_node* root, int inorder[], int* index_ptr) {
        if (root == NULL)
            return;
    
        BSTStoreInord(root->bal, inorder, index_ptr);
    
        inorder[*index_ptr] = root->adat;
        (*index_ptr)++;
    
        BSTStoreInord(root->jobb, inorder, index_ptr);
    }

    bst_node* minVUtil(bst_node* root) {
        bst_node* curr = root;
        while (curr && curr->bal != NULL)
            curr = curr->bal;

        return curr;
    }

    bst_node* BSTUJ(int x) {
        bst_node *uj = new bst_node;
        uj->adat = x;
        uj->bal = NULL;
        uj->jobb = NULL;
        return uj;
    }

    bst_node* lvlOrdUtil(bst_node *root, int x) {
        if(root==NULL){   
            root = BSTUJ(x);
            return root;
        }

        if(x <= root->adat)
        root->bal = lvlOrdUtil(root->bal, x);
        else
        root->jobb = lvlOrdUtil(root->jobb, x);
        return root;
    }

    bst_node* BSTInsert(bst_node* root, int x) {
        if (root == NULL)
        return BSTUJ(x);

        if (x < root->adat)
            root->bal = BSTInsert(root->bal, x);
        else if (x > root->adat)
            root->jobb = BSTInsert(root->jobb, x);

        return root;
    }

    bst_node* BSTSearch(bst_node* root, int x) {
        if (root == NULL || root->adat == x)
            return root;

        if (root->adat < x)
            return BSTSearch(root->jobb, x);

        return BSTSearch(root->bal, x);
    }

    bst_node* BSTDelete(bst_node* root, int x) {
        if(root == NULL)
            return root;

        if(x < root->adat)
            root->bal = BSTDelete(root->bal, x);

        else if(x > root->adat)
            root->jobb = BSTDelete(root->jobb, x);

        else {
            if (root->bal == NULL) {
                bst_node* temp = root->jobb;
                free(root);
                return temp;
            }
            else if (root->jobb == NULL) {
                bst_node* temp = root->bal;
                free(root);
                return temp;
            }

            bst_node* temp = minVUtil(root->bal);
            root->adat = temp->adat;
            root->jobb = BSTDelete(root->jobb, temp->adat);
        }
        return root;
}

    int BSTMinVal(bst_node* root) {
        bst_node* curr = root;
        while (curr->bal != NULL)
            curr = curr->bal;

        return(curr->adat);
    }

    //& pl. int c = 0; BSTKthLargest(root, k, c);
    void BSTKthLargest(bst_node *root, int k, int &c) {
        if (root == NULL || c >= k)
            return;

        BSTKthLargest(root->jobb, k, c);
        c++;
        if (c == k) {
            cout << root->adat << endl;
            return;
        }
        BSTKthLargest(root->bal, k, c);
    }

    int KSmallestUsingMorris(bst_node *root, int k) {
        int count = 0;

        int ksmall = INT_MIN;
        bst_node *curr = root;

        while (curr != NULL) {
            if (curr->bal == NULL) {
                count++;

                if (count==k)
                    ksmall = curr->adat;

                curr = curr->jobb;
            } else {
                bst_node *pre = curr->bal;
                while (pre->jobb != NULL && pre->jobb != curr)
                    pre = pre->jobb;

                if (pre->jobb==NULL) {
                    pre->jobb = curr;
                    curr = curr->bal;
                }

                else {
                    pre->jobb = NULL;

                    count++;
                    if (count==k)
                        ksmall = curr->adat;

                    curr = curr->jobb;
                }
            }
        }
        return ksmall;
    }

    int BSTFLessThanN(bst_node* root, int N) {
        if (root == NULL)
            return -1;

        if (root->adat == N)
            return N;

        else if (root->adat < N) {
            int k = BSTFLessThanN(root->jobb, N);
            if (k == -1)
                return root->adat;
            else
                return k;
        }

        else if (root->adat > N)
            return BSTFLessThanN(root->bal, N);   
    }

    int BSTCntNodes(bst_node *root) {
        bst_node *curr, *pre;

        int count = 0;
        if (root == NULL)
            return count;

        curr = root;
        while (curr != NULL) {
            if (curr->bal == NULL) {
                count++;

                curr = curr->jobb;
            }
            else {
                pre = curr->bal;

                while (pre->jobb != NULL &&
                        pre->jobb != curr)
                    pre = pre->jobb;

                if(pre->jobb == NULL) {
                    pre->jobb = curr;
                    curr = curr->bal;
                }

                else {
                    pre->jobb = NULL;

                    count++;
                    curr = curr->jobb;
                }
            }
        }

        return count;
    }

    int BSTFMedian(bst_node *root) {
        if (root == NULL)
        return 0;

        int count = BSTCntNodes(root);
        int currCount = 0;
        bst_node *curr = root, *pre, *prev;
        while (curr != NULL) {
            if (curr->bal == NULL) {
                currCount++;

                if (count % 2 != 0 && currCount == (count+1)/2)
                    return prev->adat;

                else if (count % 2 == 0 && currCount == (count/2)+1)
                    return (prev->adat + curr->adat)/2;

                prev = curr;

                curr = curr->jobb;
            } else {
                pre = curr->bal;
                while (pre->jobb != NULL && pre->jobb != curr)
                    pre = pre->jobb;

                if (pre->jobb == NULL) {
                    pre->jobb = curr;
                    curr = curr->bal;
                } else {
                    pre->jobb = NULL;
                    prev = pre;

                    currCount++;
                    if (count % 2 != 0 && currCount == (count+1)/2 )
                        return curr->adat;

                    else if (count%2==0 && currCount == (count/2)+1)
                        return (prev->adat+curr->adat)/2;

                    prev = curr;
                    curr = curr->jobb;
                }
            }
        }
    }

    void RangeTraversal(bst_node* root, int n1, int n2){
        if (!root)
            return;

        bst_node* curr = root;

        while (curr) {
            if (curr->bal == NULL) {
                if (curr->adat <= n2 &&
                    curr->adat >= n1)
                {
                    cout << curr->adat << " ";
                }

                curr = curr->jobb;
            }

            else {
                bst_node* pre = curr->bal;
                while (pre->jobb != NULL &&
                        pre->jobb != curr)
                            pre = pre->jobb;

                if (pre->jobb == NULL)
                {
                    pre->jobb = curr;
                    curr = curr->bal;
                }

                else {
                    pre->jobb = NULL;
                    if (curr->adat <= n2 &&
                        curr->adat >= n1)
                    {
                        cout << curr->adat << " ";
                    }

                    curr = curr->jobb;
                }
            }
        }
    }

    //& pl.int preIndex = 0; BSTPreorderIn(pre, &preIndex, 0, size-1, size);
    bst_node* BSTPreorderIn(int pre[], int* preIndex, int low, int high, int size) {
        if (*preIndex >= size || low > high)
            return NULL;

        bst_node* root = BSTUJ(pre[*preIndex]);
        *preIndex = *preIndex + 1;

        if (low == high)
            return root;

        int i;
        for (i = low; i <= high; ++i)
            if (pre[i] > root->adat)
                break;

        root->bal = BSTPreorderIn(pre, preIndex, *preIndex, i - 1, size);
        root->jobb = BSTPreorderIn(pre, preIndex, i, high, size);

        return root;
    }

    //& pl. BSTSortedArrIn(arr, 0, n-1);
    bst_node* BSTSortedArrIn(int arr[], int start, int end) {
        if (start > end)
            return NULL;

        int mid = (start + end)/2;
        bst_node *root = BSTUJ(arr[mid]);

        root->bal =  BSTSortedArrIn(arr, start, mid-1);
        root->jobb = BSTSortedArrIn(arr, mid+1, end);

        return root;
    }

    bst_node* BSTLvlOrdIn(int arr[], int n) {
        if(n==0)return NULL;
        bst_node *root =NULL;
    
        for(int i=0;i<n;i++)
        root = lvlOrdUtil(root , arr[i]);
        
        return root;
    }

    void BSTMorrisTraversal(bst_node* root) {
        bst_node *curr, *pre;

        if (root == NULL)
            return;

        curr = root;
        while (curr != NULL) {
            if (curr->bal == NULL) {
                printf("%d ", curr->adat);
                curr = curr->jobb;

            } else {
                pre = curr->bal;
                while (pre->jobb != NULL && pre->jobb != curr)
                    pre = pre->jobb;

                if (pre->jobb == NULL) {
                    pre->jobb = curr;
                    curr = curr->bal;

                } else {
                    pre->jobb = NULL;
                    printf("%d ", curr->adat);
                    curr = curr->jobb;
                }
            }
        }
    }

    void BSTarrToBt(int* arr, bst_node* root, int* index_ptr) {
        if (root == NULL)
            return;
    
        BSTarrToBt(arr, root->bal, index_ptr);
        root->adat = arr[*index_ptr];
        (*index_ptr)++;
    
        BSTarrToBt(arr, root->jobb, index_ptr);
    }

    void binaryTreeToBST(bst_node* root) {
        if (root == NULL)
            return;
    
        int n = BTCntNodes(root);
    
        int* arr = new int[n];
        int i = 0;
        BSTStoreInord(root, arr, &i);
    
        qsort(arr, n, sizeof(arr[0]), compUtil);
    
        i = 0;
        BSTarrToBt(arr, root, &i);
    
        delete[] arr;
    }

    //TODO: READINS maybe Prints, (Construct all possible BSTs for keys 1 to N)

    //!!!NEED TO CHECK THESE FOR BST-s!!!

    bool BSTIsLeaf(bst_node *root, int x) {
        if(root == NULL)
            return false;

        if(root->bal == NULL && root->jobb == NULL && root->adat == x)
            return true;
        
        return (BSTIsLeaf(root->bal, x) || BSTIsLeaf(root->jobb, x));
    }

    void BSTHasChild(bst_node *root, int x) {
        if(root == NULL)
            return;

        if(root->adat == x) {
            if(root->bal == NULL && root->jobb == NULL)
                cout<<"Nincsenek fiai"<<endl;
            else
                cout << "A fiai: " << root->bal->adat << " " << root->jobb->adat << endl;
        }

        BSTHasChild(root->bal, x);
        BSTHasChild(root->jobb, x);
    }

    void BSTInorder(bst_node *root) {
        if(root->bal != NULL) {
            BSTInorder(root->bal);
        }
        //cout << 0 << " ";
        cout<<root->adat<<" ";
        if(root->jobb != NULL) {
            BSTInorder(root->jobb);
        }
    }

    void BSTPreorder(bst_node *root) {
        //cout << 0 << " ";
        cout<<root->adat<<" ";
        if(root->bal != NULL) {
            BSTPreorder(root->bal);
        }
        if(root->jobb != NULL) {
            BSTPreorder(root->jobb);
        }
    }

    void BSTPostorder(bst_node *root) {
        if(root->bal != NULL) {
            BSTPostorder(root->bal);
        }
        if(root->jobb != NULL) {
            BSTPostorder(root->jobb);
        }
        //cout << 0 << " ";
        cout<<root->adat<<" ";
    }

    void BSTLvlOrd(bst_node *root) {
        if(root == NULL) return;
        queue<bst_node*> Q;
        Q.push(root);  
        while(!Q.empty()) {
            bst_node* current = Q.front();
            Q.pop();
            cout<<current->adat<<" ";
            if(current->bal != NULL) Q.push(current->bal);
            if(current->jobb != NULL) Q.push(current->jobb);
        }
    }

    //& pl. BTRootToLeaf(root, path(array, declared before), length of the path array);
    void BSTRootToLeaf(bst_node* root, int path[], int pathLen) {
        if (root==NULL)
        return;

        path[pathLen] = root->adat;
        pathLen++;
        
        if (root->bal==NULL && root->jobb==NULL) {
            for(int i = 0; i < pathLen; i++) {
                cout << path[i] << " ";
            }
            cout<<endl;

        } else {
            BSTRootToLeaf(root->bal, path, pathLen);
            BSTRootToLeaf(root->jobb, path, pathLen);
        }
    }
    //!!!NEED TO CHECK THESE FOR BST-s!!!

}BST;

#endif