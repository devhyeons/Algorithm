#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <climits>
#include <cmath>
#include <queue>

using namespace std;

vector<int> graph[101];
pair<int,int> deleted_w;
bool visited[101];
int c_n;

int bfs(int start){
    queue<int> q;
    q.push(start);
    visited[start] = true;

    int cnt =0;
    
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        
        for (auto v : graph[cur]){
            if (!visited[v]){
                if ((deleted_w.first == cur && deleted_w.second == v) ||( deleted_w.first == v && deleted_w.second == cur)) {
                    continue;
                }
                q.push(v);
                    visited[v] = true;
                    cnt ++; 
            }
        }
    }  
    return cnt;
}

void initVisited(){
    for (int i=0; i<=c_n; i++){
        visited[i] = false;
    }
}

int findW(){

    vector<int> cnts;
    initVisited();
    
    for (int i=1; i<=c_n; i++){
        if (!visited[i]) {
            int cnt = bfs(i);
            cnts.push_back(cnt);
        }
    }
    
    if (!cnts.empty()) {
        return abs(cnts[1]-cnts[0]);
    }
    return -1; 
}

int solution(int n, vector<vector<int>> wires) {
    int answer = INT_MAX;
    c_n = n;
    
    for (int i=0; i<wires.size(); i++){
        int v = wires[i][0];
        int u = wires[i][1];
        
        graph[v].push_back(u);
        graph[u].push_back(v);
    }
    
    for (int i=0; i<wires.size(); i++){
        deleted_w = {wires[i][0], wires[i][1]};
        answer = min(answer, findW());
    }
    
    return answer;
}