#include <iostream>
#include <vector>
#define INF 987654321
#define MAX 31
#define GRAVE -1
using namespace std;
struct info {
	int from, to, cost;
};
vector<info> edge;
int map[MAX][MAX], hole[MAX][MAX];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int dist[MAX*MAX];
int W, H, G, E;
int main(void) {

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	while (1) {
		cin >> H >> W;
		if (W == 0 && H == 0) break;
		edge.clear();

		//init
		for (int i = 0; i < W; i++) {
			for (int j = 0; j < H; j++) {
				int d = i * H + j;
				map[i][j] = d;
				hole[i][j] = 0;
				dist[map[i][j]] = INF;
			}
		}
		cin >> G;
		for (int i = 0, x, y; i < G; i++) {
			cin >> y >> x;
			map[x][y] = GRAVE;
		}

		cin >> E;
		for (int i = 0, x1, y1, x2, y2, t; i < E; i++) {
			cin >> y1 >> x1 >> y2 >> x2 >> t;
			hole[x1][y1] = 1;
			edge.push_back({map[x1][y1], map[x2][y2], t });
		}


		//정점과 연결되어있는 정점 찾기
		for (int i = 0; i < W; i++) {
			for (int j = 0; j < H; j++) {
				if (map[i][j] == GRAVE || hole[i][j]) continue;
				for (int k = 0, newX, newY; k < 4; k++) {
					newX = i + dx[k];
					newY = j + dy[k];
					if (newX < 0 || newX >= W || newY < 0 || newY >= H || map[newX][newY] == GRAVE) continue;
					edge.push_back({ map[i][j], map[newX][newY], 1 });
				}
			}
		}


		//벨만포드 알고리즘 구현 시작 
		dist[0] = 0;
		int updated = 1;
		for (int v = 0; v < W*H - 1 - G && updated == 1; v++) {
			updated = 0;
			for (info e : edge) {
				if (dist[e.from] == INF) continue;
				if (e.from == W * H - 1) continue;
				if (dist[e.to] > dist[e.from] + e.cost) {
					updated = 1;
					dist[e.to] = dist[e.from] + e.cost;
				}
			}
		}

		//cycle 판단 : update가 또 되는가?
		updated = 0;
		for (info e : edge) {
			if (dist[e.from] == INF) continue;
			if (e.from == W * H - 1) continue;
			if (dist[e.to] > dist[e.from] + e.cost) {
				updated = 1;
				break;
			}
		}

		//결과출력
		if (updated == 1) cout << "Never\n";
		else if (dist[W*H - 1] == INF) cout << "Impossible\n";
		else cout << dist[W*H - 1] << "\n";
	}


	return 0;
}
