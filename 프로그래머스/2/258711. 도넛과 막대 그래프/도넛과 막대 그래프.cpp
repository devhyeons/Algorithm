#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// 모든 노드의 연결 관계 저장
vector<int> graph[1000001];

// 진입 차수 / 진출 차수
// inDeg : 해당 노드로 들어오는 간선 개수
// outDeg : 해당 노드에서 나가는 간선 개수
vector<int> inDeg(1000001);
vector<int> outDeg(1000001);


// 그래프 개수
int donut = 0;  // 도넛 그래프 개수
int stick = 0;  // 막대 그래프 개수
int eight = 0;  // 8자 그래프 개수


int maxNode = -1; // 존재하는 가장 큰 노드 번호
int root = -1;    // 생성한 정점 번호


// DFS 탐색 후 그래프 형태 판단을 위한 정보
struct graphType {
    bool hasCycle = false; // 순환 존재 여부 (도넛, 8자)
    bool hasCross = false; // 교차점 존재 여부 (8자)
    bool hasEnd  = false;  // 끝점 존재 여부 (막대)
};


// 현재 연결된 그래프를 DFS 탐색하면서 특징 확인
void dfs(int node, graphType &info, unordered_set<int> &path){

    // 현재 탐색 중인 경로에서 같은 노드를 다시 만남
    // ex) 1 -> 2 -> 3 -> 1
    // 사이클 존재
    if (path.count(node)){
        info.hasCycle = true;
        return;
    }


    // 현재 DFS 경로에 노드 추가
    path.insert(node);


    // 더 이상 연결된 노드가 없다면 끝점
    // 막대 그래프는 마지막 노드의 outDegree가 0
    if (graph[node].empty()){
        info.hasEnd = true;
        return;
    }


    // inDegree와 outDegree가 모두 2 이상인 노드 존재
    // 여러 갈래가 합쳐지고 다시 나가는 구조
    // => 8자 그래프의 중심점
    if (inDeg[node]>=2 && outDeg[node]>=2 ){
        info.hasCross = true;
    }


    // 연결된 다음 노드 탐색
    for (int nxt : graph[node]){
        dfs(nxt, info, path);
    }
}





vector<int> solution(vector<vector<int>> edges) {

    vector<int> answer;


    // 방향 그래프 생성
    for (auto e : edges){

        int u = e[0];
        int v = e[1];


        // u -> v 간선 추가
        graph[u].push_back(v);


        // 진입 / 진출 차수 계산
        outDeg[u]++;
        inDeg[v]++;


        // 존재하는 최대 노드 번호 저장
        maxNode = max(maxNode, max(u,v));
    }



    // 생성한 정점 찾기
    //
    // 생성 정점 특징:
    // 1. 다른 정점에서 들어오는 간선이 없음
    // 2. 여러 그래프를 만들기 위해 2개 이상의 간선을 가짐
    //
    // 즉:
    // inDegree == 0
    // outDegree >= 2
    //
    for (int i=1; i<=maxNode; i++){

        if (inDeg[i]==0 && outDeg[i]>=2) {

            root = i;
            break;
        }
    }



    // 생성 정점에서 연결된 각각의 그래프 탐색
    //
    // root
    //  ├── 도넛
    //  ├── 막대
    //  └── 8자
    //
    // 각각 독립된 그래프이므로 자식 노드마다 DFS 실행
    for (auto n : graph[root]){


        // 현재 그래프에서만 사용할 방문 경로
        unordered_set<int> path;


        // 현재 그래프 특징 저장
        graphType info;


        // root 다음 노드부터 탐색
        dfs(n, info, path);



        // 사이클 존재
        // => 도넛 또는 8자
        if (info.hasCycle){


            // 교차점 존재
            // => 8자 그래프
            if (info.hasCross){
                eight++;
            }


            // 사이클만 존재
            // => 도넛 그래프
            else {
                donut++;
            }

        }


        // 사이클 없음
        // => 끝점이 존재하는 막대 그래프
        else {
            stick++;
        }
    }



    // 결과 반환
    // [생성한 정점 번호, 도넛 개수, 막대 개수, 8자 개수]
    answer.push_back(root);
    answer.push_back(donut);
    answer.push_back(stick);
    answer.push_back(eight);


    return answer;
}