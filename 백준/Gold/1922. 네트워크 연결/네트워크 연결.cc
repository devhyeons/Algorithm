#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

int n,m;

int parent[1001];

struct Edge{
    int u,v,w;
};

vector<Edge> edges;

void initParent(){
    for (int i=1; i<=n; i++){
        parent[i] = i;
    }
}

int find(int x){
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unionSet(int a, int b){
     int pa = find(a);
     int pb = find(b);

     if (pa==pb) return;

     if (pa < pb){
         parent[pb] = pa;
     }
     else {
         parent[pa] = pb;
     }
}

bool comp(Edge a, Edge b){
    return a.w < b.w;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> m;

    int a,b,c;
    for (int i=0; i<m; i++){
        cin >> a >> b >> c;
        edges.push_back({a,b,c});
    }

    sort(edges.begin(), edges.end(), comp);

    initParent();

    int minCost = 0;

    for (auto e : edges){
        if (find(e.u) != find(e.v)){
            unionSet(e.u, e.v);
            minCost = minCost + e.w;
        }
    }

    cout << minCost << "\n";

    return 0;
}