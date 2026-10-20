#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

// 물류창고에는 알파벳 대문자로 종류 구분 컨테이너
// n*m존재
// 특정 컨테이너 출고 요청 들어올 때, 지게차로 창고에서
// 접근 가능한 해당 종류의 컨테이너 모두 꺼냄.
// 접근 가능 컨테이너랑 : 4면중 적어도 1면이 창고 외부와 연결된 컨테이너 의미.

// 크레인 : 창고 외부와 연결되지 않는 컨테이너도 꺼낼 수 있음.
// 크레인 사용 시 요청된 종류 모든 컨테이너 꺼낼 수 있다.

// 요청 순서 : requests
// 모든 요청 순서대로 완료한 후 남은 컨테이너 수는?

// 알파벳 하나 : 지게차 (바깥 있는 것만 꺼냄.)
// 알파벳 두번 반복 : 크레인 활용 (모든 요청 컨테이너 꺼냄.)

// storage <= 25 * 10^2 
// requests <= 10^2 

struct State{
    int x,y;
    bool checked = false;
};

vector<State> loca[26];
char board[51][51];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int n,m;
void printBoard(){
    cout << "\n";
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";    
    }
}

bool bfs(int sx, int sy){
    bool visited[51][51];
    
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            visited[i][j] = false;
        }
    }
    queue<pair<int,int>> q;
    q.push({sx,sy});
    visited[sx][sy] = true;
    
    while(!q.empty()){
        auto[x,y] = q.front();
        q.pop();
        
        for (int dir = 0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            
            if (nx < 0 || ny < 0 || nx >= n || ny >= m) {
                return true;
            }
            
            if (visited[nx][ny]) continue;
            if (board[nx][ny] == '.') {
            
            visited[nx][ny] = true;
            q.push({nx,ny});
            }
        }
    }
    
    return false;
}

int solution(vector<string> storage, vector<string> requests) {
    int answer = 0;
    
    n = storage.size();
    m = storage[0].size();
    
    for (int i=0; i<storage.size(); i++){
        for (int j=0; j<storage[0].size(); j++){
            char c = storage[i][j];
            board[i][j] = c;
            loca[c-'A'].push_back({i,j, false});
        }
    }  
    
     for (auto r : requests){
         char rc = r[0];
         vector<pair<int,int>> candi;
         if (r.size() == 1){
            // 지게차  
             
             for (int i=0; i<loca[rc-'A'].size(); i++){
                auto [x,y,b] = loca[rc-'A'][i];
                 if (b) continue;
                 bool checked = bfs(x,y);

                 if (checked) {candi.push_back({x,y});
                        loca[rc-'A'][i].checked = true;
                              }
             }
             
             for (auto c : candi){
                 board[c.first][c.second] = '.';
             }
         }
        
         else if( r.size() >= 2){
            // 크레인
             
            for (int i=0; i<loca[rc-'A'].size(); i++){
                auto [x,y,b] = loca[rc-'A'][i];
                board[x][y] = '.';
                loca[rc-'A'][i].checked = true;
            }
         }
         
         //printBoard();
     }

    
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
           // cout << board[i][j] << " ";
            if (board[i][j] != '.'){
                answer ++;
            }
        }
        //cout << "\n";
    }
    
    return answer;
}