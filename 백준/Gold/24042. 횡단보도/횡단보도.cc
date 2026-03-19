#include <iostream>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

// 교차로에는 사람이 지나갈 수 있는 개지역이 있고, 그 지역 사이를 잇는 몇개의 횡단보도가 있다.
// 횡단보도의 주기는 총 M분
// 1분마다 신호가 바뀐다.

// 횡단보도와 신호 정보가 주어질 때, 0분에서 1~N번 지역까지 가는 최소시간을 구하기.

int n,m;

struct Node{
    int end, cycle;
};

vector<Node> graph[100001];
long long dist[100001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin>>n;
    cin>> m;

    int a,b;
    for (int i=0; i<m; i++){
        cin >> a >> b;
        graph[a].push_back({b,i});
        graph[b].push_back({a,i});
    }

    for (int i=1; i<=n; i++){
        dist[i] = LLONG_MAX;
    }


    // 지그 도착 시간 t에서 다음 간선을 언제 탈 수 있을까?
    // 현재 시간 -> 다음 가능 시간으로 점프.

    // 시간에 따라 변하는 그래프

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    dist[1] = 0;
    pq.push({0,1}); // 거리, 도착 지점

    while(!pq.empty()){
        auto [d,u] = pq.top();
        pq.pop();

        // d : 현재 시간, u : 해당 정점.
        if (d > dist[u]) continue;

        for (auto &nextGraph : graph[u]){
            int v = nextGraph.end;
            int cycle = nextGraph.cycle;

            // 핵심 중요) 다음 가능한 시간 계산
            // -> 지금 시간 d에서 다음 가능한 cycle까지 얼마나 기다려야 하는가?

            long long wait = (cycle - (d%m) + m)%m;
            long long nextDist = d + wait+1; //항상 양수로 만들고자 (d%m)+m
            // 현재 위치 -> 목표 위치까지 가는 거리를 의미.

            if (dist[v] > nextDist){
                dist[v] = nextDist;
                pq.push({nextDist, v});
            }
        }
    }

    cout << dist[n] << "\n";

    return 0;
}