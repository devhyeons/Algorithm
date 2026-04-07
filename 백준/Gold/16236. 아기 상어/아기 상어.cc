#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;


// 물고기 M마리와 아기상어 1마리 있다.
// 한 칸에는 최대 1칸만 존재.

// 가장 처음 아기상어 크기 = 2
// 아기상어는 1초에 상하좌우 인접 한칸씩 이동

// 아기상어 = 자신크기보다 큰 물고기 칸 지나갈 수 없다.
// 이하는 다 가능.

// 아기상어는 자신의 크기보다 작은 물고기만 먹을 수 있다.
// 즉 크기가 같으면, 먹을수는 없지만 지나갈 수 있다.


// 상어 이동 결정
// 1. 더이상 먹을 수 없는 공간 x-> 끝
// 2. 먹을 수 있는 물고기 1마리 -> 그 물고기
// 3. 1마리 이상 -> 거리 가장 가까운 물고기
// 거리 : 지나가야하는 칸 갯수 최소
// 그런 물고기 많으면, r 최소, c 최소

// 물고기 먹으면 -> 그 칸 빈칸
// 아기 상어는 자신의 크기와 같은 수 물고기 먹을 때마다 = 크기 1 증가 ++

// 크기 2 : 물고기 2마리 먹으면 -> 크기 3됨.

// 공간의 상태 주어질 때 몇 초동안 물고기 잡아먹을 수 있는지 확인

// 9 : 아기 상어 위치


struct Shark{
    int sx,sy;
    int curSize = 2;
    int curEat = 0;
};

int board[21][21];
int n;
Shark baby;

int dx[4] = {-1,1,0,0};
int dy[4] = {0,0,-1,1};

struct candiFish{
    int fx,fy;
    int dist;
};


bool comp(candiFish a, candiFish b){
    if (a.dist != b.dist) return a.dist < b.dist;
    if (a.fx != b.fx){
        return a.fx < b.fx;
    }
    if (a.fy != b.fy){
        return a.fy < b.fy;
    }
}

void printBoard(){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int eatFish(Shark & baby){
    // 1. 이동 결정 .. 최소 값으로 ..
    int dist[21][21];

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            dist[i][j] = -1;
        }
    }

    queue<pair<int,int>> q;
    q.push({baby.sx,baby.sy});
    dist[baby.sx][baby.sy] = 0;

    vector<candiFish> candi;

    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();

        for (int dir =0; dir<4; dir ++){
            int nx = x + dx[dir];
            int ny  = y + dy[dir];

            if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if (board[nx][ny] > baby.curSize) continue;
            if (dist[nx][ny] != -1) continue;
            if (board[nx][ny] == baby.curSize || board[nx][ny] == 0){
                //지나갈수는 있느나 candi에 넣을 수는 없다.
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx,ny});
            }
            if (board[nx][ny] > 0 && board[nx][ny] < baby.curSize){
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx,ny});
                candi.push_back({nx,ny,dist[nx][ny]});
            }
        }
    }

    if (candi.empty()) return 0;

    sort(candi.begin(), candi.end(), comp);
    auto best =candi[0];

    int fishSize = board[best.fx][best.fy];

    board[baby.sx][baby.sy] = 0;
    board[best.fx][best.fy] = 9;
    baby.sx = best.fx;
    baby.sy = best.fy;

    baby.curEat = baby.curEat +1; //fishSize더하는게 아니라 ++1임 ㅠ 
    if (baby.curEat == baby.curSize){
        baby.curSize ++;
        baby.curEat = 0;
    }

    return best.dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> board[i][j];

            if (board[i][j] == 9){
                baby.sx = i;
                baby.sy = j;
            }
        }
    }

    int timeCnt = 0;

    while(1){
        auto fishCnt = eatFish(baby);
        if (fishCnt == 0) {
            cout << timeCnt << "\n";
            return 0;
        }
      
        timeCnt = timeCnt + fishCnt;
    }

    return 0;
}
