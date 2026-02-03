#include <iostream>
#include <algorithm>

using namespace std;


// * = 쿠키 신체부분
// _ = 신체 x

// 심장의 위치, 팔, 다리, 허리의 길이를 구하라.
// n<=10^3

// 쿠키의 신체 조건
// 1. 머리는 심장 바로 윗 칸에 1칸 크기
// 2. 왼쪽 팔은 심장 바로 왼쪽
// 3. 오른팔은 심장 바로 오른쪽
// 4. 허리는 심장 바로 아래로
// 5. 왼쪽다리는 허리 왼쪽, 오른쪽다리는 허리 오른쪽
// 절대 끊겨있지 않고, 굽혀진곳도 없음.

int n;
char input;
int board[1001][1001];


void initBoard(){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            board[i][j] = -1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cin >> input;
            if (input == '*'){
                board[i][j] = 1;
            }
        }
    }


    // 머리 체크
    // 행 체크
    pair<int,int> headPosition;
    for (int i=0; i<n; i++){
        vector<pair<int,int>> h;
        for (int j=0; j<n; j++){
            if (board[i][j] == 1){
                h.push_back({i,j});
            }
        }

        if (!h.empty() && h.size() == 1){
            headPosition = h.front();
            break;
        }
    }

    pair<int,int> heartPosition = {headPosition.first +1, headPosition.second};

    //왼쪽 팔
    int leftH = 0;
    for (int i=0; i<heartPosition.second; i++){
        if (board[heartPosition.first][i] == 1){
            leftH ++;
        }
    }

    // 오른쪽 팔
    int rightH = 0;
    for (int i=heartPosition.second+1; i<n; i++){
        if (board[heartPosition.first][i] == 1){
            rightH++;
        }
    }


    // 허리
    int waist = 0;
    for (int i=heartPosition.first+1; i<n; i++){
        if (board[i][heartPosition.second] == 1){
            waist++;
        }
    }

    // 왼쪽 다리
    int leftL = 0;
    for (int i=heartPosition.first+waist; i<n; i++){
        if (board[i][headPosition.second-1] ==1){
            leftL++;
        }
    }

    // 오른쪽 다리
    int rightL = 0;
    for (int i=heartPosition.first+waist; i<n; i++){
        if (board[i][headPosition.second+1] ==1){
            rightL++;
        }
    }

    cout << heartPosition.first+1 << " " << heartPosition.second+1<< "\n";
    cout << leftH << " " << rightH << " " << waist << " " << leftL << " " << rightL << "\n";

    return 0;
}