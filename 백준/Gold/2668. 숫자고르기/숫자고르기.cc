#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>

using namespace std;


// 세로 2줄
// 가로 N칸으로 이루어진 표가 있다.

// 첫째줄 칸에는 1,2,...N이 차례대로 들어있고
// 둘째 줄에는 각 칸 1~N이하 정수 있다.

// 첫번째 줄 숫자 적절히 뽑으면, 바로 밑 둘째줄 집합과 일치
// 최대한 정수들을 많이 뽑는 방법 찾기.

// N<=100

// 첫째줄에 뽑은 정수 수와
// 뽑은 수들 오름차순 출력

int graph[101];
bool visited[101] = {false};
bool finished[101] = {false};
int n;
vector<int> ans;

// 순환 체크
void dfs(int x){
    visited[x] = true;
    int next = graph[x];

    if (!visited[next]){
        dfs(next);
    }

    // 아예 경로 탐색 끝났는지 확인
    else if (!finished[next]){
        for (int i=next; i!=x; i=graph[i]){
            ans.push_back(i);
        }
        ans.push_back(x);
    }

    finished[x] = true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int input;
    cin >> n;

    for (int i=1; i<=n; i++){
        cin >> input;
        graph[i] = input;
    }

    for (int i=1; i<=n; i++){
       if (!visited[i]){
           dfs(i);
       }
    }


    cout << ans.size() << "\n";
    sort(ans.begin(), ans.end());
    for (auto a : ans){
        cout << a << "\n";
    }
    return 0;
}