#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// 2차원 가상 벽면에 기둥과 보를 이용한 구조물을 설치할 수 있는데, 
// 기둥과 보는 길이 1인 선분으로 표현되며 규칙 갖는다.

// 1. 기둥은 바닥 위에 있거나, 보의 한쪽 끝 부분에 있거나, 다른 기둥 위에 있어야한다.
// 2. 보 는 한쪽 끝 부분이 기둥 위에 있거나, 양쪽 끝 부분이 다른 보와 동시에 연결되어야 한다. 

// 삭제 기능으로 삭제된 후에도 규칙을 만족해야 한다.
// 규칙을 만족하지 못할 경우, 해당 작업은 무시된다.

// n, 삭제 작업이 담긴게 주어질 때,
// 모든 명령어를 수행한 후 구조물의 상태를 return.

// build_frame [x,y,a,b]
// x,y = 설치 좌표
// a : 구조물 종류, 0=기둥, 1=보
// b : 설치/삭제 종류, 0=삭제, 1=설치

// 교차점 좌표를 기준으로 보의 오른쪽
// 교차점 좌표를 기준으로 기둥은 위쪽 설치 or 삭제

// 최종 구조물 상태
// [x,y,a] 형식 : x,y는 기둥과 보의 교차점 좌표, [가로,세로]
// a : 구조물 종류 , 0=기둥 1=보
// x좌표 기준 오름차순, y좌표 기준 오름차순
// x,y둘다 같으면 기둥 < 보 상태 

// 한 점만 값을 저장하고, 어차피 기둥은 그 상단, 보는 오른쪽까지 보는걸로.. 


bool bo[101][101]; //보의 존재 여부 저장 배열
bool stick[101][101]; //기둥의 존재 여부 저장 배열
int N;


bool canInsertStick(int x, int y){
    if (y == 0) return true;
    if (y - 1 >= 0 && stick[x][y - 1]) return true;
    if (bo[x][y]) return true;
    if (x - 1 >= 0 && bo[x - 1][y]) return true;
    return false;
}

bool canInsertBo(int x, int y){
    // 오른쪽 끝이 (x+1, y)
    if (x + 1 > N) return false;
    if (y - 1 >= 0 && stick[x][y - 1]) return true;         // 왼쪽 끝 기둥 위
    if (y - 1 >= 0 && stick[x + 1][y - 1]) return true;     // 오른쪽 끝 기둥 위
    if (x - 1 >= 0 && bo[x - 1][y] && bo[x + 1][y]) return true; // 양옆 보
    return false;
}


void deleteStick(int x, int y){
    bool prev = stick[x][y];
    stick[x][y] = false;

    // 위 기둥
    if (y + 1 <= N && stick[x][y + 1] && !canInsertStick(x, y + 1)) {
        stick[x][y] = prev; return;
    }
    // 위 보들
    if (y + 1 <= N && x - 1 >= 0 && bo[x - 1][y + 1] && !canInsertBo(x - 1, y + 1)) {
        stick[x][y] = prev; return;
    }
    if (y + 1 <= N && bo[x][y + 1] && !canInsertBo(x, y + 1)) {
        stick[x][y] = prev; return;
    }
}


void deleteBo(int x, int y){
    bool prev = bo[x][y];
    bo[x][y] = false;

    // 인접 보들
    if (bo[x][y] && !canInsertBo(x, y)) { bo[x][y] = prev; return; }
    if (x - 1 >= 0 && bo[x - 1][y] && !canInsertBo(x - 1, y)) { bo[x][y] = prev; return; }
    if (x + 1 <= N && bo[x + 1][y] && !canInsertBo(x + 1, y)) { bo[x][y] = prev; return; }

    // 양 끝 기둥
    if (stick[x][y] && !canInsertStick(x, y)) { bo[x][y] = prev; return; }
    if (x + 1 <= N && stick[x + 1][y] && !canInsertStick(x + 1, y)) { bo[x][y] = prev; return; }
}


void insertStick(int x, int y){
    if (canInsertStick(x,y)){
        stick[x][y] = true;
    }
}


void insertBo(int x, int y){
    if (canInsertBo(x,y)){
        bo[x][y] = true;
    }
}


bool comp(const vector<int>& a, const vector<int>& b){
    if (a[0] != b[0]) return a[0] < b[0]; // x
    if (a[1] != b[1]) return a[1] < b[1]; // y
    return a[2] < b[2];                   // a (기둥 0 < 보 1)
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    N = n;
    
    //초기화 
    for (int i=0; i<=n; i++){
        for (int j=0; j<=n; j++){
            bo[i][j] = false;
            stick[i][j] = false;
        }
    }
    
    for (int i=0; i<build_frame.size(); i++){
        int x = build_frame[i][0];
        int y = build_frame[i][1];
        int a = build_frame[i][2]; // 0:기둥, 1:보
        int b = build_frame[i][3]; // 0:삭제, 1:설치
        
        if (a==0 && b==0){
            //기둥 삭제
            deleteStick(x,y);
        } else if (a==0 && b==1){
            // 기둥 설치
            insertStick(x,y);
        } else if  (a==1 && b==0){
            //보 삭제
            deleteBo(x,y);
        } else {
            // 보 설치
            insertBo(x,y);
        }
    }
    
    for (int i=0; i<=n; i++){
        for (int j=0; j<=n; j++){
            if (stick[i][j]) answer.push_back({i,j,0});
            if (bo[i][j]) answer.push_back({i,j,1});
        }
    }
    
    sort(answer.begin(), answer.end(), comp);
    
    return answer;
}