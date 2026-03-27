#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

// 도시에는 N개의 빌딩이 있다.
// i번째 빌딩의 키는 hi, 모든 빌딩은 일렬로 서있고 오른쪽에서만 볼 수 있다.

// i번째 빌딩 관리인이 볼 수 있는 다른 빌딩 옥상정원은 i+1 ~ N이다.

// 그러나 자신의 위치한 빌딩보다 높거나 같은 빌딩 있으면 그 다음 모든 빌딩 볼 수 없다.

// 각 관리인들이 벤치마팅 가능한 빌딩의 수 합을 출력한다.

// N <= 8 * 10^4

int n;
stack<long long> s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    long long ans = 0;

    int input;
    for (int i=1; i<=n; i++){
        cin >> input;
        while(!s.empty() && s.top() <= input){
            s.pop();
        }
        // 현재 들어온 값의 건물을 볼 수 있는 왼쪽 건물들의 갯수
        // 따라서 현재의 s.size() 를 ans에 더하는 것임.
        ans = ans  + s.size();

        s.push(input);
    }

    cout << ans << "\n";

    return 0;
}