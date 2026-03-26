#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dp[50005];


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int t = 0; t<3; t++){
        int n;
        cin >> n;

        int totalSum = 0;
        vector<int> coinVal(n);
        vector<int> coinCnt(n);

        for (int i=0; i<n; i++){
            cin >> coinVal[i] >> coinCnt[i];
            totalSum = coinVal[i] * coinCnt[i] + totalSum;
        }



        if (totalSum %2 != 0){
            cout << 0 << "\n";
            continue;
        }

        int target = totalSum/2;

        for (int i=0; i<50005; i++){
            dp[i] = 0;
        }

        dp[0] = 1;

        for (int i=0; i<n; i++){
            int v = coinVal[i];
            int c = coinCnt[i];

            for (int j=target; j>=0; j--){
                if (dp[j]){
                    for (int k=1; k<=c && j+v*k <= target; k++){
                        if(dp[j+v*k]) continue;
                        dp[j+v*k] = 1;
                    }
                }
                if (dp[target]) break;
            }
            if (dp[target]) break;
        }

        cout << dp[target] << "\n";
    }



    return 0;
}