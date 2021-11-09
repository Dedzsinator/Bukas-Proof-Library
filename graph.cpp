#include <iostream>
#include <fstream>
#include "graph-test.h"
using namespace std;
ifstream in("graph.txt");
int ell[100][4], inc[100][100], n, boole[100][100], adj[100][100], m;

int main() {
    in>>n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            in>>boole[i][j];
        }
    }
    
    if(grIsEulerian(boole, n)) {
        cout<<"YES";
    } else {
        cout<<"NO";
    }
    return 0;
}