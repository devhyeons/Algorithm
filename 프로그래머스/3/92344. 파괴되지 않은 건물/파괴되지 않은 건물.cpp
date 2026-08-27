#include <string>
#include <vector>

using namespace std;

// 적군은 건물 공격 -> 파괴 ->  내구도가 0이하가 되면 파괴된다.
// 아군 -> 회복 스킬 -> 건물 내구도 높임

// 내구도가 0 이하가 된 이미 파괴된 건물도, 공격을 받으면 계속해서 내구도가 하락한다.

// 아군 회복, 적군 공격 스킬 skill

// 건물 내구도 board
// 적군의 공격, or 아군의 회복스킬 끝난 후 파괴되지 않은 건물의 개수는?

// skill [type, r1, c1, r2, c2, degree] 형태
// type = 1 : 공격, type = 2 : 회복
// (r1,c1) ~ (r2,c2)까지 degree만큼 내구도 높이거나 낮춤

// 회복스킬 받아서 1 이상되면 파괴되지 않은 건물 됨.

vector<vector<int>> copyB;
int diff[1001][1001];
// board n,m <= 10^3 
// skill <= 25*10^4

// 효율성 테스트 실패 : 효율성을 위해 diff로 skill변화량 미리 누적해두고, 한번에 적용 방법

void attack(pair<int,int> b1, pair<int,int> b2, int degree){
    for (int i=b1.first; i<=b2.first; i++){
        for (int j=b1.second; j<=b2.second; j++){
            copyB[i][j] = copyB[i][j] - degree;
        }
    }
}

void recovery(pair<int,int> b1, pair<int,int> b2, int degree){
     for (int i=b1.first; i<=b2.first; i++){
        for (int j=b1.second; j<=b2.second; j++){
            copyB[i][j] = copyB[i][j] + degree;
        }
    }
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    
    int answer = 0;
    copyB = board;
    int n = (int)board.size();
    int m = (int)board[0].size();
    
    for (int i=0; i<skill.size(); i++){
        // skill[i][0] = type (1 : 공격, 2: 회복)
        // (skill[i][1], skill[i][2]) ~ (skill[i][3], skill[i][4]) 범위로
        // degree만큼 + or - 진행  
        int type = skill[i][0];
        pair<int,int> b1 = {skill[i][1], skill[i][2]};
        pair<int,int> b2 = {skill[i][3], skill[i][4]};
    
        int degree = (type==1) ? -skill[i][5] : skill[i][5];
        
        diff[b1.first][b1.second] += degree;
        diff[b1.first][b2.second+1] -= degree;
        diff[b2.first+1][b1.second] -=degree;
        diff[b2.first+1][b2.second+1] +=degree; 
    }
    
    //행 (왼 -> 오) 누적
    for (int i=0; i<n; i++){
        long long run = 0;
        for (int j=0; j<m; j++){
            run+=diff[i][j];
            diff[i][j] = run;
        }
    }
   
    //열 (위->아래) 누적
    for (int j = 0; j < m; ++j) {
        long long run = 0;
        for (int i = 0; i < n; ++i) {
            run += diff[i][j];
            diff[i][j] = run;
        }
    }
    
    
    for (int i=0; i<board.size(); i++){
        for (int j=0; j<board[i].size(); j++){
            if (board[i][j] + diff[i][j] > 0) answer ++;
        }
    }
    
    return answer;
}