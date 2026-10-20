#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

// ** Union-Find로 집합관계 찾기 

// 표 크기는 50*50으로 고정
// 초기 모든 셀은 비어있음
// 각 셀은 문자열 값 가질 수 있고, 다른 셀과 병합 가능
// (r,c) 각 명령 기능 구현

// 1. update r c value
// r,c 셀 값을 value로 변경

// 2. update value1, value2
// value1 값 갖고있는 모든 셀 선택 -> value2로 변경

// 3. merge r1 c1 r2 c2 
// 두개 셀 병합 (단 동일 위치 시 무시)
// 선택한 두 셀이 인접하지 않을 수 있다. 
// 두 셀중 한 셀이 값을 가질 경우, 병합 셀도 그 값 갖게됨.
// 모두 값 가질 경우 r1,c1 위치 셀 값 갖게됨
// 이후에는 어느위치 선택해도 병합된 셀로 접근

// 4. unmerge r c
// r,c 위치 셀 선택하여 해당 셀의 모든 병합 해제
// 병합 해제전 셀이 값 갖고 있을 경우 그 위치 값 그대로 갖게됨.

// 5. print r c
// r c 위치 셀 값 출력
// 셀 비어있을 경우 "EMPTY" 출력

int parent[2601]; 
string cell[2601];


int getId(int r, int c){
    return (r-1) * 50 + c;
}

int findParent(int x){
    if (parent[x] == x) return x;
    return parent[x] = findParent(parent[x]);
}


void mergeCell(int a, int b){
    int rootA = findParent(a);
    int rootB = findParent(b);
    
    if (rootA == rootB) return;
    
    if (cell[rootA].empty()){
        cell[rootA] = cell[rootB];
    }
    
    parent[rootB] = rootA;
    cell[rootB] = "";
}

void unmergeCell(int x){
    int root = findParent(x);
    string savedValue = cell[root];
    vector<int> members;
    
    for (int i=1; i<=2500; i++){
        if (findParent(i) == root){
            members.push_back(i);
        }
    }
    
    for (int id : members){
        parent[id] = id;
        cell[id] = "";
    }
    
    cell[x] = savedValue;
}


vector<string> solution(vector<string> commands) {
    vector<string> answer;
    
    for (int i=1; i<=2500; i++){
        parent[i] = i;
        cell[i] = "";
    }

    
    for (auto c : commands){
        stringstream ss(c);
        
        string cmd;
        
        ss >> cmd;
        
       
if (cmd == "UPDATE") {
    vector<string> tokens;
    string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    if (tokens.size() == 3) {
        // UPDATE r c value
        int r = stoi(tokens[0]);
        int c = stoi(tokens[1]);
        string value = tokens[2];

        int id = getId(r, c);
        int root = findParent(id);

        cell[root] = value;
    }
    else if (tokens.size() == 2) {
        // UPDATE value1 value2
        string value1 = tokens[0];
        string value2 = tokens[1];

        for (int i = 1; i <= 2500; i++) {
            if (findParent(i) == i &&
                cell[i] == value1) {
                cell[i] = value2;
            }
        }
    }
}

        else if (cmd == "MERGE"){
            int r1,c1,r2,c2;
            ss >> r1 >> c1 >> r2 >> c2;
            
            int a = getId(r1,c1);
            int b = getId(r2,c2);
            
            mergeCell(a,b);
            
        }
        else if (cmd == "UNMERGE"){
            int r,c;
            ss >> r >> c;
            
            int id = getId(r,c);
            unmergeCell(id);
        }
        else if (cmd == "PRINT"){
            int r,c;
            ss >> r >> c;
            int id = getId(r,c);
            
            int root = findParent(id);
            
            if (cell[root].empty()){
                answer.push_back("EMPTY");
            }
            
            else {
                answer.push_back(cell[root]);
            }
        }
        else {
            
        }
    }
    return answer;
}