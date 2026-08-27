#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w) {
    int answer = 0;
    int cellLen = 2 * w + 1;  // 기지국 하나가 커버하는 길이
    int curStart = 1;         // 아직 커버되지 않은 구간의 시작 (1-indexed)

    for (int i = 0; i < stations.size(); i++) {
        int start = curStart;
        int end = stations[i] - w - 1;  // 이번 기지국이 커버하기 전까지의 미커버 구간 끝

        if (start <= end) {
            int L = end - start + 1;
            answer += (L + cellLen - 1) / cellLen;
        }

        curStart = stations[i] + w + 1;  // 이 기지국이 커버하는 범위 다음부터
    }

    // 마지막 기지국 이후 남은 구간 처리
    if (curStart <= n) {
        int L = n - curStart + 1;
        answer += (L + cellLen - 1) / cellLen;
    }

    return answer;
}