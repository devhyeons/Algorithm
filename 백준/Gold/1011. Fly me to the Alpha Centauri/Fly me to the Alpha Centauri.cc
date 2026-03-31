#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// 수학적 계산

int x,y;
int t;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    for (int i=0; i<t; i++){
        cin >> x >> y;
        
        long long d = y-x; // 이동해야 하는 거리
        
        long long k = sqrt(d); // 1->2-> .. k -> ... -> 1로 최대 ㅏ
        
        if (k*k == d){
            cout << 2*k -1 << "\n";
        }
        
        else if (k*k+k >= d){
            cout << 2 * k << "\n";
        }
        
        else {
            cout << 2*k + 1 << "\n";
        }
    }

    return 0;
}