#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

// 강철부대는 여러 지역에 흩어져서 임무 수행 중
// 강철부대가 위치한 지역을 포함한 지역은 유일 번호로 구분
// 두 지역간의 길을 통과하는데 걸리는 시간은 1로 동일

// 지도 정보 활용해서 최단시간으로 부대 복귀하고자 함.
// 각 부대원이 순서대로 강철부대에 복귀할 수 있는 최단시간 담은 배열 return
// 복귀 불가능한 부대원은 최단시간 -1로 설정
// bfs : 최단경로를 이용해서 찾기 dist 

int dist[100001]; //각 지역 접근 여부 저장
unordered_map<int,vector<int>> m;
int copyN, copyD;
vector<vector<int>> copyR;

int bfs(int start){
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int cnt = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if (cur == copyD) return dist[cur];
        for (auto a : m[cur]){
            if (dist[a] != -1) continue;
            q.push(a);
            dist[a] = dist[cur]+1;
        }
    }
    return -1;
}

void init(){
    for (int i=0; i<=copyN; i++){
        dist[i] = -1;
    }
}

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    copyN = n;
    copyD = destination;
    copyR = roads;
 
    for (int i=0; i<roads.size(); i++){
        m[roads[i][0]].push_back(roads[i][1]);
        m[roads[i][1]].push_back(roads[i][0]);
    }
    
    for (int i=0; i<sources.size(); i++){
        init();
        answer.push_back(bfs(sources[i]));
    }
 
    return answer;
}