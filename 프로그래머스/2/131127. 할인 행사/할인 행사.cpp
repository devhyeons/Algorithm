#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> category;
unordered_map<string, int> visited;

bool checkVisited(unordered_map<string, int> v) {
    for (auto c : category) {
        if (v[c.first] < c.second) {
            return false;
        }
    }
    return true;
}

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;

    for (int i = 0; i < want.size(); i++) {
        category[want[i]] = number[i];
    }

    int windowSize = 10;

    // 첫 번째 윈도우
    for (int i = 0; i < windowSize; i++) {
        visited[discount[i]]++;
    }

    if (checkVisited(visited)) {
        answer++;
    }

    // 윈도우 이동
    for (int i = 1; i <= discount.size() - windowSize; i++) {
        visited[discount[i - 1]]--;
        visited[discount[i + windowSize - 1]]++;

        if (checkVisited(visited)) {
            answer++;
        }
    }

    return answer;
}