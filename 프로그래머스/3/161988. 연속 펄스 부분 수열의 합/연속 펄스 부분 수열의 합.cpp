#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


  long long solution(vector<int> sequence) {
    int n = sequence.size();
    vector<int> pulse1(n), pulse2(n);

    // 1. 펄스 수열 두 개 생성
    for (int i = 0; i < n; i++) {
        pulse1[i] = sequence[i] * (i % 2 == 0 ? 1 : -1);  // [+1, -1, +1, ...]
        pulse2[i] = sequence[i] * (i % 2 == 0 ? -1 : 1);  // [-1, +1, -1, ...]
    }

    // 2. DP 수행
    vector<long long> dp1(n), dp2(n);
    dp1[0] = pulse1[0];
    dp2[0] = pulse2[0];
    long long answer = max(dp1[0], dp2[0]);

    for (int i = 1; i < n; i++) {
        dp1[i] = max((long long)pulse1[i], dp1[i - 1] + pulse1[i]);
        dp2[i] = max((long long)pulse2[i], dp2[i - 1] + pulse2[i]);
        answer = max({answer, dp1[i], dp2[i]});
    }

    return answer;
}