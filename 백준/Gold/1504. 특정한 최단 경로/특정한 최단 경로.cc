#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

// 1->N까지 최단 거리 이동하려고 함.
// 반드시 두 정점을 통과해야 한다.

// 1~N번 정점까지 이동할 때, 반드시 두 정점 거치면서 최단경로 이동하는 프로그램은?

// a->에서 다른곳 갈때는 무조건 b를 선택해서 가도록 구하기..
// n<=800...

int graph[801][801];
int nxt[801][801]; //i->j갈때 가야할 노드는?

int n, e;
int nu, nv;


void initGraph() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            graph[i][j] = 1e8;
            nxt[i][j] = -1;
        }
    }

    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0;
    }
}


void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (graph[i][k] + graph[k][j] < graph[i][j]){
                    nxt[i][j] = nxt[i][k];
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

vector<int> path;

vector<int> getPath(int start, int end) {

    if (nxt[start][end] == -1) return {-1};

    int cur = start;

    while (cur != end) {
        path.push_back(cur);
        cur = nxt[cur][end];
        if (cur == -1) return {-1};
    }
    path.push_back(end);
    return path;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> e;

    int a, b, c;
    initGraph();

    for (int i = 0; i < e; i++) {
        cin >> a >> b >> c;
        graph[a][b] = c;
        graph[b][a] = c;
        nxt[a][b] = b;
        nxt[b][a] = a;
    }

    cin >> nu >> nv; // 반드시 거쳐야하는 곳.

    floyd();
    getPath(1,n);

//    for (int i = 1; i <= n; i++) {
//        for (int j = 1; j <= n; j++) {
//            cout << graph[i][j] << " ";
//        }
//        cout << "\n";
//    }

    if (path.size() == 1) {
        cout << -1 << "\n";
        return 0;
    }


    bool eu = false, ev = false;

    for (auto p: path) {
        if (p == nu) {
            eu = true;
        }
        if (p == nv) {
            ev = true;
        }
    }

    if (eu && ev) {
        cout << graph[1][n] << "\n";
    } else {
        if (graph[1][nu] + graph[nu][nv] + graph[nv][n] >= 1e8  &&graph[1][nv] + graph[nv][nu] + graph[nu][n] >= 1e8){
            cout << -1 << "\n";
            return 0;
        }

        cout << min(graph[1][nu] + graph[nu][nv] + graph[nv][n], graph[1][nv] + graph[nv][nu] + graph[nu][n]);
    }

    return 0;
}


//4 5
//1 2 2
//1 4 1
//2 3 7
//3 4 2
//2 4 4
//2 3