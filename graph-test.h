#ifndef GRAFOK
#define GRAFOK
#define INF 99999
#include <bits/stdc++.h>
using namespace std;

template<typename T, int size>
    int ArrSize(T(&)[size]){
        return size;
    }

template <typename T>
    void univ_swap(T& a, T& b) {
        T c(a); a = b; b = c;
    }

//~ Matrixok atalakitasai

void boolToIncid(int boole[100][100], int n, int inc[100][100]) {
    int siz = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(boole[i][j] == 1) {
                siz++;
            }
        }
    }
    siz = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(boole[i][j] == 1) {
                siz++;
                inc[i][siz] = 1;
                inc[j][siz] = 1;
            }
        }
    }
}

//!(main: m = 0)
void boolToEll(int boole[100][100], int n, int ell[100][4], int &m) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(boole[i][j] != 0) {
                m++;
                ell[m][1] = j;
                ell[m][2] = i;
            }
        }
    }
}

void boolToAdj(int boole[100][100], int n, int adj[100][100]) {
    int k;
    for(int i = 1; i <= n; i++) {
        k = 0;
        for(int j = 1; j <= n; j++) {
            if(boole[i][j] == 1) {
                k++;
                adj[i][k] = j;
            }
            adj[i][0] = k;
        }
    }
}

//!VISSZATERITI A CSOMOPONTOK SZAMAT A NUM-ON KERESZTUL, (mainben legyen 0)
void ellToAdj(int ell[100][3], int n, int adj[100][100], int &num) {
    int t[100];
    for(int i = 1; i <= 2*n; i++) {
        t[i] = false;
    }
    for(int i = 1; i <= n + 1; i++) {
        adj[i][0] = 0;
    }
    for(int i = 1; i <= n; i++) {
        t[ell[i][1]] = true;
        t[ell[i][2]] = true;
        adj[ell[i][1]][0]++;
        adj[ell[i][2]][0]++;
        adj[ell[i][1]][adj[ell[i][1]][0]] = ell[i][2];
        adj[ell[i][2]][adj[ell[i][2]][0]] = ell[i][1];
    }
    while(t[num+1] == true) {
        num++;
    }
}

void incidToEll(int inc[100][100],int n,int m, int ell[100][3]) {
    bool ok;
    for(int i = 1; i <= m; i++) {
        ok = true;
        for(int j = 1; i < n; j++) {
            if(inc[j][i] == 1) {
                if(ok) {
                    ell[i][1] = j;
                    ok = !ok;
                } else {
                    ell[i][2] = j;
                }
            }
        }
    }
}

void adjToBool(int adj[100][100], int n, int boole[100][100]) {
    //Le van nullazva a boole
    for(int i = 1; i <= adj[i][0]; i++) {
        for(int j = 1; j <= adj[i][0]; j++) {
            boole[i][adj[i][j]] = 1;
        }
    }
}

void ellToBool(int ell[100][3], int n, int boole[100][100]) {
    //Le van nullazva a boole
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 2; j++) {
            boole[ell[i][1]][ell[i][2]] = 1;
            boole[ell[i][2]][ell[i][1]] = 1;
        }
    }
}

void EllToIncid(int ell[100][3], int m, int &n, int inc[100][100]) {
    n = 0;
    int maxi = 1;
    int cnt = 0;
    for(int i = 1; i <= m; i++) {
        maxi = ell[i][2];
        if(maxi > n) {
            n = maxi;
        }
        cnt++;
        inc[ell[i][1]][cnt] = 1;
        inc[ell[i][2]][cnt] = 1;
    }
}

//^CHECK
void incidToBool(int inc[100][100], int n, int m, int boole[100][100]) {
}

//^CHECK
void incidToAdj(int inc[100][100], int n, int m, int adj[100][100]) {
    
}

//^CHECK
void adjToIncid(int adj[100][100], int n, int inc[100][100]) {

}

void adjToEll(int adj[100][100], int n, int ell[100][3]) {
    int k = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(adj[i][j] != 0) {
                ell[k][1] = i;
                ell[k][2] = adj[i][j];
                k++;
            }
        }
    }
}

//~ Bejarasok

void BFS(int boole[30][30],int n, int cs) {
    int first, last, pont;
    int queue[50];
    bool arr[50];

    for(int i = 1; i <= n; i++) {
        arr[i] = false;
    }
    arr[cs] = true;
    first = last = 1;
    queue[first] = cs;
    cout<<cs << " ";
    while(first <= last) {
        pont = queue[first];
        first++;

        for(int i = 1; i <= n; i++) {
            if(!arr[i] && boole[pont][i] != 0) {
                last++;
                queue[last] = i;
                arr[i] = true;
                cout<<i << " ";
            }
        }
    }
}

void DFS(int boole[30][30],int n, int cs) {
    int stack[30] = {0};
    int visited[30] = {false};
    int top = 1;
    stack[top] = cs;
    cout << cs << " ";
    visited[stack[top]] = 1;
    bool ok = false;

    while(top != 0) {
        ok = false;
        for(int i = 1; i <= n && ok == false; i++) {
            if(boole[stack[top]][i] == 1 && visited[i] == false) {
                top++;
                stack[top] = i;
                visited[i] = true;
                cout<< stack[top] << " ";
                ok = true;
            }
        }
        if(ok==false) {
            top--;
        }
    }
}

//~ Fak

void DFSUtil(int u, int adj[100][100], bool visited[], int n) {
        visited[u] = true;
        for (int i=1; i <= n; i++)
            if (visited[adj[u][i]] == false)
                DFSUtil(adj[u][i], adj, visited, n);
    }

int GrCTrees(int adj[100][100], int n) {
    bool visited[n];
    memset(visited,false,sizeof(visited));
    int res = 0;
    for (int u=1; u <= n; u++) {
        if (visited[u] == false) {
            DFSUtil(u, adj, visited, n);
            res++;
        }
    }
    return res;
}

//~ Feszitofa alkotas

//&Kruskal
void azonos(int a,int b, int komp[100], int n) {
    int c = komp[b];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(komp[i] == c) {
                komp[i] = komp[a];
            }
        }
    }
}

void BSort(int ell[100][4], int m) {
    bool x = false;
    int lp = 0;
    do {
        x = false;
        for (int i = 1; i < m - lp; i++) {
            if (ell[i][3] > ell[i + 1][3]) {
                x = true;
                univ_swap(ell[i][1], ell[i + 1][1]);
                univ_swap(ell[i][2], ell[i + 1][2]);
                univ_swap(ell[i][3], ell[i + 1][3]);
            }
            lp++;
        }
    } while (x == true);
}

bool ellenoriz(int a,int b, int komp[100]) {
    return komp[a] == komp[b];
}

void GrKruskal(int boole[100][100], int n, int ell[100][4], int m, int ell2[100][3]) {
    int komp[100], k, i;
    boolToEll(boole,n,ell,m);
    BSort(ell, m);
    k=1, i = 1;
    while(k <= n - 1) {
        if(ellenoriz(ell[i][1], ell[i][2], komp) == false) {
            azonos(ell[i][1], ell[i][2], komp, n);
            ell2[k][1] = ell[i][1];
            ell2[k][2] = ell[i][2];
            ell2[k][3] = ell[i][3];
            k++;
        }
        i++;
    }
}

//&Prim

int minKey(int key[100], bool mstSet[100], int n) {
    int min = INT_MAX, min_index;

    for (int v = 1; v <= n; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[100], int boole[100][100], int n, int ell[100][3]) {
    for (int i = 2; i <= n; i++) {
        ell[i - 1][1] = parent[i];
        ell[i - 1][2] = i;
        ell[i - 1][3] = boole[i][parent[i]];
    }
}

void GrPrim(int boole[100][100], int n, int ell[100][3]) {
    int parent[100];
    int key[100];
    bool mstSet[100];

    for (int i = 1; i <= n; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[1] = 0;
    parent[1] = -1;

    for (int count = 1; count <= n - 1; count++) {
        int u = minKey(key, mstSet, n);

        mstSet[u] = true;

        for (int v = 1; v <= n; v++)
            if (boole[u][v] && mstSet[v] == false && boole[u][v] < key[v])
                parent[v] = u, key[v] = boole[u][v];
    }
    printMST(parent, boole, n, ell);
}

//~ Legrovidebb utak

//& Dijkstra
int minDistance(int dist[], bool sptSet[], int n) {
    int min = INT_MAX, min_index;

    for (int v = 1; v <= n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void grDijkstra(int boole[100][100], int src, int n) {
    int dist[100];
    bool sptSet[100];

    for (int i = 1; i <= n; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for(int count = 1; count <= n - 1; count++) {
        int u = minDistance(dist, sptSet, n);
        sptSet[u] = true;

        for (int v = 1; v <= n; v++)
            if (!sptSet[v] && boole[u][v] && dist[u] != INT_MAX &&
                dist[u] + boole[u][v] < dist[v])
                dist[v] = dist[u] + boole[u][v];
    }

    cout << "Csomopont \tTavolsag a kiinduloponntol" << endl;
    for (int i = 1; i <= n; i++) {
        if(dist[i] == INT_MAX) {
            cout << i << " \t\t" << "INF" << endl;
        } else {
            cout << i << " \t\t" << dist[i] << endl;
        }
    }
}

//& Floyd Warshall
void grFloydWar(int graph[100][100], int n) {
    //!!! PUT 99 OR BIG NUMBER WHERE SHOULD BE INF
    int dist[100][100], i, j, k;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++)
            dist[i][j] = graph[i][j];

    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j])
                    && (dist[k][j] != INF
                        && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    cout << "The following matrix shows the shortest "
            "distances"
            " between every pair of vertices \n";
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == 99)
                cout << "INF" << "     ";
            else
                cout << dist[i][j] << "     ";
        }
        cout << endl;
    }
}

//~ Spec

bool existPath(int ell[100][4],int n, int u, int v) {
    bool bol[n][n];
    memset(bol, false, sizeof(bol));

    for (int i = 1; i <= n; i++)
        bol[ell[i][1]][ell[i][2]] = true;

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                bol[i][j] = bol[i][j] || bol[i][k] && bol[k][j];
            }
        }
    }

    if (u >= n || v >= n) {
        return false;
    }

    if (bol[u][v])
        return true;
    return false;
}

bool checkIsolated(int boole[100][100], int n) {
    for (int i = 1; i <= n; i++) {
        int count = 0;
        for (int j = 1; j <= n; j++) {
            if (boole[i][j])
                count++;
        }
        if (count == 0)
            return true;
    }
    return false;
}

void PathMat(int boole[100][100], int n) {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(boole[i][j] == 0) {
                    boole[i][j] = boole[i][k] * boole[k][j];
                }
            }
        }
    }
}

void delVert(int adj[100][100], int n, int cs) {
    //& WORKS WITH ADJ LIST

    adj[cs][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= adj[i][0]; j++) {
            if(adj[i][j] == cs) {
                for(int k = j; k <= (adj[i][0] - 1); k++) {
                    adj[i][k] = adj[i][k+1];
                }
                adj[i][0]--;
            }
        }
    }
}

int cntDeg(int boole[100][100], int n, int num) {
    int cnt = 0;
    for(int j = 1; j <= n; j++) {
        if(boole[num][j] != 0) {
            cnt++;
        }
    }

    return cnt;
}

//? i = 0 ?????
void inOutDeg(int adj[100][100], int n,int in[100],int out[100]) {
    for(int i=0;i<n;i++) {
        out[i] = ArrSize(adj[i]);
            for(int j=0;j<ArrSize(adj[i]);j++)
                in[adj[i][j]]++;
    }
}

//^CHECK
//!!! in main k = 1;
void checkHamiltGr(int boole[100][100], int n, int k) {
    int p[100], x[100];
    memset(p,0,sizeof(p));
    memset(x,0,sizeof(x));
    for(int i = 1; i <= n; i++) {
        if(!p[i]) {
            p[i] = 1;
            x[k] = i;
            if(k == 1 || boole[x[k-1]][x[k]]) {
                if(k == n && boole[x[k]][x[1]] == 1) {
                    cout << "YES" << endl;
                    return;
                } else {
                    checkHamiltGr(boole, n, k+1);
                }

            }
            p[i] = 0;
        }
    }
}

//^CHECK
void checkEulerGr(int adj[100][100], int n) {
    //& WORKS WITH ADJ LIST
    int in[100];
    int out[100];
    inOutDeg(adj,n,in,out);

    int cnt = 0;
    for(int i=0;i<n;i++) {
        if(in[i] != out[i]) {
            cnt++;
        }
    }

    if(cnt == 2) {
        cout << "Eulerian Graph" << endl;
    } else {
        cout << "Not an Eulerian Graph" << endl;
    }
}

//^CHECK
void checkBipartite(int adj[100][100], int n) {
    //& WORKS WITH ADJ LIST
    int in[100];
    int out[100];
    inOutDeg(adj,n,in,out);

    int cnt = 0;
    for(int i=0;i<n;i++) {
        if(in[i] != out[i]) {
            cnt++;
        }
    }

    if(cnt == 0) {
        cout << "Bipartite Graph" << endl;
    } else {
        cout << "Not a Bipartite Graph" << endl;
    }
}

//^CHECK
void isCompGraph(int inc[100][100], int n, int m) {
    //& WORKS WITH INC MATRIX
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(inc[i][j] == 1) {
                cnt++;
            }
        }
    }

    if((cnt/2) == m) {
        cout << "Complete Graph" << endl;
    } else {
        cout << "Not Complete Graph" << endl;
    }
}

//& Check Circle
bool isCircU(int adj[100][100],int n,int v, bool visited[], int parent) {
    visited[v] = true;
    for(int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if(isCircU(adj, n, i, visited, v))
                return true;
        } else if (i != parent) {
            return true;
        }
    }
    return false;
}

bool isCirc(int adj[100][100], int n) {
    bool visited[n];
    memset(visited,false,sizeof(visited));

    for (int u = 1; u <= n; u++) {
        if (visited[u] == true)
            if (isCircU(adj, n, u, visited, -1)) {
                return true;
            }
    }
    return false;
}

//^CHECK
void checkSCC(int adj[100][100], int n) {
    //& WORKS WITH ADJ LIST
    int in[100];
    int out[100];
    inOutDeg(adj,n,in,out);

    int cnt = 0;
    for(int i=0;i<n;i++) {
        if(in[i] != out[i]) {
            cnt++;
        }
    }

    if(cnt == 0) {
        cout << "Strongly Connected Graph" << endl;
    } else {
        cout << "Not a Strongly Connected Graph" << endl;
    }
}

void getCliques(int n, int boole[100][100]) {
    int e, u, bejar[20], lat[20], h = 1;
    for(int i = 1; i <= n; i++) {
        if(lat[i] == 0) {
            e = 1;
            u = 2;
            lat[i] = h;
            bejar[e] = i;
            while(e < u) {
                for(int j = 1; j <= n; j++) {
                    if((boole[bejar[e]][j]) == 1 && (lat[j] == 0)) {
                        bejar[u] = j;
                        lat[j] = h;
                        u++;
                    }
                }
                e++;
            }
            h++;
        }
    }

    for(int i = 1; i <= h-1; i++) {
        cout<<i << "th click: ";
        for(int j = 1; j <= n; j++) {
            if(lat[j] == i) {
                cout<<j<< " ";
            }
        }
        cout<<endl;
    }
}
# endif