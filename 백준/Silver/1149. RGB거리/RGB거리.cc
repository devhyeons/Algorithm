#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

// 집은 빨강, 초록, 파랑 중 하나의 색으로 색칠
// 각각 집 색칠 비용 주어질 때, 규칙 만족하는 비용 최솟값은?

// 1번의 집 색과 2번의 집 색은 같지 않아야 한다.
// N번의 집과 N-1번 색 같지 않아야 한다.

int n;
int cost[1001][3]; // N번 집에서 각 색상 비용

int dp[1001][3];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int i=1; i<=n; i++){
        for (int j=0; j<3; j++){
            cin >> cost[i][j];
        }
    }

    // 모든 집을 칠하는 비용의 최솟값은?
    dp[1][0] = cost[1][0];
    dp[1][1] = cost[1][1];
    dp[1][2] = cost[1][2];

    for (int i=2; i<=n; i++){
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + cost[i][0];
        dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + cost[i][1];
        dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + cost[i][2];
    }

    long long ans = min({dp[n][0], dp[n][1], dp[n][2]});
    cout << ans;

    return 0;
}
