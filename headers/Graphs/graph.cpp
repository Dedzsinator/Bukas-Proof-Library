#pragma once

#include <queue>
#include <vector>
#include <iostream>
#include <stack>
#include <limits.h>
#include <algorithm>

template<typename T>
class Graph {
private:
  template<typename U>
  class Node {
  public:
    size_t id;
    size_t dim;
    std::vector<size_t> neighbors;
    
    Node(size_t id) {
      this->id = id;
      this->dim = 0;
    }
    
    Node(size_t id, size_t dim) {
      this->id = id;
      this->dim = dim;
    }
  };

  std::vector<Node<T>> nodes;

public:
  Graph() {}

  Graph(std::vector<std::vector<size_t>> adjMatrix) {
    for (size_t i = 0; i < adjMatrix.size(); i++) {
      Node<T> node(i);
      nodes.push_back(node);
    }
    for (size_t i = 0; i < adjMatrix.size(); i++) {
      for (size_t j = 0; j < adjMatrix[i].size(); j++) {
        if (adjMatrix[i][j] == 1) {
          nodes[i].neighbors.push_back(j);
        }
      }
    }
  }

  Graph(std::vector<std::vector<size_t>> incMatrix, bool inc) {
    for (size_t i = 0; i < incMatrix.size(); i++) {
      Node<T> node(i);
      nodes.push_back(node);
    }
    for (size_t i = 0; i < incMatrix.size(); i++) {
      for (size_t j = 0; j < incMatrix[i].size(); j++) {
        if (incMatrix[i][j] == 1) {
          nodes[i].neighbors.push_back(j);
        }
      }
    }
  }

  //more constructors

  void addNode(size_t id, size_t dim) {
    if (dim == 0) {
      Node<T> node(id);
      nodes.push_back(node);
    } else {
      Node<T> node(id, dim);
      nodes.push_back(node);
    }
  }
  
  void addEdge(size_t id1, size_t id2) {
    nodes[id1].neighbors.push_back(id2);
    nodes[id2].neighbors.push_back(id1);
  }
  
  void removeNode(size_t id) {
    nodes.erase(nodes.begin() + id);
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (nodes[i].neighbors[j] == id) {
          nodes[i].neighbors.erase(nodes[i].neighbors.begin() + j);
        }
      }
    }
  }
  
  void removeEdge(size_t id1, size_t id2) {
    for (size_t i = 0; i < nodes[id1].neighbors.size(); i++) {
      if (nodes[id1].neighbors[i] == id2) {
        nodes[id1].neighbors.erase(nodes[id1].neighbors.begin() + i);
      }
    }
    for (size_t i = 0; i < nodes[id2].neighbors.size(); i++) {
      if (nodes[id2].neighbors[i] == id1) {
        nodes[id2].neighbors.erase(nodes[id2].neighbors.begin() + i);
      }
    }
  }
  
  void printGraph() {
    for (size_t i = 0; i < nodes.size(); i++) {
      std::cout << "Node " << nodes[i].id << ": ";
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        std::cout << nodes[i].neighbors[j] << " ";
      }
      std::cout << std::endl;
    }
  }
  
  void printNode(size_t id) {
    std::cout << "Node " << nodes[id].id << ": ";
    for (size_t i = 0; i < nodes[id].neighbors.size(); i++) {
      std::cout << nodes[id].neighbors[i] << " ";
    }
    std::cout << std::endl;
  }
  
  void printNeighbors(size_t id) {
    std::cout << "Node " << nodes[id].id << ": ";
    for (size_t i = 0; i < nodes[id].neighbors.size(); i++) {
      std::cout << nodes[id].neighbors[i] << " ";
    }
    std::cout << std::endl;
  }
  
  void printDegree(size_t id) {
    std::cout << "Node " << nodes[id].id << " has degree " << nodes[id].neighbors.size() << std::endl;
  }

  //transformings into other data structures
  
  std::vector<std::vector<size_t>> toAdjacencyMatrix() {
    std::vector<std::vector<size_t>> adjMatrix(nodes.size(), std::vector<size_t>(nodes.size(), 0));
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        adjMatrix[i][nodes[i].neighbors[j]] = 1;
      }
    }
    return adjMatrix;
  }
  
  std::vector<std::vector<size_t>> toAdjacencyList() {
    std::vector<std::vector<size_t>> adjList(nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        adjList[i].push_back(nodes[i].neighbors[j]);
      }
    }
    return adjList;
  }
  
  std::vector<std::vector<size_t>> toIncidenceMatrix() {
    std::vector<std::vector<size_t>> incMatrix(nodes.size(), std::vector<size_t>(nodes.size(), 0));
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        incMatrix[i][nodes[i].neighbors[j]] = 1;
      }
    }
    return incMatrix;
  }
  
  std::vector<std::vector<size_t>> toIncidenceList() {
    std::vector<std::vector<size_t>> incList(nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        incList[i].push_back(nodes[i].neighbors[j]);
      }
    }
    return incList;
  }
  
  //traversals
  
  std::vector<size_t> BFS(size_t id) {
    std::vector<size_t> bfs;
    std::vector<bool> visited(nodes.size(), false);
    std::queue<size_t> q;
    q.push(id);
    visited[id] = true;
    while (!q.empty()) {
      size_t node = q.front();
      q.pop();
      bfs.push_back(node);
      for (size_t i = 0; i < nodes[node].neighbors.size(); i++) {
        if (!visited[nodes[node].neighbors[i]]) {
          q.push(nodes[node].neighbors[i]);
          visited[nodes[node].neighbors[i]] = true;
        }
      }
    }
    return bfs;
  }
  
  std::vector<size_t> DFS(size_t id) {
    std::vector<size_t> dfs;
    std::vector<bool> visited(nodes.size(), false);
    std::stack<size_t> s;
    s.push(id);
    visited[id] = true;
    while (!s.empty()) {
      size_t node = s.top();
      s.pop();
      dfs.push_back(node);
      for (size_t i = 0; i < nodes[node].neighbors.size(); i++) {
        if (!visited[nodes[node].neighbors[i]]) {
          s.push(nodes[node].neighbors[i]);
          visited[nodes[node].neighbors[i]] = true;
        }
      }
    }
    return dfs;
  }
  
  std::vector<size_t> kOrderNeighbors(size_t id, size_t k) {
    std::vector<size_t> kOrder;
    std::vector<bool> visited(nodes.size(), false);
    std::queue<size_t> q;
    q.push(id);
    visited[id] = true;
    while (!q.empty()) {
      size_t node = q.front();
      q.pop();
      kOrder.push_back(node);
      if (k == 0) {
        continue;
      }
      for (size_t i = 0; i < nodes[node].neighbors.size(); i++) {
        if (!visited[nodes[node].neighbors[i]]) {
          q.push(nodes[node].neighbors[i]);
          visited[nodes[node].neighbors[i]] = true;
        }
      }
      k--;
    }
    return kOrder;
  }
  
  std::vector<size_t> levelOrder(size_t id) {
    std::vector<size_t> levelOrder;
    std::vector<bool> visited(nodes.size(), false);
    std::queue<size_t> q;
    q.push(id);
    visited[id] = true;
    while (!q.empty()) {
      size_t node = q.front();
      q.pop();
      levelOrder.push_back(node);
      for (size_t i = 0; i < nodes[node].neighbors.size(); i++) {
        if (!visited[nodes[node].neighbors[i]]) {
          q.push(nodes[node].neighbors[i]);
          visited[nodes[node].neighbors[i]] = true;
        }
      }
    }
    return levelOrder;
  }

  //topo sort util 
  
  void topologicalSortUtil(size_t id, std::vector<bool> &visited, std::stack<size_t> &s) {
    visited[id] = true;
    for (size_t i = 0; i < nodes[id].neighbors.size(); i++) {
      if (!visited[nodes[id].neighbors[i]]) {
        topologicalSortUtil(nodes[id].neighbors[i], visited, s);
      }
    }
    s.push(id);
  }

  
  std::vector<size_t> topologicalSort() {
    std::vector<size_t> topological;
    std::vector<bool> visited(nodes.size(), false);
    std::stack<size_t> s;
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
  
  //shortest paths
  
  std::vector<size_t> Dijkstra(size_t id1, size_t id2) {
    std::vector<size_t> dijkstra;
    std::vector<size_t> dist(nodes.size(), INT_MAX);
    std::vector<size_t> prev(nodes.size(), -1);
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> pq;
    dist[id1] = 0;
    pq.push(std::make_pair(0, id1));
    while (!pq.empty()) {
      size_t u = pq.top().second;
      pq.pop();
      for (size_t i = 0; i < nodes[u].neighbors.size(); i++) {
        size_t v = nodes[u].neighbors[i];
        size_t weight = 1;
        if (dist[v] > dist[u] + weight) {
          dist[v] = dist[u] + weight;
          prev[v] = u;
          pq.push(std::make_pair(dist[v], v));
        }
      }
    }
    size_t u = id2;
    while (u != -1) {
      dijkstra.push_back(u);
      u = prev[u];
    }
    std::reverse(dijkstra.begin(), dijkstra.end());
    return dijkstra;
  }
  
  std::vector<size_t> BellmanFord(size_t id1, size_t id2) {
    std::vector<size_t> bellmanFord;
    std::vector<size_t> dist(nodes.size(), INT_MAX);
    std::vector<size_t> prev(nodes.size(), -1);
    dist[id1] = 0;
    for (size_t i = 0; i < nodes.size() - 1; i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        for (size_t k = 0; k < nodes[j].neighbors.size(); k++) {
          size_t v = nodes[j].neighbors[k];
          size_t weight = 1;
          if (dist[v] > dist[j] + weight) {
            dist[v] = dist[j] + weight;
            prev[v] = j;
          }
        }
      }
    }
    size_t u = id2;
    while (u != -1) {
      bellmanFord.push_back(u);
      u = prev[u];
    }
    std::reverse(bellmanFord.begin(), bellmanFord.end());
    return bellmanFord;
  }
  
  std::vector<size_t> FloydWarshall() {
    std::vector<std::vector<size_t>> dist(nodes.size(), std::vector<size_t>(nodes.size(), INT_MAX));
    for (size_t i = 0; i < nodes.size(); i++) {
      dist[i][i] = 0;
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        dist[i][nodes[i].neighbors[j]] = 1;
      }
    }
    for (size_t k = 0; k < nodes.size(); k++) {
      for (size_t i = 0; i < nodes.size(); i++) {
        for (size_t j = 0; j < nodes.size(); j++) {
          if (dist[i][k] + dist[k][j] < dist[i][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }
        }
      }
    }
    std::vector<size_t> floydWarshall;
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        floydWarshall.push_back(dist[i][j]);
      }
    }
    return floydWarshall;
  }
  
  //calc distance matrix for shortest paths
  
  std::vector<size_t> DijkstraDistanceMatrix() {
    std::vector<size_t> distMatrix;
    for (size_t i = 0; i < nodes.size(); i++) {
      std::vector<size_t> dist(nodes.size(), INT_MAX);
      std::vector<size_t> prev(nodes.size(), -1);
      std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> pq;
      dist[i] = 0;
      pq.push(std::make_pair(0, i));
      while (!pq.empty()) {
        size_t u = pq.top().second;
        pq.pop();
        for (size_t j = 0; j < nodes[u].neighbors.size(); j++) {
          size_t v = nodes[u].neighbors[j];
          size_t weight = 1;
          if (dist[v] > dist[u] + weight) {
            dist[v] = dist[u] + weight;
            prev[v] = u;
            pq.push(std::make_pair(dist[v], v));
          }
        }
      }
      for (size_t j = 0; j < nodes.size(); j++) {
        distMatrix.push_back(dist[j]);
      }
    }
    return distMatrix;
  }

  
  std::vector<size_t> Johnson() {
    std::vector<size_t> johnson;
    std::vector<size_t> dist(nodes.size(), INT_MAX);
    std::vector<size_t> prev(nodes.size(), -1);
    std::vector<std::vector<size_t>> adjList = toAdjacencyList();
    for (size_t i = 0; i < nodes.size(); i++) {
      addNode(nodes.size(), 0);
      addEdge(nodes.size() - 1, i);
    }
    std::vector<size_t> bellmanFord = BellmanFord(nodes.size() - 1, nodes.size() - 2);
    if (bellmanFord.size() == 0) {
      return johnson;
    }
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < adjList[i].size(); j++) {
        adjList[i][j] += dist[i] - dist[adjList[i][j]];
      }
    }
    for (size_t i = 0; i < nodes.size(); i++) {
      std::vector<size_t> dists = Dijkstra(i, nodes.size() - 1);
      for (size_t j = 0; j < dists.size(); j++) {
        johnson.push_back(dists[j] + dist[adjList[i][j]]);
      }
    }
    return johnson;
  }
  
  //minimum spanning trees
  
  std::vector<size_t> Prim() {
    std::vector<size_t> prim;
    std::vector<size_t> dist(nodes.size(), INT_MAX);
    std::vector<size_t> prev(nodes.size(), -1);
    std::vector<bool> visited(nodes.size(), false);
    std::priority_queue<std::pair<size_t, size_t>, std::vector<std::pair<size_t, size_t>>, std::greater<std::pair<size_t, size_t>>> pq;
    dist[0] = 0;
    pq.push(std::make_pair(0, 0));
    while (!pq.empty()) {
      size_t u = pq.top().second;
      pq.pop();
      visited[u] = true;
      for (size_t i = 0; i < nodes[u].neighbors.size(); i++) {
        size_t v = nodes[u].neighbors[i];
        size_t weight = 1;
        if (!visited[v] && dist[v] > weight) {
          dist[v] = weight;
          prev[v] = u;
          pq.push(std::make_pair(dist[v], v));
        }
      }
    }
    for (size_t i = 0; i < nodes.size(); i++) {
      prim.push_back(prev[i]);
    }
    return prim;
  }
  
  std::vector<size_t> Kruskal() {
    std::vector<size_t> kruskal;
    std::vector<std::pair<size_t, std::pair<size_t, size_t>>> edges;
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        edges.push_back(std::make_pair(1, std::make_pair(i, nodes[i].neighbors[j])));
      }
    }
    std::sort(edges.begin(), edges.end());
    std::vector<size_t> parent(nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
      parent[i] = i;
    }
    for (size_t i = 0; i < edges.size(); i++) {
      size_t u = edges[i].second.first;
      size_t v = edges[i].second.second;
      size_t setU = parent[u];
      size_t setV = parent[v];
      if (setU != setV) {
        kruskal.push_back(u);
        parent[u] = parent[v];
      }
    }
    return kruskal;
  }

  //boruvka
  std::vector<size_t> Boruvka {

  }

  //reverse delete algorithm
  std::vector<size_t> ReverseDelete() {

  }

  //max Flow
  
  std::vector<size_t> FordFulkerson() {
    std::vector<size_t> fordFulkerson;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<std::vector<size_t>> rGraph = adjMatrix;
    size_t s = 0;
    size_t t = nodes.size() - 1;
    std::vector<size_t> parent(nodes.size());
    size_t maxFlow = 0;
    while (true) {
      std::vector<bool> visited(nodes.size(), false);
      std::queue<size_t> q;
      q.push(s);
      visited[s] = true;
      while (!q.empty()) {
        size_t u = q.front();
        q.pop();
        for (size_t v = 0; v < nodes.size(); v++) {
          if (!visited[v] && rGraph[u][v] > 0) {
            q.push(v);
            parent[v] = u;
            visited[v] = true;
          }
        }
      }
      if (!visited[t]) {
        break;
      }
      size_t pathFlow = INT_MAX;
      for (size_t v = t; v != s; v = parent[v]) {
        size_t u = parent[v];
        pathFlow = std::min(pathFlow, rGraph[u][v]);
      }
      for (size_t v = t; v != s; v = parent[v]) {
        size_t u = parent[v];
        rGraph[u][v] -= pathFlow;
        rGraph[v][u] += pathFlow;
      }
      maxFlow += pathFlow;
    }
    fordFulkerson.push_back(maxFlow);
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        fordFulkerson.push_back(rGraph[i][j]);
      }
    }
    return fordFulkerson;
  }
  
  std::vector<size_t> EdmondsKarp() {
    std::vector<size_t> edmondsKarp;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<std::vector<size_t>> rGraph = adjMatrix;
    size_t s = 0;
    size_t t = nodes.size() - 1;
    std::vector<size_t> parent(nodes.size());
    size_t maxFlow = 0;
    while (true) {
      std::vector<bool> visited(nodes.size(), false);
      std::queue<size_t> q;
      q.push(s);
      visited[s] = true;
      while (!q.empty()) {
        size_t u = q.front();
        q.pop();
        for (size_t v = 0; v < nodes.size(); v++) {
          if (!visited[v] && rGraph[u][v] > 0) {
            q.push(v);
            parent[v] = u;
            visited[v] = true;
          }
        }
      }
      if (!visited[t]) {
        break;
      }
      size_t pathFlow = INT_MAX;
      for (size_t v = t; v != s; v = parent[v]) {
        size_t u = parent[v];
        pathFlow = std::min(pathFlow, rGraph[u][v]);
      }
      for (size_t v = t; v != s; v = parent[v]) {
        size_t u = parent[v];
        rGraph[u][v] -= pathFlow;
        rGraph[v][u] += pathFlow;
      }
      maxFlow += pathFlow;
    }
    edmondsKarp.push_back(maxFlow);
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        edmondsKarp.push_back(rGraph[i][j]);
      }
    }
    return edmondsKarp;
  }
  
  std::vector<size_t> BoykovKolmongorov() {}

  std::vector<size_t> Dinic() {}
  
  std::vector<size_t> PushRelabel() {}
  
  //connectivity
  
  std::vector<size_t> ConnectedComponents() {}
  
  std::vector<size_t> StronglyConnectedComponents() {}
  
  std::vector<size_t> ArticulationPoints() {}
  
  std::vector<size_t> Bridges() {}

  //other
  
  std::vector<size_t> EulerianPath() {}
  
  std::vector<size_t> HamiltonianPath() {}

  //coloring
  
  std::vector<size_t> GreedyColoring() {}
  
  std::vector<size_t> WelshPowell() {}

  //matching
  
  std::vector<size_t> HopcroftKarp() {}
  
  std::vector<size_t> EdmondsBlossom() {}

  //planarity
  
  std::vector<size_t> BoyerMyrvold() {}
  
  std::vector<size_t> Kuratowski() {}

  //Flow
  
  std::vector<size_t> MaxFlow() {}
  
  std::vector<size_t> MinCostMaxFlow() {}
  
  std::vector<size_t> MaxFlowMinCost() {}
  
  std::vector<size_t> MinCostFlow() {}

  //clustering
  
  std::vector<size_t> KMeans() {}
  
  std::vector<size_t> DBScan() {}

  //community detection
  
  std::vector<size_t> Louvain() {}

  //centrality
  
  std::vector<size_t> DegreeCentrality() {
    std::vector<size_t> degreeCentrality;
    for (size_t i = 0; i < nodes.size(); i++) {
      degreeCentrality.push_back(nodes[i].neighbors.size());
    }
    return degreeCentrality;
  }

  //ranking
  
  std::vector<size_t> PageRank() {
    std::vector<size_t> pageRank;
    std::vector<size_t> outDegree(nodes.size(), 0);
    for (size_t i = 0; i < nodes.size(); i++) {
      outDegree[i] = nodes[i].neighbors.size();
    }
    for (size_t i = 0; i < nodes.size(); i++) {
      size_t rank = 0;
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        rank += outDegree[nodes[i].neighbors[j]];
      }
      pageRank.push_back(rank);
    }
    return pageRank;
  }

  //betweenness
  
  std::vector<size_t> Brandes() {
    std::vector<size_t> brandes;
    std::vector<std::vector<size_t>> adjList = toAdjacencyList();
    for (size_t i = 0; i < nodes.size(); i++) {
      std::vector<size_t> stack;
      std::vector<size_t> dist(nodes.size(), INT_MAX);
      std::vector<size_t> sigma(nodes.size(), 0);
      std::vector<size_t> delta(nodes.size(), 0);
      std::vector<size_t> pred(nodes.size());
      std::queue<size_t> q;
      std::stack<size_t> s;
      dist[i] = 0;
      sigma[i] = 1;
      q.push(i);
      while (!q.empty()) {
        size_t v = q.front();
        q.pop();
        s.push(v);
        for (size_t j = 0; j < adjList[v].size(); j++) {
          size_t w = adjList[v][j];
          if (dist[w] == INT_MAX) {
            q.push(w);
            dist[w] = dist[v] + 1;
          }
          if (dist[w] == dist[v] + 1) {
            sigma[w] += sigma[v];
            pred[w] = v;
          }
        }
      }
      while (!s.empty()) {
        size_t w = s.top();
        s.pop();
        for (size_t j = 0; j < adjList[w].size(); j++) {
          size_t v = adjList[w][j];
          if (dist[v] == dist[w] + 1) {
            delta[v] += (sigma[v] / sigma[w]) * (1 + delta[w]);
          }
        }
        if (w != i) {
          brandes.push_back(delta[w]);
        }
      }
    }
    return brandes;
  }

  //closeness
  
  std::vector<size_t> Closeness() {
    std::vector<size_t> closeness;
    std::vector<std::vector<size_t>> distMatrix = DijkstraDistanceMatrix();
    for (size_t i = 0; i < nodes.size(); i++) {
      size_t sum = 0;
      for (size_t j = 0; j < nodes.size(); j++) {
        sum += distMatrix[i * nodes.size() + j];
      }
      closeness.push_back(sum);
    }
    return closeness;
  }

  //eccentricity
  
  std::vector<size_t> Eccentricity() {
    std::vector<size_t> eccentricity;
    std::vector<std::vector<size_t>> distMatrix = DijkstraDistanceMatrix();
    for (size_t i = 0; i < nodes.size(); i++) {
      size_t max = 0;
      for (size_t j = 0; j < nodes.size(); j++) {
        if (distMatrix[i * nodes.size() + j] > max) {
          max = distMatrix[i * nodes.size() + j];
        }
      }
      eccentricity.push_back(max);
    }
    return eccentricity;
  }

  //diameter
  
  std::vector<size_t> Diameter() {
    std::vector<size_t> diameter;
    std::vector<std::vector<size_t>> distMatrix = DijkstraDistanceMatrix();
    size_t max = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        if (distMatrix[i * nodes.size() + j] > max) {
          max = distMatrix[i * nodes.size() + j];
        }
      }
    }
    diameter.push_back(max);
    return diameter;
  }

  //radius
  
  std::vector<size_t> Radius() {
    std::vector<size_t> radius;
    std::vector<std::vector<size_t>> distMatrix = DijkstraDistanceMatrix();
    size_t min = INT_MAX;
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        if (distMatrix[i * nodes.size() + j] < min) {
          min = distMatrix[i * nodes.size() + j];
        }
      }
    }
    radius.push_back(min);
    return radius;
  }

  //chinese postman
  
  std::vector<size_t> ChinesePostman() {
    std::vector<size_t> chinesePostman;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<size_t> oddDegree;
    for (size_t i = 0; i < nodes.size(); i++) {
      size_t degree = 0;
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        degree++;
      }
      if (degree % 2 != 0) {
        oddDegree.push_back(i);
      }
    }
    std::vector<std::vector<size_t>> distMatrix = DijkstraDistanceMatrix();
    size_t min = INT_MAX;
    size_t start = 0;
    size_t end = 0;
    for (size_t i = 0; i < oddDegree.size(); i++) {
      for (size_t j = i + 1; j < oddDegree.size(); j++) {
        if (distMatrix[oddDegree[i] * nodes.size() + oddDegree[j]] < min) {
          min = distMatrix[oddDegree[i] * nodes.size() + oddDegree[j]];
          start = oddDegree[i];
          end = oddDegree[j];
        }
      }
    }
    std::vector<size_t> eulerian = EulerianPath();
    for (size_t i = 0; i < eulerian.size() - 1; i++) {
      if (eulerian[i] == start && eulerian[i + 1] == end) {
        eulerian.insert(eulerian.begin() + i + 1, start);
        eulerian.insert(eulerian.begin() + i + 2, end);
      }
    }
    for (size_t i = 0; i < eulerian.size() - 1; i++) {
      chinesePostman.push_back(eulerian[i]);
    }
    return chinesePostman;
  }

  //traveling salesman
  
  std::vector<size_t> TravelingSalesman() {
    //use 3opt
    std::vector<size_t> travelingSalesman;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<size_t> path;
    for (size_t i = 0; i < nodes.size(); i++) {
      path.push_back(i);
    }

    size_t min = INT_MAX;
    do {
      size_t current = 0;
      for (size_t i = 0; i < path.size() - 1; i++) {
        current += adjMatrix[path[i]][path[i + 1]];
      }
      current += adjMatrix[path[path.size() - 1]][path[0]];
      if (current < min) {
        min = current;
        travelingSalesman = path;
      }
    } while (std::next_permutation(path.begin(), path.end()));
    return travelingSalesman;
  }

  //graph coloring
  
  std::vector<size_t> GraphColoring() {
    std::vector<size_t> graphColoring;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<size_t> color(nodes.size(), -1);
    color[0] = 0;
    for (size_t i = 1; i < nodes.size(); i++) {
      std::vector<bool> available(nodes.size(), true);
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (color[nodes[i].neighbors[j]] != -1) {
          available[color[nodes[i].neighbors[j]]] = false;
        }
      }
      size_t c;
      for (c = 0; c < nodes.size(); c++) {
        if (available[c]) {
          break;
        }
      }
      color[i] = c;
    }
    for (size_t i = 0; i < nodes.size(); i++) {
      graphColoring.push_back(color[i]);
    }
    return graphColoring;
  }

  //cromatic number
  
  std::vector<size_t> ChromaticNumber() {
    std::vector<size_t> chromaticNumber;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<size_t> color(nodes.size(), -1);
    color[0] = 0;
    for (size_t i = 1; i < nodes.size(); i++) {
      std::vector<bool> available(nodes.size(), true);
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (color[nodes[i].neighbors[j]] != -1) {
          available[color[nodes[i].neighbors[j]]] = false;
        }
      }
      size_t c;
      for (c = 0; c < nodes.size(); c++) {
        if (available[c]) {
          break;
        }
      }
      color[i] = c;
    }
    size_t max = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
      if (color[i] > max) {
        max = color[i];
      }
    }
    chromaticNumber.push_back(max);
    return chromaticNumber;
  }

  //graph isomorphism with another Graph
  
  std::vector<size_t> GraphIsomorphism(Graph<T> g) {
    std::vector<size_t> graphIsomorphism;
    std::vector<std::vector<size_t>> adjMatrix1 = toAdjacencyMatrix();
    std::vector<std::vector<size_t>> adjMatrix2 = g.toAdjacencyMatrix();
    std::vector<size_t> perm;
    for (size_t i = 0; i < nodes.size(); i++) {
      perm.push_back(i);
    }
    do {
      bool isIsomorphic = true;
      for (size_t i = 0; i < nodes.size(); i++) {
        for (size_t j = 0; j < nodes.size(); j++) {
          if (adjMatrix1[i][j] != adjMatrix2[perm[i]][perm[j]]) {
            isIsomorphic = false;
            break;
          }
        }
        if (!isIsomorphic) {
          break;
        }
      }
      if (isIsomorphic) {
        for (size_t i = 0; i < perm.size(); i++) {
          graphIsomorphism.push_back(perm[i]);
        }
        break;
      }
    } while (std::next_permutation(perm.begin(), perm.end()));
    return graphIsomorphism;
  }

  //cromatic polynomial
  
  std::vector<size_t> ChromaticPolynomial() {
    std::vector<size_t> chromaticPolynomial;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<size_t> color(nodes.size(), -1);
    color[0] = 0;
    for (size_t i = 1; i < nodes.size(); i++) {
      std::vector<bool> available(nodes.size(), true);
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (color[nodes[i].neighbors[j]] != -1) {
          available[color[nodes[i].neighbors[j]]] = false;
        }
      }
      size_t c;
      for (c = 0; c < nodes.size(); c++) {
        if (available[c]) {
          break;
        }
      }
      color[i] = c;
    }
    size_t max = 0;
    for (size_t i = 0; i < nodes.size(); i++) {
      if (color[i] > max) {
        max = color[i];
      }
    }
    size_t chromatic = max;
    size_t chromaticPolynomialValue = 0;
    for (size_t i = 0; i <= chromatic; i++) {
      size_t sign = 1;
      for (size_t j = 0; j < nodes.size(); j++) {
        size_t count = 0;
        for (size_t k = 0; k < nodes[j].neighbors.size(); k++) {
          if (color[nodes[j].neighbors[k]] == i) {
            count++;
          }
        }
        sign *= count;
      }
      chromaticPolynomialValue += sign;
    }
    chromaticPolynomial.push_back(chromaticPolynomialValue);
    return chromaticPolynomial;
  }

  //prufer encoding
  
  std::vector<size_t> PruferEncoding() {
    std::vector<size_t> pruferEncoding;
    std::vector<std::vector<size_t>> adjList = toAdjacencyList();
    std::vector<size_t> degree(nodes.size(), 0);
    for (size_t i = 0; i < nodes.size(); i++) {
      degree[i] = nodes[i].neighbors.size();
    }
    for (size_t i = 0; i < nodes.size() - 2; i++) {
      size_t min = INT_MAX;
      size_t leaf = 0;
      for (size_t j = 0; j < nodes.size(); j++) {
        if (degree[j] == 1) {
          leaf = j;
          break;
        }
      }
      for (size_t j = 0; j < nodes[leaf].neighbors.size(); j++) {
        if (degree[nodes[leaf].neighbors[j]] < min) {
          min = degree[nodes[leaf].neighbors[j]];
        }
      }
      pruferEncoding.push_back(min);
      degree[leaf]--;
      degree[nodes[leaf].neighbors[min]]--;
    }
    return pruferEncoding;
  }

  //prufer decoding
  
  std::vector<size_t> PruferDecoding() {
    std::vector<size_t> pruferDecoding;
    std::vector<std::vector<size_t>> adjList = toAdjacencyList();
    std::vector<size_t> degree(nodes.size(), 0);
    for (size_t i = 0; i < nodes.size(); i++) {
      degree[i] = nodes[i].neighbors.size();
    }
    for (size_t i = 0; i < nodes.size() - 2; i++) {
      size_t min = INT_MAX;
      size_t leaf = 0;
      for (size_t j = 0; j < nodes.size(); j++) {
        if (degree[j] == 1) {
          leaf = j;
          break;
        }
      }
      for (size_t j = 0; j < nodes[leaf].neighbors.size(); j++) {
        if (degree[nodes[leaf].neighbors[j]] < min) {
          min = degree[nodes[leaf].neighbors[j]];
        }
      }
      pruferDecoding.push_back(leaf);
      degree[leaf]--;
      degree[nodes[leaf].neighbors[min]]--;
    }
    return pruferDecoding;
  }

  //graph complement
  
  std::vector<size_t> GraphComplement() {
    std::vector<size_t> graphComplement;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        if (i != j) {
          if (adjMatrix[i][j] == 0) {
            graphComplement.push_back(1);
          } else {
            graphComplement.push_back(0);
          }
        } else {
          graphComplement.push_back(0);
        }
      }
    }
    return graphComplement;
  }

  //get dual Graph
  
  std::vector<size_t> DualGraph() {
    std::vector<size_t> dualGraph;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes.size(); j++) {
        if (i != j) {
          if (adjMatrix[i][j] == 1) {
            dualGraph.push_back(1);
          } else {
            dualGraph.push_back(0);
          }
        } else {
          dualGraph.push_back(0);
        }
      }
    }
    return dualGraph;
  }

  //huffman
  
  std::vector<size_t> Huffman() {
    std::vector<size_t> huffman;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<std::pair<size_t, size_t>> edges;
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        edges.push_back(std::make_pair(i, nodes[i].neighbors[j]));
      }
    }
    std::sort(edges.begin(), edges.end());
    std::vector<size_t> parent(nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
      parent[i] = i;
    }
    for (size_t i = 0; i < edges.size(); i++) {
      size_t u = edges[i].first;
      size_t v = edges[i].second;
      size_t setU = parent[u];
      size_t setV = parent[v];
      if (setU != setV) {
        huffman.push_back(u);
        parent[u] = parent[v];
      }
    }
    return huffman;
  }

  //hungarian algorithm
  
  std::vector<size_t> Hungarian() {
    std::vector<size_t> hungarian;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<size_t> u(nodes.size(), 0);
    std::vector<size_t> v(nodes.size(), 0);
    std::vector<size_t> p(nodes.size());
    std::vector<size_t> way(nodes.size());
    for (size_t i = 0; i < nodes.size(); i++) {
      p[0] = i;
      size_t j0 = 0;
      std::vector<size_t> minv(nodes.size(), INT_MAX);
      std::vector<bool> used(nodes.size(), false);
      do {
        used[j0] = true;
        size_t i0 = p[j0];
        size_t delta = INT_MAX;
        size_t j1;
        for (size_t j = 0; j < nodes.size(); j++) {
          if (!used[j]) {
            size_t cur = adjMatrix[i0][j] - u[i0] - v[j];
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
        for (size_t j = 0; j < nodes.size(); j++) {
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
      } while (j0 != 0);
    }
    for (size_t i = 0; i < nodes.size(); i++) {
      hungarian.push_back(p[i]);
    }
    return hungarian;
  }

  //graph matching
  
  std::vector<pair<size_t, size_t> GraphMatching() {
    //give back the mathing edges pairs
    std::vector<std::pair<size_t, size_t>> graphMatching;
    std::vector<std::vector<size_t>> adjMatrix = toAdjacencyMatrix();
    std::vector<size_t> matching(nodes.size(), -1);
    std::vector<bool> used(nodes.size(), false);
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (matching[nodes[i].neighbors[j]] == -1) {
          matching[i] = nodes[i].neighbors[j];
          matching[nodes[i].neighbors[j]] = i;
          used[i] = true;
          used[nodes[i].neighbors[j]] = true;
          break;
        }
      }
    }

    std::vector<size_t> p(nodes.size());
    std::vector<size_t> way(nodes.size());

    for (size_t i = 0; i < nodes.size(); i++) {
      if (!used[i]) {
        std::vector<size_t> minv(nodes.size(), INT_MAX);
        std::vector<bool> visited(nodes.size(), false);
        size_t j0 = i;
        size_t j1 = 0;
        do {
          visited[j0] = true;
          size_t i0 = matching[j0];
          size_t delta = INT_MAX;
          for (size_t j = 0; j < nodes.size(); j++) {
            if (adjMatrix[i0][j] - adjMatrix[i][j] < minv[j]) {
              minv[j] = adjMatrix[i0][j] - adjMatrix[i][j];
              way[j] = j0;
            }
            if (minv[j] < delta) {
              delta = minv[j];
              j1 = j;
            }
          }
          for (size_t j = 0; j < nodes.size(); j++) {
            if (visited[j]) {
              adjMatrix[p[j]] += delta;
              adjMatrix[j] -= delta;
            } else {
              minv[j] -= delta;
            }
          }
          j0 = j1;
        } while (matching[j0] != -1);
        do {
          size_t j1 = way[j0];
          matching[j0] = p[j0];
          p[j0] = j1;
          j0 = j1;
        } while (j0 != 0);
      }
    }

    for (size_t i = 0; i < nodes.size(); i++) {
      if (matching[i] != -1) {
        graphMatching.push_back(std::make_pair(i, matching[i]));
      }
    }

    return graphMatching;
  }
  //propery detection
  
  bool isEulerian() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] % 2 != 0) {
        return false;
      }
    }
    return true;
  }

  
  bool isHamiltonian() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] < nodes.size() / 2) {
        return false;
      }
    }
    return true;
  }

  
  bool isPlanar() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] > 5) {
        return false;
      }
    }
    return true;
  }

  
  bool isBipartite() {
    std::vector<size_t> color = GraphColoring();
    for (size_t i = 0; i < nodes.size(); i++) {
      for (size_t j = 0; j < nodes[i].neighbors.size(); j++) {
        if (color[i] == color[nodes[i].neighbors[j]]) {
          return false;
        }
      }
    }
    return true;
  }

  
  bool isComplete() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != nodes.size() - 1) {
        return false;
      }
    }
    return true;
  }

  
  bool isTree() {
    std::vector<size_t> degree = DegreeCentrality();
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
    std::vector<size_t> degree = DegreeCentrality();
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
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != degree[0]) {
        return false;
      }
    }
    return true;
  }

  
  bool isCyclic() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != 2) {
        return false;
      }
    }
    return true;
  }

  
  bool isAcyclic() {
    std::vector<size_t> degree = DegreeCentrality();
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

  
  bool isDirected() {
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
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] != 1) {
        return false;
      }
    }
    return true;
  }

  
  bool isConnected() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] == 0) {
        return false;
      }
    }
    return true;
  }

  
  bool isStronglyConnected() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] == 0) {
        return false;
      }
    }
    return true;
  }

  
  bool isBiconnected() {
    std::vector<size_t> degree = DegreeCentrality();
    for (size_t i = 0; i < nodes.size(); i++) {
      if (degree[i] == 0) {
        return false;
      }
    }
    return true;
  }

  
  bool isNPartite() {
    std::vector<size_t> color = GraphColoring();
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
};
