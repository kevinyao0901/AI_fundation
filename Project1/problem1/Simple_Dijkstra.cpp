#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Edge {
    int to;
    int weight;
    int next;
};

const int MAX_NODES = 100000;
const int MAX_EDGES = 1000000;
const long long INF = numeric_limits<long long>::max();

int head[MAX_NODES];
long long dist[MAX_NODES];
bool visited[MAX_NODES];

Edge edges[MAX_EDGES];
int edgeCount = 0;

void addEdge(int from, int to, int weight) {
    edges[edgeCount] = { to, weight, head[from] };
    head[from] = edgeCount++;
}

int main() {
    int numNodes, numEdges;
    cin >> numNodes >> numEdges;

    for (int i = 0; i < MAX_NODES; ++i) {
        head[i] = -1;
        dist[i] = INF;
        visited[i] = false;
    }

    dist[1] = 0;
    for (int i = 0; i < numEdges; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        addEdge(from, to, weight);
    }

    int current = 1;
    while (!visited[current]) {
        visited[current] = true;
        for (int i = head[current]; i != -1; i = edges[i].next) {
            int neighbor = edges[i].to;
            int weight = edges[i].weight;
            if (!visited[neighbor] && dist[neighbor] > dist[current] + weight) {
                dist[neighbor] = dist[current] + weight;
            }
        }
        int nextNode = -1;
        long long minDist = INF;
        for (int i = 1; i <= numNodes; ++i) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                nextNode = i;
            }
        }
        current = nextNode;
    }

    if (dist[numNodes] == INF) {
        cout << -1;
    }
    else {
        cout << dist[numNodes];
    }

    return 0;
}
