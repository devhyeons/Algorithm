#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 땅따먹기 게임
// n행 4열로 이루어짐, 모든 칸에 숫자가 적혀있다.
// 1행부터 땅을 밟으며 한 행씩 내려올때, 
// 각 행의 4칸 중 한 칸만 밟으면서 내려와야 한다.
// 단 땅따먹기 게임에서느 한 행씩 내려올 때 같은 열 연속 밟을 수 x

// 마지막 행까지 내려올 때 얻을 수 있는 점수의 최대값은?(return)
// 행 갯수 <= 10^5 

int dp[100001][4];

int solution(vector<vector<int> > land)
{
    int answer = 0;
    
    for (int i=0; i<4; i++){
        dp[0][i] = land[0][i];
    }

    for (int i=1; i<land.size(); i++){
        for (int j=0; j<4; j++){
            if (j==0){
                dp[i][j] = max(dp[i-1][1], max(dp[i-1][2], dp[i-1][3])) + land[i][j];
            }
            else if (j==1){
                dp[i][j] = max(dp[i-1][0], max(dp[i-1][2], dp[i-1][3])) + land[i][j];                
            }
            else if (j==2){
                dp[i][j] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][3])) + land[i][j];                
            }
            else {
                 dp[i][j] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2])) + land[i][j];               
            }
        }
    }
    
    int last = land.size()-1;
    for (int i=0; i<4; i++){
        answer = max(answer, dp[last][i]);
    }
    
    return answer;
}