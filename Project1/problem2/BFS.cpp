#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

const int N = 3; 
const string TARGET_STATE = "12345678x"; 
const int MOVES[][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} }; 


vector<string> getNextStates(const string& state) {
    vector<string> nextStates; 
    int blankPos = state.find('x'); 
    int r = blankPos / N, c = blankPos % N; // 计算空白格的行列位置

    // 遍历四个方向的移动
    for (const auto& move : MOVES) {
        int nr = r + move[0], nc = c + move[1]; 
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) { 
            string nextState = state; 
            swap(nextState[r * N + c], nextState[nr * N + nc]); // 交换空白格和相邻格子的值
            nextStates.push_back(nextState); // 将生成的状态加入到下一步可能的状态列表中
        }
    }

    return nextStates; 
}


int bfs(const string& start) {
    unordered_map<string, int> dist; // 记录每个状态到达起始状态的距离
    queue<string> q; // 使用队列进行广度优先搜索
    q.push(start); // 将起始状态加入队列
    dist[start] = 0; 

    while (!q.empty()) { // 当队列非空时
        string currentState = q.front(); 
        q.pop(); 

        if (currentState == TARGET_STATE) return dist[currentState]; // 如果当前状态等于目标状态，则返回距离

        vector<string> nextStates = getNextStates(currentState); // 获取当前状态的下一步可能状态
        for (const string& nextState : nextStates) { // 遍历下一步可能状态列表
            if (!dist.count(nextState)) { 
                dist[nextState] = dist[currentState] + 1; // 计算下一步状态的距离
                q.push(nextState); 
            }
        }
    }

    return -1; // 如果无法到达目标状态，则返回-1
}

int main() {
    string start;
    for (int i = 0; i < N * N; i++) { // 输入初始状态
        char num;
        cin >> num;
        start += num;
    }
    cout << bfs(start) << endl; // 输出最短路径的步数
    return 0;
}
