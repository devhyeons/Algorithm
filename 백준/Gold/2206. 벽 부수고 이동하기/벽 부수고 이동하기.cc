#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;


// 이동 중 한 개의 벽 부술 수 있다면, 한개 부수고 이동 가능
// N : 1000, M : 1000 --> 백트래킹으로 1개 선택하는건 매우 시간 복잡도가 안맞을거같은데.. 2초라도,,

// 맵 주어질 때, 최단 경로 구하는 프로그램 작성
// 최단 거리 출력, 불가능하면 -1 출력.
int dist[1001][1001][2];
bool visited[1001][1001][2] = {false};
int board[1001][1001];


int n,m;
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int ans = -1;

struct Cell{
    int x,y, broken;
};


void bfs(int sx, int sy){
    queue<Cell> q;
    q.push({sx,sy, false});
    dist[sx][sy][0] = 1;
    visited[sx][sy][0] = true;

    while(!q.empty()){
        auto [x,y,b] = q.front();
        q.pop();

        if (x == n-1 && y == m-1){
            ans = dist[x][y][b];
            return;
        }

        for (int dir =0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx < 0 || ny < 0 || nx >=n || ny >=m ) continue;
            if (board[nx][ny] == 1 && b==0 && !visited[nx][ny][1]) {
                dist[nx][ny][1] = dist[x][y][b] + 1;
                visited[nx][ny][1] = true;
                q.push({nx,ny,1});
            }

            else if (board[nx][ny] == 0 && !visited[nx][ny][b]) {
                dist[nx][ny][b] = dist[x][y][b] + 1;
                visited[nx][ny][b] = true;
                q.push({nx,ny,b});
            }
        }
    }

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i=0; i<n; i++){
        string s;
        cin >> s;
        for (int j=0; j<s.size(); j++){
            int c = s[j]-'0';
            board[i][j] = c;
        }
    }

    bfs(0,0);
    cout << ans << "\n";

    return 0;
}
