#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

// n의 네자릿수 d1, d2, d3, d4
// 1. d : d는 n을 두배로 바꾼다.

// 2. s : n = n-1을 저장
// 3. L = n의 각 자릿수 왼편 회전 (d2,d3,d4,d1)
// 4. R = n 각 자릿수 오른쪽 회전 (d4,d1,d2,d3)

// A -> B로 바꾸는 최소 명령은?
// A-> B로 바꾸는 최소 명령어 나열을 출력

int t;
char op[4] = {'D', 'S', 'L', 'R'};

string bfs(int a, int b){

    bool visited[100001] = {false};
    queue<pair<int,string>> q;
    q.push({a, ""});
    visited[a] = true;

    while(!q.empty()){
        auto [cur, ops] = q.front();
        q.pop();

        int nxt[4];
        nxt[0] = (cur*2)%10000;
        nxt[1] = (cur==0) ? 9999 : cur-1;
        nxt[2] = (cur%1000) * 10 + cur/1000;
        nxt[3] = (cur%10) * 1000 + cur/10;

        for (int i=0; i<4; i++){
            if (nxt[i] == b){
                return ops + op[i];
            }

            if (!visited[nxt[i]]){
                visited[nxt[i]] = true;
                q.push({nxt[i], ops+op[i]});
            }
        }
    }
    return "";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;

    while(t--){
        int a,b;
        cin >> a >> b;
        cout << bfs(a,b) << "\n";
    }

    return 0;
}