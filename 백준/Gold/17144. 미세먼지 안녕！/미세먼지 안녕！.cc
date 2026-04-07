#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

// 공기 청정기는 항상 1번 열에 설치되어있고, 크기는 두 행 차지
// 공기청정기가 설치되어있지 않는 칸에는 먼지가 있고 먼지양은 칸 수

// 1초동안 일어나는 일
// 1. 미세먼지 확산 -> 모든 칸 동시에 일어남.
// (r,c) 미세먼지가 인접한 네 방향으로 확산
// 인접 방향에 공기청정기 있거나, 칸 없으면 그 방향으로는 확산 안일어남
// 확산되는 약은 기존/5 -> 소수점 버림
// 원래 칸에 남아있는 양은 (a- (a/5)*확산수))

// 2. 공기청정기 작동
// -> 위쪽은 반시계 순환
// -> 아래쪽은 시계순환

// 바람불면서 미세먼지 바람의 방향대로 한칸씩 이동
// 공기청정기에서 부는 바람은 미세먼지 없고, 정화된다.

// 방 정보 있을 때 T초 후 방에 남아있는 미세먼지 양은?

int r,c,t;

int board[51][51];
int dx[4]= {1,0,-1,0};
int dy[4] = {0,1,0,-1};


vector<pair<int,int>> airs;

void printBoard(){
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}


void spreadDust(){

    int tmp[51][51] = {0};

    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            if (board[i][j] > 0){
                int curDust = board[i][j];
                int cnt = 0;
                for (int dir =0; dir<4; dir++){
                    int nx = i + dx[dir];
                    int ny = j + dy[dir];

                    if (nx < 0 || ny < 0|| nx >= r || ny >=c) continue;
                    if (board[nx][ny] == -1) continue;

                    tmp[nx][ny] = tmp[nx][ny] + (curDust/5);
                    cnt ++;
                }
                tmp[i][j] = tmp[i][j] + (curDust - ((curDust/5) * cnt));
            }
        }
    }

    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            if (board[i][j] != -1){
                board[i][j] = tmp[i][j];
            }
        }
    }

    for (auto a :airs){
        board[a.first][a.second] = -1;
    }
}

void cleanAir(){

    int tmp[51][51] = {0};

    // <위쪽 순환>
    auto [tx, ty] = airs[0];

    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            tmp[i][j] = board[i][j];
        }
    }

    // 왼
    for (int i=tx-1; i>0; i--){
        tmp[i][0] = tmp[i-1][0];
    }
    tmp[0][0] = 0;

    // 위
    for (int i=0; i<c-1; i++){
        tmp[0][i] = tmp[0][i+1];
    }
    tmp[0][c-1]=0;


    //오른
    for (int i=0; i<tx; i++){
        tmp[i][c-1] = tmp[i+1][c-1];
    }
    tmp[tx][c-1] = 0;


    //아래
    for (int i=c-1; i>1; i--){
        tmp[tx][i] = tmp[tx][i-1];
    }
    tmp[tx][1] = 0;


    // <아래 순환>
    auto [bx,by] = airs[1];

    //왼
    for (int i=bx+1; i<r-1; i++){
        tmp[i][0] = tmp[i+1][0];
    }
    tmp[r-1][0] = 0;

    //아래
    for (int i=0; i<c-1; i++){
        tmp[r-1][i] = tmp[r-1][i+1];
    }
    tmp[r-1][c-1] = 0;


    // 오른
    for (int i=r-1; i>bx; i--){
        tmp[i][c-1] = tmp[i-1][c-1];
    }
    tmp[bx][c-1] = 0;


    // 위
    for (int i=c-1; i>1; i--){
        tmp[bx][i] = tmp[bx][i-1];
    }
    tmp[bx][1] = 0;
    tmp[bx][by] = -1;


    for (int i=0; i<r; i++)
        for (int j=0; j<c; j++)
            board[i][j] = tmp[i][j];
}

void calDust(){
    int sum = 0;
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            if (board[i][j] <= 0) continue;
            sum = sum + board[i][j];
        }
    }
    cout << sum << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> r >> c >> t;

    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            cin >> board[i][j];
            // 공기청정기 설치 = -1
            // 나머지 : 미세먼지의 양

            if (board[i][j] == -1){
                airs.push_back({i,j});
            }
        }
    }

    while(t--){
        // 1. 미세먼지 확산
        spreadDust();

        // 2. 공기청정기 작동
        cleanAir();
    }

    calDust();

    return 0;
}


//4 5
//1 2 2
//1 4 1
//2 3 7
//3 4 2
//2 4 4
//2 3