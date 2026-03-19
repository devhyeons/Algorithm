#include <iostream>
#include <algorithm>
#include <queue>

// 알고리즘 : 브루트포스 

using namespace std;

// 리모컨에는 버튼 0~9까지와 +,-가 있다.
// + : 현재보고있는 채널 +1 채널
// - : 현재 -1 채널로 이동
// 0에서 - 누르면 -> 채널 변화 x

// 수비니가 지금 이동하려는 채널은 N이다.
// 어떤 버튼이 고장났는지 주어질 때, 채널 N이동하기 위해 최소 몇번 눌러야 하는가?

// 수빈이가 현재 보고있는 채널은 100이댜.

// 채널 n<= 5*10^5
// 고장난 버튼의 갯수 M : 10개


bool broken[10];
int n,m;

bool canMake(int num){
    if (num == 0) return !broken[0];
    while(num > 0){
        if (broken[num%10]) return false;
        num = num/10;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i=0; i<m; i++){
        int x; cin >> x;
        broken[x] = true;
    }

    // 숫자 번호 안쓰고, + - 만 사용하는 경우
    int answer = abs(n - 100);

    // 완전히 커버 가능한 모든 숫자를 위해서 i= 1000000 까지 살펴봄. 
    for (int i=0; i<=1000000; i++){
        // i를 만들 수 있으면
        if (canMake(i)){
            // 숫자 버튼 누른 횟수 + (+,- 이동 횟수)
            int cnt = to_string(i).length() + abs(n-i);
            // +,- 로만 만드는 경우랑 min 비교
            answer = min(answer,cnt);
        }
    }

    cout << answer;

    return 0;
}