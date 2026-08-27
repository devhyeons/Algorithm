#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// kruskal 문제 !

struct edge {
    int u, v, w;
};

int parent[102];

int findParent(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findParent(parent[x]); // 경로 압축
}

bool unionSet(int a, int b) {
    int pa = findParent(a);
    int pb = findParent(b);
    if (pa == pb) return false; // 싸이클 방지
    
    // 항상 한쪽 루트를 다른 루트에 붙인다
    if (pa < pb) parent[pb] = pa;
    else parent[pa] = pb;
    return true;
}

bool comp(edge a, edge b) {
    return a.w < b.w;
}

int solution(int n, vector<vector<int>> costs) {
    vector<edge> edges;
    for (auto &c : costs) {
        edges.push_back({c[0], c[1], c[2]});
    }
    
    for (int i = 0; i < n; i++) parent[i] = i; // parent 초기화
    
    sort(edges.begin(), edges.end(), comp);
    
    int answer = 0, cnt = 0;
    for (auto &e : edges) {
        if (unionSet(e.u, e.v)) {
            answer += e.w;
            cnt++;
            if (cnt == n - 1) break; // MST 완성
        }
    }
    
    return answer;
}
