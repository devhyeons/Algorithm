#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <unordered_set>

using namespace std;

// 세로길이 n, 가로길이 M
// 석유는 여러 덩어리로 나눠 묻혀있다.
// 시추관을 수직으로 단 하나만 뚫을 수 있을 때
// 가장 많은 석유를 뽑을 수 있는 시추관 위치는?

// 열 하나를 관통, 열과 열 사이는 불가능

// 시추관이 뽑을 수 있는 석유량 = 시추관이 지나는 석유 덩어리 크기들의 합값

// 시추관 하나 설치해서 뽑을 수 있는 가장 많은 석유량 return solution

// n*m <= 500*500
// bfs 후에 brute force하게 풀어도 시간복잡도 가능으로 보여진다.

int board[501][501];
bool visited[501][501];

vector<vector<int>> cl;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int n,m;
int cnts[501*501];

void bfs(int idx, int targetX, int targetY){
    
    queue<pair<int,int>> q;
    q.push({targetX, targetY});
    visited[targetX][targetY] = true;
    board[targetX][targetY] = idx;
    int cnt = 0;
    
    while(!q.empty()){
        auto[x,y] = q.front();
        cnt ++;
        q.pop();
        
        for (int dir =0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx <0 || ny < 0 || nx >=n || ny >= m){
                continue;
            }
            if (visited[nx][ny] || cl[nx][ny] == 0){
                continue;
            }
            
            board[nx][ny] = idx;
            visited[nx][ny] = true;
            q.push({nx,ny});
        }
    }
    cnts[idx] = cnt;
    return;
}

int solution(vector<vector<int>> land) {
    int answer = 0;
    int idx = 1;
    n = land.size();
    m = land[0].size();
    cl = land;
    
    for (int i=0; i<land.size(); i++){
        for (int j=0; j<land[0].size(); j++){
            if (!visited[i][j] && land[i][j] == 1){
                bfs(idx, i,j);
                idx++;
            }
        }
    }

    for (int i=0; i<land[0].size(); i++){
        unordered_set<int> us;
        for (int j=0; j<land.size(); j++){
            if (board[j][i] != 0){
                us.insert(board[j][i]);
            }
        }
        
        int total  = 0;
        for (auto s : us){
            total = total + cnts[s];
        }
        
        answer = max(answer, total);
    }
    return answer;
}