#include <bits/stdc++.h>
#include "antibukas.h"
#define MAX_MATRIX_SIZE 1000
using namespace std;

int result[10];

int main() {
    int matrix[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr[] = {10,20,30,40,50,60,70};
    int lim = 1;
    int scal = 5;
    
    ArrElemNtoK(arr,2, 2, result);
    printArr(result,0,ArrSize(result));
    //ArrRange(lim,scal,1, result);
    //printArr(result, lim,scal);

    return 0;
}