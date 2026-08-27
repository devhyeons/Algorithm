#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Car {
    int inTime = 0;
    int totalTime = 0;
    bool in = false;
};

unordered_map<int, Car> m;
set<int> carNums;

int defaultT;
int defaultF;
int unitT;
int unitF;

int calTime(string time) {
    int h = stoi(time.substr(0, 2));
    int m = stoi(time.substr(3, 2));
    return h * 60 + m;
}

int calFee(int carNum) {
    int total = m[carNum].totalTime;

    if (total <= defaultT)
        return defaultF;

    int extra = total - defaultT;

    return defaultF + ceil((double)extra / unitT) * unitF;
}

vector<int> solution(vector<int> fees, vector<string> records) {

    defaultT = fees[0];
    defaultF = fees[1];
    unitT = fees[2];
    unitF = fees[3];

    for (auto &r : records) {

        int num = stoi(r.substr(6, 4));
        carNums.insert(num);

        string time = r.substr(0, 5);

        if (r.substr(11, 2) == "IN") {

            m[num].inTime = calTime(time);
            m[num].in = true;

        } else {

            m[num].totalTime += calTime(time) - m[num].inTime;
            m[num].in = false;
        }
    }

    // 출차하지 않은 차량 처리
    int endTime = calTime("23:59");

    for (auto &it : m) {

        if (it.second.in) {

            it.second.totalTime += endTime - it.second.inTime;
        }
    }

    vector<int> answer;

    for (int num : carNums) {
        answer.push_back(calFee(num));
    }

    return answer;
}