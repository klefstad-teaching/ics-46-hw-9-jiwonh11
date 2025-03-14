#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "dijkstras.h"

using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distances(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    using Node = pair<int, int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    distances[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(const auto& edge: G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;

    if (destination >= distances.size() || distances[destination] == INF) {
        return path; 
    }

    for(int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for(size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if(i < v.size() - 1) {
            cout << " -> ";
        }
    }
    cout << "\nTotal cost is " << total << endl;
}
