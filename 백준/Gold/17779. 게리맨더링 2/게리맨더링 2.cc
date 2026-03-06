#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;


// n*n 격자로 나타낼 수 있다.
// (r,c)로 나타낸다.

// 격자의 각 칸 = 구역
// 구역을 5개의 선거구로 나눠야 하고
// 각 구역은 다섯 선거구 중 하나에 포함되어야 한다.

// 선거구는 구역을 적어도 하나 포함해야하고,
// 한 선거구에 포함되어있는 구역은 모두 연결되어야 한다.

// 구역 A에서 인접한 구역을 통해 구역 B로 갈 수 있을 때
// 두 구역은 연결되어있다고 한다.
// 중간에 통하는 인접 구역은 0개 이상이어야 하고, 모두 같은 선거구에 포함되어야 한다.

struct Cell {
    int peopleNum;
    int num = -1;
};

int n;

int board[21][21];
int minV = 100 * 100 * 100 * 100;


int calMin(Cell tmp[][21]){
    int sums[5] = {0,0,0,0,0};
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            sums[tmp[i][j].num-1] = sums[tmp[i][j].num-1]+board[i][j];
        }
    }

    sort (sums, sums+5);

    return sums[4]-sums[0];
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++) {
            cin >> board[i][j];
        }
    }

    // 선거구 정하기
    for (int d1=1; d1<=n; d1++){
        for (int d2=1; d2<=n; d2++){
            for (int x=0; x<n; x++){
                for (int y=0; y<n; y++){

                    if (x+d1+d2 >= n || y+d2 >= n || y-d1 < 0) continue;


                    Cell tmpBoard[21][21];
                    // 초기화
                    for (int r=0; r<n; r++){
                        for (int c=0; c<n; c++){
                            tmpBoard[r][c].num = -1;
                        }
                    }

                    // 5번 경계선 색칠
                    for (int i=0; i<=d1; i++){
                        tmpBoard[x+i][y-i].num = 5;
                    }

                    for (int i=0; i<=d2; i++) {
                        tmpBoard[x+i][y+i].num = 5;
                    }

                    for (int i=0; i<=d2; i++){
                        tmpBoard[x+d1+i][y-d1+i].num = 5;
                    }

                    for (int i=0; i<=d1; i++){
                        tmpBoard[x+d2+i][y+d2-i].num = 5;
                    }

                    // 1번 체크
                    for (int r=0; r<x+d1; r++){
                        for (int c=0; c<=y; c++){
                            if (tmpBoard[r][c].num == 5){
                                break;
                            }
                            tmpBoard[r][c].num = 1;
                        }
                    }


                    // 2번 체크
                    for (int r=0; r<=x+d2; r++){
                        for (int c=n-1; c>y; c--){
                            if (tmpBoard[r][c].num == 5){
                                break;
                            }
                            tmpBoard[r][c].num = 2;
                        }
                    }


                    // 3번 체크
                    for (int r=x+d1; r<n; r++){
                        for (int c=0; c<y-d1+d2; c++){
                            if (tmpBoard[r][c].num == 5){
                                break;
                            }
                            tmpBoard[r][c].num = 3;
                        }
                    }


                    // 4번 체크
                    for (int r=x+d2+1; r<n; r++){
                        for (int c=n-1; c>=y-d1+d2; c--){
                            if (tmpBoard[r][c].num == 5){
                                break;
                            }
                            tmpBoard[r][c].num = 4;
                        }
                    }


                    // 5번 체크
                    for (int r=0; r<n; r++){
                        for (int c=0; c<n; c++){
                            if (tmpBoard[r][c].num == -1){
                                tmpBoard[r][c].num = 5;
                            }
                        }
                    };
                    minV = min(minV, calMin(tmpBoard));
                }
            }
        }
    }

    // 선거구 인원 중
    // 인구가 가장 많은 선거구와 가장 적은 선거구의 차이 최솟값은?
    cout << minV;

    return 0;
}