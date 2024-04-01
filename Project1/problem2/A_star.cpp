#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <cmath>

#define pis pair<int, string>

using namespace std;

string s, e = "12345678x";  // ��ʼ״̬��Ŀ��״̬

unordered_map<string, int> dist;  // �洢ÿ��״̬����Ŀ��״̬����̲���
unordered_map<string, pair<char, string>> pre;  // �洢ÿ��״̬��ǰ��״̬���ƶ���ʽ

int dx[4] = { -1, 1, 0, 0 }, dy[4] = { 0, 0, -1, 1 };  // �ϡ��¡������ĸ�������ƶ�

char op[4] = { 'u', 'd', 'l', 'r' };  // �ƶ���ʽ��Ӧ���ַ���ʾ

int get(string str) {
    for (int i = 0; i < str.size(); i++)
        if (str[i] == 'x')
            return i;  // ��ȡ�ո��λ��
    return -1;
}

int f(string str) {
    int res = 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] != 'x') {
            int value = str[i] - '1';  // Ŀ��λ��
            int a = value / 3, b = value % 3;
            int x = i / 3, y = i % 3;
            res += abs(a - x) + abs(b - y);  // ���㵱ǰ״̬��Ŀ��״̬�������پ���
        }
    return res;
}

void bfs() {
    priority_queue<pis, vector<pis>, greater<pis>> heap;  // С���ѣ�������������ʽ����ֵ����
    heap.push({ f(s), s });  // ��ʼ״̬���
    dist[s] = 0;  // ��ʼ״̬����Ŀ��״̬����̲���Ϊ0

    while (!heap.empty()) {
        string t = heap.top().second;
        heap.pop();
        if (t == e) return;  // �Ѿ�����Ŀ��״̬

        int d = dist[t];  // ��ǰ״̬�Ĳ���
        int p = get(t);  // ��ǰ״̬�ո��λ��
        int x = p / 3, y = p % 3;
        string temp = t;  // ��ǰ״̬�ĸ���

        for (int i = 0; i < 4; i++) {  // �����ĸ������ƶ�
            int a = x + dx[i], b = y + dy[i];
            if (a >= 0 && a < 3 && b >= 0 && b < 3) {
                t = temp;
                swap(t[3 * a + b], t[3 * x + y]);  // �ƶ��ո�
                if (dist.count(t) == 0 || dist[t] > d + 1) {
                    dist[t] = d + 1;  // ���²���
                    pre[t] = { op[i], temp };  // ��¼ǰ��״̬���ƶ���ʽ
                    heap.push({ d + 1 + f(t), t });  // ���
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
        s += x;  // �����ʼ״̬
        if (x != 'x')
            str += x;  // �������ո����������
    }

    int cnt = 0;
    for (int i = 0; i < str.size(); i++)
        for (int j = i + 1; j < str.size(); j++)
            if (str[j] < str[i])
                cnt++;  // ͳ��������

    if (cnt & 1)
        puts("unsolvable");  // ������Ϊ�������޽�
    else {
        bfs();  // ִ������
        string res;
        while (e != s) {
            res += pre[e].first;  // ���ƶ���ʽ����·��
            e = pre[e].second;  // ����ǰ��״̬
        }
        reverse(res.begin(), res.end());  // ��ת·���õ���ȷ˳��
        cout << res << endl;
    }

    return 0;
}
