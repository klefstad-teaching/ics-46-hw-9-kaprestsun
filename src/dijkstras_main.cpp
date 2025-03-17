#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <stack>
using namespace std;

int main(){
    Graph G;
    file_to_graph("src/small.txt", G);
    // G.addEdge(0, 1, 4);
    // G.addEdge(0, 2, 2);
    // G.addEdge(1, 2, 5);
    // G.addEdge(1, 3, 10);
    // G.addEdge(2, 3, 3);
    // G.addEdge(3, 4, 8);
    // G.addEdge(4, 5, 4);
    
    int source = 0;
    int destination = 5;
    vector<int> previous(G.numVertices, -1);


    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    vector<int> path = extract_shortest_path(distances, previous, destination);

    print_path(path, distances[destination]);

}