#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int n,m,k;
int board[21][21];

int dx4[5] = {0,-1,1,0,0};
int dy4[5] = {0,0,0,-1,1};


struct Smell{
    int time = 0;
    int sharkNum = 0;
};

Smell smellBoard[21][21] = {0,};

struct Shark{
    int sx,sy;
    int dir;
    int bestDir[5][5];
    bool lived = true;
};

Shark sharks[401]; //상어들 각 번호 index 매칭

bool checkOnlyOneShark(){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if(board[i][j] != 0 && board[i][j] != 1){
                return false;
            }
        }
    }
    return true;
}

void eraseSmell(){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (smellBoard[i][j].time > 0){
                smellBoard[i][j].time--;
            }
            if (smellBoard[i][j].time == 0){
                smellBoard[i][j].sharkNum = 0;
            }
        }
    }
}

void spreadSmell(){
    for (int i=1; i<=m; i++){
        if (!sharks[i].lived) continue;

        auto & s = sharks[i];
        smellBoard[s.sx][s.sy].sharkNum = i;
        smellBoard[s.sx][s.sy].time = k;
    }
}

pair<int,int> realMoveShark(int idx){
    auto & s = sharks[idx];
    int curDir = s.dir;

    // 1. 냄새 빈칸 찾기
    for (int i=0; i<4; i++){
        int nextD = s.bestDir[curDir][i];
        int nx = s.sx + dx4[nextD];
        int ny = s.sy + dy4[nextD];

        if (nx < 0 || ny < 0 || nx >=n || ny >= n) continue;
        if (smellBoard[nx][ny].time == 0) {
            s.dir = nextD;
            return {nx,ny};
        }
    }

    // 2. 냄새 빈 칸 없으면, 자신냄새 찾기
    for (int i=0; i<4; i++){
        int nextD = s.bestDir[curDir][i];
        int nx = s.sx + dx4[nextD];
        int ny = s.sy + dy4[nextD];

        if (nx < 0 || ny < 0 || nx >=n || ny >= n) continue;
        if (smellBoard[nx][ny].sharkNum == idx) {
            s.dir = nextD;
            return {nx,ny};
        }
    }

    return {s.sx, s.sy};
}

void moveShark(){
    int nextBoard[21][21] = {0};
    for (int i=1; i<=m; i++){
        if (!sharks[i].lived){ continue; }

        // 이동 위치 계산
        auto [nx,ny] = realMoveShark(i);

        if (nextBoard[nx][ny] == 0){
            // 바로 입주
            nextBoard[nx][ny] = i;
        }
        else {

            if (nextBoard[nx][ny] < i){
                // 들어가도 죽음
                sharks[i].lived = false;
            }
        }
    }


    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            board[i][j] = nextBoard[i][j];
            if (board[i][j] != 0){
                int idx = board[i][j];
                sharks[idx].sx = i;
                sharks[idx].sy = j;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
           cin >> board[i][j];
           if (board[i][j] != 0){
               sharks[board[i][j]].sx = i;
               sharks[board[i][j]].sy = j;
           }
        }
    }

    for (int i=1; i<=m; i++){
        cin >> sharks[i].dir;
    }

    for (int num=1; num<=m; num++){
        // 위, 아래, 왼, 오른 의미
        for (int i=1; i<=4; i++){
            for (int j=0; j<4; j++){
                cin >> sharks[num].bestDir[i][j];
            }
        }
    }

    int timeCnt = 0;

    // 처음 상어 냄새 뿌리기
    for (int i=1; i<=m; i++){
        auto & s = sharks[i];
        smellBoard[s.sx][s.sy].sharkNum = i;
        smellBoard[s.sx][s.sy].time = k;
    }

    while(!checkOnlyOneShark() && timeCnt < 1000){

        // 1. 상어 인접 칸 이동
        moveShark();

        // 2. 냄새 삭제
        eraseSmell();

        // 3. 냄새 뿌리기 (냄새는 K번 이동 시 사라짐)
        spreadSmell();

        timeCnt ++;
    }

    if (!checkOnlyOneShark() && timeCnt >= 1000){
        cout << -1 << "\n";
    }

    else {
        cout << timeCnt << "\n";
    }

    return 0;
}