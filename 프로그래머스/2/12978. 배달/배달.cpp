#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// n개의 마을로 이루어진 나라가 있다.
// 각 마을에는 1-n까지 번호가 각각 부여되어있음
// 양방향 통행 도로 있는데, 각 마을 이동 시 도로 지나야함
// 도로마다 걸리는 시간 다르다.
// 1번 마을에 있는 음식점에서, 각 마을로 음식 배달 하려 할때
// n개의 마을 중 k시간 이하로 배달 가능한 마을에서만 주문
// n=5, k=3

// 각 마을 연결하는 도로정보 road, 음식 배달 가능시간 k
// 음식 주문 받을 수 있는 마을 갯수 return 

// -> 그래프 최단거리 (다익스트라 활용 pq )

struct Edge{
    int v, w;
};

vector<Edge> graph[51]; 
int dist[51]; 

void initDist(){
    for (int i=0; i<51; i++){
        dist[i] = INT_MAX;
    }
}

void dijkstra(int starts){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, starts});
    dist[starts] = 0;
    
    while(!pq.empty()){
        // curW : 누적거리, curV : 정점번호
        auto [curW, curV] = pq.top();
        pq.pop();
        
        // 이미 더 짧은 거리로 갱신되었다면.
        if (curW > dist[curV]) continue;
        
        for (auto [u,w] : graph[curV]){
            if (dist[u] > curW + w){
                dist[u] = curW + w;
                pq.push({dist[u], u});
            }
        }
    }
     
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    
    for (auto r : road){
        graph[r[0]].push_back({r[1], r[2]});
        graph[r[1]].push_back({r[0], r[2]});
    }
    
    initDist();
    dijkstra(1);
    
    for (int i=1; i<=N; i++){
        if (dist[i] <= K) answer ++;
    }
    
    return answer;
}