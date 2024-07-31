#pragma once
//! FOR Testing without errors
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#include <queue>
#include <vector>
#include <iostream>
#include <stack>
#include <limits.h>
#include <algorithm>
#include <limits>
#include <unordered_map>
#include <numeric>
#include <float.h>
#include <math.h>
#include <set>

using namespace std;

template<typename T>
class Graph {
private:
  template<typename U>
  class Node {
  public:
      size_t id;
      size_t dim;
      unordered_map<size_t, double> neighbors;

      Node(size_t id) {
          this->id = id;
          this->dim = 0;
      }

      Node(size_t id, size_t dim) {
          this->id = id;
          this->dim = dim;
      }
      
      //✅
      void addNeighbor(size_t neighborId, double weight) {
          neighbors[neighborId] = weight;
      }
  };

  vector<Node<T>> nodes;
  size_t numNodes;
  bool isDirected;

  void push(size_t u, size_t v, vector<vector<double>>& capacity, vector<vector<double>>& flow, vector<double>& excess) {
      double send = min(excess[u], capacity[u][v] - flow[u][v]);
      flow[u][v] += send;
      flow[v][u] -= send;
      excess[u] -= send;
      excess[v] += send;
  }

  void relabel(size_t u, vector<vector<double>>& capacity, vector<vector<double>>& flow, vector<size_t>& height) {
      size_t minHeight = ULONG_MAX;
      for (const auto& neighbor : nodes[u].neighbors) {
          size_t v = neighbor.first;
          if (capacity[u][v] - flow[u][v] > 0) {
              minHeight = min(minHeight, height[v]);
          }
      }
      if (minHeight < ULONG_MAX) {
          height[u] = minHeight + 1;
      }
  }

public:
    // Constructor for an empty nodes✅
  Graph(size_t numNodes = 0, bool isDirected = false) : numNodes(numNodes), isDirected(isDirected) {
    if(numNodes != 0) {
      nodes.reserve(numNodes);
      for (size_t i = 0; i < numNodes; ++i) {
          nodes.emplace_back(i);
      }
    }
  }

  // Constructor from adjacency matrix✅
  Graph(const vector<vector<double>>& adjacencyMatrix, bool isDirected = false) : isDirected(isDirected) {
      size_t n = adjacencyMatrix.size();
      nodes.reserve(n);
      for (size_t i = 0; i < n; ++i) {
          nodes.emplace_back(i);
      }
      for (size_t i = 0; i < n; ++i) {
          for (size_t j = 0; j < n; ++j) {
              if (adjacencyMatrix[i][j] != 0) {
                  nodes[i].addNeighbor(j, adjacencyMatrix[i][j]);
                  if (!isDirected) {
                      nodes[j].addNeighbor(i, adjacencyMatrix[i][j]);
                  }
              }
          }
      }

      numNodes = n;
  }

  // Constructor from edge list✅
  Graph(const vector<tuple<T, T, double>>& edgeList, T nodeCount, bool isDirected = false) : isDirected(isDirected) {
      nodes.reserve(nodeCount);
      for (size_t i = 0; i < nodeCount; ++i) {
          nodes.emplace_back(i);
      }
      for (const auto& edge : edgeList) {
          size_t from, to;
          double weight;
          tie(from, to, weight) = edge;
          nodes[from].addNeighbor(to, weight);
          if (!isDirected) {
              nodes[to].addNeighbor(from, weight);
          }
      }

      numNodes = nodeCount;
  }

  // Constructor from adjacency list✅
  Graph(const vector<vector<pair<T, double>>>& adjacencyList, bool isDirected = false) : isDirected(isDirected) {
      size_t n = adjacencyList.size();
      nodes.reserve(n);
      for (size_t i = 0; i < n; ++i) {
          nodes.emplace_back(i);
      }
      for (size_t i = 0; i < n; ++i) {
          for (const auto& neighbor : adjacencyList[i]) {
              size_t neighborId = neighbor.first;
              double weight = neighbor.second;
              nodes[i].addNeighbor(neighborId, weight);
              if (!isDirected) {
                  nodes[neighborId].addNeighbor(i, weight);
              }
          }
      }

      numNodes = n;
  }

  // Constructor from incidence matrix✅
  Graph(const vector<vector<int>>& incidenceMatrix, bool isDirected = false) : isDirected(isDirected) {
      size_t nodeCount = incidenceMatrix.size();
      size_t edgeCount = incidenceMatrix[0].size();
      nodes.reserve(nodeCount);
      for (size_t i = 0; i < nodeCount; ++i) {
          nodes.emplace_back(i);
      }
      for (size_t j = 0; j < edgeCount; ++j) {
          size_t from = -1, to = -1;
          double weight = 1.0;
          for (size_t i = 0; i < nodeCount; ++i) {
              if (incidenceMatrix[i][j] != 0) {
                  if (from == -1) {
                      from = i;
                      if (isDirected && incidenceMatrix[i][j] == -1) {
                          weight = -1.0;
                      }
                  } else {
                      to = i;
                  }
              }
          }
          if (from != -1 && to != -1) {
              nodes[from].addNeighbor(to, weight);
              if (!isDirected) {
                  nodes[to].addNeighbor(from, weight);
              }
          }
      }

      numNodes = nodeCount;
  }

  // Constructor from another nodes
  Graph(const Graph<T>& other) {
      nodes = other.nodes;
      numNodes = other.numNodes;
      isDirected = other.isDirected;
  }

  // Constructor from predecessor list
  Graph(const vector<size_t>& predecessorList) {
      size_t n = predecessorList.size();
      nodes.reserve(n);
      for (size_t i = 0; i < n; ++i) {
          nodes.emplace_back(i);
      }
      for (size_t i = 0; i < n; ++i) {
          if (predecessorList[i] != -1) {
              nodes[predecessorList[i]].addNeighbor(i, 1);
          }
      }

      numNodes = n;
  }

  // Add a node✅
  void addNode(size_t id, size_t dim = 0) {
      nodes.emplace_back(id, dim);
  }

  // Add an edge✅
  void addEdge(size_t sourceId, size_t destId, double weight = 1.0) {
      // Ensure both source and destination nodes exist in the nodes
      // This might involve checking if the nodes exist and adding them if they don't

      // Add edge from source to destination
      nodes[sourceId].addNeighbor(destId, weight);

      // If the nodes is undirected, also add the edge from destination to source
      if (!isDirected) {
          nodes[destId].addNeighbor(sourceId, weight);
      }
  }

  // Get neighbors of a node✅
  const unordered_map<size_t, double>& getNeighbors(size_t id) const {
      return nodes[id].neighbors;
  }

  // Check if the nodes is directed✅
  bool isGraphDirected() const {
      return isDirected;
  }

  //✅
  void removeNode(size_t id) {
        //remove the node from every neighbor's list and delete the node itself and the connecting edges
        for(auto& node : nodes) {
            node.neighbors.erase(id);
        }
        nodes.erase(nodes.begin() + id);
    }

  //✅
  void removeEdge(size_t id1, size_t id2) {
      // Directly remove id2 from the neighbors of id1 if neighbors is a set
      nodes[id1].neighbors.erase(id2);

      // Directly remove id1 from the neighbors of id2 if neighbors is a set
      nodes[id2].neighbors.erase(id1);
  }
  
  //✅
  void printGraph() {
      for(const auto& node : nodes) {
          cout << "Node " << node.id << ": ";
          for(const auto& neighbor : node.neighbors) {
              if(neighbor.second != 0) {
                  cout << neighbor.first << " ";
              }
          }
          cout << endl;
      }
  }

  //print adj matrix✅
  void printAdjMatrix() {
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        if (nodes[i].neighbors[j] == 1) {
          cout << "1 ";
        } else {
          cout << "0 ";
        }
      }
      cout << endl;
    }
  }
  
  //✅
  void printNeighbors(size_t id) {
    cout << nodes[id].id << ": ";
    for (size_t i = 0; i < nodes[id].neighbors.size(); i++) {
      if(nodes[id].neighbors[i] != 0) {
        cout << nodes[id].neighbors[i] << " ";
      }
    }
    cout << endl;
  }
  
  vector<size_t> getNeighbors(size_t id) {
    vector<size_t> neighbors;
    for (size_t i = 0; i < nodes[id].neighbors.size(); i++) {
      if (nodes[id].neighbors[i] != 0) {
        neighbors.push_back(i);
      }
    }
    return neighbors;
  }
  
  //✅
  void printDegree(size_t id) {
      //the degree is the number of neighbors where its a 1 in the map
      int degree = 0;
      for(auto& neighbor : nodes[id].neighbors) {
          if(neighbor.second != 0) {
              degree++;
          }
      }

      cout << "Degree of node " << id << " is " << degree << endl;
  }

  size_t getDegree(size_t id) {
    int degree = 0;
    for (auto& neighbor : nodes[id].neighbors) {
      if (neighbor.second != 0) {
        degree++;
      }
    }
    return degree;
  }

  Graph<T> operator+(const Graph<T>& other) {
    Graph<T> newGraph = *this;
    for(const auto& node : other.nodes) {
        newGraph.addNode(node.id);
        for(const auto& neighbor : node.neighbors) {
            newGraph.addEdge(node.id, neighbor.first, neighbor.second);
        }
    }

    return newGraph;
  }

  Graph<T> operator-(const Graph<T>& other) {
    Graph<T> newGraph = *this;
    for(const auto& node : other.nodes) {
        newGraph.removeNode(node.id);
    }

    return newGraph;
  }

  Graph<T> operator--() {
    removeNode(nodes.size() - 1);
    return *this;
  }

  Graph<T> operator++() {
    addNode(nodes.size());
    return *this;
  }

  Graph<T> operator=(const Graph<T>& other) {
    nodes = other.nodes;
    numNodes = other.numNodes;
    isDirected = other.isDirected;
    return *this;
  }

  Graph<T> operator+=(const Graph<T>& other) {
    for(const auto& node : other.nodes) {
        addNode(node.id);
        for(const auto& neighbor : node.neighbors) {
            addEdge(node.id, neighbor.first, neighbor.second);
        }
    }

    return *this;
  }

  Graph<T> operator-=(const Graph<T>& other) {
    for(const auto& node : other.nodes) {
        removeNode(node.id);
    }

    return *this;
  }

  Graph<T> operator--(int) {
    Graph<T> temp = *this;
    removeNode(nodes.size() - 1);
    return temp;
  }

  Graph<T> operator++(int) {
    Graph<T> temp = *this;
    addNode(nodes.size());
    return temp;
  }


  //! Modify these
  Graph<T> operator==(const Graph<T>& other) {
    return nodes.size() == other.nodes.size();
  }

  Graph<T> operator!=(const Graph<T>& other) {
    return nodes.size() != other.nodes.size();
  }

  //transformings into other data structures
  vector<vector<int>> getIncidenceMatrix() {
        size_t nodeCount = nodes.size();
        size_t edgeCount = 0;
        for (const auto& node : nodes) {
            edgeCount += node.neighbors.size();
        }
        vector<vector<int>> incidenceMatrix(nodeCount, vector<int>(edgeCount, 0));
        size_t edgeIndex = 0;
        for (size_t i = 0; i < nodeCount; ++i) {
            for (const auto& neighbor : nodes[i].neighbors) {
                incidenceMatrix[i][edgeIndex] = 1;
                incidenceMatrix[neighbor.first][edgeIndex] = isDirected ? -1 : 1;
                edgeIndex++;
            }
        }
        return incidenceMatrix;
    }

  vector<vector<pair<T, double>>> getAdjacencyList() {
      vector<vector<pair<T, double>>> adjacencyList(nodes.size());
      for (size_t i = 0; i < nodes.size(); ++i) {
          for (const auto& neighbor : nodes[i].neighbors) {
              adjacencyList[i].emplace_back(neighbor.first, neighbor.second);
          }
      }
      return adjacencyList;
  }

  vector<vector<double>> getAdjacencyMatrix() {
      vector<vector<double>> adjacencyMatrix(nodes.size(), vector<double>(nodes.size(), 0));
      for (size_t i = 0; i < nodes.size(); ++i) {
          for (const auto& neighbor : nodes[i].neighbors) {
              adjacencyMatrix[i][neighbor.first] = neighbor.second;
          }
      }
      return adjacencyMatrix;
  }

  vector<tuple<T, T, double>> getEdgeList() {
      vector<tuple<T, T, double>> edgeList;
      for (size_t i = 0; i < nodes.size(); ++i) {
          for (const auto& neighbor : nodes[i].neighbors) {
              if (isDirected || i < neighbor.first) {
                  edgeList.emplace_back(i, neighbor.first, neighbor.second);
              }
          }
      }
      return edgeList;
  }

  //traversals
  //✅
  vector<size_t> BFS(size_t id) {
      vector<size_t> BFS;
      vector<bool> visited(nodes.size(), false);
      queue<size_t> q;
      
      q.push(id);
      visited[id] = true;

      while (!q.empty()) {
          size_t node = q.front();
          q.pop();
          BFS.push_back(node);
          
          // Traverse all neighbors of the current node
          for (const auto& neighborPair : nodes[node].neighbors) {
              size_t neighbor = neighborPair.first;
              if (!visited[neighbor]) {
                  q.push(neighbor);
                  visited[neighbor] = true;
              }
          }
      }

      return BFS;
  }

  //✅
  vector<size_t> DFS(size_t id) {
      vector<size_t> DFS;
      vector<bool> visited(nodes.size(), false);
      stack<size_t> s;
      
      s.push(id);

      while (!s.empty()) {
          size_t node = s.top();
          s.pop();
          
          if (visited[node]) continue; // Skip already visited nodes
          
          visited[node] = true;
          DFS.push_back(node);
          
          // Traverse all neighbors of the current node
          for (const auto& neighborPair : nodes[node].neighbors) {
              size_t neighbor = neighborPair.first;
              if (!visited[neighbor]) {
                  s.push(neighbor);
              }
          }
      }

      return DFS;
  }

  //✅
  vector<size_t> kOrderNeighbors(size_t id, size_t k) {
    vector<vector<double>> boole = this->getAdjacencyMatrix();
    queue<int> q;
    vector<bool> visited(nodes.size(), false);
    vector<int> distance(nodes.size(), 0);
    vector<size_t> res;

    q.push(id);
    visited[id] = true;

    while(!q.empty()) {
        int top = q.front();
        q.pop();

        for(int i = 0; i < nodes.size(); i++) {
            if(boole[top][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                distance[i] = distance[top] + 1;
            }
        }
    }

    for(int i = 0; i < nodes.size(); i++) {
        if(distance[i] == k) {
            res.push_back(i);
        }
    }

    return res;
  }

  //topo sort util 
  
  void topologicalSortUtil(size_t id, vector<bool> &visited, stack<size_t> &s) {
    visited[id] = true;
    for (size_t i = 0; i < nodes[id].neighbors.size(); i++) {
      if (!visited[nodes[id].neighbors[i]]) {
        topologicalSortUtil(nodes[id].neighbors[i], visited, s);
      }
    }
    s.push(id);
  }

  vector<size_t> topologicalSort() {
    vector<size_t> topological;
    vector<bool> visited(nodes.size(), false);
    stack<size_t> s;
    for (size_t i = 0; i < nodes.size(); i++) {
      if (!visited[i]) {
        topologicalSortUtil(i, visited, s);
      }
    }
    while (!s.empty()) {
      topological.push_back(s.top());
      s.pop();
    }
    return topological;
  }
  
  //!shortest paths
  //!A*

  //!Moore algorithm

  //!Best First Search
  vector<int> Moore() {
      vector<vector<size_t>> nodes = this->getAdjacencyMatrix();
      int n = nodes.size();
      vector<int> dist(n, 1e9);
      dist[0] = 0;
      vector<int> inQueue(n, 0);
      queue<int> q;
      q.push(0);
      inQueue[0] = 1;
      while (!q.empty()) {
          int u = q.front();
          q.pop();
          inQueue[u] = 0;
          for (int v = 0; v < n; v++) {
              if (nodes[u][v] != 0 && dist[v] > dist[u] + nodes[u][v]) {
                  dist[v] = dist[u] + nodes[u][v];
                  if (!inQueue[v]) {
                      q.push(v);
                      inQueue[v] = 1;
                  }
              }
          }
      }
      return dist;
  }

  pair<vector<size_t>, vector<size_t>> Dijkstra(size_t source) {
    vector<size_t> dist(nodes.size(), numeric_limits<size_t>::max());
    vector<size_t> prev(nodes.size(), -1);
    dist[source] = 0;

    using pii = pair<size_t, size_t>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (const auto& [v, weight] : nodes[u].neighbors) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return {dist, prev};
}

  pair<vector<size_t>, vector<size_t>> BellmanFord(size_t source) {
      vector<size_t> dist(nodes.size(), numeric_limits<size_t>::max());
      vector<size_t> prev(nodes.size(), -1);
      dist[source] = 0;

      for (size_t i = 0; i < nodes.size() - 1; ++i) {
          for (size_t u = 0; u < nodes.size(); ++u) {
              for (const auto& [v, weight] : nodes[u].neighbors) {
                  if (dist[u] != numeric_limits<size_t>::max() && dist[u] + weight < dist[v]) {
                      dist[v] = dist[u] + weight;
                      prev[v] = u;
                  }
              }
          }
      }

      return {dist, prev};
  }

  vector<vector<size_t>> FloydWarshall() {
      size_t n = nodes.size();
      vector<vector<size_t>> dist(n, vector<size_t>(n, numeric_limits<size_t>::max()));

      // Initialize distances
      for (size_t i = 0; i < n; ++i) {
          dist[i][i] = 0;
      }

      for (size_t u = 0; u < n; ++u) {
          for (const auto& [v, weight] : nodes[u].neighbors) {
              dist[u][v] = weight;
          }
      }

      // Floyd-Warshall algorithm
      for (size_t k = 0; k < n; ++k) {
          for (size_t i = 0; i < n; ++i) {
              for (size_t j = 0; j < n; ++j) {
                  if (dist[i][k] != numeric_limits<size_t>::max() &&
                      dist[k][j] != numeric_limits<size_t>::max() &&
                      dist[i][k] + dist[k][j] < dist[i][j]) {
                      dist[i][j] = dist[i][k] + dist[k][j];
                  }
              }
          }
      }

      return dist;
  }

  pair<vector<vector<size_t>>, vector<vector<size_t>>> Johnson() {
      Graph<T> g(nodes.size() + 1, true);
      for (size_t u = 0; u < nodes.size(); ++u) {
          for (const auto& [v, weight] : nodes[u].neighbors) {
              g.addEdge(u, v, weight);
          }
          g.addEdge(nodes.size(), u, 0);
      }

      auto [h, _] = g.BellmanFord(nodes.size());

      for (size_t u = 0; u < nodes.size(); ++u) {
          for (auto& [v, weight] : nodes[u].neighbors) {
              weight += h[u] - h[v];
          }
      }

      vector<vector<size_t>> dist(nodes.size(), vector<size_t>(nodes.size(), numeric_limits<size_t>::max()));
      vector<vector<size_t>> next(nodes.size(), vector<size_t>(nodes.size(), -1));

      for (size_t u = 0; u < nodes.size(); ++u) {
          auto [d, p] = Dijkstra(u);
          for (size_t v = 0; v < nodes.size(); ++v) {
              if (d[v] != numeric_limits<size_t>::max()) {
                  dist[u][v] = d[v] + h[v] - h[u];
                  next[u][v] = p[v];
              }
          }
      }

      return {dist, next};
  }

  pair<vector<size_t>, vector<size_t>> BellmanKalaba(size_t source) {
      vector<size_t> dist(nodes.size(), numeric_limits<size_t>::max());
      vector<size_t> prev(nodes.size(), -1);
      dist[source] = 0;

      for (size_t i = 0; i < nodes.size(); ++i) {
          for (size_t u = 0; u < nodes.size(); ++u) {
              for (const auto& [v, weight] : nodes[u].neighbors) {
                  if (dist[u] != numeric_limits<size_t>::max() && dist[u] + weight < dist[v]) {
                      dist[v] = dist[u] + weight;
                      prev[v] = u;
                  }
              }
          }
      }

      return {dist, prev};
  }

  vector<vector<double>> DijkstraDistanceMatrix() {
      vector<vector<double>> distMatrix(nodes.size(), vector<double>(nodes.size(), numeric_limits<double>::max()));

      for (size_t i = 0; i < nodes.size(); ++i) {
          auto [dist, _] = this->Dijkstra(i);
          for (size_t j = 0; j < nodes.size(); ++j) {
              distMatrix[i][j] = dist[j];
          }
      }

      return distMatrix;
  }

  //minimum spanning trees
  vector<pair<size_t, size_t>> Prim() {
        vector<pair<size_t, size_t>> mstEdges;
        vector<double> dist(nodes.size(), numeric_limits<double>::max());
        vector<size_t> prev(nodes.size(), -1);
        vector<bool> visited(nodes.size(), false);
        priority_queue<pair<double, size_t>, vector<pair<double, size_t>>, greater<pair<double, size_t>>> pq;

        dist[0] = 0;
        pq.push(make_pair(0, 0));

        while (!pq.empty()) {
            size_t u = pq.top().second;
            pq.pop();
            if (visited[u]) continue;
            visited[u] = true;

            for (const auto& [v, weight] : nodes[u].neighbors) {
                if (!visited[v] && weight < dist[v]) {
                    dist[v] = weight;
                    prev[v] = u;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }

        for (size_t i = 1; i < nodes.size(); ++i) {
            if (prev[i] != -1) {
                mstEdges.push_back({prev[i], i});
            }
        }

        return mstEdges;
    }

  Graph<T> Prim(int) {
      return Graph<T>(Prim());
  }

  vector<pair<size_t, size_t>> Kruskal() {
      vector<pair<double, pair<size_t, size_t>>> edges;
      vector<size_t> parent(nodes.size());

      for (size_t i = 0; i < nodes.size(); ++i) {
          for (const auto& [neighbor, weight] : nodes[i].neighbors) {
              if (i < neighbor) {
                  edges.push_back({weight, {i, neighbor}});
              }
          }
      }

      sort(edges.begin(), edges.end());

      iota(parent.begin(), parent.end(), 0);

      auto find = [&](size_t u) {
          while (parent[u] != u) {
              u = parent[u];
          }
          return u;
      };

      auto unionSets = [&](size_t u, size_t v) {
          size_t rootU = find(u);
          size_t rootV = find(v);
          if (rootU != rootV) {
              parent[rootU] = rootV;
          }
      };

      vector<pair<size_t, size_t>> mstEdges;

      for (const auto& [weight, edge] : edges) {
          size_t u = edge.first;
          size_t v = edge.second;
          if (find(u) != find(v)) {
              unionSets(u, v);
              mstEdges.push_back(edge);
          }
      }

      return mstEdges;
  }

  Graph<T> Kruskal(int) {
      return Graph<T>(Kruskal());
  }

  vector<pair<size_t, size_t>> Boruvka() {
      size_t n = nodes.size();
      vector<size_t> parent(n), rank(n, 0);
      vector<pair<double, pair<size_t, size_t>>> edges;

      for (size_t i = 0; i < n; ++i) {
          for (const auto& [neighbor, weight] : nodes[i].neighbors) {
              if (i < neighbor) {
                  edges.push_back({weight, {i, neighbor}});
              }
          }
      }

      iota(parent.begin(), parent.end(), 0);

      auto find = [&](size_t u) {
          while (parent[u] != u) {
              u = parent[u];
          }
          return u;
      };

      auto unionSets = [&](size_t u, size_t v) {
          size_t rootU = find(u);
          size_t rootV = find(v);
          if (rootU != rootV) {
              if (rank[rootU] > rank[rootV]) {
                  parent[rootV] = rootU;
              } else if (rank[rootU] < rank[rootV]) {
                  parent[rootU] = rootV;
              } else {
                  parent[rootV] = rootU;
                  rank[rootU]++;
              }
          }
      };

      vector<pair<size_t, size_t>> mstEdges;

      while (mstEdges.size() < n - 1) {
          vector<size_t> cheapest(n, numeric_limits<size_t>::max());

          for (size_t i = 0; i < edges.size(); ++i) {
              const auto& [weight, edge] = edges[i];
              size_t u = edge.first;
              size_t v = edge.second;
              size_t rootU = find(u);
              size_t rootV = find(v);
              if (rootU != rootV) {
                  if (cheapest[rootU] == numeric_limits<size_t>::max() || weight < edges[cheapest[rootU]].first) {
                      cheapest[rootU] = i;
                  }
                  if (cheapest[rootV] == numeric_limits<size_t>::max() || weight < edges[cheapest[rootV]].first) {
                      cheapest[rootV] = i;
                  }
              }
          }

          for (size_t i = 0; i < n; ++i) {
              if (cheapest[i] != numeric_limits<size_t>::max()) {
                  const auto& [weight, edge] = edges[cheapest[i]];
                  size_t u = edge.first;
                  size_t v = edge.second;
                  if (find(u) != find(v)) {
                      unionSets(u, v);
                      mstEdges.push_back(edge);
                  }
              }
          }
      }

      return mstEdges;
  }

  Graph<T> Boruvka(int) {
      return Graph<T>(Boruvka());
  }

  //reverse delete algorithm
  vector<size_t> ReverseDelete() {}

  //max Flow / min Cut ✅
  bool bfsFulkerson(vector<vector<double>>& residualGraph, size_t source, size_t sink, vector<size_t>& parent) {
      size_t n = residualGraph.size();
      vector<bool> visited(n, false);

      queue<size_t> q;
      q.push(source);
      visited[source] = true;
      parent[source] = -1;

      while (!q.empty()) {
          size_t u = q.front();
          q.pop();

          for (size_t v = 0; v < n; ++v) {
              if (!visited[v] && residualGraph[u][v] > 0) {
                  q.push(v);
                  parent[v] = u;
                  visited[v] = true;
              }
          }
      }

      return visited[sink];
  }

  pair<double, vector<vector<double>>> FordFulkerson(size_t source, size_t sink) {
        vector<vector<double>> nodes = this->getAdjacencyMatrix();
        size_t u, v;
        size_t n = nodes.size();

        vector<vector<double>> residualGraph = this->getAdjacencyMatrix();
        vector<size_t> parent(n);

        double maxFlow = 0;

        while (bfsFulkerson(residualGraph, source, sink, parent)) {
            double pathFlow = numeric_limits<double>::max();
            for (v = sink; v != source; v = parent[v]) {
                u = parent[v];
                pathFlow = min(pathFlow, residualGraph[u][v]);
            }

            for (v = sink; v != source; v = parent[v]) {
                u = parent[v];
                residualGraph[u][v] -= pathFlow;
                residualGraph[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        return {maxFlow, residualGraph};
    }

  pair<double, vector<vector<double>>> EdmondsKarp(size_t source, size_t sink) {
        vector<vector<double>> residualGraph(numNodes, vector<double>(numNodes, 0));
        for (const auto& node : nodes) {
            for (const auto& neighbor : node.neighbors) {
                residualGraph[node.id][neighbor.first] = neighbor.second;
            }
        }

        vector<size_t> parent(numNodes);
        double maxFlow = 0;

        while (bfsFulkerson(residualGraph, source, sink, parent)) {
            double pathFlow = numeric_limits<double>::max();
            for (size_t v = sink; v != source; v = parent[v]) {
                size_t u = parent[v];
                pathFlow = min(pathFlow, residualGraph[u][v]);
            }

            for (size_t v = sink; v != source; v = parent[v]) {
                size_t u = parent[v];
                residualGraph[u][v] -= pathFlow;
                residualGraph[v][u] += pathFlow;
            }

            maxFlow += pathFlow;
        }

        return {maxFlow, residualGraph};
    }

  bool bfsLevelGraph(size_t source, size_t sink, vector<vector<double>>& residualGraph, vector<size_t>& level) {
        fill(level.begin(), level.end(), -1);
        level[source] = 0;

        queue<size_t> q;
        q.push(source);

        while (!q.empty()) {
            size_t u = q.front();
            q.pop();

            for (const auto& neighbor : nodes[u].neighbors) {
                size_t v = neighbor.first;
                if (level[v] == -1 && residualGraph[u][v] > 0) {
                    level[v] = level[u] + 1;
                    q.push(v);
                    if (v == sink) return true; // Early exit if sink is reached
                }
            }
        }

        return false;
    }

  double dfsBlockingFlow(size_t u, size_t sink, double flow, vector<vector<double>>& residualGraph, vector<size_t>& level, vector<size_t>& start) {
      if (u == sink) {
          return flow;
      }

      for (; start[u] < numNodes; ++start[u]) {
          size_t v = start[u];
          if (level[v] == level[u] + 1 && residualGraph[u][v] > 0) {
              double curr_flow = min(flow, residualGraph[u][v]);
              double temp_flow = dfsBlockingFlow(v, sink, curr_flow, residualGraph, level, start);

              if (temp_flow > 0) {
                  residualGraph[u][v] -= temp_flow;
                  residualGraph[v][u] += temp_flow;
                  return temp_flow;
              }
          }
      }

      return 0;
  }

  pair<double, vector<vector<double>>> Dinic(size_t source, size_t sink) {
      vector<vector<double>> residualGraph(numNodes, vector<double>(numNodes, 0));
      for (const auto& node : nodes) {
          for (const auto& neighbor : node.neighbors) {
              residualGraph[node.id][neighbor.first] = neighbor.second;
          }
      }

      vector<size_t> level(numNodes);
      vector<size_t> start(numNodes);
      double maxFlow = 0;

      while (bfsLevelGraph(source, sink, residualGraph, level)) {
          fill(start.begin(), start.end(), 0);

          while (double flow = dfsBlockingFlow(source, sink, numeric_limits<double>::max(), residualGraph, level, start)) {
              maxFlow += flow;
          }
      }

      return {maxFlow, residualGraph};
  }

  pair<double, vector<vector<double>>> PushRelabel(size_t source, size_t sink) {
      vector<vector<double>> capacity(numNodes, vector<double>(numNodes, 0));
      vector<vector<double>> flow(numNodes, vector<double>(numNodes, 0));
      vector<double> excess(numNodes, 0);
      vector<size_t> height(numNodes, 0);

      for (const auto& node : nodes) {
          for (const auto& neighbor : node.neighbors) {
              capacity[node.id][neighbor.first] = neighbor.second;
          }
      }

      height[source] = numNodes;
      for (const auto& neighbor : nodes[source].neighbors) {
          size_t v = neighbor.first;
          flow[source][v] = capacity[source][v];
          flow[v][source] = -capacity[source][v];
          excess[v] = capacity[source][v];
          excess[source] -= capacity[source][v];
      }

      queue<size_t> excessVertices;
      for (size_t i = 0; i < numNodes; ++i) {
          if (i != source && i != sink && excess[i] > 0) {
              excessVertices.push(i);
          }
      }

      while (!excessVertices.empty()) {
          size_t u = excessVertices.front();
          excessVertices.pop();

          bool pushed = false;
          for (const auto& neighbor : nodes[u].neighbors) {
              size_t v = neighbor.first;
              if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1) {
                  push(u, v, capacity, flow, excess);
                  if (v != source && v != sink && excess[v] == flow[u][v]) {
                      excessVertices.push(v);
                  }
                  pushed = true;
              }
          }

          if (!pushed) {
              relabel(u, capacity, flow, height);
              excessVertices.push(u);
          }
      }

      return {excess[sink], flow};
  }

  pair<double, vector<vector<double>>> BoykovKolmogorov(size_t source, size_t sink) {
      vector<vector<double>> capacity(numNodes, vector<double>(numNodes, 0));
      vector<vector<double>> flow(numNodes, vector<double>(numNodes, 0));
      vector<double> excess(numNodes, 0);
      vector<size_t> height(numNodes, 0);

      for (const auto& node : nodes) {
          for (const auto& neighbor : node.neighbors) {
              capacity[node.id][neighbor.first] = neighbor.second;
          }
      }

      height[source] = numNodes;
      for (const auto& neighbor : nodes[source].neighbors) {
          size_t v = neighbor.first;
          flow[source][v] = capacity[source][v];
          flow[v][source] = -capacity[source][v];
          excess[v] = capacity[source][v];
          excess[source] -= capacity[source][v];
      }

      queue<size_t> excessVertices;
      for (size_t i = 0; i < numNodes; ++i) {
          if (i != source && i != sink && excess[i] > 0) {
              excessVertices.push(i);
          }
      }

      while (!excessVertices.empty()) {
          size_t u = excessVertices.front();
          excessVertices.pop();

          bool pushed = false;
          for (const auto& neighbor : nodes[u].neighbors) {
              size_t v = neighbor.first;
              if (capacity[u][v] - flow[u][v] > 0 && height[u] == height[v] + 1) {
                  push(u, v, capacity, flow, excess);
                  if (v != source && v != sink && excess[v] == flow[u][v]) {
                      excessVertices.push(v);
                  }
                  pushed = true;
              }
          }

          if (!pushed) {
              relabel(u, capacity, flow, height);
              excessVertices.push(u);
          }
      }

      return {excess[sink], flow};
  }

  pair<vector<size_t>, vector<size_t>> minCut(size_t source, size_t sink, const vector<vector<double>>& residualGraph) {
    vector<bool> visited(numNodes, false);
    queue<size_t> q;
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        size_t u = q.front();
        q.pop();

        for (size_t v = 0; v < numNodes; ++v) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    vector<size_t> set1, set2;
    for (size_t i = 0; i < numNodes; ++i) {
        if (visited[i]) {
            set1.push_back(i);
        } else {
            set2.push_back(i);
        }
    }

    return {set1, set2};
  }

  //connectivity
  
  vector<size_t> ConnectedComponentsUnionFind() {
    vector<size_t> components(nodes.size());
    iota(components.begin(), components.end(), 0);
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (components[i] != components[j]) {
          size_t oldComponent = components[j];
          for (size_t k = 0; k < components.size(); k++) {
            if (components[k] == oldComponent) {
              components[k] = components[i];
            }
          }
        }
      }
    }
    return components;
  }

  vector<vector<size_t>> TarjanUtil(int u, vector<size_t>& visited, vector<size_t>& low, vector<size_t>& onStack, stack<int>& st, int& nrVisited) {
      visited[u] = low[u] = nrVisited++;
      st.push(u);
      onStack[u] = 1;

      vector<vector<size_t>> sccs;

      // DFS
      for (size_t v : nodes[u]) {
          if (visited[v] == -1) {
              vector<vector<size_t>> sccs = TarjanUtil(v, visited, low, onStack, st, nrVisited);
              sccs.insert(sccs.end(), sccs.begin(), sccs.end());
              low[u] = min(low[u], low[v]);
          } else if (onStack[v]) {
              low[u] = min(low[u], visited[v]);
          }
      }

      if (visited[u] == low[u]) {
          vector<size_t> scc;
          while (st.top() != u) {
              scc.push_back(st.top());
              onStack[st.top()] = 0;
              st.pop();
          }
          scc.push_back(st.top());
          onStack[st.top()] = 0;
          st.pop();
          sccs.push_back(scc);
      }

      return sccs;
    }

    vector<vector<size_t>> TarjanStrongConnect() {
      vector<size_t> visited(nodes.size(), -1);
      vector<size_t> low(nodes.size(), -1);
      vector<size_t> onStack(nodes.size(), 0);
      stack<size_t> st;
      int nrVisited = 0;

      vector<vector<size_t>> allSCCs;

      for (size_t i = 0; i < nodes.size(); i++) {
          if (visited[i] == -1) {
              vector<vector<size_t>> sccs = TarjanUtil(i, visited, low, onStack, st, nrVisited);
              allSCCs.insert(allSCCs.end(), sccs.begin(), sccs.end());
          }
      }

      return allSCCs;
    }

  void fillOrder(size_t v, vector<bool>& visited, stack<size_t>& Stack) {
      visited[v] = true;
      for (size_t i = 0; i < nodes[v].size(); ++i) {
          if (!visited[nodes[v][i]]) {
              fillOrder(nodes[v][i], visited, Stack);
          }
      }
      Stack.push(v);
  }

  void DFSUtil(size_t v, vector<bool>& visited, vector<size_t>& scc) {
      visited[v] = true;
      scc.push_back(v);
      for (size_t i = 0; i < nodes[v].size(); ++i) {
          if (!visited[nodes[v][i]]) {
              DFSUtil(nodes[v][i], visited, scc);
          }
      }
  }

  vector<vector<size_t>> KosarajuStrongConnect() {
      stack<size_t> Stack;
      vector<bool> visited(nodes.size(), false);

      // Step 1: Fill vertices in stack according to their finishing times
      for (size_t i = 0; i < nodes.size(); ++i) {
          if (!visited[i]) {
              fillOrder(i, visited, Stack);
          }
      }

      // Step 2: Transpose the nodes
      vector<vector<size_t>> transposedGraph(nodes.size());
      for (size_t v = 0; v < nodes.size(); ++v) {
          for (size_t i = 0; i < nodes[v].size(); ++i) {
              transposedGraph[nodes[v][i]].push_back(v);
          }
      }

      // Step 3: Process all vertices in order defined by Stack
      fill(visited.begin(), visited.end(), false);
      vector<vector<size_t>> sccs;
      while (!Stack.empty()) {
          size_t v = Stack.top();
          Stack.pop();

          if (!visited[v]) {
              vector<size_t> scc;
              DFSUtil(v, visited, scc);
              sccs.push_back(scc);
          }
      }

      return sccs;
  }

  void BiconnectedDFS(size_t u, vector<size_t>& disc, vector<size_t>& low, vector<int>& parent, stack<pair<size_t, size_t>>& st, vector<vector<pair<size_t, size_t>>>& biconnectedComponents, size_t& time) {
      static const size_t UNVISITED = -1;
      disc[u] = low[u] = ++time;
      size_t children = 0;

      for (size_t v : nodes[u]) {
          if (disc[v] == UNVISITED) {
              children++;
              parent[v] = u;
              st.push({u, v});
              BiconnectedDFS(v, disc, low, parent, st, biconnectedComponents, time);

              low[u] = min(low[u], low[v]);

              if ((parent[u] == UNVISITED && children > 1) || (parent[u] != UNVISITED && low[v] >= disc[u])) {
                  vector<pair<size_t, size_t>> component;
                  while (st.top() != make_pair(u, v)) {
                      component.push_back(st.top());
                      st.pop();
                  }
                  component.push_back(st.top());
                  st.pop();
                  biconnectedComponents.push_back(component);
              }
          } else if (v != parent[u] && disc[v] < disc[u]) {
              low[u] = min(low[u], disc[v]);
              st.push({u, v});
          }
      }
  }

  vector<vector<pair<size_t, size_t>>> TarjanBiconnect() {
      size_t n = nodes.size();
      vector<size_t> disc(n, -1), low(n, -1);
      vector<int> parent(n, -1);
      stack<pair<size_t, size_t>> st;
      vector<vector<pair<size_t, size_t>>> biconnectedComponents;
      size_t time = 0;

      for (size_t i = 0; i < n; ++i) {
          if (disc[i] == -1) {
              BiconnectedDFS(i, disc, low, parent, st, biconnectedComponents, time);
          }
      }

      // If stack is not empty, pop all edges
      while (!st.empty()) {
          vector<pair<size_t, size_t>> component;
          while (!st.empty()) {
              component.push_back(st.top());
              st.pop();
          }
          biconnectedComponents.push_back(component);
      }

      return biconnectedComponents;
  }
  
  void DFS(size_t u, vector<size_t>& disc, vector<size_t>& low, vector<int>& parent, vector<bool>& articulationPoints, vector<pair<size_t, size_t>>& bridges, size_t& time) {
    static const size_t UNVISITED = -1;
    disc[u] = low[u] = ++time;
    size_t children = 0;

    for (size_t v : nodes[u]) {
        if (disc[v] == UNVISITED) {
            children++;
            parent[v] = u;
            DFS(v, disc, low, parent, articulationPoints, bridges, time);

            low[u] = min(low[u], low[v]);

            if (parent[u] == UNVISITED && children > 1) {
                articulationPoints[u] = true;
            }
            if (parent[u] != UNVISITED && low[v] >= disc[u]) {
                articulationPoints[u] = true;
            }
            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }
        } else if (v != parent[u]) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

  pair<vector<pair<size_t, size_t>>,vector<bool>> findBridgesAndArticulationPoints() {
      size_t n = nodes.size();
      vector<size_t> disc(n, -1), low(n, -1);
      vector<int> parent(n, -1);
      size_t time = 0;

      for (size_t i = 0; i < n; ++i) {
          if (disc[i] == -1) {
              DFS(i, disc, low, parent, articulationPoints, bridges, time);
          }
      }
  }

  //algorithms to find if a nodes is eulerian
  vector<size_t> Fleury() {}

  vector<size_t> Hierholzer() {}

  vector<size_t> HamiltonianPath() {}

  vector<size_t> HamiltonianCycle() {}

  //coloring
  
  vector<size_t> GreedyColoring() {}
  
  vector<size_t> WelshPowell() {}

  //matching
  bool DFS(size_t u, vector<size_t>& matching, vector<size_t>& dist) {
      if (u != -1) {
          for (size_t v : nodes[u]) {
              if (dist[matching[v]] == dist[u] + 1) {
                  if (DFS(matching[v], matching, dist)) {
                      matching[v] = u;
                      matching[u] = v;
                      return true;
                  }
              }
          }
          dist[u] = numeric_limits<size_t>::max();
          return false;
      }
      return true;
  }

  bool BFS(vector<size_t>& matching, vector<size_t>& dist) {
      queue<size_t> q;
      size_t n = nodes.size();
      for (size_t u = 0; u < n; ++u) {
          if (matching[u] == -1) {
              dist[u] = 0;
              q.push(u);
          } else {
              dist[u] = numeric_limits<size_t>::max();
          }
      }
      bool found = false;
      while (!q.empty()) {
          size_t u = q.front();
          q.pop();
          if (u != -1) {
              for (size_t v : nodes[u]) {
                  if (dist[matching[v]] == numeric_limits<size_t>::max()) {
                      dist[matching[v]] = dist[u] + 1;
                      q.push(matching[v]);
                      if (matching[v] == -1) {
                          found = true;
                      }
                  }
              }
          }
      }
      return found;
  }

  vector<size_t> HopcroftKarp() {
    size_t n = nodes.size();
    vector<size_t> matching(n, -1);
    vector<size_t> dist(n);
    while (BFS(matching, dist)) {
        for (size_t u = 0; u < n; ++u) {
            if (matching[u] == -1 && DFS(u, matching, dist)) {
                matching[u] = u;
            }
        }
    }
    return matching;
  }
  
  vector<size_t> EdmondsBlossom() {}

  pair<vector<size_t>, vector<size_t>> Hungarian() {
    size_t n = nodes.size();
    vector<size_t> u(n), v(n), p(n), way(n);
    for (size_t i = 1; i < n; ++i) {
        p[0] = i;
        size_t j0 = 0;
        vector<size_t> minv(n, numeric_limits<size_t>::max());
        vector<bool> used(n, false);
        do {
            used[j0] = true;
            size_t i0 = p[j0], delta = numeric_limits<size_t>::max(), j1;
            for (size_t j = 1; j < n; ++j) {
                if (!used[j]) {
                    size_t cur = nodes[i0].neighbors[j].second - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (size_t j = 0; j < n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            size_t j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<size_t> matching(n);
    for (size_t j = 1; j < n; ++j) {
        matching[p[j]] = j;
    }
    return {matching, v};
  }

  //planarity
  
  vector<size_t> BoyerMyrvold() {
  }
  
  //is K5
  bool isK5() {
    vector<vector<size_t>> adjacencyMatrix = getAdjacencyMatrix();
    size_t n = nodes.size();
    for (size_t i = 0; i < n; i++) {
      if (nodes[i].neighbors.size() != n - 1) {
        return false;
      }
    }
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        if (i != j && !adjacencyMatrix[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  //is K33
  bool isK33() {
    vector<vector<size_t>> adjacencyMatrix = getAdjacencyMatrix();
    size_t n = nodes.size();
    if (n != 6) {
      return false;
    }
    for (size_t i = 0; i < n; i++) {
      if (nodes[i].neighbors.size() != 3) {
        return false;
      }
    }
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        if (i != j && !adjacencyMatrix[i][j]) {
          return false;
        }
      }
    }
    return true;
  }

  bool Kuratowski() {
    return !isK5() && !isK33();
  }

  //Flow
  
  vector<double> MinCostMaxFlow() {}
  
  vector<double> MaxFlowMinCost() {}

  //clustering
  
  vector<double> ClusteringCoefficient() {
        vector<double> clusteringCoefficient;

        // Calculate the number of edges between neighbors of a node
        for (size_t i = 0; i < nodes.size(); i++) {
            double triangles = 0;
            double totalTriplets = 0;

            for (auto it1 = nodes[i].neighbors.begin(); it1 != nodes[i].neighbors.end(); ++it1) {
                for (auto it2 = next(it1); it2 != nodes[i].neighbors.end(); ++it2) {
                    totalTriplets++;
                    if (nodes[it1->first].neighbors.find(it2->first) != nodes[it1->first].neighbors.end()) {
                        triangles++;
                    }
                }
            }

            double degree = nodes[i].neighbors.size();
            if (degree > 1) {
                if (isDirected) {
                    clusteringCoefficient.push_back(2 * triangles / (degree * (degree - 1)));
                } else {
                    clusteringCoefficient.push_back(3 * triangles / totalTriplets);
                }
            } else {
                clusteringCoefficient.push_back(0.0);
            }
        }

        return clusteringCoefficient;
    }

  double ClusteringCoefficient(size_t id) {
    vector<double> clusteringCoefficient = ClusteringCoefficient();
    return clusteringCoefficient[id];
  }

  //community detection
  
  vector<double> CommunityDetection() {

  }

  //centrality
  
  vector<double> DegreeCentrality() {
    vector<double> degreeCentrality;
    for (size_t i = 0; i < nodes.size(); i++) {
      degreeCentrality.push_back(nodes[i].neighbors.size());
    }
    return degreeCentrality;
  }

  double DegreeCentrality(size_t id) {
    vector<double> degreeCentrality = DegreeCentrality();
    return degreeCentrality[id];
  }

  //ranking
  
  vector<double> PageRank() {
    vector<double> pageRank;
    vector<vector<double>> adjacencyMatrix = getAdjacencyMatrix();
    size_t n = nodes.size();
    vector<double> outDegree(n, 0);
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        outDegree[i] += adjacencyMatrix[i][j];
      }
    }
    for (size_t i = 0; i < n; i++) {
      double sum = 0;
      for (size_t j = 0; j < n; j++) {
        if (adjacencyMatrix[j][i] != 0) {
          sum += adjacencyMatrix[j][i] / outDegree[j];
        }
      }
      pageRank.push_back(sum);
    }
    return pageRank;
  }

  double PageRank(size_t id) {
    vector<double> pageRank = PageRank();
    return pageRank[id];
  }

  //density
  double Density() {
    double n = nodes.size();
    double edges = 0;
    auto edgelist = this->getEdgeList();

    edges = edgelist.size();

    return edges / (n * (n - 1));
  }

  //betweenness
  
  vector<double> Betweenness() {
    vector<double> betweenness;
    vector<vector<double>> distMatrix = DijkstraDistanceMatrix();
    for (size_t i = 0; i < nodes.size(); i++) {
      double sum = 0.0;
      for (size_t j = 0; j < nodes.size(); j++) {
        for (size_t k = 0; k < nodes.size(); k++) {
          if (distMatrix[j][k] == distMatrix[j][i] + distMatrix[i][k]) {
            sum++;
          }
        }
      }
      betweenness.push_back(sum);
    }
    return betweenness;
  }

  double Betweenness(size_t id) {
    vector<double> betweenness = Betweenness();
    return betweenness[id];
  }

  //closeness
  vector<double> Closeness() {
    vector<double> closeness;
    vector<vector<double>> distMatrix = DijkstraDistanceMatrix();
    for (size_t i = 0; i < nodes.size(); i++) {
      double sum = 0;
      for (size_t j = 0; j < nodes.size(); j++) {
        sum += distMatrix[i][j];
      }
      closeness.push_back(sum);
    }
    return closeness;
  }

  double Closeness(size_t id) {
    vector<double> closeness = Closeness();
    return closeness[id];
  }

  //eigen vector centrality
  vector<double> EigenVectorCentrality() {
  
  }

  double EigenVectorCentrality(size_t id) {
    vector<double> eigenVectorCentrality = EigenVectorCentrality();
    return eigenVectorCentrality[id];
  }

  //katz centrality
  vector<double> KatzCentrality() {
    
  }

  //eccentricity
  vector<double> Eccentricity() {
      vector<double> eccentricity(nodes.size(), 0);
      vector<vector<double>> distMatrix = this->DijkstraDistanceMatrix();

      for (size_t i = 0; i < nodes.size(); i++) {
          double maxDist = -1; // Initialize to -1 to handle non-infinite distances
          for (size_t j = 0; j < nodes.size(); j++) {
              if (distMatrix[i][j] != numeric_limits<double>::max() && distMatrix[i][j] > maxDist) {
                  maxDist = distMatrix[i][j];
              }
          }
          eccentricity[i] = maxDist;
      }

      return eccentricity;
  }

  double Eccentricity(size_t id) {
    vector<double> eccentricity = Eccentricity();
    return eccentricity[id];
  }

  // diameter
  double Diameter() {
    vector<double> eccentricity = this->Eccentricity();
    double maxDist = -1; // Initialize to a very small value
    for (size_t i = 0; i < nodes.size(); i++) {
        if (eccentricity[i] > maxDist) {
            maxDist = eccentricity[i];
        }
    }
    return maxDist;
}

  // Radius
  double Radius() {
      vector<double> eccentricity = this->Eccentricity();
      double minDist = numeric_limits<double>::max();

      for (size_t i = 0; i < nodes.size(); i++) {
          if (eccentricity[i] < minDist) {
              minDist = eccentricity[i];
          }
      }
      return minDist;
  }

  //chinese postman
  
  vector<size_t> ChinesePostman() {
    
  }

  //traveling salesman
  
  vector<size_t> TravelingSalesman() {

  }

  // Graph coloring
  vector<size_t> GraphColoring() {
      vector<size_t> color(nodes.size(), -1); // -1 indicates no color assigned
      queue<size_t> q;

      for (size_t start = 0; start < nodes.size(); ++start) {
          if (color[start] == -1) { // If the node is not colored
              color[start] = 0; // Assign the first color
              q.push(start);

              while (!q.empty()) {
                  size_t node = q.front();
                  q.pop();

                  for (const auto& neighbor_pair : nodes[node].neighbors) {
                      size_t neighbor = neighbor_pair.first; // Access the neighbor node
                      if (color[neighbor] == -1) { // If the neighbor is not colored
                          color[neighbor] = 1 - color[node]; // Assign the opposite color
                          q.push(neighbor);
                      } else if (color[neighbor] == color[node]) {
                          // If the neighbor has the same color, the nodes is not bipartite
                          return vector<size_t>(); // Return an empty vector to indicate failure
                      }
                  }
              }
          }
      }

      return color;
  }

  //cromatic number
  
  size_t ChromaticNumber() {
    vector<size_t> color = GraphColoring();
    size_t maxColor = 0;
    for (size_t i = 0; i < color.size(); i++) {
      if (color[i] > maxColor) {
        maxColor = color[i];
      }
    }
    return maxColor + 1;
  }

  //chromatic polynomial
  vector<size_t> ChromaticPolynomial() {
    vector<size_t> color = GraphColoring();
    vector<size_t> chromaticPolynomial;
    for (size_t i = 0; i < color.size(); i++) {
      if (color[i] >= chromaticPolynomial.size()) {
        chromaticPolynomial.resize(color[i] + 1);
      }
      chromaticPolynomial[color[i]]++;
    }
    return chromaticPolynomial;
  }

  //chromatic index
  size_t ChromaticIndex() {
    vector<size_t> color = GraphColoring();
    size_t maxColor = 0;
    for (size_t i = 0; i < color.size(); i++) {
      if (color[i] > maxColor) {
        maxColor = color[i];
      }
    }
    return maxColor;
  }

  //nodes isomorphism with another Graph
  bool isIsomorphism(Graph<T>& nodes) {
    vector<size_t> color1 = this->GraphColoring();
    vector<size_t> color2 = nodes.GraphColoring();
    sort(color1.begin(), color1.end());
    sort(color2.begin(), color2.end());
    return color1 == color2;
  }

  //prufer encoding
  vector<size_t> PruferEncode() {
    vector<vector<double>> adj = this->getAdjacencyMatrix();
    set<int> leafs;
    int n = adj.size();
    vector<int> degree(n);
    vector<bool> killed(n, false);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            degree[i] += adj[i][j];
        }
        if (degree[i] == 1)
            leafs.insert(i);
    }

    vector<size_t> code(n - 2);
    for (int i = 0; i < n - 2; i++) {
        int leaf = *leafs.begin();
        leafs.erase(leafs.begin());
        killed[leaf] = true;

        int v;
        for (int u = 0; u < n; u++) {
            if (adj[leaf][u] && !killed[u]) {
                v = u;
                break;
            }
        }

        code[i] = v;
        if (--degree[v] == 1)
            leafs.insert(v);
    }

    return code;
  }

  //prufer decoding
  vector<tuple<T, T, double>> PruferDecode(vector<size_t>& pruferCode) {
      int n = pruferCode.size() + 2;
      vector<int> degree(n, 1);
      vector<tuple<T, T, double>> edges;

      for (int i = 0; i < n - 2; i++) {
          degree[pruferCode[i]]++;
      }

      for (int i = 0; i < n - 2; i++) {
          for (int j = 0; j < n; j++) {
              if (degree[j] == 1) {
                  edges.push_back(make_tuple(j, pruferCode[i], 1.0)); // Assuming weight 1.0 for simplicity
                  degree[j]--;
                  degree[pruferCode[i]]--;
                  break;
              }
          }
      }

      int u = -1, v = -1;

      for (int i = 0; i < n; i++) {
          if (degree[i] == 1 && u == -1) {
              u = i;
          } else if (degree[i] == 1 && v == -1) {
              v = i;
          }
      }

      edges.push_back(make_tuple(u, v, 1.0)); // Assuming weight 1.0 for simplicity

      return edges;
  }

  //nodes complement
  vector<vector<size_t>> GraphComplement() {
    vector<vector<size_t>> adj = this->getAdjacencyMatrix();
    for (size_t i = 0; i < adj.size(); i++) {
        for (size_t j = 0; j < adj[i].size(); j++) {
            adj[i][j] = !adj[i][j];
        }
    }
    return adj;
  }

  Graph<T> GraphComplement(int) {
    return Graph<T>(GraphComplement());
  }

  //get dual Graph
  vector<vector<size_t>> DualGraph() {
    vector<vector<size_t>> adj = this->getAdjacencyMatrix();
    vector<vector<size_t>> dualGraph(adj.size(), vector<size_t>(adj.size(), 0));
    for (size_t i = 0; i < adj.size(); i++) {
        for (size_t j = 0; j < adj[i].size(); j++) {
            dualGraph[i][j] = adj[i][j] * adj[j][i];
        }
    }
    return dualGraph;
  }

  Graph<T> DualGraph(int) {
    return Graph<T>(DualGraph());
  }

  //nodes matching
  vector<pair<size_t, size_t>> GraphMatching() {
    
  }

  //propery detection
  
  size_t Cayley() {
    size_t n = nodes.size();
    return pow(n, n - 2);
  }

  bool isEulerian() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (static_cast<int>(degree[i]) % 2 != 0) {
        return false;
      }
    }
    return true;
  }

  bool isHamiltonian() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] < nodes.size() / 2) {
        return false;
      }
    }
    return true;
  }
  
  bool isPlanar() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] > 5) {
        return false;
      }
    }
    return true;
  }

  bool isBipartite() {
      vector<size_t> color = GraphColoring();
      if (color.empty()) {
          return false; // If GraphColoring returns an empty vector, the nodes is not bipartite
      }
      for (size_t i = 0; i < nodes.size(); i++) {
          for (const auto& neighbor_pair : nodes[i].neighbors) {
              size_t neighbor = neighbor_pair.first; // Access the neighbor node
              if (color[i] == color[neighbor]) {
                  return false;
              }
          }
      }
      return true;
  }

  bool isComplete() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != nodes.size() - 1) {
        return false;
      }
    }
    return true;
  }

  bool isTree() {
    vector<double> degree = DegreeCentrality();
    size_t edges = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
      edges += degree[i];
    }
    edges /= 2;
    if (edges == nodes.size() - 1) {
      return true;
    }
    return false;
  }

  bool isForest() {
    vector<double> degree = DegreeCentrality();
    size_t edges = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
      edges += degree[i];
    }
    edges /= 2;
    if (edges == nodes.size() - 1) {
      return true;
    }
    return false;
  }

  bool isRegular() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != degree[0]) {
        return false;
      }
    }
    return true;
  }

  bool isCyclic() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != 2) {
        return false;
      }
    }
    return true;
  }

  bool isAcyclic() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != 1) {
        return false;
      }
    }
    return true;
  }
  
  bool isWeighted() {
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (nodes[i].weights[j] == 0) {
          return false;
        }
      }
    }
    return true;
  }

  bool chkDirected() {
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (nodes[nodes[i].neighbors[j]].neighbors[i] != i) {
          return false;
        }
      }
    }
    return true;
  }
  
  bool isDAG() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != 1) {
        return false;
      }
    }
    return true;
  }

  bool isConnected() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] == 0) {
        return false;
      }
    }
    return true;
  }

  bool isStronglyConnected() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] == 0) {
        return false;
      }
    }
    return true;
  }

  bool isBiconnected() {
    vector<double> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] == 0) {
        return false;
      }
    }
    return true;
  }

  bool isNPartite() {
    vector<size_t> color = GraphColoring();
    size_t n = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
      if (color[i] > n) {
        n = color[i];
      }
    }
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (color[i] == color[nodes[i].neighbors[j]]) {
          return false;
        }
      }
    }
    return true;
  }

  //treeify
  size_t findParent(vector<size_t>& parent, size_t u) {
        if (parent[u] != u) {
            parent[u] = findParent(parent, parent[u]);
        }
        return parent[u];
    }

    void unionSets(vector<size_t>& parent, vector<size_t>& rank, size_t u, size_t v) {
        size_t rootU = findParent(parent, u);
        size_t rootV = findParent(parent, v);
        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }

    void transformToTree() {
        // Vector to store all edges
        vector<tuple<size_t, size_t, double>> edges;

        // Gather all edges from the nodes
        for (const auto& node : nodes) {
            for (const auto& neighbor : node.neighbors) {
                edges.push_back(make_tuple(node.id, neighbor.first, neighbor.second));
            }
        }

        // Sort edges by weight
        sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
            return get<2>(a) < get<2>(b);
        });

        // Union-Find structure to detect cycles
        vector<size_t> parent(numNodes);
        vector<size_t> rank(numNodes, 0);

        // Initialize Union-Find structure
        for (size_t i = 0; i < numNodes; ++i) {
            parent[i] = i;
        }

        // Resulting edges of the Minimum Spanning Tree
        vector<tuple<size_t, size_t, double>> result;

        for (const auto& edge : edges) {
            size_t u = get<0>(edge);
            size_t v = get<1>(edge);
            double weight = get<2>(edge);

            size_t set_u = findParent(parent, u);
            size_t set_v = findParent(parent, v);

            // If including this edge does not cause a cycle
            if (set_u != set_v) {
                result.push_back(edge);
                unionSets(parent, rank, set_u, set_v);
            }
        }

        // Clear current neighbors and add edges from the result
        for (auto& node : nodes) {
            node.neighbors.clear();
        }

        for (const auto& edge : result) {
            size_t u = get<0>(edge);
            size_t v = get<1>(edge);
            double weight = get<2>(edge);

            nodes[u].addNeighbor(v, weight);
            if (!isDirected) {
                nodes[v].addNeighbor(u, weight);
            }
        }
    }
};
