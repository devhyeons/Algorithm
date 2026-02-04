#include <iostream>
#include <algorithm>

using namespace std;

// N개 수 중 어떤 수가
// 다른 두개의 수 합으로 나타낼 수 있으면 -> 좋다.

// N개의 수 주어질 때, 좋은 수의 개수는 몇개일까?

// 수의 위치가 다르면, 같아도 다른 수이다.

int n;
int input;

// n<=2* 10^3;
// input <= 10^9

int nums[2001];

// 투포인터로 풀기

bool isGood(int target, int idx){
    int l = 0;
    int r = n-1;

    while(l < r){
        if (l==idx){
            l++;
            continue;
        }
        if (r==idx){
            r--;
            continue;
        }
        
        long long sum = nums[l] + nums[r];
        if (sum == target){
            return true;
        }

        else if (sum < target){
            l++;
        }
        else {
            r--;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i=0; i<n; i++){
        cin >> input;
        nums[i] = input;
    }

    int cnt = 0;

    sort (nums, nums+n);

    for (int i=0; i<n; i++){
        if (isGood(nums[i],i)){
            cnt++;
        }
    }

    cout << cnt << "\n";

    return 0;
}