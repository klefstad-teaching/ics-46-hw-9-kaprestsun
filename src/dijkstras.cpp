#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>

using namespace std;
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous[source] = -1;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({source, 0});
    while(!minHeap.empty()){
        int u = minHeap.top().second;
        if(visited[u]) continue;
        visited[u] = true;
        for(Edge edge:G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if(!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    stack<int> path;
    vector<int> shortest;
    for (int i = destination; i != -1; i = previous[i]) {
        path.push(at);
    }
    while (!path.empty()) {
        path.push_back(shortest.top());
        shortest.pop();
    }
    return shortest;
}


void print_path(const vector<int>& v, int total){
    for(int i : v)
        std::cout << i << " ";
    std::cout << "Total cost is " << total << std::endl;
}
