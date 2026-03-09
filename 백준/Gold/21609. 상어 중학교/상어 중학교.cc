#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Cell {
    int groupId;
    int blockId;
};

struct Loca {
    int x, y;
};

struct Group {
    int groupId;
    int sx, sy; // 기준 블록 좌표
    int blockCnt;
    int rainBowCnt;
    vector<Loca> members;
};

int n, m;
int score = 0;
Cell board[21][21];
bool visited[21][21];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
vector<Group> groups;

bool bfs(int startX, int startY, int idx) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    vector<Loca> pushed;
    pushed.push_back({startX, startY});

    visited[startX][startY] = true;
    int color = board[startX][startY].blockId;

    // [수정] 기준 블록 좌표 초기화 (현재 시작점이 일반 블록이므로)
    int minX = startX;
    int minY = startY;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int dir = 0; dir < 4; dir++) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if (nx < 0 || ny < 0 || nx >= n || ny >= n) continue;
            if (board[nx][ny].blockId <= -1 || visited[nx][ny]) continue;

            // 무지개 블록이거나 색이 같은 일반 블록일 때
            if (board[nx][ny].blockId == 0 || board[nx][ny].blockId == color) {
                visited[nx][ny] = true;
                pushed.push_back({nx, ny});
                q.push({nx, ny});

                // [수정] 일반 블록일 경우에만 기준 블록 후보로 체크
                if (board[nx][ny].blockId == color) {
                    if (nx < minX) {
                        minX = nx; minY = ny;
                    } else if (nx == minX && ny < minY) {
                        minY = ny;
                    }
                }
            }
        }
    }

    if (pushed.size() < 2) return false;

    int rainbowCnt = 0;
    for (auto p : pushed) {
        if (board[p.x][p.y].blockId == 0) {
            visited[p.x][p.y] = false; // 무지개는 방문 해제
            rainbowCnt++;
        }
    }

    // [수정] 갱신된 minX, minY를 기준 블록으로 저장
    groups.push_back({idx, minX, minY, (int)pushed.size(), rainbowCnt, pushed});
    return true;
}

void groupingBoard() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) visited[i][j] = false;
    }
    groups.clear();

    int groupIdx = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 일반 블록(1 이상)이고 방문 안 한 곳에서만 시작
            if (board[i][j].blockId > 0 && !visited[i][j]) {
                bfs(i, j, groupIdx++);
            }
        }
    }
}

bool compGroup(const Group& a, const Group& b) {
    if (a.blockCnt != b.blockCnt) return a.blockCnt > b.blockCnt;
    if (a.rainBowCnt != b.rainBowCnt) return a.rainBowCnt > b.rainBowCnt;
    if (a.sx != b.sx) return a.sx > b.sx;
    return a.sy > b.sy;
}

void findBigGroup() {
    sort(groups.begin(), groups.end(), compGroup);
    Group& best = groups[0];
    for (auto p : best.members) board[p.x][p.y].blockId = -2;
    score += (best.blockCnt * best.blockCnt);
}

void gravityBoard() {
    while (true) {
        bool moved = false;
        // 밑에서부터 훑어야 연쇄 이동이 잘 됨
        for (int i = n - 2; i >= 0; i--) {
            for (int j = 0; j < n; j++) {
                if (board[i][j].blockId < 0) continue;

                int currX = i;
                while (currX + 1 < n && board[currX + 1][j].blockId == -2) {
                    board[currX + 1][j].blockId = board[currX][j].blockId;
                    board[currX][j].blockId = -2;
                    currX++;
                    moved = true;
                }
            }
        }
        if (!moved) break;
    }
}

void rotate90() {
    Cell tmp[21][21];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tmp[n - 1 - j][i].blockId = board[i][j].blockId;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) board[i][j] = tmp[i][j];
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> board[i][j].blockId;
    }

    while (true) {
        groupingBoard();
        if (groups.empty()) break;
        findBigGroup();
        gravityBoard();
        rotate90();
        gravityBoard();
    }
    cout << score << "\n";
    return 0;
}