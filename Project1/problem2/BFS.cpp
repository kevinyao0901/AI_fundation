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
    int r = blankPos / N, c = blankPos % N; // ����հ׸������λ��

    // �����ĸ�������ƶ�
    for (const auto& move : MOVES) {
        int nr = r + move[0], nc = c + move[1]; 
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) { 
            string nextState = state; 
            swap(nextState[r * N + c], nextState[nr * N + nc]); // �����հ׸�����ڸ��ӵ�ֵ
            nextStates.push_back(nextState); // �����ɵ�״̬���뵽��һ�����ܵ�״̬�б���
        }
    }

    return nextStates; 
}


int bfs(const string& start) {
    unordered_map<string, int> dist; // ��¼ÿ��״̬������ʼ״̬�ľ���
    queue<string> q; // ʹ�ö��н��й����������
    q.push(start); // ����ʼ״̬�������
    dist[start] = 0; 

    while (!q.empty()) { // �����зǿ�ʱ
        string currentState = q.front(); 
        q.pop(); 

        if (currentState == TARGET_STATE) return dist[currentState]; // �����ǰ״̬����Ŀ��״̬���򷵻ؾ���

        vector<string> nextStates = getNextStates(currentState); // ��ȡ��ǰ״̬����һ������״̬
        for (const string& nextState : nextStates) { // ������һ������״̬�б�
            if (!dist.count(nextState)) { 
                dist[nextState] = dist[currentState] + 1; // ������һ��״̬�ľ���
                q.push(nextState); 
            }
        }
    }

    return -1; // ����޷�����Ŀ��״̬���򷵻�-1
}

int main() {
    string start;
    for (int i = 0; i < N * N; i++) { // �����ʼ״̬
        char num;
        cin >> num;
        start += num;
    }
    cout << bfs(start) << endl; // ������·���Ĳ���
    return 0;
}
