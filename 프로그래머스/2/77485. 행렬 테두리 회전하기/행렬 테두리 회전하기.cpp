#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

// row x col 행렬 존재
// 직사각형 모양 범위를 여러번 선택해, 
// 테두리 부분 숫자들 -> 시계방향 회전시키려 함

// 각 회전 (x1, y1, x2, y2) 정수 4개로 표현
// 의미는 
// x1행 y1열부터 ~ x2행 y2열까지 영역 직사각형 태두리 한칸씩 시계방향 회전 

// 회전 queries 주어질 때, 적용 후 회전에 의해 위치 바뀐 숫자들 중
// 가장 작은 숫자들을 순서대로 배열 담아 return 

int arr[101][101];
int r,c;

void printArr(){
    for (int i=0; i<r; i++){
        for (int j=0; j<c; j++){
            cout << arr[i][j] << " ";
        }
        cout << "\n";
    }
}

int rotateTime(int x1, int y1, int x2, int y2){
    int minV = INT_MAX; // 회전 중 가장 작은 값
    
    int copyB[101][101];
    
    for (int i=x1; i<=x2; i++){
        for (int j=y1; j<=y2; j++){
            copyB[i][j] = arr[i][j];
        }
    }
    
    // 하
    for (int j=y1; j<y2; j++){
        copyB[x2][j] = arr[x2][j+1];
    }
    
    // 좌
    for (int i= x1; i<x2; i++){
        copyB[i][y1] = arr[i+1][y1];
    }
    
    // 상
    for (int j=y2; j>y1; j--){
        copyB[x1][j] = arr[x1][j-1];
    }
    
    
    // 우
    for (int i=x2; i>x1; i--){
        copyB[i][y2] = arr[i-1][y2];
    }
    
    // 회전한 테두리 중에서 최소
    for (int i=x1; i<=x2; i++){
        for (int j=y1; j<=y2; j++){
            arr[i][j] = copyB[i][j];
        }
    }
    
    // i== x1 && j = y1~y2
    // i== x2 && j = y1~y2
    for (int j=y1; j<=y2; j++){
        minV = min(minV, arr[x1][j]);
        minV = min(minV, arr[x2][j]);
    }

    for (int i=x1; i<=x2; i++){
        minV = min(minV, arr[i][y1]);
        minV = min(minV, arr[i][y2]);       
    }

    return minV;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    r = rows;
    c = columns;
    
    // 1. 배열 1부터 증가하며 row * col 배열 만들기
    for (int i=1; i<=rows; i++){
        for (int j=1; j<=columns; j++){
            arr[i-1][j-1] = ((i-1) * columns + j);
        }
    }

    
    // 2. 각 회전에 맞춰 회전 진행 
    for (auto q : queries){
        
        int x1 = q[0]-1;
        int y1 = q[1]-1;
        int x2 = q[2]-1;
        int y2 = q[3]-1;
        
        int minV  = rotateTime(x1,y1,x2,y2);
        answer.push_back(minV);
    }
   
    return answer;
}