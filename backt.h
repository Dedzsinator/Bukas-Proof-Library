#ifndef BACKTRACK
#define BACKTRACK
#include <bits/stdc++.h>
using namespace std;
ifstream f("atjar.be");

//**  PERM/COMB/VAR  */

void Cinit(int k, int v[100]) {
    if(k>1) {
        v[k] = v[k-1];
    } else {
        v[k] = k-1;
    }
}

void Ckiir(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
}

bool Ckov(int k, int v[100], int n, int r) {
    if(v[k] < n-r+k) {
        v[k]++;
        return true;
    }
    return false;
}

bool Cellen(int k, int v[100]) {
    for(int i = 1; i < k; i++) {
        if(v[k] == v[i]) {
            return false;
        }
    }
    return true;
}

bool Vellen(int k, int v[100]) {
    for(int i = 1; i < k; i++) {
        if(v[k] == v[i]) {
            return false;
        }
    }
    return true;
}

bool Vkov(int k, int v[100], int n, int r) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

void Vkiir(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
}

bool Pellen(int k, int v[100]) {
    for(int i = 1; i < k; i++) {
        if(v[k] == v[i]) {
            return false;
        }
    }
    return true;
}

bool Pkov(int k, int v[100], int n) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

void Pkiir(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
}

void backComp(int n, int r) {
    int v[100], k;
    k = 1;
    Cinit(k, v);
    while(k > 0) {
        if(Ckov(k, v, n, r)) {
            if(Cellen(k, v)) {
                if(k == r) {
                    Ckiir(k, v);
                } else {
                    k++;
                    Cinit(k, v);
                }
            }
        } else {
            k--;
        }
    }
}

void backVar(int n, int r) {
    int v[100], k;
    k = 1;
    v[k] = 0;
    while(k > 0) {
        if(Vkov(k, v, n, r)) {
            if(Vellen(k, v)) {
                if(k == r) {
                    Vkiir(k, v);
                } else {
                    k++;
                    v[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}

void backPerm(int n) {
    int v[100], k;
    k = 1;
    v[k] = 0;
    while(k > 0) {
        if(Pkov(k, v, n)) {
            if(Pellen(k, v)) {
                if(k == n) {
                    Pkiir(k, v);
                } else {
                    k++;
                    v[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}

//**  PERM/COMB/VAR  */

//* DESCARTES */

void kiirDescartes(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
}

bool kovDescartes(int k, int v[100], int a[100]) {
    if(v[k] < a[k]) {
        v[k]++;
        return true;
    }
    return false;
}

void backDescartes(int n, int a[100]) {
    int k, v[100];
    k = 1;
    v[k] = 0;
    while(k > 0) {
        if(kovDescartes(k, v, a)) {
            if(k == n) {
                kiirDescartes(k, v);
            } else {
                k++;
                v[k] = 0;
            }
        } else {
            k--;
        }
    }
}

//* DESCARTES */

//** COINS */

void beolvasCoins(int a[100], int b[100], int n, int ossz) {
    for(int i = 1; i <= n; i++) {
        b[i] = ossz / a[i];
    }
}

void kiirCoins(int k, int v[100], int a[100], int b[100]) {
    cout<<"felhasznalt penzermek erteke: " << endl;
    for(int i = 1; i <= k; i++) {
        if(v[i] != 0) {
            cout<<a[i] << " ";
        }
    }
    cout<<"\n";
    cout<<"A kifizetes modja:" << endl;
    int j = 1;
    while(v[j] == 0) {
        j++;
    }
    if(j <= k) {
        cout<<a[j] << "*" << v[j] << " ";
    }
    for(int i = j + 1; i <= k; i++) {
        if(v[i] != 0) {
            cout << "+" << " " << a[i] << "*" << v[i] << " ";
        }
    }
    cout<<endl;
}

bool kovCoins(int k, int n, int v[100], int b[100]) {
    if((v[k] < b[k]) && (k <= n)) {
        v[k]++;
        return true;
    }
    return false;
}

bool ellenCoins(int k, int ossz, int v[100], int a[100]) {
    int sum = 0;
    for(int i = 1; i <= k; i++) {
        sum += v[i] * a[i];
    }
    if(sum > ossz) {
        return false;
    }
    return true;
}

bool megoldCoins(int k, int ossz, int v[100], int a[100]) {
    int sum = 0;
    for(int i = 1; i <= k; i++) {
        sum += v[i] * a[i];
    }
    return (sum == ossz);
}

void backCoins(int n, int ossz, int ermek[100]) {
    int v[100], k, b[100];
    beolvasCoins(ermek, b, n, ossz);
    k = 1;
    v[k] = -1;
    while(k != 0) {
        if(kovCoins(k, n, v, b)) {
            if(ellenCoins(k, ossz, v, ermek)) {
                if(megoldCoins(k, ossz, v, ermek)) {
                    kiirCoins(k, v, ermek, b);
                } else {
                    k++;
                    v[k] = -1;
                }
            }
        } else {
            k--;
        }
    }
}

//** COINS */

//** Nth QUEEN */
void kiirQueenSimp(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
}

bool ellenQueenSimp(int k, int v[100]) {
    for(int i = 1; i < k; i++) {
        if(v[i] == v[k]) {
            return false;
        }
        if(abs(v[i] - v[k]) == abs(i - k)) {
            return false;
        }
    }
    return true;
}

bool kovQueenSimp(int k, int n, int v[100]) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

void backQueenSimp(int n) {
    int v[100], k;
    k = 1;
    v[k] = 0;
    while(k > 0) {
        if(kovQueenSimp(k, n, v)) {
            if(ellenQueenSimp(k, v)) {
                if(k == n) {
                    kiirQueenSimp(k, v);
                } else {
                    k++;
                    v[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}

void kiirQueen(int n, int v[100]) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(v[j] == i) cout << "* ";
            else cout << "- ";
        }
        cout << endl<<endl;
    }
}

bool ellenQueen(int k, int v[100]) {
    for(int i = 1; i < k; i++) {
        if(v[i] == v[k]) return false;
        if(abs(v[i] - v[k]) == abs(i - k)) return false;
    }
    return true;
}

//& in main: backQueen(1, n, v); v = empty array
void backQueen(int k, int n, int v[100]) {
    for(int i = 1; i <= n; i++) {
        v[k] = i;
        if(ellenQueen(k, v)) {
            if(k == n) { 
                kiirQueen(n, v);
            } else {
                backQueen(k+1, n, v);
            }
        }
    }
}

//** Nth QUEEN */

//** DELEGACIONS */

void initDeleg(int k,int n, int r, int v[100]) {
    if(k <= r) {
        v[k] = 0;
    } else {
        v[k] = n;
    }
}

void kiirDeleg(int r, int k, int v[100]) {
    cout<<"Nok: ";
    for(int i = 1; i <= r; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
    cout<<"Ferfiak: ";
    for(int i = r+1; i <= k; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
}

bool kovDeleg(int k, int m, int v[100]) {
    if(v[k] < m) {
        v[k]++;
        return true;
    }
    return false;
}

bool ellenDeleg(int k,int n, int r, int v[100]) {
    if((k > 1) && (v[k-1] >= v[k])) {
        return false;
    } else {
        for(int i = 1; i < k; i++) {
            if(v[k] == v[i]) {
                return false;
            }
        }
    }

    if((k <= r) && (v[k] > n)) {
        return false;
    }

    return true;
}

void backDeleg(int m, int n, int p, int r) {
    int k, v[100];
    if((m < p) || (n < r) || (m-n<p-r)) {
        cout<<"Nem lehet!"<<endl;
        return;
    }
    k = 1;
    initDeleg(k, n, r, v);
    while(k > 0) {
        if(kovDeleg(k, m, v)) {
            if(ellenDeleg(k,n, p, v)) {
                if(k == p) {
                    kiirDeleg(r, k, v);
                } else {
                    k++;
                    initDeleg(k, n, r, v);
                }
            }
        } else {
            k--;
        }
    }
}

//** DELEGACIONS */

//** MAP COLORING */

void kiirMapColoring(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout<<v[i] << " ";
    }
    cout<<endl;
}

bool kovMapColoring(int k, int v[100]) {
    if(v[k] < 4) {
        v[k]++;
        return true;
    }
    return false;
}

bool ellenMapColoring(int k, int terkep[100][100], int v[100]) {
    for(int i = 1; i < k; i++) {
        if(terkep[i][k] && v[k] == v[i]) {
            return false;
        }
    }
    return true;
}

void backMapColoring(int n, int terkep[100][100]) {
    int k, v[100];
    v[1] = 1;
    k = 2;
    v[k] = 0;
    while(k > 0) {
        if(kovMapColoring(k, v)) {
            if(ellenMapColoring(k, terkep, v)) {
                if(k == n) {
                    kiirMapColoring(k, v);
                } else {
                    k++;
                    v[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}

//** MAP COLORING */

//* LIMBS */



//* LIMBS */

//** MISSIONARIES */

void atjarfMissionaries(int atjar[5][2]) {
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 2; j++) {
            f>>atjar[i][j];
        }
    }
}

void kiirMissionaries(int k, int v[100][5]) {
    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= 5; j++) {
            cout<< v[i][j] << " ";
        }
        cout<<endl;
    }
}

void initMissionaries(int k, int kb, int mb, int kj, int mj, int v[100][5]) {
    v[k][1] = kb;
    v[k][2] = mb;
    v[k][3] = kj;
    v[k][4] = mj;
    v[k][5] = 0;
}

bool kov(int k, int v[100][5]) {
    if(v[k][5] < 5) {
        v[k][5]++;
        return true;
    }
    return false;
}

bool ellenMissionaries(int k, int kb, int mb, int kj, int mj, int atjar[5][2], int v[100][5]) {
    kb = v[k][1];
    mb = v[k][2];
    kj = v[k][3];
    mj = v[k][4];
    if(k % 2 == 1) {
        kb -= atjar[v[k][5]][1];
        kj += atjar[v[k][5]][1];
        mb -= atjar[v[k][5]][2];
        mj += atjar[v[k][5]][2];
    } else {
        kb += atjar[v[k][5]][1];
        mb += atjar[v[k][5]][2];
        kj -= atjar[v[k][5]][1];
        mj -= atjar[v[k][5]][2];
    }

    if((kb < 0) || (kj < 0) || (mb < 0) || (mj < 0) || ((mb > 0) && (kb > mb)) || ((mj > 0) && (kj > mj))) {
        return false;
    }
    if(k > 1) {
        if(v[k][5] == v[k-1][5]) {
            return false;
        } else {
            for(int i = 1; i < k; i++) {
                if((v[i][1] == v[k][1]) && (v[i][2] == v[k][2]) && ((k-i) % 2 == 0)) {
                    return false;
                }
            }
        }
    }

    return true;
}

void backMissionaries(int kb, int mb) {
    int v[100][5], k, kj, mj, atjar[5][2];
    atjarfMissionaries(atjar);
    k = 1;
    initMissionaries(k, kb, mb, kj, mj, v);
    while(k > 0) {
        if(kov(k, v)) {
            if(ellenMissionaries(k, kb, mb, kj, mj, atjar, v)) {
                k++;
                initMissionaries(k, kb, mb, kj, mj, v);
                if((kb == 0 && mb == 0)) {
                    kiirMissionaries(k, v);
                    return;
                }
            }
        } else {
            k--;
        }
    }
    cout<<"Nincs megoldas"<<endl;
}

//** MISSIONARIES */

//** EULER/HAMILTON */
void kiirEuler(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout << v[i] << " ";
    }
    cout<<endl;
}

bool kovEuler(int k, int n, int v[100]) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

bool ellenEuler(int k, int v[100]) {
    if(k > 1) {

    }
}

void backEuler(int boole[100][100]) {
    int v[100],n, k;
    k = 1;
    v[k] = 0;
    while(k > 0) {
        if(kovEuler(k, n, v)) {
            if(ellenEuler(k, v)) {
                if(k==n) {
                    kiirEuler(k, v);
                } else {
                    k++;
                    v[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}
//!!!EULER NOT WORKING!!!


void kiirHam(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout << v[i] << " ";
    }
    cout<<endl;
}

bool kovHam(int k, int n, int v[100]) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

bool ellenHam(int k, int v[100], int boole[100][100]) {
    for(int i = 1; i < k; i++) {
        if(v[k] == v[i] || boole[v[i]][v[i+1]] != 1) {
            return false;
        }
    }
    return true;
}

void backHam(int boole[100][100]) {
    int v[100],n, k;
    k = 1;
    v[k] = 0;
    while(k > 0) {
        if(kovHam(k, n, v)) {
            if(ellenHam(k, v, boole)) {
                if(k==n) {
                    kiirHam(k, v);
                } else {
                    k++;
                    v[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}


//** EULER/HAMILTON */

//** CAMELS */

void kiirCamels(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout<<v[i];
    }
    cout<<endl;
}

bool kovCamels(int k, int n, int v[100]) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

bool ellenCamels(int k, int v[100], int tv[100]) {
    for(int i = 1; i < k; i++) {
        if(v[k] == v[i]) {
            return false;
        }
    }
    if(k > 1 && (v[k-1] == tv[v[k]])) {
        return false;
    }
    return true;
}

bool solvedCamels(int k, int n,int v[100], int tv[100]) {
    if(k == n) {
        return true;
    }

    for(int i = 2; i <= k; i++) {
        if(v[i-1] == tv[v[i]]) {
            return false;
        }
    }

    return false;
}

void ert_tartCamels(int k, int tv[100], int v[100]) {
    for(int i = 2; i <= k; i++) {
        tv[v[i]] += v[i-1];
    }
}

void backCamels(int n) {
    int k, v[100], tv[100];
    k = 1;
    v[k] = 0;
    while(k > 0) {
        if(kovCamels(k, n, v)) {
            if(ellenCamels(k, v, tv)) {
                if(solvedCamels(k, n, v, tv)) {
                    kiirCamels(k, v);
                    ert_tartCamels(k, tv, v);
                } else {
                    k++;
                    v[k] = 0;
                }
            }
        } else {
            k--;
        }
    }
}

//** CAMELS */

//* ARRAY PARTITIONS/SUB-ARRAYS */

void kiirArrPart(int k, int arr[100], int v[100]) {
    for(int i = 1; i <= k; i++) {
        if(v[i] == 1) {
            cout << arr[i] << " ";
        }
    }
    cout<<endl;
}

bool kovArrPart(int k, int v[100]) {
    if(v[k] < 1) {
        v[k]++;
        return true;
    }
    return false;
}

void backArrPart(int n, int arr[100]) {
    int v[100], k;
    k = 1;
    v[k] = -1;
    while(k > 0) {
        if(kovArrPart(k, v)) {
            if(k == n) {
                kiirArrPart(k, arr, v);
            } else {
                k++;
                v[k] = -1;
            }
        } else {
            k--;
        }
    }
}

bool ellenSubArr(int k, int v[100]) {
    for(int i = 1; i < k; i++) {
        if(v[i]==v[k])
            return false;

        if(v[i]>v[i+1])
            return false;
        }
    return true;
}

void kiirSubArr(int k, int v[100]) {
    for(int i = 1; i<=k; i++)
        cout << v[i] << " ";
    cout << endl;
}

bool kovSubArr(int k, int n, int v[100]) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

void backSubArr(int n) {
    int v[100], k;
    k = 1;
    v[k] = 0;
    while(k>0) {
        if(kovSubArr(k, n, v)) {
            if(ellenSubArr(k, v)) {
                if(k<=n) {
                    kiirSubArr(k, v);
                    k++;
                    v[k]=0;
                }
            }
        }
        else
            k--;
    }
}

//* ARRAY PARTITIONS/SUB-ARRAYS */

//* SZAMFELBONTAS */

bool kovNums(int k, int n, int v[100]) {
    if(v[k] < n) {
        v[k]++;
        return true;
    }
    return false;
}

bool ellenNums(int k, int v[100]) {
    for(int i = 1; i < k; i++) {
        if(v[k] == v[i]) {
            return false;
        }
    }
    return true;
}

void kiirNums(int k, int v[100]) {
    for(int i = 1; i <= k; i++) {
        cout << i << " " <<  v[i] << " ";
    }
    cout << endl;
}



//* SZAMFELBONTAS */

//* RESZGRAF */



//* RESZGRAF */

//* MINI SUM */



//* MINI SUM */

//* PARANTHESIS */



//* PARANTHESIS */

#endif