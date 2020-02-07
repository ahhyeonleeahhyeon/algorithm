#include <iostream>
#include <cstring>
#define MAX 40
using namespace std;
int map[MAX][MAX];
int people[MAX][MAX];
int sum[6] = { 0, };
int N;
int min_people, max_people, answer;
void solution(int x, int y, int d1, int d2) 
{
	//5번선거구 지정
	for (int i = 0; i <= d1; i++) {
		map[x + i][y - i] = 5;
		for (int j = y - i; j <= y; j++) {
			map[x + i][j] = 5;
		}
	}
	for (int i = 0; i <= d2; i++) {
		map[x + i][y + i] = 5;
		for (int j = y; j <= y + i; j++) {
			map[x + i][j] = 5;
		}
	}

	for (int i = 0; i <= d2; i++) {
		map[x + d1 + i][y - d1 + i] = 5;
		for (int j = y - d1 + i; j <= y + d2 - d1; j++) {
			map[x + d1 + i][j] = 5;
		}
	}
	for (int i = 0; i <= d1; i++) {
		map[x + d2 + i][y + d2 - i] = 5;
		for (int j = y + d2 - d1; j <= y + d2 - i; j++) {
			map[x + d2 + i][j] = 5;
		}
	}

	//1번 선거구
	for (int i = 1; i < x + d1; i++) {
		for (int j = 1; j <= y; j++) {
			if (map[i][j] != 5) map[i][j] = 1;
		}
	}

	//2번선거구
	for (int i = 1; i <= x + d2; i++) {
		for (int j = y + 1; j <= N; j++) {
			if (map[i][j] != 5) map[i][j] = 2;
		}
	}

	//3번선거구
	for (int i = x + d1; i <= N; i++) {
		for (int j = 1; j < y - d1 + d2; j++) {
			if (map[i][j] != 5) map[i][j] = 3;
		}
	}

	//4번 선거구
	for (int i = x + d2 + 1; i <= N; i++) {
		for (int j = y - d1 + d2; j <= N; j++) {
			if (map[i][j] != 5) map[i][j] = 4;
		}
	}


	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int data = map[i][j];
			sum[data] += people[i][j];
		}
	}

}
void print() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << map[i][j] << "\t";
		}
		cout << endl;
	}
}
int main(void) 
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N;

	answer = 987654321;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> people[i][j];
		}
	}

	for (int i = 1; i < N - 1; i++) {
		for (int j = 2; j < N - 1; j++) {
			for (int k = 1; k < j ; k++) {
				for (int w = 1; w <= N - j; w++) {
					solution(i, j, k, w);

					int count = 0;
					for (int s = 1; s <= 5; s++) {
						if (sum > 0) count++;
						if (min_people > sum[s]) min_people = sum[s];
						if (max_people < sum[s]) max_people = sum[s];
					}

					if (count == 5)
					{
						int diff = max_people - min_people;
						if (answer > diff) answer = diff;
					}
					min_people = 987654321, max_people = 0;
					memset(map, 0, sizeof(map));
					memset(sum, 0, sizeof(sum));
				}
			}
		}
	}


	cout << answer << endl;
	return 0;
}
