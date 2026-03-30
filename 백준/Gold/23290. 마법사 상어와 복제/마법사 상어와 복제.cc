#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// 가장 윗 칸 (1,1), 가장 오른쪽 아래 (4,4)

// 격자에는 물고기 M마리 있다.
// 각 물고기 격자에 칸 하나에 들어가 있음, 이동 방향 갖고 있음
// 이동방향은 8가지 중 하나

// 마법사 상어도 연습을 위해 들어가있다.
// 상어도 격자 한 칸에 들어가있다.

// 둘 이상의 물고기가 같은 칸에 있을 수 있음, 마법사 상어와 물고기도 같은 칸 가능

// 다음 작업 순차적 이루어짐

// 1. 상어가 모든 물고기에게 복제 마법 시전 (아래 5번에서 물고기 복제됨)
// 2. 모든 물고기가 한 칸 이동한다.
// 2-1) 상어가 있는 칸, 물고기의 냄새가 있는 칸, 격자 범위 벗어나는 곳 이동 x
// 2-2) 자신이 갖고 있는 이동방향이 이동할 수 있는 칸을 향할 때 까지 45도 회전
// 2-3) 이동 가능 칸 없으면 -> 이동 x
// 그 외는 이동

// 3.상어가 연속해서 3칸 이동.
// 현재칸에서 상하좌우 인접 칸으로 이동할 수 있다.
// 연속해서 이동 하는 중, 격자 범위 벗어나는 칸 있으면 그 방법은 불가능 이동 방법
// 연속 이동 중 상어가 물고기 있는 칸으로 이동하면, 그 칸에 있는 모든 물고기는 격자 제외
// 제외되는 모든 물고기는 물고기 냄새를 남긴다.
// 가능한 방법중 제외되는 물고기의 수가 가장 많은 방법으로 이동
// 그러한 방법이 여러개일 경우 사전 순 가장 앞서는 방법

// 4. 두번 전 연습에서 생긴 물고기의 냄새가 격자에서 사라진다.
// 5. 모든 복제된 물고기는 1에서의 위치 방향 그대로 갖는다.

int m, s;

int dx8[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dy8[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

// 상, 좌, 하, 우 우선순위
int dx4[5] = {0,-1, 0, 1, 0};
int dy4[5] = {0,0, -1, 0, 1};

int board[4][4][8]; // 물고기 (x,y)에 방향 d 가진 물고기 개수
int smell[4][4]; // 해당 칸의 냄새 남은 시간 -> 물고기 죽으면 값 설정 후, 매 턴마다 감소
int sx, sy; //상어 위치
int copyBoard[4][4][8];

struct Loca {
    int x, y, dir;
};

void copyFishes() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 8; k++) {
                copyBoard[i][j][k] = board[i][j][k];
            }
        }
    }
}


void moveFish() {
    int tmpBoard[4][4][8] = {0,};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 8; k++) {
                if (board[i][j][k] != 0){
                    bool moved = false;
                    for (int step=0; step<8; step++) {
                        int nextDir = ((k - step + 8) % 8);
                        int nx = i + dx8[nextDir];
                        int ny = j + dy8[nextDir];

                        if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
                        if (nx == sx && ny == sy) continue;
                        if (smell[nx][ny] != 0) continue;
                        tmpBoard[nx][ny][nextDir] = board[i][j][k] + tmpBoard[nx][ny][nextDir];
                        moved = true;
                        break;
                    }

                    if(!moved){
                        tmpBoard[i][j][k] = board[i][j][k] + tmpBoard[i][j][k];
                    }
                }
            }
        }
    }

    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            for (int k=0; k<8; k++){
                board[i][j][k] = tmpBoard[i][j][k];
            }
        }
    }
}

int maxFish = -1;
vector<int> bestPath;
bool visited[4][4] = {false};

void dfsShark(int x, int y, int depth, int fishSum, vector<int>& path){
    if (depth == 3){
        if (maxFish < fishSum){
            maxFish = fishSum;
            bestPath = path;
        }
        return;
    }

    for (int i=1; i<=4; i++){
        int nx = x + dx4[i];
        int ny = y + dy4[i];

        int addFish = 0 ;
        if (nx < 0 || ny < 0 || nx >= 4 || ny >= 4) continue;
        bool alreadyVisited = visited[nx][ny];

        if (!alreadyVisited) {
            for (int d = 0; d < 8; d++) addFish+= board[nx][ny][d];
        }

        visited[nx][ny] = true;
        path.push_back(i);

        dfsShark(nx,ny,depth+1, fishSum+addFish, path);

        path.pop_back();
        visited[nx][ny] = alreadyVisited;
    }
}

void moveShark(int turn) {
    maxFish= -1;
    bestPath.clear();
    
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            visited[i][j] = false;
        }
    }

    vector<int> path;
    dfsShark(sx,sy,0,0,path);

    for (int dir : bestPath){
        sx = sx + dx4[dir];
        sy = sy + dy4[dir];

        int fishCell = 0;
        for (int d = 0; d<8; d++){
            fishCell = fishCell + board[sx][sy][d];
        }

        if (fishCell > 0){
            for (int d=0; d<8; d++){
                board[sx][sy][d] = 0;
            }
            smell[sx][sy] = turn;
        }
    }
}

void eraseSmell(int curTurn) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (smell[i][j] > 0 && curTurn - smell[i][j] == 2) {
                smell[i][j] = 0;
            }
        }
    }
}

void duplication() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 8; k++) {
                board[i][j][k] = board[i][j][k] + copyBoard[i][j][k];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> s;

    int x, y, dir;
    for (int i = 0; i < m; i++) {
        cin >> x >> y >> dir;
        x--;
        y--;
        dir--;
        board[x][y][dir]++;
    }

    cin >> sx >> sy;
    sx--; sy--;

    for (int i = 1; i <= s; i++) {
        // 1. 상어가 물고기 복제
        copyFishes();

        // 2. 물고기 이동
        moveFish();

        // 3. 상어 연속3칸 이동
        moveShark(i);

        // 4. 두번 전 연습 물고기 냄새 격자 사라짐
        eraseSmell(i);

        // 5. 복제 완료
        duplication();
    }


    int ans = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 8; k++) {
                if (board[i][j][k] != 0) {
                    ans = board[i][j][k] + ans;
                }
            }
        }
    }

    cout << ans << "\n";

    return 0;
}