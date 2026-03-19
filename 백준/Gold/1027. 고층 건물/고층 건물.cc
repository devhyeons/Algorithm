#include <iostream>
#include <algorithm>

using namespace std;

// 가장 많은 고층 빌딩이 보이는 고층 빌딩 찾으려 한다.
// 빌딩 총 N개 있는데, 빌딩은 선분으로 나타냄

// i번째 빌등은 (i,0)부터 (i,높이까지)
// 고층 빌딩 A에서 다른 고층빌딩 B 볼수있으려면,
// 두 지붕을 잇는 선분 A,B제외 다른 고층빌딩을 지나거나 접하지 않아야한다.

// 가장 많은 고층 빌딩이 보이는 빌딩 구하고, 거기서 보이는 빌딩 수 출력

// 빌딩 수 = N <= 5 * 10^1
// 높이는 <= 10^9

int n;
long long buildings[51];
long long input;
int maxBuild[51];

bool comp(int a, int b){
    return a > b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;

    // 가장 많은 고층 빌딩이 보이는 빌딩과, 거기서 보이는 빌딩 수 출력.
    for (int i=1; i<=n; i++){
        cin >> buildings[i];
    }


    for (int i=1; i<=n; i++){
        for (int j=1; j<=n; j++){
            // 2개씩 쌍 찾기.
            if (i==j) continue;

            double a = (double)(buildings[i] - buildings[j]) / (i- j); // 기울기
            double c = buildings[i] - (a * i);

            bool isFail = false;
            int startIdx = min(i,j);
            int endIdx = max(i,j);

            for (int k=startIdx+1; k<endIdx; k++){
                if ((double)(a*k)+c <= buildings[k]) {
                    isFail = true;
                    break;
                }
            }

            if (!isFail) {
                maxBuild[i] ++;
            }
        }
    }


    sort(maxBuild, maxBuild+n+1, comp);
    cout << maxBuild[0] << "\n";

    return 0;
}