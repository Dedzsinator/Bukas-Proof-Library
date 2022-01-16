#include <bits/stdc++.h>
#include "antibukas.h"
ifstream in("graph.txt");
using namespace std;

int result[10];
int ell[100][4], inc[100][100], n, boole[100][100], adj[100][100], m, cnt, path[100];

int main() {
    int matrix[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr[] = {10,20,30,40,50,60,70};
    int lim = 1;
    int scal = 5;
    
    ArrElemNtoK(arr,2, 2, result);
    ArrPrint(result,0,ArrSize(result));
    //ArrRange(lim,scal,1, result);
    //ArrPrint(result, lim,scal);

    in>>n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            in>>boole[i][j];
        }
    }
    
    cout<<endl<<endl<<endl;

    grIsEulerian(boole, n, 1, path, cnt);
        for(int i = 1; i <= cnt; i++) {
            cout << path[i] << " ";
        }

    return 0;
}