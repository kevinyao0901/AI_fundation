#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfsShortestPath(vector<vector<int>>& graph, int start, int end) {
    if (start == end) {
        return 0;
    }

    int numNodes = graph.size();
    vector<bool> visited(numNodes + 1, false);
    queue<pair<int, int>> q;
    q.push({ start, 0 });
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front().first;
        int distance = q.front().second;
        q.pop();

        if (node == end) {
            return distance;
        }

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                q.push({ neighbor, distance + 1 });
                visited[neighbor] = true;
            }
        }
    }

    return -1;
}

int main() {
    int numNodes, numEdges;
    cin >> numNodes >> numEdges;

    vector<vector<int>> graph(numNodes + 1);

    for (int i = 0; i < numEdges; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    int result = bfsShortestPath(graph, 1, numNodes);
    cout << result;

    return 0;
}
