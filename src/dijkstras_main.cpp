#include "dijkstras.h"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char * argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    Graph G;
    try {
        file_to_graph(argv[1], G);
    }catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);

    for (int destination = 0; destination < G.numVertices; ++destination) {
        vector<int> path = extract_shortest_path(distances, previous, destination);
        cout << source << " to " << destination << ": ";
        if (path.empty()) {
            cout << "No path found." << endl;
        }else{
            print_path(path, distances[destination]);
        }
    }
    return 0; 
}