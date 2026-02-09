#include <iostream>
#include <algorithm>

using namespace std;

// 공이 있을 때, 같은 색으로 이루어진 사이클을 찾는 것이 핵심
// 게임판의 상태가 주어질 때 사이클이 존재하는지 아닌지 구해보기.


// 사이클이 존재하면 YES
// 없으면 NO 출력

int n,m;
int board[51][51];
bool visited[51][51];
bool finished[51][51];
bool flag = false;

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

char input;

void dfs(int x, int y, int px, int py, int depth){
    for (int dir =0; dir<4; dir++){
        int nx = x + dx[dir];
        int ny = y + dy[dir];

        if (nx < 0 || ny < 0 || nx >=n || ny >=m ) continue;
        if (board[nx][ny] != board[x][y]) continue;

        if (nx == px && ny == py) continue;

        if (visited[nx][ny]){
            if (depth >= 4){
                cout << "Yes";
                exit(0);
            }
        }
        else {
            visited[nx][ny] = true;
            dfs(nx,ny,x,y,depth+1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> input;
            board[i][j] = input-'A';
        }
    }

    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (!visited[i][j]){
                visited[i][j] = true;
                dfs(i,j,-1,-1,1);
            }
        }
    }
    
        cout << "No";

    return 0;
}