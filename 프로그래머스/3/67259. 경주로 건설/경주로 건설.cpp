#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 경주로 부지 N*N
// 각 격자칸 0 or 1로 채워짐, 0은 비어, 1은 채워짐
// 0-0에서, n-1/n-1까지 무사히 도달 가능하게 끊어지지 않은 경주로 건설

// 상하좌우 인접한 두 빈칸 연결해서 건설, 벽있는 칸에는 건설 불가능
// 좌우 or 상하 연결은 직선도로, 직선이 서로 직각으로 만나는 지점 = 코너
// 직선 하나 만들때는 100원 소모
// 코너 하나는 500원 소모

// 경주로 건설에 필요한 최소 비용 계산 

struct State {
    int x,y,cost,dir;
    bool operator<(State const& o) const {
        return cost > o.cost;  // 최소 힙: cost 작은 순으로 꺼냄
    }
};


int dist[26][26][4]; //좌표와 방향별 계산 cost 담는 배열
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
vector<vector<int>> copyB;
int n;

// 0,1,2,3
// 상,우,하,좌

bool checkDir(int curDir, int nxtDir){
    if (curDir == -1){
        return false;  
    }
    return (curDir%2) != (nxtDir%2);
}

int bfs(){
    priority_queue<State> pq;
    
    for (int dir=0; dir<4; dir++){
        dist[0][0][dir] = 0;
        pq.push({0,0,0,dir});
    }
    
    while(!pq.empty()){
        auto [x,y,cost,dirs] = pq.top();
        pq.pop();
        
        if (cost > dist[x][y][dirs])
            continue; // 이미 더 좋은 경로를 처리했다. 
        
        if (x == (n-1) && y == (n-1)) {
            return cost;
        }
        
        for (int dir=0; dir<4; dir++){
            int nx = x+dx[dir];
            int ny = y+dy[dir];
            
            if (nx < 0 || ny < 0 || nx >=n || ny >=n) continue;
            if (copyB[nx][ny] == 1) continue;
           
            int add = checkDir(dirs,dir) ? 600 : 100;
            int nc = cost + add;
    
            if (nc < dist[nx][ny][dir]){
                dist[nx][ny][dir] = nc;
                pq.push({nx,ny,nc,dir});
            }
        }
    }
    return -1;
}

void init(){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int d=0; d<4; d++) {
              dist[i][j][d] = 1e9;   
            }
        }
    }
}

int solution(vector<vector<int>> board) {
    n= board.size();
    init();
    copyB=board;
    return bfs();
}