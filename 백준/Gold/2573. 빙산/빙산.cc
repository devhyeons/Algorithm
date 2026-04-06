#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// 각 부분별 높이 정보가 배열의 각 칸 양의 정수로 저장
// 빈 칸은 다 0

// 일년마다 칸의 동서남북 네 방향 붙어있는 0 갯수만큼 줄어듬.
// 단 0보다 더 줄어들지는 않는다.

// 한 덩어리 빙산 주어리 때, 두 덩어리 이상으로 분리되는 최소 시간은?

int n,m;
int board[301][301];

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
bool visited[301][301] = {false};

void initVisited(){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            visited[i][j] = false;
        }
    }
}

void bfs(int sx, int sy){
    queue<pair<int,int>> q;
    q.push({sx,sy});
    visited[sx][sy] = true;

    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();

        for (int dir=0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx < 0 || ny < 0 || nx >=n || ny >=m ) continue;
            if (board[nx][ny] == 0 ) continue;
            if (visited[nx][ny]) continue;
            q.push({nx,ny});
            visited[nx][ny] = true;
        }
    }
}

bool checkSperate(){
    int cnt = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (board[i][j] != 0 && !visited[i][j]){
                if (cnt >= 1) {
                    return true;
                }
                bfs(i,j);
                cnt++;
            }
        }
    }

    initVisited();
    return false;
}

bool checkAll(){
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (board[i][j] != 0) return false;
        }
    }
    return true;
}

void sperate(){

    int tmp[301][301]; //지워야 할 갯수.

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            tmp[i][j] = 0;
        }
    }

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (board[i][j] != 0){
                for (int dir = 0; dir<4; dir++){
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];

                    if (nx < 0 || ny < 0 || nx >=n || ny >=m) continue;
                    if(board[nx][ny] == 0){
                        tmp[i][j] ++;
                    }
                }
            }
        }
    }

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (board[i][j] != 0) {
                board[i][j] = max(0, board[i][j] - tmp[i][j]);
            }
        }
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> board[i][j];
        }
    }

    // 첫 빙산 분리되는 최초시간은?
    // 만일 빙산이 다 녹을 때 까지 분리되지 않는다면 0 출력

    int cnt = 0;

    while(!checkAll()){
        if (checkSperate()){
            cout << cnt << "\n";
            return 0;
        }
        cnt++;
        sperate();
    }

    cout << 0 << "\n";

    return 0;
}