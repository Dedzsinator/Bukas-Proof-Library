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

//! (main: siz = 0)
void boolToIncid(int boole[100][100], int n, int inc[100][100], int &siz) {
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

//! (main: num = 0)
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

void grBFS(int boole[30][30],int n, int cs) {
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

void grDFS(int boole[30][30],int n, int cs) {
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

int grCntTrees(int adj[100][100], int n) {
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

void grKruskal(int boole[100][100], int n, int ell[100][4], int m, int ell2[100][3]) {
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

void grPrim(int boole[100][100], int n, int ell[100][3]) {
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
int miniDist(int dist[100], bool visited[100], int n) {
    int mini = INT_MAX, min_index;

    for (int v = 1; v <= n; v++) {
        if (visited[v] == false && dist[v] <= mini) {
            mini = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void pP(int parent[100], int j) {
    if (parent[j] == -1)
        return;

    pP(parent, parent[j]);

    cout << " -> " << j;
}

void grDijkstra(int boole[100][100], int src, int n) {
    int dist[100];
    bool visited[100];
    int parent[100];

    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for(int c = 1; c <= n - 1; c++) {
        int u = miniDist(dist, visited, n);
        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (!visited[v] && boole[u][v] && dist[u] + boole[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + boole[u][v];
            }
        }
    }
    cout << "Csomopont\t Tavolsag\tUt" << endl;
    for (int i = 1; i <= n; i++) {
        cout << src << " -> " << i << "\t\t " << dist[i] << "\t\t" << src;
        pP(parent, i);
        cout << endl;
    }
}

//& Floyd Warshall
void grFloydWarshall(int graph[100][100], int n) {
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

void grRevDGr(int boole[100][100], int n, int boole2[100][100]) {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(boole[i][j] == 1) {
                boole2[j][i] = 1;
            }
        }
    }
}

bool grExistPath(int ell[100][4],int n, int u, int v) {
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

bool grCheckIsolated(int boole[100][100], int n) {
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

void grPathMat(int boole[100][100], int n) {
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

void grDelVert(int adj[100][100], int n, int cs) {
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

int grCntDeg(int boole[100][100], int n, int num) {
    int cnt = 0;
    for(int j = 1; j <= n; j++) {
        if(boole[num][j] != 0) {
            cnt++;
        }
    }

    return cnt;
}

//? i = 0 ?????
void grInOutDeg(int adj[100][100], int n,int in[100],int out[100]) {
    for(int i=0;i<n;i++) {
        out[i] = ArrSize(adj[i]);
            for(int j=0;j<ArrSize(adj[i]);j++)
                in[adj[i][j]]++;
    }
}

//& Check Hamilton
bool iS(int v, int boole[100][100], int path[100], int pos, int n) {
    if (boole[path[pos - 1]][v] == 0)
        return false;

    for (int i = 1; i <= pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hmCU(int boole[100][100], int path[100], int pos, int n) {
    if (pos == n+1) {
        if (boole[path[pos - 1]][path[1]] == 1)
            return true;
        else
            return false;
    }

    for (int v = 2; v <= n; v++) {
        if (iS(v, boole, path, pos, n)) {
            path[pos] = v;
            if (hmCU(boole, path, pos + 1, n) == true) {
                return true;
            }

            path[pos] = -1;
        }
    }
    return false;
}

bool grIsHamiltonian(int boole[100][100], int n) {
    int path[100];
    for (int i = 1; i <= n; i++) {
        path[i] = -1;
    }

    path[1] = 1;
    if (hmCU(boole, path, 2, n) == false ) {
        cout << "\nNem Hamiltoni kor";
        return false;
    }

    cout <<"Van Hamiltoni kore: \n";
    for (int i = 1; i <= n; i++) {
        cout << path[i] << " ";
    }
    cout << path[1] << " ";
    cout << endl;

    return true;
}

//& Check Eulerian
//!!!NOT WORKING
bool grIsEulerian(int boole[100][100],int n) {
    if(grIsStrongConnect(boole, n) == false) {
        return false;
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(boole[i][j] != grCntDeg(boole, n, i)) {
                return false;
            }
        }
    }
    return true;
}

bool grIsBipartite(int boole[100][100], int n, int src) {
    int visited[n];
    for (int i = 1; i <= n; ++i) {
        visited[i] = -1;
    }
    visited[src] = 1; 

    queue<int> q;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if(boole[u][u] == 1) {
            return false;
        }

        for (int v = 1; v <= n; ++v) {
            if (boole[u][v] && visited[v] == -1) {
                visited[v] = 1 - visited[u];
                q.push(v);

            } else if (boole[u][v] && visited[v] == visited[u])
                return false;
        }
    }

    return true;
}

bool GrIsComplete(int boole[100][100], int n) {
    int inc[100][100], siz = 0;
    boolToIncid(boole,n, inc, siz);
    if(siz == n*(n-1)/2) {
        return true;
    } else {
        return false;
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

bool grIsCyclic(int adj[100][100], int n) {
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

//& Check for strongly connected comps
void ut(int v, bool visited[100], int n) {
    visited[v] = true;
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            ut(i, visited, n);
        }
    }
}

bool grIsStrongConnect(int boole[100][100], int n) {
    int boole2[100][100];
    memset(boole2, false, sizeof(boole2));
    bool visited[n];
    memset(visited,false,sizeof(visited));

    ut(1, visited, n);

    for(int i = 1; i <= n; i++) {
        if(visited[i] == false) {
            return false;
        }
    }

    grRevDGr(boole, n, boole2);

    memset(visited,false,sizeof(visited));

    ut(1, visited, n);

    for(int i = 1; i <= n; i++) {
        if(visited[i] == false) {
            return false;
        }
    }

    return true;
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