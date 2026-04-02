#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

// M개의 우주가 있고, 각 우주에는 1~N 번호까지 매겨진 행성 N개 있다.

// 행성의 크기 알고있을 때, 균등한 우주의 쌍이 몇 개인지 구하시오.
// 구성이 같은데 순서만 다른 우주의 쌍은 한 번만 센다.

// 두 우주 A,B가 있고, 우주 A에 있는 행성크기 A..n
// 우주 B에 있는 행성 크기 B..Bn

// 두 우주의 행성 크기가 모든 1<=i,j<=N에 대해 아래 조건 만족 시 두 우주 균등
// Ai<Aj -> Bi<Bj
// Ai=Aj -> Bi=Bj
// Ai>Aj -> Bi>Bj

// 균등한 우주 쌍의 개수는?

int m,n;


map<vector<int>, int> mp; // 해당 배열,cnt 수

bool comp(int a, int b){
    return a > b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    int input;
    for (int i=0; i<m; i++){
        vector<int> copyP;
        vector<int> origin;
        for (int j=0; j<n; j++){
            cin >> input;
            origin.push_back(input);
            copyP.push_back(input);
        }

        sort(copyP.begin(), copyP.end(),comp);
        copyP.erase(unique(copyP.begin(), copyP.end()), copyP.end());

        vector<int> compressed(n);

        for (int j=0; j<n; j++){
            // 값 -> 순위로 변경
            // lower_bound(시작위치, 끝위치, 찾을값, 비교함수)
            int rank = lower_bound(copyP.begin(), copyP.end(), origin[j],comp) - copyP.begin();
            compressed[j] = rank;
        }


        mp[compressed]++;
    }

    long long ans = 0;
    for (auto & m : mp){
        long long cnt = m.second;
        if (cnt >=2){
            ans = ans + (cnt * (cnt-1))/2;
        }
    }

    cout << ans << "\n";

    return 0;
}