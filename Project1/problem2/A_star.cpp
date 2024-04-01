#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>

#define pis pair<int, string>

using namespace std;

string s, e = "12345678x";  // 初始状态和目标状态

unordered_map<string, int> dist;  // 存储每个状态到达目标状态的最短步数
unordered_map<string, pair<char, string>> pre;  // 存储每个状态的前驱状态和移动方式

int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };  // 上、下、左、右四个方向的移动

char op[4] = { 'u', 'd', 'l', 'r' };  // 移动方式对应的字符表示

int get(string str) {
    for (int i = 0; i < str.size(); i++)
        if (str[i] == 'x')
            return i;  // 获取空格的位置
    return -1;
}

int f(string str) {
    int res = 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] != 'x') {
            int value = str[i] - '1';  // 目标位置
            int a = value / 3, b = value % 3;
            int x = i / 3, y = i % 3;
            res += abs(a - x) + abs(b - y);  // 计算当前状态到目标状态的曼哈顿距离
        }
    return res;
}

void bfs() {
    priority_queue<pis, vector<pis>, greater<pis>> heap;  // 小顶堆，按步数和启发式函数值排序
    heap.push({ f(s), s });  // 初始状态入队
    dist[s] = 0;  // 初始状态到达目标状态的最短步数为0

    while (!heap.empty()) {
        string t = heap.top().second;
        heap.pop();
        if (t == e) return;  // 已经到达目标状态

        int d = dist[t];  // 当前状态的步数
        int p = get(t);  // 当前状态空格的位置
        int x = p / 3, y = p % 3;
        string temp = t;  // 当前状态的副本

        for (int i = 0; i < 4; i++) {  // 尝试四个方向移动
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3) {
                t = temp;
                swap(t[3 * a + b], t[3 * x + y]);  // 移动空格
                if (dist.count(t) == 0 || dist[t] > d + 1) {
                    dist[t] = d + 1;  // 更新步数
                    pre[t] = { op[i], temp };  // 记录前驱状态和移动方式
                    heap.push({ d + 1 + f(t), t });  // 入队
                }
            }
        }
    }
}

int main() {
    string str;
    for (int i = 0; i < 9; i++) {
        char x;
        cin >> x;
        s += x;  // 读入初始状态
        if (x != 'x')
            str += x;  // 不包括空格的数字序列
    }

    int cnt = 0;
    for (int i = 0; i < str.size(); i++)
        for (int j = i + 1; j < str.size(); j++)
            if (str[j] < str[i])
                cnt++;  // 统计逆序数

    if (cnt & 1)
        puts("unsolvable");  // 逆序数为奇数，无解
    else {
        bfs();  // 执行搜索
        string res;
        while (e != s) {
            res += pre[e].first;  // 按移动方式构造路径
            e = pre[e].second;  // 回溯前驱状态
        }
        reverse(res.begin(), res.end());  // 反转路径得到正确顺序
        cout << res << endl;
    }

    return 0;
}
