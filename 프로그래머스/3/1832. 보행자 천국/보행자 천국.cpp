#include <vector>

using namespace std;

int MOD = 20170805;

long long dp[501][501][2]; //격자, dir로 들어왔을 때 경우의 수 
int copyM, copyN;
long long answer = 0;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
   // DFS로 푸니 시간 초과 발생
    // 따라서 DP로 격자당 도달 가능한 수를 저장해서
    // 최종 DP[m-1][n-1] 을 더하자.. 
    
    dp[0][0][0] = 1;
    dp[0][0][1] = 0;

    
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
               if (city_map[i][j] == 1) { // 통행 불가
                dp[i][j][0] = dp[i][j][1] = 0;
                continue;
            }
            
            // 위쪽에서 오는 경우
            if (i > 0) {
                if (city_map[i-1][j] == 2){
                    dp[i][j][0] = (dp[i-1][j][0]) % MOD;
                } else {
                    dp[i][j][0] = (dp[i-1][j][0] + dp[i-1][j][1]) % MOD;
                }
            }
            
            // 왼쪽에서 오는 경우
            if (j > 0) {
                if (city_map[i][j-1] == 2) { // 직진만 가능
                    dp[i][j][1] = (dp[i][j-1][1]) % MOD;
                } else {
                    dp[i][j][1] = (dp[i][j-1][0] + dp[i][j-1][1]) % MOD;
                }
            }
        }
    }
    
    return (dp[m-1][n-1][0] + dp[m-1][n-1][1]) % MOD; 
}