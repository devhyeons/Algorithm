#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

long long sum = LLONG_MAX;

// 두 용액을 혼합해서 -> 0에 가장 가까운 용액 만들기..
// 오름차순 정렬 -> 투포인터 활용 .. (2개 합..)

int n;
vector<int> arr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    int input;
    for (int i=0; i<n; i++){
        cin >> input;
        arr.push_back(input);
    }

    sort(arr.begin(), arr.end());

    int st = 0;
    int ed = n-1;

    int ansSt = 0;
    int ansEd = 0;

    while(st < ed){
        long long curSum = arr[st] + arr[ed];
        if (curSum == 0){
            cout << arr[st] << " " << arr[ed] << "\n";
            return 0;
        }

        else if (curSum > 0){
            if (abs(sum) > abs(curSum)){
                ansSt = st;
                ansEd = ed;
                sum = curSum;
            }
            ed--;
        }

        else {
            if (abs(sum) > abs(curSum)){
                ansSt = st;
                ansEd = ed;
                sum = curSum;
            }
            st ++;
        }
    }

    cout << arr[ansSt] << " " << arr[ansEd] << "\n";

    return 0;
}
