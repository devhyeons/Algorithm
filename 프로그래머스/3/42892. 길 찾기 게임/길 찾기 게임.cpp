#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 두 팀으로 나누고, 각 팀이 같은 곳을 다른 순서대로 방문하도록 해서, 
// 먼저 순회를 마친 팀이 승리 하는 것.

// 방문할 곳을 2차원 좌표 값을 구하고, 각 장소를 이진트리의 노드가 되도록 구성한 후
// 순회 방법을 힌트로 주어 각 팀이 스스로 경로를 찾도록 할 계획

// 모든 노드는 다른 x값을 가진다.
// 같은 레벨에 있는 노드는 같은 y좌표를 갖는다.
// 자식 노드의 y값은 항상 부모 노드보다 작다.

// 임의의 노드 v의 왼쪽 서브 트리에 있는 모든 노드의 x값은 v의 x값보다 작다.
// 오른쪽 서브트리는 v의 x값보다 크다 

// 이진 트리 구성하는 노드 담긴 좌표 주어질 때
// 노드들로 구성된 이진트리를 전위 순회, 후위 순회한 결과 2차원 배열에 return 

vector<int> L;
vector<int> R;
vector<int> X;
vector<int> pre, post;

void insertBST(int root, int idx){
    int curNode = root;
    while(true){
        if(X[curNode] > X[idx]){
            if (L[curNode] != -1) {
                curNode = L[curNode];
            }
            else {
               L[curNode] = idx;   
               break;
            }
        }
        
        else {
            if (R[curNode] != -1){
                curNode = R[curNode];
            }
            else {
               R[curNode] = idx; 
               break;
            }
        }
    }
    
}

// 전위순회 
void prevOrder(int root){
    if (root == -1) return;
    pre.push_back(root);
    prevOrder(L[root]);
    prevOrder(R[root]);
}

// 후위순회 
void postOrder(int root){
    if (root == -1) return;
    postOrder(L[root]);
    postOrder(R[root]);
    post.push_back(root);
}
bool comp (vector<int> a, vector<int> b){
    if (a[1] == b[1]){
        return a[0] < b[0];
    }
    return a[1] > b[1];
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    int n = nodeinfo.size();
    L.resize(n+1, -1);
    R.resize(n+1, -1);
    X.resize(n+1,-1);
    for (int i=0; i<nodeinfo.size(); i++){
       nodeinfo[i].push_back(i+1);
       X[i+1] = nodeinfo[i][0];
    }
    
    sort(nodeinfo.begin(), nodeinfo.end(), comp);
    
    int root = nodeinfo[0][2];
    for (int i=1; i<nodeinfo.size(); i++){
        int idx = nodeinfo[i][2];
        insertBST(root, idx);
    }
    
    prevOrder(root);
    postOrder(root);
    
    answer.push_back(pre);
    answer.push_back(post);
    
    
    return answer;
}