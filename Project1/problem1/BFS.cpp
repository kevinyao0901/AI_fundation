#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 100010;

int n, m;
vector<int> h[N]; // 邻接表存储
int d[N]; // d数组为距离
queue<int> q; // 使用STL的queue作为队列（使用BFS）

void add(int a, int b) // 插入一条边
{
    h[a].push_back(b);
}

int bfs() // 宽搜开始！
{
    q.push(1); // 初始化队列

    memset(d, -1, sizeof d); // 初始化距离, -1表示没有被遍历过

    d[1] = 0; // 让第一个点设置为遍历过的

    while (!q.empty()) // 经典宽搜框架（队列不为空时）
    {
        int t = q.front(); q.pop(); // 取出队头

        for (auto j : h[t]) // 扩展它的每一个临边
        {
            if (d[j] == -1) // 假如j没有扩展过
            {
                d[j] = d[t] + 1; // 存储j离起点的距离，并且标记为已经访问过
                q.push(j); // 将j入队
            }
        }
    }

    return d[n]; // 返回1号点到n号点的最短距离
}

int main()
{
    cin >> n >> m;

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        add(a, b); // 插入一条从a到b长度为1的边
    }

    cout << bfs() << endl;

    return 0;
}
