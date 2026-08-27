#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 1부터 n까지 서로다른 번호 매겨진 등대 n 존재
// 등대 - 등대 오가는 뱃길 n-1개 존재
// 어느 등대에서 출발하든 -> 모든 등대까지 이동가능

// 한 뱃길의 양쪽 끝 등대 중 적어도 하나는 켜져있게 등대 켜야 함.
// 등대 갯수 n, 각 뱃길 연결 lighthouse 있을 때
// 윤성이가 켜두어야 하는 등대 갯수의 최솟값은?

vector<vector<int>> graph;
vector<vector<int>> dp;


void dfs(int u, int parent){
    dp[u][1] = 1; // u를 켜는 경우
    
    for (int v : graph[u]){
        if (v == parent) continue;
        
        dfs(v,u);
        
        // u를 끄면, 자식 v는 반드시 켜야한다.
        dp[u][0] = dp[u][0] + dp[v][1];
        
        // u를 켜면, 자식 v는 켜도되고, 꺼도 된다.
        dp[u][1] = dp[u][1] + min(dp[v][0], dp[v][1]);
    }
}


int solution(int n, vector<vector<int>> lighthouse) {
    int answer = 0;
    graph.assign(n+1, {});
    dp.assign(n+1, vector<int>(2,0));
    
    for (auto l : lighthouse){
        int u = l[0];
        int v = l[1];
        
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    // 아무 노드나 루트로 잡음..
    dfs(1,0);
    
    //1번을 키거나 끄거나..
    return min(dp[1][0], dp[1][1]);
}