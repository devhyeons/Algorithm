#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>
#include <queue>

using namespace std;

// 도시의 각 칸
// 1. 빈탄 , 2. 치킨집, 3. 집

// r,c= 1부터 시작  ** -- 필요.

// 치킨 거리 : 집에서 가장 가까운 치킨 집 사이의 거리
// 각각의 집은 치킨 거리 갖고 있고,
// 도시의 치킨 거리 = 모든 집의 치킨거리 합

// M개만 고르고, 나머지 치킨집 폐업 시킬려고 할 때
// 가장 도시의 치킨거리가 작게될려면?

// 최대 M개 골랐을 때. 도시의 치킨 거리 최솟값은?

int n, m;
int board[51][51];
vector<pair<int, int>> chickens;
vector<pair<int, int>> homes;

int calChicken(vector<int> checked) {
    int sum = 0;
    for (auto h: homes) {
        int minDist = INT_MAX;
        for (auto c: checked) {
            int newDist = abs(h.first - chickens[c].first) + abs(h.second - chickens[c].second);
            minDist = min(minDist, newDist);
        }
        sum = sum + minDist;
    }
    return sum;
}

int minCityDist = INT_MAX;

void backTracking(vector<int> &checked, int idx) {
    if (checked.size() > m) return;
    
    if (!checked.empty() && checked.size() <= m) {
        minCityDist = min(minCityDist, calChicken(checked));
    }

    for (int i = idx; i < chickens.size(); i++) {
        checked.push_back(i);
        backTracking(checked, i + 1);
        checked.pop_back();
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j]; //도시의 정보
            if (board[i][j] == 2) {
                chickens.push_back({i, j});
            }
            if (board[i][j] == 1) {
                homes.push_back({i, j});
            }
        }
    }

    vector<int> checked;
    backTracking(checked, 0);

    cout << minCityDist << "\n";

    return 0;
}