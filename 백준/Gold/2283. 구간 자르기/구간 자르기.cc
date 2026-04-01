#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 수직선 상에 구간 N개가 있다,.
// 임의의 두 정수 (A<B) 정하여
// 각 구간에서 A와 B 사이에 포함되지 않는 부분을 모두 잘라냈을 때
// 남은 부분들의 길이 총 합이 K가 되도록 하자.

// N 주어짐
// 2~N+1번째 줄에 왼쪽끝점과 오른쪽 끝점 위치 주어진다.
// 양 끝점 위치는 0이상

// 두 정수 A,B 출력
// 존재하지 않으면 0 0
// 존재할 때 여러개이면 A가 가장 작은 경우
// 그것도 여러개면 B가 가장 작은 경우 출력


int n,k;
int cnt[1000002];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    for (int i=0; i<n; i++){
        int s,e;
        cin >> s >> e;
        for (int j=s; j<e; j++){
            cnt[j]++;
        }
    }

    int left =0;
    int right= 0;
    long long currentSum = 0;

    while(left <= right && right<=1000000){
        if (currentSum == k){
            cout << left  << " " << right << "\n";
            return 0;
        }
        else if (currentSum < k ){
            currentSum = currentSum + cnt[right];
            right++;
        }
        else{
            currentSum = currentSum-cnt[left];
            left++;
        }
    }

    cout << 0 << " " << 0 << "\n";


    return 0;
}