#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

int n,m;
int board[21][21];
pair<int,int> boj; // 기사님 백준 위치
int curEng;

struct Customer{
    int sx, sy;
    int lx, ly;
    bool isEnd = false; //이미 운반해준 손님인지 여부 체크
};

struct CandiCustomer{
    int num;
    int sx, sy;
    int lx, ly;
    int curDist;
};

Customer customers[402];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

int bfs(int sx, int sy, int lx, int ly){
    int dist[21][21];

    for (int i=0; i<21; i++){
        for (int j=0; j<21; j++){
            dist[i][j] = -1;
        }
    }

    queue<pair<int,int>> q;
    q.push({sx,sy});
    dist[sx][sy] = 0;

    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();

        if (x == lx && y == ly){
            return dist[x][y];
        }

        for (int dir=0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx < 0 || ny < 0 || nx >=n || ny >=n) continue;
            if (dist[nx][ny] != -1) continue;
            if (board[nx][ny] == 1) continue;
            q.push({nx,ny});
            dist[nx][ny] = dist[x][y] + 1;
         }
    }

    return dist[lx][ly];
}

bool compCandiCustomer(CandiCustomer a, CandiCustomer b){
    if (a.curDist != b.curDist){
        return a.curDist < b.curDist;
    }
    if (a.sx != b.sx){
        return a.sx < b.sx;
    }
    if (a.sy != b.sy){
        return a.sy < b.sy;
    }
}

CandiCustomer findShortCustomer(){
    int minDist = 500*500;
    vector<CandiCustomer> candi;
    for (int i=1; i<=m; i++){
        if (customers[i].isEnd) continue;
        int resDist = bfs(boj.first, boj.second,customers[i].sx, customers[i].sy);
        if (minDist >= resDist){
            minDist = resDist;
            candi.push_back({i,customers[i].sx, customers[i].sy,customers[i].lx, customers[i].ly,resDist});
        }
    }

    if (candi.empty()) return {-1,-1,-1,-1};
    sort(candi.begin(), candi.end(), compCandiCustomer);

    auto best = candi[0];

    return best;
}

bool moveTaxi(){
    // 1. 최단거리 승객 구하기(출발지)
    // - 행 작, 열 작
    auto bestC = findShortCustomer();
    if (bestC.curDist == -1) return false;

    // 2. 택시 이동 (택시 원래 위치 - 승객 출발지)
    if (curEng - bestC.curDist < 0){
        return false;
    }
    else {
        curEng = curEng - bestC.curDist;
    }

    // 3. 택시 이동 (승객 출발지 - 승객 목적지)
    // 그 승객으로 이동해서->목적지까지 이동해서 (최단경로로 이동)
    // 연료 1칸씩 소모시키기
    // 이 때 연료 부족하면 -> 실패, 업무 끝.
    // 연료 충분 시 -> 도착 후, 소모연료 2배 충전

    int moveDist = bfs(bestC.sx, bestC.sy, bestC.lx, bestC.ly);
    if (curEng - moveDist < 0){
        return false;
    }
    else{
        curEng = curEng - moveDist; // 연료 삭제
        curEng = curEng + (moveDist)*2; // 연료 충전
        customers[bestC.num].isEnd = true;
    }

    boj.first = bestC.lx;
    boj.second = bestC.ly;

    return true;
}

bool checkEng(){
    for (int i=1; i<=m; i++){
        if(!customers[i].isEnd) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x,y;
    int sx,sy,lx,ly;

    cin >> n >> m >> curEng;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> board[i][j];
            // 0 : 빈칸 , 1 : 벽
        }
    }

    cin >> x >> y;
    x--; y--;
    boj = {x,y};

    for (int i=1; i<=m; i++){
        cin >> sx >> sy >> lx >> ly;
        sx--; sy--; lx--; ly--;
        customers[i] = {sx,sy,lx,ly,false};
    }

    while(!checkEng()){
        // 택시 움직임.
        bool res = moveTaxi();
        if (!res) {
            cout << -1 << "\n";
            return 0;
        }
    }

    cout << curEng << "\n";
    return 0;
}