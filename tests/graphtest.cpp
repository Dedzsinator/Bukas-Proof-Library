#include <iostream>
#include <vector>
#include "../headers/Graphs/graph.cpp"

using namespace std;

void printPaths(vector<size_t>& dist, vector<size_t>& prev) {
    cout << "Vertex\tDistance\tPath" << endl;
    for (size_t i = 0; i < dist.size(); ++i) {
        if (dist[i] == numeric_limits<size_t>::max()) {
            cout << i << "\tINF\t\t" << endl;
        } else {
            cout << i << "\t" << dist[i] << "\t\t";
            vector<size_t> path;
            for (size_t j = i; j != -1; j = prev[j]) {
                path.push_back(j);
            }
            reverse(path.begin(), path.end());
            for (size_t j : path) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
}

void printMatrix(const vector<vector<size_t>>& matrix, const string& name) {
    cout << name << " Matrix:" << endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            if(elem == numeric_limits<size_t>::max()) {
                cout << "INF\t";
            } else {
                cout << elem << "\t";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    
    //!!!!! NEED TO PLACE HUFFMAN DECODE-ENCODE SOMEWHERE

    //test directed weighted graphs
    vector<vector<double>> adjacencyMatrix = {
        {0, 12, 6, 0, 0, 0},
        {0, 0, 5, 9, 0, 0},
        {0, 0, 0, 4, 2, 0},
        {0, 0, 0, 0, 0, 7},
        {0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 0}
    };

    Graph<int> g(adjacencyMatrix , false);

    cout<< "Traversal related testing" << endl;

    auto path = g.DFS(0);

    cout<< "DFS: ";

    for(auto i : path) {
        cout<< i << " ";
    }
    
    cout<<endl;

    auto path1 = g.BFS(0);

    cout<< "BFS: ";

    for(auto i : path1) {
        cout<< i << " ";
    }

    cout<<endl;

    auto path2 = g.kOrderNeighbors(0, 2);

    cout<< "K order traversal: ";

    for(auto i : path2) {
        cout<< i << " ";
    }

    cout<<endl;

    cout<< "Shortest path testing" << endl;

    cout << "Dijkstra's Algorithm:" << endl;

    auto [dijkstraDist, dijkstraPrev] = g.Dijkstra(1);

    printPaths(dijkstraDist, dijkstraPrev);

    cout << "Johnson's Algorithm:" << endl;

    auto [johnsonDist, johnsonNext] = g.Johnson();

    printMatrix(johnsonDist, "johnsonDist");
    printMatrix(johnsonNext, "johnsonNext");

    cout<< endl << "Flow related testing" << endl;

    cout << "Ford Fulkerson" << endl;

    auto [maxFlow, flow] = g.FordFulkerson(0,5);

    cout<< "Max flow: "<< maxFlow <<endl;

    cout<<endl;

    cout << "Edmonds Karp" << endl;

    auto [maxFlow1, flow1] = g.EdmondsKarp(0,5);

    cout<< "Max flow: "<< maxFlow1 <<endl;

    cout<<endl;

    cout << "Dinic" << endl;

    auto [maxFlow2, flow2] = g.Dinic(0,5);

    cout<< "Max flow: "<< maxFlow2 <<endl;

    cout<<endl;

    cout << "Push Relabel" << endl;

    auto [maxFlow3, flow3] = g.PushRelabel(0,5);

    cout<< "Max flow: "<< maxFlow3 <<endl;

    cout<<endl;

    cout<< "Boykov Kolmogorov" << endl;

    auto [maxFlow4, flow4] = g.BoykovKolmogorov(0,5);

    cout<< "Max flow: "<< maxFlow4 <<endl;

    cout<<endl;

    cout<< "Min cut" << endl;

    auto [set1, set2] = g.minCut(0, 5, flow);

    cout<< "Set 1: ";

    for(auto i : set1) {
        cout<< i << " ";
    }

    cout<<endl;

    cout<< "Set 2: ";

    for(auto i : set2) {
        cout<< i << " ";
    }

    cout<<endl;

    cout<< "Network property testing" << endl;

    cout<< "Is network connected: " << g.isConnected() << endl;

    cout<< "Cayley formula: " << g.Cayley() << endl;

    cout<< "Is network strongly connected: " << g.isStronglyConnected() << endl;

    cout<< "Is network cyclic: " << g.isCyclic() << endl;

    cout<< "Is network bipartite: " << g.isBipartite() << endl;

    cout<< "Is network planar: " << g.isPlanar() << endl;

    cout<< "Is network tree: " << g.isTree() << endl;

    cout<< "Is network forest: " << g.isForest() << endl;

    cout<< "Is network eulerian: " << g.isEulerian() << endl;

    cout<< "Is complete: " << g.isComplete() << endl;

    cout<< "Is regular: " << g.isRegular() << endl;

    //eccentricity, pagerank, closeness, betweenness, degree centrality, clustering coefficient, diameter, radius, community detection
    //my member functons calculate the above properties for all nodes


    //! the diameter and radius doesnt work if its at the bottom of the section !!!
    auto eccentricity = g.Eccentricity();

    cout<< "Eccentricity: ";

    for(auto i : eccentricity) {
        cout<< i << " ";
    }

    cout<<endl;

    auto pagerank = g.PageRank();

    cout<< "Pagerank: ";

    for(auto i : pagerank) {
        cout<< i << " ";
    }

    cout<<endl;

    auto closeness = g.Closeness();

    cout<< "Closeness: ";

    for(auto i : closeness) {
        cout<< i << " ";
    }

    cout<<endl;

    auto betweenness = g.Betweenness();

    cout<< "Betweenness: ";

    for(auto i : betweenness) {
        cout<< i << " ";
    }

    cout<<endl;

    auto degreeCentrality = g.DegreeCentrality();

    cout<< "Degree centrality: ";

    for(auto i : degreeCentrality) {
        cout<< i << " ";
    }

    cout<<endl;

    auto clusteringCoefficient = g.ClusteringCoefficient();

    cout<< "Clustering coefficient: ";

    for(auto i : clusteringCoefficient) {
        cout<< i << " ";
    }

    cout<<endl;

    cout<< "Diameter: " << g.Diameter() << endl;

    cout<< "Radius: " << g.Radius() << endl;

    cout<< "Density: " << g.Density() << endl;
    
    /*

    auto communityDetection = g.CommunityDetection();

    cout<< "Community detection: ";

    for(auto i : communityDetection) {
        cout<< i << " ";
    }

    */

    cout<<endl;

    cout<< "Chromatic number: " << g.ChromaticNumber() << endl;

    auto chromaticPolynomial = g.ChromaticPolynomial();

    cout<< "Chromatic polynomial: ";

    for(auto i : chromaticPolynomial) {
        cout<< i << " ";
    }

    cout<<endl;

    auto colors = g.GraphColoring();

    cout<< "Graph coloring: ";

    for(auto i : colors) {
        cout<< i << " ";
    }

    cout<<endl;

    cout<<"Chromatic index: "<<g.ChromaticIndex()<<endl;

    cout<<"Treeify testing"<<endl;

    vector<tuple<size_t, size_t, double>> edgeList2 = {
        {0, 2, 1},
        {0, 4, 1},
        {0, 5, 1},
        {1, 4, 1},
        {1, 5, 1},
        {2, 3, 1},
        {2, 4, 1},
        {4, 5, 1},
        {3, 4, 1},
        {4, 6, 1},
        {4, 7, 1}
    };

    Graph<size_t> g2(edgeList2, 8);

    g2.printGraph();

    cout<<endl;

    //treeify the graph
    g2.transformToTree();

    auto edgeList = g2.getEdgeList();

    cout<< "Treeified graph: " << endl;

    for(auto i : edgeList) {
        cout<< get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
    }

    cout<<endl;

    cout<< "Prufer encode testing" << endl;

    auto prufer = g2.PruferEncode();

    cout<< "Prufer encode: ";

    for(auto i : prufer) {
        cout<< i << " ";
    }

    vector<tuple<size_t, size_t, double>> pruferDecode = g2.PruferDecode(prufer);

    cout<< "Prufer decode: "<< endl;

    for(auto i : pruferDecode) {
        cout<< get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << endl;
    }

    cout<<endl;

    cout<< "Components testing" << endl;

    cout<< "Tarjan" << endl;

    auto components = g2.TarjanStrongConnect();

    //print the components
    for(auto i : components) {
        for(auto j : i) {
            cout<< j << " ";
        }
        cout<<endl;
    }

    cout<<endl;

    cout<< "Kosaraju" << endl;

    auto components1 = g2.KosarajuStrongConnect();

    //print the components

    for(auto i : components1) {
        for(auto j : i) {
            cout<< j << " ";
        }
        cout<<endl;
    }

    cout<<endl;

    cout<< "Tarjan Biconnect" << endl;

    vector<vector<pair<size_t, size_t>>> components2 = g2.TarjanBiconnect();

    //print the components

    for(auto i : components2) {
        for(auto j : i) {
            cout<< j.first << " " << j.second << " ";
        }
        cout<<endl;
    }

    cout<<endl;

    cout<< "Articulation points and bridges" << endl;

    pair<vector<pair<size_t, size_t>>,vector<bool>> articulationPoints = g2.findBridgesAndArticulationPoints();

    cout<< "Articulation points: ";

    for(size_t i = 0; i < articulationPoints.second.size(); i++) {
        if(articulationPoints.second[i]) {
            cout<< i << " ";
        }
    }

    cout<<endl;

    cout<< "Bridges: ";

    for(auto i : articulationPoints.first) {
        cout<< i.first << " " << i.second << " ";
    }

    cout<<endl;

    /*

    vector<vector<double>> adjacencyMatrix = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 1, 1, 0, 0},
        {1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    Graph<int> g(adjacencyMatrix);

    /*
    Graph<int> g;

    g.addNode(0); // Adjusted to 0-based indexing
    g.addNode(1);
    g.addNode(2);

    g.addEdge(0, 1);

    g.addEdge(0, 2);

    g.printGraph();

    cout<<endl;

    g.printAdjMatrix();

    cout<<endl<<"Edge removal (0,1)" << endl;

    g.removeEdge(0, 1);

    g.printNeighbors(0);

    cout<<endl;

    g.printGraph();

    cout<<endl;

    g.printAdjMatrix();

    cout<<endl;

    if(g.isGraphDirected()) {
        cout<<"Graph is directed"<<endl;
    } else {
        cout<<"Graph is undirected"<<endl;
    }

    g.addEdge(0, 1);
    g.addNode(3);
    g.addEdge(0, 3);

    cout<<endl;

    g.printAdjMatrix();

    cout<<endl;

    g.printDegree(0);

    cout<<endl;

    cout<<"Removing node 3" << endl;

    g.removeNode(3);

    cout<<endl;

    g.printNeighbors(0);

    cout<<endl;

    g.printGraph();

    cout<<endl<<endl;

    cout<<"Testing graph constructors"<<endl<<endl;

    vector<vector<double>> adjacencyMatrix = {
        {0, 1, 0, 0},
        {1, 0, 1, 1},
        {0, 1, 0, 1},
        {0, 1, 1, 0}
    };
    Graph<int> g1(adjacencyMatrix);
    g1.printGraph();
    g1.printAdjMatrix();

    cout<<endl<<endl;

    vector<tuple<int, int, double>> edgeList = {
        {0, 1, 1},
        {1, 2, 1},
        {1, 3, 1},
        {2, 3, 1}
    };
    Graph<int> g2(edgeList, 4);
    g2.printGraph();
    g2.printAdjMatrix();

    cout<<endl<<endl;

    vector<vector<pair<int, double>>> adjacencyList = {
        {{1, 1}},
        {{0, 1}, {2, 1}, {3, 1}},
        {{1, 1}, {3, 1}},
        {{1, 1}, {2, 1}}
    };
    Graph<int> g3(adjacencyList);
    g3.printGraph();
    g3.printAdjMatrix();

    cout<<endl<<endl;

    vector<vector<int>> incidenceMatrix = {
        {1, 0, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 1}
    };
    Graph<int> g4(incidenceMatrix);
    g4.printGraph();
    g4.printAdjMatrix();

    cout<<endl<<endl;

    //!!!!!! */

    /*

    cout<<"DS testing"<<endl<<endl;

    cout<<"Adjacency Matrix"<<endl;
    //get Adjacency Matrix of g
    vector<vector<double>> adjMatrix = g.getAdjacencyMatrix();
    for(int i = 0; i < adjMatrix.size(); i++) {
        for(int j = 0; j < adjMatrix[i].size(); j++) {
            cout<<adjMatrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl<<"Adjacency List"<<endl;
    //get Adjacency List of g
    vector<vector<pair<int, double>>> adjList = g.getAdjacencyList();
    for(int i = 0; i < adjList.size(); i++) {
        cout<<i<<": ";
        for(int j = 0; j < adjList[i].size(); j++) {
            cout<<"("<<adjList[i][j].first<<", "<<adjList[i][j].second<<") ";
        }
        cout<<endl;
    }

    cout<<endl<<"Incidence Matrix"<<endl;
    //get Incidence Matrix of g
    vector<vector<int>> incMatrix = g.getIncidenceMatrix();
    for(int i = 0; i < incMatrix.size(); i++) {
        for(int j = 0; j < incMatrix[i].size(); j++) {
            cout<<incMatrix[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl<<"Edge List"<<endl;
    //get Edge List of g
    vector<tuple<int, int, double>> edgeList = g.getEdgeList();
    for(int i = 0; i < edgeList.size(); i++) {
        cout<<"("<<get<0>(edgeList[i])<<", "<<get<1>(edgeList[i])<<", "<<get<2>(edgeList[i])<<") ";
    }
    cout<<endl;

    //!!!!!!

    cout<< "Traversal related testing" << endl;

    cout<< "DFS" << endl;
    vector<size_t> path = g.DFS(2);

    for(size_t i = 0; i < path.size(); i++) {
        cout<<path[i]<<" ";
    }

    cout<<endl;

    cout<< "BFS" << endl;

    vector<size_t> path1 = g.BFS(2);

    for(size_t i = 0; i < path1.size(); i++) {
        cout<<path1[i]<<" ";
    }

    cout<<endl;

    cout<< "K order traversal" << endl;

    vector<size_t> path2 = g.kOrderNeighbors(0, 2);

    for(size_t i = 0; i < path2.size(); i++) {
        cout<<path2[i]<<" ";
    }

    cout<<endl;

    cout<< "Topological sort" << endl;

    vector<size_t> path4 = g.topologicalSort();

    for(size_t i = 0; i < path4.size(); i++) {
        cout<<path4[i]<<" ";
    }

    cout<<endl;

    cout << "Shortest path testing" << endl;

    //!
    size_t source = 0;
    cout << "Dijkstra's Algorithm:" << endl;
    auto [dijkstraDist, dijkstraPrev] = g.Dijkstra(source);
    printPaths(dijkstraDist, dijkstraPrev);
    cout << endl;
    
    cout << "Bellman-Ford Algorithm:" << endl;
    auto [bellmanFordDist, bellmanFordPrev] = g.BellmanFord(source);
    printPaths(bellmanFordDist, bellmanFordPrev);
    cout << endl;
    cout << "Floyd-Warshall Algorithm:" << endl;
    auto floyWarshall = g.FloydWarshall();
    for (size_t i = 0; i < floyWarshall.size(); ++i) {
        for (size_t j = 0; j < floyWarshall[i].size(); ++j) {
            if (floyWarshall[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << floyWarshall[i][j] << " ";
            }
        }
        cout << endl;
    }

    //!
    //cout << "Johnson's Algorithm:" << endl;
    //auto [johnsonDist, johnsonNext] = g.Johnson();

    cout << "Bellman-Kalaba Algorithm:" << endl;
    auto [bellmanKalabaDist, bellmanKalabaPrev] = g.BellmanKalaba(source);
    printPaths(bellmanKalabaDist, bellmanKalabaPrev);
    cout << endl;

    cout<< "Mst related testing" << endl;

    cout << "Prim" << endl;

    vector<pair<size_t, size_t>> path5 = g.Prim();

    for(size_t i = 0; i < path5.size(); i++) {
        cout<<path5[i].first<<" "<<path5[i].second<<endl;
    }

    cout<<endl;

    cout << "Kruskal" << endl;

    vector<pair<size_t, size_t>> path10 = g.Kruskal();

    for(size_t i = 0; i < path10.size(); i++) {
        cout<<path10[i].first<<" "<<path10[i].second<<endl;
    }

    cout<<endl;

    cout << "Boruvka" << endl;

    vector<pair<size_t, size_t>> path11 = g.Boruvka();

    for(size_t i = 0; i < path11.size(); i++) {
        cout<<path11[i].first<<" "<<path11[i].second<<endl;
    }

    cout<<endl;

    cout<< "Flow related testing" << endl;

    cout << "Ford Fulkerson" << endl;

    cout<< "Max flow: "<<g.FordFulkerson(0,5)<<endl;

    cout<<endl;

    cout << "Edmonds Karp" << endl;

    cout<< "Max flow: "<<g.EdmondsKarp(0,5)<<endl;

    cout<<endl;

    cout << "Dinic" << endl;

    cout<< "Max flow: "<<g.Dinic(0,5)<<endl;

    cout<<endl;

    cout << "Push Relabel" << endl;

    cout<< "Max flow: "<<g.PushRelabel(0, 5)<<endl;

    cout<<endl;

    cout<< "Boykov Kolmogorov" << endl;

    cout<< "Max flow: "<<g.BoykovKolmogorov(0, 5)<<endl;

    cout<<endl;

    */

    return 0;
}