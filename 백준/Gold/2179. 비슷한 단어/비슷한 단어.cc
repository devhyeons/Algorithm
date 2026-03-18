#include <iostream>
#include <algorithm>
#include <set>
#include <map>


using namespace std;

// N개의 영단어가 주어질 때, 가장 비슷한 두 단어 구해내는 프로그램

// 두 단어의 비슷한 정도는 두 단어의 '접두사 길이'로 측정한다.
// 접두사  = 앞부분에서 공통적으로 나타나는 문자열

// 접둑사 길이가 최대인 경우가 여러개 일 때에는 입력 순서대로 제일 앞쪽 단어를 답
// 비슷한 두 단어 구할 때, 같은 단어는 제외한다.

int n;
vector<string> orderInput;

struct Node{
    string word;
    int idx;
};

bool comp(Node a, Node b){
    if (a.word == b.word) return a.idx < b.idx;
    return a.word < b.word;
}

int getLcp(const string & a, const string & b){
    int len = min(a.length(), a.length());
    int cnt = 0;
    for (int i=0; i<len; i++){
        if (a[i] == b[i]) cnt++;
        else break;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    vector<Node> sortedNodes;

    for (int i=0; i<n; i++){
        string s;
        cin >> s;
        orderInput.push_back(s);
        sortedNodes.push_back({s,i});
    }
    // 1. 사전순 정렬 (비슷한 단어끼리 인접, 입력 순서 고려)
    sort (sortedNodes.begin(), sortedNodes.end(), comp);

    // 2. 인접한 단어들끼리 LCP 최댓값 찾기 (접두사)
    int maxLen = 0;
    for (int i=0; i<n-1; i++){
        int lcp = getLcp(sortedNodes[i].word, sortedNodes[i+1].word);
        if (lcp > maxLen) maxLen = lcp;
    }

    // 3. "입력 순서" 조건 맞추기
    // 원본 순서대로 순회하며, 해당 단어가 maxLen만큼 접두사 갖는지 확인.

    string s1 = "", t1= "";
    bool found = false;

    for (int i=0; i<n; i++){
        string target = orderInput[i].substr(0,maxLen);
        if (s1 == ""){
            int cnt = 0;
            for (int j = i+1; j<n; j++){
                if (orderInput[j].length() >= maxLen && orderInput[j].substr(0, maxLen) == target){
                    if (orderInput[i]==orderInput[j]) continue;
                    s1=orderInput[i];
                    t1 = orderInput[j];
                    found = true;
                    break;
                }
            }
        }
        if (found) break;
    }

    cout << s1 << "\n";
    cout << t1 << "\n";

    return 0;
}