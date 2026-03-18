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

    for (auto l : lights){
        candi.push_back({max(0,l-h),min(n,l+h)});
    }

    if (candi[0].start != 0) {
        return false;
    }

    int last = candi[0].last;
    for (auto c : candi){
        if (c.start > last){
            return false;
        }
        last = c.last;
    }

    if (last == n) return true;
    else return false;
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
    int ans;

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