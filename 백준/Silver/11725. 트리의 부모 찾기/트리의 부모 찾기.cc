
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;


// 노드 개수 N
// N-1 연결 두 정점 주어짐.

// 부모 노드 번호 2번부터 순서대로 출력

vector<int> adj[100001];
int parent[100001];
// v의 2^k번째 조상

int n;

void dfs(int cur, int par){
    parent[cur] = par;
    for (auto nxt : adj[cur]){
        // 방금 타고온 부모가 = 다음이랑 똑같으면 xx 넘어감
        if (nxt == par) continue;
        dfs(nxt, cur);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    int u,v;
    for (int i=0; i<n-1; i++){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1,1);

    for (int i=2; i<=n; i++){
        cout << parent[i] << "\n";
    }

    return 0;
}