#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <set>

using namespace std;

// 가로등 설치 개수 M, 가로등 위치 x 결정
// 각 가로등은 높이만큼 주위를 비출 수 있다.
// 최소한의 높이로 모든 길 0~N을 밝히고자 한다.

// 가로등 높이 H : 왼쪽 H, 오른쪽 H 만큼 비춘다.

// 굴다리 N을 모두 비추기 위한 가로등의 최소 높이는?

int n,m;
vector<int> lights;

struct Loca{
    int start,last;
};

bool availH(int h){
    vector<Loca> candi;

    // 시작점 체크
    if (lights[0]-h > 0) return false;

    int last = lights[0]+h;
    for (int i=1; i<m; i++){
        if (lights[i]-h > last){
            return false;
        }
        last = lights[i]+h;
    }

    // 끝점 체크
    return last >= n;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> m;
    int x;

    for (int i=0; i<m; i++){
        cin >> x;
        lights.push_back(x);
    }

    int left = 1;
    int right = n;
    int ans = n; //초기화 필수.

    while (left <= right){
        int mid = (left + right)/2;
        if (availH(mid)){
            right = mid -1;
            ans = mid;
        }
        else {
            left = mid +1;
        }
    }

    cout << ans << "\n";
    return 0;
}