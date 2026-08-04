#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

// 직사각형 미로에서 탈출하려고 한다.
// 각 칸 = 통로 or 벽으로 이루어짐
// 한 칸에는 미로 빠져나가는 문 있는데, 이 문은 레버 당겨서만 열수있음
// 레버는 통로들 중 한 칸에 있다.


// 즉 출발 -> 레버 -> 미로칸으로 이동 필요.
// 레버당기지 않았어도, 출구있는 칸 지날 수 있음

// 미로 나가는데 최소 걸리는 시간은?
// 만약 탈출 불가 시 -1 return 

// s: 시작
// E : 출구
// L : 레버
// O : 통로
// X : 벽

pair<int,int> target;
pair<int,int> exits;
pair<int,int> starts;

int dist[101][101];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};


void initDist(){
    for (int i=0; i<101; i++){
        for (int j=0; j<101; j++){
            dist[i][j] = -1;
        }
    }
}

int n,m;
vector<string> maps;

int bfs(pair<int,int> start, pair<int,int> target, bool isTarget){
    initDist();
    queue<pair<int,int>> q;
    auto [sx,sy] = start;
    q.push({sx,sy});
    dist[sx][sy] = 0;
    
    // isTarget = t : 레버찾기
    // isTarget = f : 출구찾기 
    
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        
        if (x == target.first && y==target.second){
            return dist[x][y];
        }
        
        for (int dir = 0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx < 0 || ny < 0 || nx >= n || ny >= m ) continue;
            if (dist[nx][ny] != -1) continue;
            if (maps[nx][ny] == 'X') continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx,ny});
        }
    }    
    
    return -1;
}

int solution(vector<string> mapss) {
    int answer = 0;
    maps = mapss;
    n = maps.size();
    m = maps[0].size();
    
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (maps[i][j] == 'S'){
                starts = {i,j};
            }
            else if (maps[i][j] == 'E'){
                exits = {i,j};
            }
            
            else if (maps[i][j] == 'L'){
                target = {i,j};
            }
        }
    }
    
    // bfs (start -> target)
    int tSum = bfs(starts, target,true);
    if( tSum != -1){
        answer = answer + tSum;
    } else {
        return -1;
    }
    
    // bfs(target -> exit)
    int eSum = bfs(target, exits, false);
    if (eSum != -1){
        answer = answer + eSum;
    }
    else {
        return -1;
    }
    
    return answer;
}