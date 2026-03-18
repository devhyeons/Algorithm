#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

// 문자열에 폭발 문자열을 심어놓았다.
// 폭발 문자열 폭발시 -> 그 문자는 문자열에서 사라지고, 남은 문자열 합체.

// 폭발 과정
// 1. 문자열이 폭발 문자열 포함하는 경우, 모든 폭발 문자열 폭발
// 2. 남은 문자열 순서대로 이어붙여 새로운 문자열 만듬
// 3. 새로운 문자열에도 폭발 문자열 있을 수 있따.
// 4. 폭발은 폭발 문자열이 없어질때까지 계쏙 한다.

// 모든 폭발 끝난 후 어떤 문자열이 남는지 구하기
// 남은 문자열이 없는 경우 -> "FRULA"출력

string input, bomb;
string ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> input;
    cin >> bomb;

    stack<char> s;
    ans.reserve(1000000); //미리 할당
    int bombSize = bomb.size();

    for (int i=0; i<input.size(); i++){
        s.push(input[i]);

        if (input[i] == bomb[bombSize-1] && s.size() >= bombSize){
            string tmp;
            for (int j=0; j<bombSize; j++){
                tmp.push_back(s.top());
                s.pop();
            }

            reverse(tmp.begin(), tmp.end());

            if (tmp != bomb){
                for (int i=0; i<tmp.size(); i++){
                    s.push(tmp[i]);
                }
            }
        }
    }

    while(!s.empty()){
        ans.push_back(s.top());
        s.pop();
    }

    reverse(ans.begin(), ans.end());

    if (ans.empty()) cout << "FRULA" << "\n";
    else cout << ans;

    return 0;
}