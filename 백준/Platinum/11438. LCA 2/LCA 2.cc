#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;


// LCA : 최소 공통 조상 찾기
// 1 << k 활용

// parent[k][v] = v의 2^k번째 부모 의미.

int parent[21][100001];
int n;

// 1. 인접 리스트로 트리 구성
// 2. dfs로 depth 배열 만들기
// 3. parent 채우기
// -- LCA 구하기
// 4. depth 맞추고, 공통 점프 진행
// 5. return parent[0][a] 하기.

vector<int> graph[100001];
int depth[100001];

void dfs(int cur, int par){
    parent[0][cur] = par;
    for (auto nxt : graph[cur]){
        if (nxt == par) continue;
        depth[nxt] = depth[cur]+1;
        dfs(nxt, cur);
    }
}

int lca(int a, int b){
    if (depth[a] < depth[b]) {
        swap(a,b);
    }

    int diff = depth[a]-depth[b];

    // depth 맞추기
    for (int k=0; k<21; k++){
        if (diff & (1 << k)) {
            a = parent[k][a]; // 상위 부모로 올라간다.
        }
    }

    if (a == b) {
        return a;
    }

    // 같이 점프
    for (int k=20; k>=0; k--){
        if (parent[k][a] != parent[k][b]){
            a= parent[k][a];
            b = parent[k][b];
        }
    }

    return parent[0][a];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    int a, b;

    for (int i=0; i<n-1; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1,0);

    for (int k=1; k<21; k++){
        for (int v=1; v<=n; v++){
            parent[k][v] = parent[k-1][parent[k-1][v]];
        }
    }

    int m;
    cin >>m;

    int qa,qb;
    for (int i=0; i<m; i++){
        cin >> qa >> qb;
        cout << lca(qa, qb) << "\n";
    }

    return 0;
}