#ifndef BT
#define BT
#include <bits/stdc++.h>
using namespace std;
ifstream fin("bt.in");

int maxUtil(int inorder[100], int start, int end) {
    int i, maxi = inorder[start], maxind = start;
    for(i = start + 1; i <= end; i++) {
        if(inorder[i] > maxi) {
            maxi = inorder[i];
            maxind = i;
        }
    }
    return maxind;
}

int fIndUtil(char str[100], int si,int ei) {
    if (si > ei)
        return -1;

    stack<char> s;

    for (int i = si; i <= ei; i++) {
        if (str[i] == '(')
            s.push(str[i]);

        else if (str[i] == ')') {
            if (s.top() == '(') {
                s.pop();

                if (s.empty())
                    return i;
            }
        }
    }

    return -1;
}

typedef struct f {
    int adat;
    struct f *bal, *jobb;

    //!!! Template for main:
    /*
    BT* bt = new BT;
    bt->root = NULL;
    */

} bt_node;

typedef struct binary_tree {
    bt_node *root;

    //& pl. BTMaxSum(gy, INT_MIN(valtozo));
    int BTMaxSum(bt_node* gy, int &res) {
        if (gy == NULL)
            return 0;

        int l = BTMaxSum(gy->bal,res);
        int r = BTMaxSum(gy->jobb,res);

        int max_single = max(max(l, r) + gy->adat, gy->adat);

        int max_top = max(max_single, l + r + gy->adat);

        res = max(res, max_top);
        return max_single;
    }

    void BTDestroy(bt_node* gy) {
        if (gy == NULL)
            return;
        BTDestroy(gy->bal);
        BTDestroy(gy->jobb);
        delete gy;
    }

    bt_node* BTUJ(int x) {
        bt_node *uj = new bt_node;
        uj->adat = x;
        uj->bal = NULL;
        uj->jobb = NULL;
        return uj;
    }

    bt_node* BTInsert(bt_node* gy, int x) {
        if (gy == NULL) {
            gy = BTUJ(x);
            return gy;
        }
        queue<bt_node*> q;
        q.push(gy);

        while (!q.empty()) {
            bt_node* temp = q.front();
            q.pop();

            if (temp->bal != NULL)
                q.push(temp->bal);
            else {
                temp->bal = BTUJ(x);
                return gy;
            }

            if (temp->jobb != NULL)
                q.push(temp->jobb);
            else {
                temp->jobb = BTUJ(x);
                return gy;
            }
        }
    }

    int BTFindMax(bt_node* gy) {
        if (gy == NULL)
            return INT_MIN;

        int res = gy->adat;
        int lres = BTFindMax(gy->bal);
        int rres = BTFindMax(gy->jobb);
        if (lres > res)
            res = lres;
        if (rres > res)
            res = rres;
        
        return res;
    }

    int BTFindMin(bt_node* gy) {
        if (gy == NULL)
            return INT_MAX;

        int res = gy->adat;
        int lres = BTFindMin(gy->bal);
        int rres = BTFindMin(gy->jobb);
        if (lres < res)
            res = lres;
        if (rres < res)
            res = rres;
        
        return res;
    }

    //^CHECK
    int BTHeight(bt_node* gy) {
        if (gy == NULL)
            return -1;
        else {
            int lDepth = BTHeight(gy->bal);
            int rDepth = BTHeight(gy->jobb);

            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
    }

    //^CHECK
    bool BTIsBal(bt_node *gy) {
        int lh;
        int rh;

        if (gy == NULL)
            return 1;

        lh = BTHeight(gy->bal);
        rh = BTHeight(gy->jobb);

        if (abs(lh - rh) <= 1 && BTIsBal(gy->bal) && BTIsBal(gy->jobb))
            return 1;

        return 0;
    }

    //^CHECK
    int BTMinHeight(bt_node *gy) {
        if (gy == NULL)
            return 0;

        if (gy->bal == NULL && gy->jobb == NULL)
        return 1;

        int l = INT_MAX, r = INT_MAX;

        if (gy->bal)
        l = BTMinHeight(gy->bal);

        if (gy->jobb)
        r =  BTMinHeight(gy->jobb);

        return min(l , r) + 1;
    }

    //^CHECK
    void BTInvert(bt_node* gy)  { 
        if (gy == NULL) 
            return; 
        else { 
            bt_node* temp; 
            BTInvert(gy->bal); 
            BTInvert(gy->jobb); 
        
            temp = gy->bal; 
            gy->bal = gy->jobb; 
            gy->jobb = temp; 
        } 
    } 

    int BTSearch(bt_node *gy, int x) {
        if (gy == NULL)
            return false;

        if (gy->adat == x)
            return true;

        bool res1 = BTSearch(gy->bal, x);
        if(res1) return true;

        bool res2 = BTSearch(gy->jobb, x);

        return res2;
    }
    //!!! SZEKVENCIAL !!!
    void BTSecvIn(bt_node*& root, int x) {
        int x1,x2;
        bt_node *cs = new bt_node;
        cs->bal = cs->jobb = NULL;
        cs->adat = x;
        if(x != 0) {
            root = cs;
            fin>>x1;
            fin>>x2;
            BTSecvIn(root->bal, x1);
            BTSecvIn(root->jobb, x2);
        }
    }

    //& pl bt_node* gy = BTParanthesisIn(str, 0, strlen(str) - 1);
    bt_node* BTParanthesisIn(char str[100], int si, int ei) {
        if (si > ei)
            return NULL;

        bt_node* gy = BTUJ(str[si] - '0');
        int index = -1;

        if (si + 1 <= ei && str[si + 1] == '(')
            index = fIndUtil(str, si + 1, ei);

        if (index != -1) {
            gy->bal = BTParanthesisIn(str, si + 2, index - 1);
            gy->jobb = BTParanthesisIn(str, index + 2, ei - 1);
        }
        return gy;
    }

    bt_node* BTLvlOrdIn(int lvlarr[100], bt_node* gy, int i, int n) {
        if (i < n) {
            bt_node* temp = BTUJ(lvlarr[i]);
            gy = temp;

            gy->bal = BTLvlOrdIn(lvlarr, gy->bal, 2 * i + 1, n);
            gy->jobb = BTLvlOrdIn(lvlarr, gy->jobb, 2 * i + 2, n);
        }
        return gy;
    }

    //& pl. bt_node* gy = BTInorderIn(inorder, 0, len-1);
    bt_node* BTInorderIn(int inorder[100], int start, int end) {
        if (start > end)
            return NULL;

        int i = maxUtil(inorder, start, end);

        bt_node* gy = BTUJ(inorder[i]);

        if (start == end)
            return gy;

        gy->bal = BTInorderIn(inorder, start, i-1);
        gy->jobb = BTInorderIn(inorder, i+1, end);

        return gy;
    }

    //TODO: ADD DYNAMIC SIZE
    //& pl. bt_node* gy = BTAncestorMatIn(mat);
    bt_node* BTAncestorMatIn(int mat[][100]) {
        int parent[100] = {0};

        bt_node* gy = NULL;
        multimap<int,int> mm;

        for (int i = 0; i < 100; i++) {
            int sum = 0;
            for (int j = 0; j < 100; j++)
                sum += mat[i][j];

            mm.insert(pair<int,int>(sum, i));
        }

        bt_node* node[100];

        for (auto it = mm.begin(); it != mm.end(); ++it) {
            node[it->second] = BTUJ(it->second);

            gy = node[it->second];

            if (it->first != 0) {
                for (int i = 0; i < 100; i++) {
                    if (!parent[i] && mat[it->second][i]) {
                        if (!node[it->second]->bal)
                            node[it->second]->bal = node[i];
                        else
                            node[it->second]->jobb = node[i];

                        parent[i] = 1;
                    }
                }
            }
        }
        return gy;
    }

    //& pl.int start = 0; bt_node* gy = BTPreorderIn(preorder, pre, start, len);
    bt_node* BTPreorderIn(int preorder[], bool pre[],int *start, int len) {
        int index = *start;

        if(index == len)
            return NULL;

        bt_node* temp = BTUJ(preorder[index]);
        (*start)++;

        if(pre[index] == false) {
            temp->bal = BTPreorderIn(preorder, pre, start, len);
            temp->jobb = BTPreorderIn(preorder, pre, start, len);
        }

        return temp;
    }

    //& pl. bt_node* gy = BTParentArrIn(parent, n);
    bt_node* BTParentArrIn(int parent[], int n) {
        map<int, bt_node*> m;
        bt_node* gy, *temp;
        int i;
        for (i = 0; i < n; i++) {
            if (m.find(i) == m.end()) {
                temp = BTUJ(i);
                m[i] = temp;
            }
            if (parent[i] == -1)
                gy = m[i];
            else if (m.find(parent[i]) == m.end()) {
                temp = BTUJ(parent[i]);
                temp->bal = m[i];
                m[parent[i]] = temp;

            } else {
                if (!m[parent[i]]->bal)
                    m[parent[i]]->bal = m[i];
                else
                    m[parent[i]]->jobb = m[i];
            }
        }
        return gy;
    }

    bool BTIsLeaf(bt_node *gy, int x) {
        if(gy == NULL)
            return false;

        if(gy->bal == NULL && gy->jobb == NULL && gy->adat == x)
            return true;
        
        return (BTIsLeaf(gy->bal, x) || BTIsLeaf(gy->jobb, x));
    }

    void BTHasChild(bt_node *gy, int x) {
        if(gy == NULL)
            return;

        if(gy->adat == x) {
            if(gy->bal == NULL && gy->jobb == NULL)
                cout<<"Nincsenek fiai"<<endl;
            else
                cout << "A fiai: " << gy->bal->adat << " " << gy->jobb->adat << endl;
        }

        BTHasChild(gy->bal, x);
        BTHasChild(gy->jobb, x);
    }

    void BTDelete(bt_node *&gy, int x) {
        if(gy == NULL)
            return;

        if(gy->adat == x) {
            if(gy->bal == NULL && gy->jobb == NULL) {
                delete gy;
                gy = NULL;
            }
            else if(gy->bal == NULL) {
                bt_node *cs = gy;
                gy = gy->jobb;
                delete cs;
            }
            else if(gy->jobb == NULL) {
                bt_node *cs = gy;
                gy = gy->bal;
                delete cs;
            }
            else {
                bt_node *cs = gy->jobb;
                while(cs->bal != NULL)
                    cs = cs->bal;
                gy->adat = cs->adat;
                BTDelete(gy->jobb, cs->adat);
            }
        }
        else {
            BTDelete(gy->bal, x);
            BTDelete(gy->jobb, x);
        }
    }

    void BTInorder(bt_node *gy) {
        if(gy->bal != NULL) {
            BTInorder(gy->bal);
        }
        //cout << 0 << " ";
        cout<<gy->adat<<" ";
        if(gy->jobb != NULL) {
            BTInorder(gy->jobb);
        }
    }

    void BTPreorder(bt_node *gy) {
        //cout << 0 << " ";
        cout<<gy->adat<<" ";
        if(gy->bal != NULL) {
            BTPreorder(gy->bal);
        }
        if(gy->jobb != NULL) {
            BTPreorder(gy->jobb);
        }
    }

    void BTPostorder(bt_node *gy) {
        if(gy->bal != NULL) {
            BTPostorder(gy->bal);
        }
        if(gy->jobb != NULL) {
            BTPostorder(gy->jobb);
        }
        //cout << 0 << " ";
        cout<<gy->adat<<" ";
    }

    void BTLvlOrd(bt_node *root) {
        if(root == NULL) return;
        queue<bt_node*> Q;
        Q.push(root);  
        while(!Q.empty()) {
            bt_node* current = Q.front();
            Q.pop();
            cout<<current->adat<<" ";
            if(current->bal != NULL) Q.push(current->bal);
            if(current->jobb != NULL) Q.push(current->jobb);
        }
    }

    //& pl. BTRootToLeaf(gy, path(array, declared before), length of the path array);
    void BTRootToLeaf(bt_node* gy, int path[], int pathLen) {
        if (gy==NULL)
        return;

        path[pathLen] = gy->adat;
        pathLen++;
        
        if (gy->bal==NULL && gy->jobb==NULL) {
            for(int i = 0; i < pathLen; i++) {
                cout << path[i] << " ";
            }
            cout<<endl;

        } else {
            BTRootToLeaf(gy->bal, path, pathLen);
            BTRootToLeaf(gy->jobb, path, pathLen);
        }
    }
}BT;

#endif