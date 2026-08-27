#include <bits/stdc++.h>
using namespace std;

vector<int> prevArr;
vector<int> nextArr;
vector<int> deleted; // ← 네 방식 그대로: 삭제된 행을 스택처럼 push/pop
vector<char> state;


string solution(int n, int k, vector<string> cmd) {
    string ans;

    prevArr.resize(n);
    nextArr.resize(n);
    deleted.clear();

    state.resize(n, 'O');
    
    // 원형 X, 경계는 -1
    for (int i = 0; i < n; ++i) {
        prevArr[i] = (i == 0 ? -1 : i - 1);
        nextArr[i] = (i == n - 1 ? -1 : i + 1);
    }

    for (auto &c : cmd) {
        if (c[0] == 'U') {
            int x = stoi(c.substr(2));
            while (x-- && prevArr[k] != -1) k = prevArr[k];
        }
        else if (c[0] == 'D') {
            int x = stoi(c.substr(2));
            while (x-- && nextArr[k] != -1) k = nextArr[k];
        }
        else if (c[0] == 'C') {
            deleted.push_back(k);
            state[k] = 'X';
            int p = prevArr[k], nx = nextArr[k];
            if (p != -1) nextArr[p] = nx;
            if (nx != -1) prevArr[nx] = p;

            // 커서 이동: 아래가 있으면 아래, 없으면 위
            k = (nx != -1 ? nx : p);
        }
        else if (c[0] == 'Z') {
            
            int r = deleted.back();
            state[r] = 'O';
            deleted.pop_back();

            int p = prevArr[r], nx = nextArr[r]; // 삭제 당시 값이 그대로 남아있음

            // 원래 자리로 다시 연결
            if (p != -1) nextArr[p] = r;
            if (nx != -1) prevArr[nx] = r;
            // prevArr[r], nextArr[r]는 그대로 두면 됨
        }
    }
    for (int i = 0; i < n; ++i) ans.push_back(state[i]);
    
    return ans;
}

