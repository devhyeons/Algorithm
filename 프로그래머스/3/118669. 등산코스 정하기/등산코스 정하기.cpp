#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

// n개의 지점으로 이루어져 있다.
// 각 지점은 1부터 n까지 번호가 붙어있으며
// 출입구, 쉼터, 산봉우리 이다.
// 각 지점은 양방향 통행 가능 등산로
// 서로 다른 지점 이동 시 등산로 이용해야 함
// 등산로별 이동하는데 일정 시간소요

// 등산코스를 따라 이동하는 중 쉼터 or 산봉우리를 방문할때마다 휴식 가능
// 휴식없이 이동해야하는 시간 중 
// 가장 긴 시간을 해당 등산코스의 intensity 

// xx산 출입구중 한곳 출발 -> 산봉우리 한곳 방문 -> 다리 원래 출입구
// 산봉우리는 반드시 1번만 포함되어야 한다.
// 이러면서 가장 intensity가 최소가 되는 등산코스는? 
// return : 산봉우리 번호, intensity최소 값.

// n<= 5 *10^4
// gates <= 5 * 10^4
// summits <= 5 * 10^4
// 시작점이 여러개인 = 다중 시작점 다익스트라
// 따라서 pq에 여러개 값을 초기에 넣고 시작.
// 현재까지 max intentsity중 Min을 구하는 문제.

unordered_set<int> us;
int dist [50001];
vector<pair<int,int>> graph[50001];
int cnt;

void initDist(){
    for (int i=0; i<=cnt; i++){
        dist[i] = INT_MAX;
    }
}

bool comp(pair<int,int> a, pair<int,int> b){
    if(a.second != b.second){
        return a.second < b.second;
    }
    return a.first < b.first;
}

pair<int,int> dijkstra(vector<int> gates){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    
    vector<pair<int,int>> candi;
    
    for (auto g : gates){
        pq.push({0,g});
    }
    
    while(!pq.empty()){
        auto [curW, curV] = pq.top();
        pq.pop();
        
        if (us.count(curV)){
            candi.push_back( {curV, curW});
            continue;
        }
        
        for (auto [u,w] : graph[curV]){
            int newDist = max(curW, w);
            if (dist[u] > newDist ){
                dist[u] = newDist;
                pq.push({dist[u], u});
            }
        } 
    }
    
    sort(candi.begin(), candi.end(), comp);
    return candi[0];
}


vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    vector<int> answer;
    // summits = 봉우리
    // gates = 게이트 수
    
    cnt = n;
    
    initDist();
    
    for (auto p : paths){
        int v = p[0];
        int u = p[1];
        int w = p[2];
        graph[v].push_back({u,w});
        graph[u].push_back({v,w});
    }
    
    for (auto s : summits){
        us.insert(s);
    }
    
    auto [nums, intensity] = dijkstra(gates);
    answer.push_back(nums);
    answer.push_back(intensity);

    return answer;
}