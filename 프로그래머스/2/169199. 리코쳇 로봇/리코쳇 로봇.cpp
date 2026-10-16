#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

// 시작위치 출발 -> 목표 위치 정확하게 멈추기 위해 최소 몇번 이동?
// 상, 하, 좌,우 중 한 방향으로 이동 가능
// 게임판 위의 장애물이나, 게임판 가장자리까지
// 부딪힐때까지 미끄러져 움직이는 것을 한번의 이동으로 정의

// "." = 빈공간
// "R" = 로봇 처음 위치
// "D" = 장애물 위치
// "G" = 목표지점

// 말이 목표위치까지 도달하는데 최소 몇번 이동해야하는지 return
// 목표 도달 불가능시 -1 return. 

// board<= 10^2, bfs로 while로 최종 중지 위치만 visited해서 푸는 원리

int dist[101][101];
int n,m;
pair<int,int> r; 
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

void initDist(){
    for(int i=0; i<101; i++){
        for (int j=0; j<101; j++){
            dist[i][j] = -1; 
        }
    }
}

int bfs(vector<string> board, int startX, int startY){
    dist[startX][startY] = 0;
    queue<pair<int,int>> q;
    q.push({startX, startY});
    
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        
        if (board[x][y] == 'G'){
            return dist[x][y];
        }
        
        for (int dir =0; dir<4; dir++){        
            int nx = x;
            int ny = y;
            while(1){
                int tx=  nx + dx[dir];
                int ty = ny + dy[dir];
                
                if (tx < 0 || ty < 0 || tx >= n || ty >= m ){
                    break;
                }
                
                if (board[tx][ty] == 'D'){
                    break;
                }
                
                nx = tx;
                ny = ty;
            }
            
            if (dist[nx][ny] != -1){
                continue;
            }
            
            dist[nx][ny] = dist[x][y] +1;
            q.push({nx,ny});
        }
    }
    return -1;
}

int solution(vector<string> board) {
    int answer = 0; 
    n = board.size();
    m = board[0].size(); 
    
    initDist();
    
    for (int i=0; i<board.size(); i++){
        for (int j=0; j<board[0].size(); j++){
            if (board[i][j] == 'R'){
                r = {i,j};
                break;
            }
        }
    }
    
    answer = bfs(board, r.first, r.second);
    
    return answer;
}