#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// (x,y)에서 출발해 (r,c)로 이동해서 탈출
// 탈출 조건

// 1. 격자 바깥으로 나갈 수 없다.
// 2. (x,y) -> (r,c)까지 이동거리 k여야 한다. 
// (x,y) , (r,c) 포함 같은 격자 2번이상 방문해도 된다.
// 3. 탈출 경로를 문자열로 나타낼 때, 문자열 사전순으로 가장 빠르 ㄴ경로로 탈출해야한다. 

// l, r, u, d 

// dlru 순서대로 방향키 조준하기. 
// 미로 탈출 최소 경로를 return, 미로탈출할 수 없을 경우 impossilble return

// dfs 돌리기? 는 맞는데, 브루트포스하게 돌리니까 시간초과 발생..
// dfs로 돌리되, 어차피 dlru순서대로 돌리므로, 이미 발견되면 그것이 최소 값이 된다.
// 따라서 그 이후로는 값을 더 보지 않아도된다.

// 또한 남은 k와 남은 dist거리를 비교한 후
// dist가 더 큰 경우에는 더이상 가도 도달하지 못하므로 continue한다.

// 즉 불필요한 이동을 줄여 모든 경우를 탐색하지 않고, 효율적인 탐색이 되도록 코드를 작성한다. 

// 처음 브루트포스 코드의 시간복잡도
// 4개의 범위를 k만큼 반복.. 4^K의 시간복잡도 발생
// k <= 2500이므로 2^5000 의 시간복잡도 발생 이는 약 10^1500.. 당연히 시간초과 발생

int dx[4] = {1,0,0,-1};
int dy[4] = {0,-1,1,0};

int board[51][51]; // 2 : Start, 3 : End, -1 : 통과가능
pair<int,int> startXY;
pair<int,int> endRC;
int copyN, copyM, copyK;
string answer = "z";
bool found  = false; 

string calNewMove(int dir, string curMove){
    if (dir == 0){
        return curMove + "d";
    }
    else if (dir == 1){
        return curMove + "l";        
        
    } else if (dir==2) {
        return curMove + "r";        
    } else {
        return curMove + "u";
    }
}

void dfs(int curK, string curMove, pair<int,int> curXY){
    if (curK == copyK){
        if (curXY == endRC){
            answer = curMove;
            found = true; 
        }
        return;
    }
    
    for (int dir=0; dir<4; dir++){
        auto [x,y] = curXY;
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        
        if (nx <= 0 || ny <= 0 || nx > copyN || ny > copyM) continue;
        
        int dist = abs(nx-endRC.first) + abs(ny-endRC.second); //지금 위치에서 도착까지 거리
        int rem = copyK - (curK+1); // 앞으로 남은 이동 횟수
        
        if (dist > rem ) continue;
        if((rem-dist)%2!=0) continue; //짝홀수 판별
        
        string newMove = calNewMove(dir, curMove);
        pair<int,int> newXY = {nx,ny};
        int newK = curK + 1;
        if (found) return;
        dfs(newK, newMove, newXY);
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    copyN = n; copyM = m; copyK = k;
    
    startXY = {x,y};
    endRC = {r,c};
    
    dfs(0, "", startXY);
    if (answer == "z"){
        answer = "impossible";
    }
    
    return answer;
}