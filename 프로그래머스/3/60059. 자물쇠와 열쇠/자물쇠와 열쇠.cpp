#include <string>
#include <vector>

using namespace std;

// 잠겨있는 자물쇠는 n*n 크기 정사각 격자
// 특이한 모양의 열쇠는 m*m 크기의 정사각 격자 형태

// 열쇠를 나타내는 key와 자물쇠 lock
// 열쇠로 자물쇠 열면 true, 아니면 false return 

// 열쇠는 회전과 이동 가능, 열쇠의 돌기 부분이 자물쇠의 홈 부분에 딱 맞게 채우면 됨.
// 자물쇠 영역 내의 열쇠의 돌기 부분과 자물쇠의 홈 부분이 정확히 일치해야 함.
// 열쇠의 돌기와 자물쇠의 돌기가 만나서는 안됨.
// 자물쇠의 모든 홈을 채워 비어있는 곳이 없어야 자물쇠 열 수 있음. 

// 완전 탐색, 브루트 포스 문제.. 

// https://yabmoons.tistory.com/678

int m,n;
vector<vector<int>> board;


vector<vector<int>> rotate90(const vector<vector<int>> &key){
    vector<vector<int>> rotateKey = vector(m, vector<int>(m,0));
    for (int i=0; i<m; i++){
        for (int j=0; j<m; j++){
            rotateKey[j][m-1-i] = key[i][j];
        }
    }
    
    return rotateKey;
}

bool checkCenterAllOne(){
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (board[i+m-1][j+m-1] != 1) return false;
        }
    }
    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = true;
    
    n = lock.size();
    m = key.size();
    int newSize = n+2*(m-1);
    
    
    // 1. 자물쇠 확장 보드 만들고, 원래 자물쇠를 board에 채우기
    board = vector(newSize, vector<int>(newSize,0));
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            board[i+m-1][j+m-1] = lock[i][j];
        }
    }
             
    // 2. 자물쇠와 열쇠 맞추기
    for (int dir=0; dir<4; dir++){ // 90도씩 회전 반복문
        for (int x=0; x<n+m-1; x++){
            for (int y=0; y<n+m-1; y++){ //모든 좌표에 이동 반복문
                
                for (int i=0; i<m; i++){
                    for (int j=0; j<m; j++){
                        board[x+i][y+j] = board[x+i][y+j] + key[i][j];
                    }
                }
                
                // 자물쇠랑 열쇠 다 채워졌는지 확인 -> (다채워지면 모두 1이기 때문)
                if (checkCenterAllOne()) return true;
                
                // 아니라면 원래 원복
                for (int i=0; i<m; i++){
                    for (int j=0; j<m; j++){
                        board[x+i][y+j] = board[x+i][y+j]-key[i][j];
                    }
                }
            }
        }
        
        // 하나의 방향에서 모든 좌표 탐색 완료
        // 이후 key 90도 rotate
        
        key = rotate90(key);
    
    }
    
    
    return false;
}