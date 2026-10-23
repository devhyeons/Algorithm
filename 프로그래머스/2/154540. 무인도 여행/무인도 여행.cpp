#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

// 지도에는 바다와 무인도들에 대한 정보 표시돼어있다.
// 각 칸 = 'X' or 1 ~ 9
// 'X' : 바다
// 숫자 : 무인도
// 상하좌우 연결 땅 : 하나의 무인도 이룸
// 각 칸에 적힌 숫자 : 식량 
// 상하좌우 연결된 칸에 적힌 모두 합한 값 = 무인도 최대 머무를수있는 기간.

// 각 섬에 최대 며칠씩 머물수있는 확인 후 > 배열에 담아 return
// if)지낼 수 있는 무인도 없으면 -1 배열 return

bool visited[101][101] = {false};
int board[101][101];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int n,m;

int bfs(int sx, int sy){
    queue<pair<int,int>> q;
    q.push({sx,sy});
    visited[sx][sy] = true;
    
    int cnt = board[sx][sy];
    
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        
        for (int dir =0; dir < 4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if (visited[nx][ny] || board[nx][ny] == -1) continue;
            
            q.push({nx,ny});
            visited[nx][ny] = true;
            cnt = cnt + board[nx][ny];
        
        }
    }
    return cnt;
}

vector<int> solution(vector<string> maps) {
    vector<int> answer;
    
    n = maps.size();
    m = maps[0].size();
    
    for (int i=0; i<maps.size(); i++){
        for (int j=0; j<maps[0].size(); j++){
            visited[i][j] = false;
            if (maps[i][j] == 'X'){
                board[i][j] = -1;
            }
            else {
                board[i][j] = maps[i][j] - '0';
            }
        }
    }
    
    
    for (int i=0; i<maps.size(); i++){
        for (int j=0; j<maps[0].size(); j++){
            if (board[i][j] != -1 && !visited[i][j]){
                int cnt = bfs(i,j);
                if (cnt > 0) {
                    answer.push_back(cnt);
                }
            }
        }
    }
    
    if (answer.empty()){
        answer.push_back(-1);
        return answer;
    }
    
    sort(answer.begin(), answer.end());
    
    return answer;
}