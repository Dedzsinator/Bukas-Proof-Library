#include <bits/stdc++.h>
#include "antibukas.h"
#define MAX_MATRIX_SIZE 1000
using namespace std;

int main() {
    int n,m;
    cin>>n>>m;
    char str[n][m];
    for (int i = 0; i < n; i++) {
        cout << " ";
        cin >> str[i];
    }
    sortCharMat(str, n);

    for (int i = 0; i < n; i++) {
        cout << " ";
        cout << str[i] << "\n";
    }
    return 0;
}