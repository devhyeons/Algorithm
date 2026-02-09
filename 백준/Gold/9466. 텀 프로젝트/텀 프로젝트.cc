#include <iostream>
#include <algorithm>

using namespace std;

int t;
int graph[100001];
bool visited[100001];
bool finished[100001];
vector<int> ans;


void init(){
    for (int i=0; i<100001; i++){
        graph[i] = -1;
        visited[i] = false;
        finished[i] = false;
    }
}

void dfs(int x){
    visited[x] = true;
    int nxt = graph[x];

    if (!visited[nxt]){
        dfs(nxt);
    }

    else if (!finished[nxt]){
        for (int i=nxt; i!=x; i=graph[i]){
            ans.push_back(i);
        }
        ans.push_back(x);
    }
    finished[x] = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while(t--){
        init();
        int n,input;
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
        cout << n-ans.size() << "\n";
        ans.clear();
    }
    return 0;
}