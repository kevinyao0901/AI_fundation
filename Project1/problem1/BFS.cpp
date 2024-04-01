#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 100010;

int n, m;
vector<int> h[N]; // �ڽӱ�洢
int d[N]; // d����Ϊ����
queue<int> q; // ʹ��STL��queue��Ϊ���У�ʹ��BFS��

void add(int a, int b) // ����һ����
{
    h[a].push_back(b);
}

int bfs() // ���ѿ�ʼ��
{
    q.push(1); // ��ʼ������

    memset(d, -1, sizeof d); // ��ʼ������, -1��ʾû�б�������

    d[1] = 0; // �õ�һ��������Ϊ��������

    while (!q.empty()) // ������ѿ�ܣ����в�Ϊ��ʱ��
    {
        int t = q.front(); q.pop(); // ȡ����ͷ

        for (auto j : h[t]) // ��չ����ÿһ���ٱ�
        {
            if (d[j] == -1) // ����jû����չ��
            {
                d[j] = d[t] + 1; // �洢j�����ľ��룬���ұ��Ϊ�Ѿ����ʹ�
                q.push(j); // ��j���
            }
        }
    }

    return d[n]; // ����1�ŵ㵽n�ŵ����̾���
}

int main()
{
    cin >> n >> m;

    while (m--)
    {
        int a, b;
        cin >> a >> b;
        add(a, b); // ����һ����a��b����Ϊ1�ı�
    }

    cout << bfs() << endl;

    return 0;
}
