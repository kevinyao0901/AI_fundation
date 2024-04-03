#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

struct Node {
    int id;
    int dist;
    Node(int i, int d) : id(i), dist(d) {}
    bool operator<(const Node& other) const {
        return dist > other.dist; // 用于小顶堆
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<Edge>> graph(n + 1);
    vector<int> dist(n + 1, numeric_limits<int>::max());
    vector<bool> visited(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c);
    }

    priority_queue<Node> pq;
    dist[1] = 0;
    pq.push(Node(1, 0));

    while (!pq.empty()) {
        int u = pq.top().id;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;

            if (!visited[v] && dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push(Node(v, dist[v]));
            }
        }
    }

    if (dist[n] == numeric_limits<int>::max())
        cout << -1;
    else
        cout << dist[n];

    return 0;
}
