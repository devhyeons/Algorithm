#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// 1. graph 에 각 값 담기 
// 2. 시작지점을 각각 s,a,b로 한 -> dijkstra 진행
// 3. 합승지점을 1 ~ n 까지 전부 해서, 그 때의 min 구하기

// <c++ 다익스트라 구현방법>
// priority_queue,  dist[]로 시작점 -> 해당 정점 간 도착 total 최소 거리 작성.

// point. 
// priority_queue<pair<int,int>> 에서
// greater 시 어떤 값 기준 sort? --> first기준 

vector<pair<int,int>> graph[201];

int c_n;

vector<int> dijkstra(int start){
    
    vector<int> dist(c_n+1, INT_MAX);
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.push({0,start});
    
    while(!pq.empty()){
        auto [w,cur] = pq.top();
        pq.pop();
        
        if (w < dist[cur]) continue;
        
        for (auto [d, v] : graph[cur]){
            if (dist[v] > dist[cur] + d) {
                dist[v] = dist[cur] + d;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INT_MAX;
    c_n = n;
    
    for (int i=0; i<fares.size(); i++){
        int v = fares[i][0];
        int u = fares[i][1];
        int w = fares[i][2];
        
        graph[v].push_back({w,u});
        graph[u].push_back({w,v});
    }
    
    auto distS = dijkstra(s);
    auto distA = dijkstra(a);
    auto distB = dijkstra(b);
    
    for (int i=1; i<=n; i++){
        answer = min(answer, distS[i]+distA[i]+distB[i]);
    }
    
    
    return answer;
}