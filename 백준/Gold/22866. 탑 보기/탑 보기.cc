#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
#include <climits>
#include <set>

using namespace std;

int N;
int h[100001];          // 빌딩 높이
int cnt[100001];        // i번 빌딩에서 볼 수 있는 총 개수
int nearIdx[100001];    // 가장 가까운 빌딩 번호 (없으면 0)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> h[i];
        nearIdx[i] = 0;   // 초기화 (보이는 빌딩 없으면 0)
    }

    stack<int> st; // 빌딩 인덱스를 저장하는 단조 스택

    /* --------------------
       왼쪽에서 보이는 빌딩 처리
       왼 → 오 방향 스캔
       -------------------- */
    for (int i = 1; i <= N; i++) {

        // 현재 빌딩보다 낮거나 같은 빌딩은
        // 뒤에서 볼 수 없으므로 제거
        while (!st.empty() && h[st.top()] <= h[i]) {
            st.pop();
        }

        // 스택에 남아 있는 빌딩 수 = 왼쪽에서 보이는 개수
        cnt[i] += st.size();

        // 가장 가까운 빌딩은 스택 top (있다면)
        if (!st.empty()) {
            nearIdx[i] = st.top();
        }

        // 현재 빌딩을 스택에 추가
        st.push(i);
    }

    // 스택 초기화 (반대 방향 계산을 위해)
    while (!st.empty()) st.pop();

    /* --------------------
       오른쪽에서 보이는 빌딩 처리
       오 → 왼 방향 스캔
       -------------------- */
    for (int i = N; i >= 1; i--) {

        // 현재 빌딩보다 낮거나 같은 빌딩 제거
        while (!st.empty() && h[st.top()] <= h[i]) {
            st.pop();
        }

        // 오른쪽에서 보이는 빌딩 수 추가
        cnt[i] += st.size();

        // 가장 가까운 빌딩 갱신
        if (!st.empty()) {
            // 이미 왼쪽에서 가까운 빌딩이 있다면
            if (nearIdx[i] != 0) {
                // 거리 비교해서 더 가까운 쪽 선택
                if (abs(st.top() - i) < abs(nearIdx[i] - i)) {
                    nearIdx[i] = st.top();
                }
            } else {
                // 왼쪽에 없으면 오른쪽이 가장 가까움
                nearIdx[i] = st.top();
            }
        }

        // 현재 빌딩 push
        st.push(i);
    }

    for (int i = 1; i <= N; i++) {
        if (cnt[i] == 0) {
            // 보이는 빌딩이 하나도 없을 때
            cout << 0 << "\n";
        } else {
            cout << cnt[i] << " " << nearIdx[i] << "\n";
        }
    }

    return 0;
}