#include <string>
using namespace std;

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,1,-1};
bool visited[11][11][11][11];
int ans;

int returnDir(char c){
    if (c == 'U') return 0;
    else if (c == 'D') return 1;
    else if (c == 'R') return 2;
    else return 3;
}

void dfs(int curX, int curY, int idx, string dirs){
    if (idx >= dirs.size()) return;
    
    int curDir = returnDir(dirs[idx]);
    int nx = curX + dx[curDir];
    int ny = curY + dy[curDir];
    
    if (nx < 0 || ny < 0 || nx > 10 || ny > 10) {
        dfs(curX, curY, idx + 1, dirs);
        return;
    }
    
    if (!visited[curX][curY][nx][ny]) {
        ans++;
        visited[curX][curY][nx][ny] = true;
        visited[nx][ny][curX][curY] = true;
    }
    dfs(nx, ny, idx + 1, dirs);
}

int solution(string dirs) {
    ans = 0;
    dfs(5, 5, 0, dirs);
    return ans;
}