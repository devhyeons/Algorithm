#include <string>
#include <vector>

using namespace std;
int dp[100001];

int solution(int n, vector<int> money) {
    int answer = 0;
    
    dp[0] = 1;
    
    for (auto i : money){
        for (int j=i; j<=n; j++){
            // ex. i==1 이면, 1로 만드는 모든 조합 n까지 만들고
            // ex. i==2 이면, 2로 만드는 조합 에 2원을 사용한다는 전체로 dp[j-2]를 더해 준다.
            
            // 이렇게 하면 2+1+1이랑 1+1+2를 중복으로 체크하지 않고,
            // 조합에 따른 경우의 수를 계산할 수 있다. 
            dp[j] = (dp[j-i] + dp[j])%1000000007;
        }
    }
    
    answer = dp[n]; 
    
    return answer;
}