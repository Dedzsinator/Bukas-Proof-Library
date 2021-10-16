#ifndef GRAFOK
#define GRAFOK
#include <bits/stdc++.h>
using namespace std;

template<typename T, int size>
    int ArrSize(T(&)[size]){
        return size;
    }

//^ Matrixok atalakitasai

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

void boolToEll(int boole[100][100], int n, int ell[100][3]) {
    int num = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (boole[i][j] == 1) {
                num++;
                ell[num][1] = j;
                ell[num][2] = i;
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

void ellToIncid(int ell[100][3], int n, int inc[100][100]) {

}

//!NOT WORKING
void incidToBool(int inc[100][100], int n, int m, int boole[100][100]) {
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(inc[j][i] != 0) {
                boole[i][j] = 1;
                boole[j][i] = 1;
            }
        }
    }
}

void incidToAdj(int inc[100][100], int n, int m, int adj[100][100]) {

}

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

//^ Bejarasok

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

//^ Legrovidebb utak
    //& Dijsktra
    //? ReWrite 66 old
    
    int minDistance(int dist[], bool sptSet[], int n) {
        int min = INT_MAX, min_index;
        for (int v = 0; v < n; v++)
            if (sptSet[v] == false && dist[v] <= min)
                min = dist[v], min_index = v;
        return min_index;
    }   
    
    void dijkstra(int graph[100][100], int src, int n) {
        int dist[100];
        bool sptSet[100];

        for (int i = 0; i < n; i++) {
            dist[i] = INT_MAX, sptSet[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < n - 1; count++) {
            int u = minDistance(dist, sptSet, n);
            sptSet[u] = true;

            for (int v = 0; v < n; v++)
                if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                    && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
        }

        cout <<"Vertex \t Distance from Source" << endl;
        for (int i = 0; i < n; i++) {
            cout  << i << " \t\t"<<dist[i]<< endl;
        }
    }

    //& Roy-Floyd
    //? 70 old


//^ Spec
void checkIzP() {
    
}

void PathMat() {
    //50 old
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

void inOutDeg(int adj[100][100], int n,int in[100],int out[100]) {
    for(int i=0;i<n;i++) {
        out[i] = ArrSize(adj[i]);
            for(int j=0;j<ArrSize(adj[i]);j++)
                in[adj[i][j]]++;
    }
}

void checkHamiltGr() {

}

/*
void bejar(int boole, int n, int cs) {
    int t[n];
    for(int i = 1; i <= n; i++) {
        t[i] = false;
    }
    t[cs] = true;
    for(int j = 1; j <= n; j++) {
        if(boole[cs][j] == 1 && !(t[j])) {
            bejar(boole, n, j);
        } 
    }
}

bool checkEulGr(int boole[100][100], int n) {
    bool t[n];
    for(int i = 1; i <= n; i++) {
        t[i] = false;
    }
}
*/

void checkEvenGr() {
    //30 old 7)
}

void checkRaceGr() {

}

void checkFullGr() {
    //34 old 8)
}

void checkCircGr() {

}

void checkContGr() {
    //52 old
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