#include <iostream>
#include <vector>
using namespace std;

int dp[100001];
int dp2[100001];

int solution(vector<int> sticker) {
    int n = sticker.size();
    if (n == 1) return sticker[0];

    // case 1: 첫 번째 스티커를 포함하는 경우 → 마지막 스티커는 사용 못함
    vector<int> dp1(n, 0);
    dp1[0] = sticker[0];
    dp1[1] = sticker[0]; // 첫번째 선택했으므로 2번째 선택 x

    for (int i = 2; i < n - 1; i++) {
        dp1[i] = max(dp1[i - 1], dp1[i - 2] + sticker[i]);
    }

    // case 2: 첫 번째 스티커를 제외하는 경우 → 마지막 스티커까지 가능
    vector<int> dp2(n, 0);
    dp2[0] = 0;
    dp2[1] = sticker[1];

    for (int i = 2; i < n; i++) {
        dp2[i] = max(dp2[i - 1], dp2[i - 2] + sticker[i]);
    }

    return max(dp1[n - 2], dp2[n - 1]);
}