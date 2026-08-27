#include <string>
#include <set>
#include <algorithm>
#include <vector>

using namespace std;

// info : 0 = 양, 1= 늑대 (루트는 항상 양)

vector<vector<int>> g; 
vector<int> cand;
bool visited[18]; //이미 방문 했는지 여부 확인 (set에 한번 더 넣지 않기 위함)
int answer = 0;

void dfs(vector<int> &info, int sheepCnt, int wolfCnt, vector<int> cand){
    answer = max(answer, sheepCnt);
    for (int i=0; i<cand.size(); i++){
        int v = cand[i];
        if (visited[v]) continue;
        
        int ns = sheepCnt + (info[v] == 0);
        int nw = wolfCnt + (info[v] == 1);
        if (ns <= nw) continue; 
        
        visited[v] = true;
        
        vector<int> nextCand = cand;
        nextCand.erase(nextCand.begin() + i);
        for (int nextV : g[v]){
            nextCand.push_back(nextV);
        }
        
        dfs(info,ns,nw,nextCand);
        
        visited[v] = false;
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    g.resize(info.size());
    
    // 부모 -> 자식 간선 연결 
    for (int i=0; i<edges.size(); i++){
        int startV = edges[i][0];
        int endV = edges[i][1];
        
        g[startV].push_back(endV);
    }
    
    for (int i=0; i<18; i++){
        visited[i] = false;
    }
    
    
    vector<int> cand = {0};
    
    dfs(info,0,0,cand);
    
    return answer;
}