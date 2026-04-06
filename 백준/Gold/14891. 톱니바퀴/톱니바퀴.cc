#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

// 톱니 초기랑, 회전방법 주어질 때
// 최종 톱니바퀴 상태 출력

// 톱니바퀴 K번 회전
// 회전은 한칸 기준 시계방향, 반시계 방향 존재

// A회전 시 , 그 옆 B와 맞닿는 극이 서로 다르면 ->
// B는 A회전 반대 방향으로 회전

int arr[5][8]; //1~4번까지
int arrDir[2] = {-1,1};
bool visited[5];

// dir = 인덱스 전달
void moveTime(int tireNum, int dir){

    if (tireNum < 1 || tireNum > 4) return;

    visited[tireNum] = true;
    bool left = false;
    bool right = false;

    if (arr[tireNum-1][2] != arr[tireNum][6] && !visited[tireNum-1]){
        left = true;
    }

    if (arr[tireNum][2] != arr[tireNum+1][6] && !visited[tireNum+1]){
        right = true;
    }

// 반시계: 왼쪽으로 한 칸
    if (dir == 0){
        int tmp = arr[tireNum][0];
        for (int i = 0; i < 7; i++){
            arr[tireNum][i] = arr[tireNum][i+1];
        }
        arr[tireNum][7] = tmp;
    }
// 시계: 오른쪽으로 한 칸
    else {
        int tmp = arr[tireNum][7];
        for (int i = 7; i > 0; i--){
            arr[tireNum][i] = arr[tireNum][i-1];
        }
        arr[tireNum][0] = tmp;
    }
    
    if (left){
        moveTime(tireNum-1, (dir+1)%2);
    }

    if (right){
        moveTime(tireNum+1, (dir+1)%2);
    }
}

void initVisited(){
    for (int i=1; i<=4; i++){
        visited[i] = false;
    }
}

int sumResult(){
    int sum = 0;
    if (arr[1][0] == 1){
        sum = sum + 1;
    }
    if (arr[2][0] == 1){
        sum = sum + 2;
    }
    if (arr[3][0] == 1){
        sum = sum + 4;
    }
    if (arr[4][0] == 1){
        sum = sum + 8;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    // 톱니바퀴 값 담기
    for (int i=1; i<=4; i++){
        string input;
        cin >> input;
        for (int j=0; j<input.size(); j++){
            arr[i][j] = input[j]-48;
        }
    }

    // 방향에 따른 회전
    int k;
    cin >> k;

    int tireNum, dir;
    for (int i=0; i<k; i++){
        initVisited();
        cin >> tireNum >> dir;
        if (dir == 1) moveTime(tireNum, 1); //시계
        else moveTime(tireNum, 0); //반시계

    }

    cout << sumResult();
    return 0;
}