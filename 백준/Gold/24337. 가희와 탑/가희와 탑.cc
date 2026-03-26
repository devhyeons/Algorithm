#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;

    // 가희와 단비가 보는 건물의 합에서 겹치는 가장 높은 건물 1개를 뺀 값이 n보다 크면 불가능
    if (a + b - 1 > n) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> ans;

    // 1. 가희가 보는 건물들 (가장 높은 건물 제외)
    for (int i = 1; i < a; i++) {
        ans.push_back(i);
    }

    // 2. 가장 높은 건물 배치
    ans.push_back(max(a, b));

    // 3. 단비가 보는 건물들 (가장 높은 건물 제외)
    for (int i = b - 1; i >= 1; i--) {
        ans.push_back(i);
    }

    // 4. 부족한 개수만큼 '1'을 채우기
    // 사전 순으로 가장 앞서려면, 첫 번째 건물 바로 뒤(인덱스 1)에 1들을 몰아넣어야 함
    int target_size = n;
    if (ans.size() < target_size) {
        int count = target_size - ans.size();
        // ans.begin() + 1 위치에 count만큼 1을 삽입
        ans.insert(ans.begin() + 1, count, 1);
    }

    // 출력
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }

    return 0;
}