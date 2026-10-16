#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <cstring>

using namespace std;

// 다음과 같은 순서대로 과제하려고 계획 세움
// 1. 시작하기로 한 시간 되면 시작
// 2. 새로운 과제를 시작할 시각이 되었을 때,
// 기존 진행중이던 과제 있으면 -> 그 과제 멈추고 새 과제 시작

// 3. 진행중이던 과제 끝냈을 때, 멈춘 과제가 있다면
// 멈춘 과제를 이어서 시작
// 만약 과제 끝난 시각에 (새로 시작), (잠시멈춘 과제)
// 모두 있으면 새로 시작해야하는 과제부터 진행

// 4. 멈춘 과제가 여러개 있을 때, 가장 최근에 멈춘 과제부터 시작

// plans => 과제계획 있을 때,
// 과제 끝낸 순서대로 이름을 배열에 담아 return.
// plans = [name, start(시각), playtime (과제시각)]
// plans.size() <= 10^3 
// plans는 시간순 배열 x 
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Assignment {
    string name;
    int times;
    int rest; // 남은 과제 시간
};

// 시작 시간 오름차순 정렬
bool comp(const vector<string>& a, const vector<string>& b) {
    return a[1] < b[1];
}

// 시작 시간이 가장 늦은 과제를 먼저 꺼내기
struct Compare {
    bool operator()(const Assignment& a, const Assignment& b) {
        if (a.times != b.times) {
            return a.times < b.times;
        }
        return a.rest < b.rest;
    }
};

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    vector<Assignment> as;

    priority_queue<Assignment, vector<Assignment>, Compare> pq;

    // 1. 시작 시간 기준 정렬
    sort(plans.begin(), plans.end(), comp);

    // 2. HH:MM -> 분 단위 변환
    for (auto p : plans) {
        int h = stoi(p[1].substr(0, 2));
        int m = stoi(p[1].substr(3, 2));

        int realT = h * 60 + m;

        as.push_back({p[0], realT, stoi(p[2])});
    }

    // 3. 과제 진행
    for (int i = 0; i < as.size(); i++) {

        // 마지막 과제는 끝까지 진행 가능
        if (i + 1 == as.size()) {
            answer.push_back(as[i].name);
            break;
        }

        // 현재 과제를 완료한 후 다음 과제까지 남는 시간
        int avail = as[i + 1].times
                  - (as[i].times + as[i].rest);

        if (avail == 0) {
            // 다음 과제 시작 시각에 정확히 완료
            answer.push_back(as[i].name);
        }
        else if (avail < 0) {
            // 현재 과제를 중단하고 남은 시간 저장
            int newRest = -avail;

            pq.push({as[i].name, as[i].times, newRest});
        }
        else {
            // 현재 과제 완료 후 여유 시간 발생
            answer.push_back(as[i].name);

            int newRest = avail;

            // 여유 시간 동안 중단된 과제 재개
            while (newRest > 0 && !pq.empty()) {

                Assignment newA = pq.top();
                pq.pop();

                if (newA.rest <= newRest) {
                    // 중단된 과제 완료
                    answer.push_back(newA.name);
                    newRest -= newA.rest;
                }
                else {
                    // 일부만 진행한 후 다시 중단
                    newA.rest -= newRest;

                    pq.push(newA);
                    newRest = 0;
                }
            }
        }
    }

    // 4. 모든 새 과제가 끝난 뒤 남은 과제 처리
    while (!pq.empty()) {
        answer.push_back(pq.top().name);
        pq.pop();
    }

    return answer;
}